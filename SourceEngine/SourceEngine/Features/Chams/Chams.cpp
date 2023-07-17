#include "Chams.h"

#include "../ESP/ESP.h"

void Draw2Color(C_BaseEntity* pEntity, IMaterial* matUnoccluded, IMaterial* matOccluded, Color_t clrUnoccluded, Color_t clrOccluded)
{
    if (!pEntity || !pEntity->ShouldDraw())
        return;

    auto DrawEntityAndAttachments = [&]()
    {
        pEntity->DrawModel(STUDIO_RENDER | STUDIO_NOSHADOWS);

        auto pAttachment = pEntity->FirstMoveChild();

        for (int n = 0; n < 32; n++) //using for because of EIP hang
        {
            if (!pAttachment)
                break;

            if (pAttachment->ShouldDraw())
                pAttachment->DrawModel(STUDIO_RENDER | STUDIO_NOSHADOWS);

            pAttachment = pAttachment->NextMovePeer();
        }

        if (pEntity->IsPlayer())
        {
            if (auto pWeapon = pEntity->GetActiveWeapon())
            {
                if (pWeapon->ShouldDraw())
                {
                    pWeapon->DrawModel(STUDIO_RENDER | STUDIO_NOSHADOWS);
                }
            }
        }
    };

    auto pRenderContext = I::MaterialSystem->GetRenderContext();

    if (!pRenderContext)
        return;

    //clear the stencil buffer to avoid clashing
    pRenderContext->ClearBuffers(false, false, true);

    pRenderContext->SetStencilEnable(true);
    {
        I::ModelRender->ForcedMaterialOverride(matUnoccluded);

        //unoccluded
        {
            pRenderContext->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_ALWAYS);
            pRenderContext->SetStencilPassOperation(STENCILOPERATION_REPLACE);
            pRenderContext->SetStencilFailOperation(STENCILOPERATION_KEEP);
            pRenderContext->SetStencilZFailOperation(STENCILOPERATION_KEEP);
            pRenderContext->SetStencilReferenceValue(1);
            pRenderContext->SetStencilWriteMask(0xFF);
            pRenderContext->SetStencilTestMask(0x0);

            I::RenderView->SetColorModulation(clrUnoccluded);
            I::RenderView->SetBlend(clrUnoccluded.a / 255.f);

            DrawEntityAndAttachments();
        }

        I::ModelRender->ForcedMaterialOverride(nullptr);

        I::ModelRender->ForcedMaterialOverride(matOccluded);

        //occluded
        {
            pRenderContext->SetStencilCompareFunction(STENCILCOMPARISONFUNCTION_EQUAL);
            pRenderContext->SetStencilPassOperation(STENCILOPERATION_KEEP);
            pRenderContext->SetStencilFailOperation(STENCILOPERATION_KEEP);
            pRenderContext->SetStencilZFailOperation(STENCILOPERATION_KEEP);
            pRenderContext->SetStencilReferenceValue(0);
            pRenderContext->SetStencilWriteMask(0x0);
            pRenderContext->SetStencilTestMask(0xFF);

            I::RenderView->SetColorModulation(clrOccluded);
            I::RenderView->SetBlend(clrOccluded.a / 255.f);

            pRenderContext->DepthRange(0.0f, 0.2f);
            DrawEntityAndAttachments();
            pRenderContext->DepthRange(0.0f, 1.0f);
        }
    }
    pRenderContext->SetStencilEnable(false);

    I::ModelRender->ForcedMaterialOverride(nullptr);

    I::RenderView->SetColorModulation(1.0f, 1.0f, 1.0f);
}

/*
CFGVAR(Chams_Enabled, true);
CFGVAR(Chams_OccludedMaterial, 1); // None, Shaded, Flat, Shiny
CFGVAR(Chams_UnoccludedMaterial, 0); // None, Shaded, Flat, Shiny
CFGVAR(Chams_OccludedCustomColor, false);
CFGVAR(Chams_UnoccludedCustomColor, false);
*/

void CChams::Run()
{
	if (!I::Engine->IsInGame())
	{
		return;
	}

	if (!m_pMatShaded)
	{
		static auto kv = new KeyValues("VertexLitGeneric");
		kv->SetString("$basetexture", "vgui/white_additive");
		kv->SetString("$bumpmap", "vgui/white_additive");
		kv->SetString("$selfillum", "1");
		kv->SetString("$selfillumfresnel", "1");
		kv->SetString("$selfillumfresnelminmaxexp", "[-0.25 1 1]");

		m_pMatShaded = I::MaterialSystem->CreateMaterial("jorhook_shaded", kv);
		m_pMatShaded->IncrementReferenceCount();
		return;
	}

    if (!m_pMatFlat)
    {
        static auto kv = new KeyValues("UnlitGeneric");
        kv->SetString("$basetexture", "vgui/white_additive");

        m_pMatFlat = I::MaterialSystem->CreateMaterial("jorhook_flat", kv);
        m_pMatFlat->IncrementReferenceCount();
        return;
    }

	int nLocalTeam = 0;
	if (const auto& pLocal = G::EntityCache.pLocal)
	{
		nLocalTeam = pLocal->m_iTeamNum();
	}

    IMaterial* pOccludedMaterial = nullptr;
    switch (V::Chams_OccludedMaterial)
    {
        case 1:
        {
            pOccludedMaterial = m_pMatShaded;
            break;
        }
        case 2:
        {
            pOccludedMaterial = m_pMatFlat;
            break;
        }
        default:
        {
            break;
        }
    }

    IMaterial* pUnoccludedMaterial = nullptr;
    switch (V::Chams_UnoccludedMaterial)
    {
        case 1:
        {
            pUnoccludedMaterial = m_pMatShaded;
            break;
        }
        case 2:
        {
            pUnoccludedMaterial = m_pMatFlat;
            break;
        }
        default:
        {
            break;
        }
    }

	for (const auto& Player : V::Chams_EnemyOnly ? G::EntityCache.GetGroup(GroupType_t::PLAYERS_ENEMIES) : G::EntityCache.GetGroup(GroupType_t::PLAYERS_ALL))
	{
        const Color_t &clr = F::ESP.GetEntityColor(Player, nLocalTeam);
        Draw2Color(Player, 
                   pUnoccludedMaterial, pOccludedMaterial, 
                   V::Chams_UnoccludedUseCustomColor ? V::Chams_UnoccludedColor : clr,
                   V::Chams_OccludedUseCustomColor ? V::Chams_OccludedColor : clr);
	}

    if (V::Chams_ShowLocal && G::EntityCache.pLocal)
    {
        const Color_t &clr = F::ESP.GetEntityColor(G::EntityCache.pLocal, nLocalTeam);

        Draw2Color(G::EntityCache.pLocal,
                   				   pUnoccludedMaterial, pOccludedMaterial,
                   				   V::Chams_UnoccludedUseCustomColor ? V::Chams_UnoccludedColor : clr,
                   				   V::Chams_OccludedUseCustomColor ? V::Chams_OccludedColor : clr);
    }

    for (const auto& Building : V::Chams_EnemyOnly ? G::EntityCache.GetGroup(GroupType_t::PLAYERS_ENEMIES) : G::EntityCache.GetGroup(GroupType_t::PLAYERS_ALL))
    {
        auto owner = I::EntityList->GetClientEntityFromHandle(reinterpret_cast<C_BaseObject*>(Building)->m_hOwnerEntity());

        if (!owner || !owner->IsPlayer())
        {
			continue;
		}

        const Color_t& clr = F::ESP.GetEntityColor(owner, nLocalTeam);

		Draw2Color(Building,
                   				   pUnoccludedMaterial, pOccludedMaterial,
                   				   V::Chams_UnoccludedUseCustomColor ? V::Chams_UnoccludedColor : clr,
                   				   V::Chams_OccludedUseCustomColor ? V::Chams_OccludedColor : clr);
	}

    for (const auto& Pickup : G::EntityCache.GetGroup(GroupType_t::WORLD_HEALTH))
    {
        Draw2Color(Pickup,
                   pUnoccludedMaterial, pOccludedMaterial,
                   V::Chams_UnoccludedUseCustomColor ? V::Chams_UnoccludedColor : V::Colors_HealthPack,
                   V::Chams_OccludedUseCustomColor ? V::Chams_OccludedColor : V::Colors_HealthPack);
    }

    for (const auto& Pickup : G::EntityCache.GetGroup(GroupType_t::WORLD_AMMO))
    {
        Draw2Color(Pickup,
                   pUnoccludedMaterial, pOccludedMaterial,
                   V::Chams_UnoccludedUseCustomColor ? V::Chams_UnoccludedColor : V::Colors_AmmoPack,
                   V::Chams_OccludedUseCustomColor ? V::Chams_OccludedColor : V::Colors_AmmoPack);
    }

    for (const auto& Pickup : G::EntityCache.GetGroup(GroupType_t::WORLD_ARMOR))
    {
        Draw2Color(Pickup,
                   pUnoccludedMaterial, pOccludedMaterial,
                   V::Chams_UnoccludedUseCustomColor ? V::Chams_UnoccludedColor : V::Colors_ArmourPack,
                   V::Chams_OccludedUseCustomColor ? V::Chams_OccludedColor : V::Colors_ArmourPack);
    }
}

void CChams::Cleanup()
{
	if (m_pMatShaded)
	{
		m_pMatShaded->DecrementReferenceCount();
		m_pMatShaded->DeleteIfUnreferenced();
		m_pMatShaded = nullptr;
	}

    if (m_pMatFlat)
    {
        m_pMatFlat->DecrementReferenceCount();
        m_pMatFlat->DeleteIfUnreferenced();
        m_pMatFlat = nullptr;
    }
}
