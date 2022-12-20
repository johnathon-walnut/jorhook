#pragma once

class C_RenderView
{
public:
	virtual void			DrawBrushModel(
		void* baseentity,
		model_t* model,
		const Vec3& origin,
		const Vec3& angles,
		bool bUnused) = 0;

	// Draw brush model that has no origin/angles change ( uses identity transform )
	// FIXME, Material proxy IClientEntity *baseentity is unused right now, use DrawBrushModel for brushes with
	//  proxies for now.
	virtual void			DrawIdentityBrushModel(void* pList, model_t* model) = 0;

	// Mark this dynamic light as having changed this frame ( so light maps affected will be recomputed )
	virtual void			TouchLight(struct dlight_t* light) = 0;
	// Draw 3D Overlays
	virtual void			Draw3DDebugOverlays(void) = 0;
	// Sets global blending fraction
	virtual void			SetBlend(float blend) = 0;
	virtual float			GetBlend(void) = 0;

	// Sets global color modulation
	virtual void			SetColorModulation(float const* blend) = 0;
	virtual void			GetColorModulation(float* blend) = 0;
	inline void                 SetColorModulation(float r, float g, float b)
	{
		float clr[3] = { r, g, b };
		SetColorModulation(clr);
	}
	inline void SetColorModulation(const Color_t& clr)
	{
		float blend[3] = { static_cast<float>(clr.r) / 255.f,
						static_cast<float>(clr.g) / 255.f,
		static_cast<float>(clr.b) / 255.f, };
		SetColorModulation(blend);
	}
	void GetMatricesForView(const C_ViewSetup& view, VMatrix* pWorldToView, VMatrix* pViewToProjection, VMatrix* pWorldToProjection, VMatrix* pWorldToPixels) {
		typedef void(__thiscall* FN)(PVOID, const C_ViewSetup&, VMatrix*, VMatrix*, VMatrix*, VMatrix*);
		GetVFunc<FN>(this, 50)(this, view, pWorldToView, pViewToProjection, pWorldToProjection, pWorldToPixels);
	}
};

#define VENGINE_RENDERVIEW_INTERFACE_VERSION "VEngineRenderView014"