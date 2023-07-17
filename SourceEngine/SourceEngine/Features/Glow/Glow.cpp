#include "Glow.h"

#include "../ESP/ESP.h"

void CGlow::DrawModel(C_BaseEntity* entity, bool drawingmodels)
{
	m_bRendering = true;

	if (!drawingmodels)
	{
		m_bDrawing = true;
	}

	entity->DrawModel(STUDIO_RENDER | STUDIO_NOSHADOWS);

	if (drawingmodels)
	{
		m_mapGlowEntities[entity] = true;
	}

	if (entity->IsPlayer())
	{
		if (const auto& pEntityWeapon = entity->GetActiveWeapon())
		{
			if (pEntityWeapon->ShouldDraw())
			{
				pEntityWeapon->DrawModel(STUDIO_RENDER | STUDIO_NOSHADOWS);

				if (drawingmodels)
				{
					m_mapGlowEntities[pEntityWeapon] = true;
				}
			}
		}

		auto pAttachment = entity->FirstMoveChild();

		for (int n = 0; n < 32; n++) //using for because of EIP hang
		{
			if (!pAttachment)
			{
				break;
			}

			if (pAttachment->ShouldDraw())
			{
				pAttachment->DrawModel(STUDIO_RENDER | STUDIO_NOSHADOWS);

				if (drawingmodels)
				{
					m_mapGlowEntities[pAttachment] = true;
				}
			}

			pAttachment = pAttachment->NextMovePeer();
		}
	}

	if (!drawingmodels)
	{
		m_bDrawing = false;
	}

	m_bRendering = false;
}

void CGlow::Run()
{
	if (!m_pMatGlowColor)
	{
		m_pMatGlowColor = I::MaterialSystem->FindMaterial("dev/glow_color", TEXTURE_GROUP_OTHER);
	}

	if (!m_pFullFrame)
	{
		m_pFullFrame = I::MaterialSystem->FindTexture("_rt_FullFrameFB", TEXTURE_GROUP_RENDER_TARGET);
	}

	if (!m_pRenderBuffer0)
	{
		m_pRenderBuffer0 = I::MaterialSystem->CreateNamedRenderTargetTextureEx("MismisGlowBuffer1", m_pFullFrame->GetActualWidth(), m_pFullFrame->GetActualHeight(),
																			RT_SIZE_LITERAL, IMAGE_FORMAT_RGB888, MATERIAL_RT_DEPTH_SHARED,
																			TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_EIGHTBITALPHA, CREATERENDERTARGETFLAGS_HDR);
		m_pRenderBuffer0->IncrementReferenceCount();
	}

	if (!m_pRenderBuffer1)
	{
		m_pRenderBuffer1 = I::MaterialSystem->CreateNamedRenderTargetTextureEx("MismisGlowBuffer2", m_pFullFrame->GetActualWidth(), m_pFullFrame->GetActualHeight(),
																			RT_SIZE_LITERAL, IMAGE_FORMAT_RGB888, MATERIAL_RT_DEPTH_SHARED,
																			TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_EIGHTBITALPHA, CREATERENDERTARGETFLAGS_HDR);
		m_pRenderBuffer1->IncrementReferenceCount();
	}

	if (!m_pMatBlurX)
	{
		static KeyValues* kv{};
		if (!kv)
		{
			kv = new KeyValues("BlurFilterX");
			kv->SetString("$basetexture", "MismisGlowBuffer1");
		}
		m_pMatBlurX = I::MaterialSystem->CreateMaterial("MismisBlurX", kv);
	}

	if (!m_pMatBlurY)
	{
		static KeyValues* kv{};
		if (!kv)
		{
			kv = new KeyValues("BlurFilterY");
			kv->SetString("$basetexture", "MismisGlowBuffer2");
			kv->SetString("$bloomamount", "5");
		}
		m_pMatBlurY = I::MaterialSystem->CreateMaterial("MismisBlurY", kv);
	}

	if (!m_pMatHalo)
	{
		static KeyValues* kv{};
		if (!kv)
		{
			kv = new KeyValues("UnlitGeneric");
			kv->SetString("$basetexture", "MismisGlowBuffer1");
			kv->SetString("$additive", "1");
		}
		m_pMatHalo = I::MaterialSystem->CreateMaterial("MismisHalo", kv);
	}

	m_mapGlowEntities.clear();

	auto local = G::EntityCache.pLocal;

	if (!local)
		return;

	int localTeam = local->m_iTeamNum();

	const int w = G::ScreenSize.w;
	const int h = G::ScreenSize.h;

	if (w < 1 || h < 1)
		return;

	if (w > 8192 || h > 8192)
		return;

	auto rc = I::MaterialSystem->GetRenderContext();

	if (!rc)
		return;

	float flOldColor[3]{};
	I::RenderView->GetColorModulation(flOldColor);
	float flOldBlend = I::RenderView->GetBlend();

	rc->SetStencilEnable(true);
	rc->SetStencilReferenceValue(-1);
	rc->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_ALWAYS);
	rc->SetStencilPassOperation(STENCILOPERATION_REPLACE);
	rc->SetStencilFailOperation(STENCILOPERATION_KEEP);
	rc->SetStencilZFailOperation(STENCILOPERATION_REPLACE);
	rc->SetStencilTestMask(0xFFFFFFFF);
	rc->SetStencilWriteMask(0xFFFFFFFF);

	// Set the blend value to 1.0 and the color modulation to white
	I::RenderView->SetBlend(1.0f);
	I::RenderView->SetColorModulation(1.0f, 1.0f, 1.0f);

	for (auto& player : V::Glow_EnemyOnly ? G::EntityCache.GetGroup(GroupType_t::PLAYERS_ENEMIES) : G::EntityCache.GetGroup(GroupType_t::PLAYERS_ALL))
	{
		if (player->deadflag())
			continue;

		DrawModel(player, true);
	}

	if (V::Glow_ShowLocal && local->IsAlive())
		DrawModel(local, true);

	for (const auto& pEntity : G::EntityCache.GetGroup(GroupType_t::BUILDINGS_ENEMIES))
	{
		DrawModel(pEntity, true);
	}

	for (const auto& Pickup : G::EntityCache.GetGroup(GroupType_t::WORLD_HEALTH))
	{
		DrawModel(Pickup, true);
	}

	for (const auto& Pickup : G::EntityCache.GetGroup(GroupType_t::WORLD_AMMO))
	{
		DrawModel(Pickup, true);
	}

	for (const auto& Pickup : G::EntityCache.GetGroup(GroupType_t::WORLD_ARMOR))
	{
		DrawModel(Pickup, true);
	}

	rc->SetStencilEnable(false);
	rc->SetStencilReferenceValue(0);
	rc->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_ALWAYS);
	rc->SetStencilPassOperation(STENCILOPERATION_KEEP);
	rc->SetStencilFailOperation(STENCILOPERATION_KEEP);
	rc->SetStencilZFailOperation(STENCILOPERATION_KEEP);
	rc->SetStencilTestMask(0xFFFFFFFF);
	rc->SetStencilWriteMask(0xFFFFFFFF);

	if (m_mapGlowEntities.empty())
		return;

	I::ModelRender->ForcedMaterialOverride(m_pMatGlowColor);

	rc->PushRenderTargetAndViewport();
	rc->SetRenderTarget(m_pRenderBuffer0);
	rc->Viewport(0, 0, w, h);
	rc->ClearColor4ub(0, 0, 0, 0);
	rc->ClearBuffers(true, false, false);

	for (auto& player : V::Glow_EnemyOnly ? G::EntityCache.GetGroup(GroupType_t::PLAYERS_ENEMIES) : G::EntityCache.GetGroup(GroupType_t::PLAYERS_ALL))
	{
		if (player->deadflag())
			continue;

		Color_t color = F::ESP.GetEntityColor(player, localTeam);
		I::RenderView->SetColorModulation(color);
		I::RenderView->SetBlend(color.a / 255.0f);
		DrawModel(player, false);
	}

	if (V::Glow_ShowLocal && local->IsAlive())
	{
		Color_t color = F::ESP.GetEntityColor(local, localTeam);
		I::RenderView->SetColorModulation(color);
		I::RenderView->SetBlend(color.a / 255.0f);
		DrawModel(local, false);
	}

	for (const auto& pEntity : G::EntityCache.GetGroup(GroupType_t::BUILDINGS_ENEMIES))
	{
		auto owner = I::EntityList->GetClientEntityFromHandle(reinterpret_cast<C_BaseObject*>(pEntity)->m_hOwnerEntity());

		if (!owner || !owner->IsPlayer())
		{
			continue;
		}

		const Color_t& color = F::ESP.GetEntityColor(owner, localTeam);
		I::RenderView->SetColorModulation(color);
		I::RenderView->SetBlend(color.a / 255.0f);
		DrawModel(pEntity, false);
	}

	for (const auto& Pickup : G::EntityCache.GetGroup(GroupType_t::WORLD_HEALTH))
	{
		I::RenderView->SetColorModulation(V::Colors_HealthPack);
		I::RenderView->SetBlend(V::Colors_HealthPack.a / 255.0f);
		DrawModel(Pickup, true);
	}

	for (const auto& Pickup : G::EntityCache.GetGroup(GroupType_t::WORLD_AMMO))
	{
		I::RenderView->SetColorModulation(V::Colors_AmmoPack);
		I::RenderView->SetBlend(V::Colors_AmmoPack.a / 255.0f);
		DrawModel(Pickup, true);
	}

	for (const auto& Pickup : G::EntityCache.GetGroup(GroupType_t::WORLD_ARMOR))
	{
		I::RenderView->SetColorModulation(V::Colors_ArmourPack);
		I::RenderView->SetBlend(V::Colors_ArmourPack.a / 255.0f);
		DrawModel(Pickup, true);
	}

	rc->SetStencilEnable(false);
	rc->SetStencilReferenceValue(0);
	rc->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_ALWAYS);
	rc->SetStencilPassOperation(STENCILOPERATION_KEEP);
	rc->SetStencilFailOperation(STENCILOPERATION_KEEP);
	rc->SetStencilZFailOperation(STENCILOPERATION_KEEP);
	rc->SetStencilTestMask(0xFFFFFFFF);
	rc->SetStencilWriteMask(0xFFFFFFFF);
	rc->PopRenderTargetAndViewport();

	rc->PushRenderTargetAndViewport();
	rc->Viewport(0, 0, w, h);

	rc->SetRenderTarget(m_pRenderBuffer1);
	rc->DrawScreenSpaceRectangle(
		m_pMatBlurX,
		0, 0, w, h,
		0.0f, 0.0f, w - 1, h - 1,
		w, h);

	rc->SetRenderTarget(m_pRenderBuffer0);
	rc->DrawScreenSpaceRectangle(
		m_pMatBlurY,
		0, 0, w, h,
		0.0f, 0.0f, w, h,
		w, h);
	rc->PopRenderTargetAndViewport();

	rc->SetStencilEnable(true);
	rc->SetStencilReferenceValue(0);
	rc->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_EQUAL);
	rc->SetStencilPassOperation(STENCILOPERATION_INVERT);
	rc->SetStencilFailOperation(STENCILOPERATION_INVERT);
	rc->SetStencilZFailOperation(STENCILOPERATION_INVERT);
	rc->SetStencilWriteMask(0x0);
	rc->SetStencilTestMask(0xFF);

	rc->DrawScreenSpaceRectangle(
		m_pMatHalo,
		0, 0, w, h,
		0.0f, 0.0f, w - 1, h - 1,
		w, h);

	rc->SetStencilEnable(false);
	rc->SetStencilReferenceValue(0);
	rc->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_ALWAYS);
	rc->SetStencilPassOperation(STENCILOPERATION_KEEP);
	rc->SetStencilFailOperation(STENCILOPERATION_KEEP);
	rc->SetStencilZFailOperation(STENCILOPERATION_KEEP);
	rc->SetStencilTestMask(0xFFFFFFFF);
	rc->SetStencilWriteMask(0xFFFFFFFF);

	I::ModelRender->ForcedMaterialOverride(nullptr);
	I::RenderView->SetColorModulation(flOldColor);
	I::RenderView->SetBlend(flOldBlend);
}