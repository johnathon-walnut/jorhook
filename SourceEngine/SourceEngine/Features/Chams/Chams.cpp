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

	int nLocalTeam = 0;
	if (const auto& pLocal = G::EntityCache.pLocal)
	{
		nLocalTeam = pLocal->m_iTeamNum();
	}

	for (const auto& Player : G::EntityCache.GetGroup(GroupType_t::PLAYERS_ALL))
	{
        Draw2Color(Player, nullptr, m_pMatShaded, { 255,255,255,255 }, F::ESP.GetEntityColor(Player, nLocalTeam));
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
}
