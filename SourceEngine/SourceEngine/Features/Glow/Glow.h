#pragma once

#include "../Vars.h"

class CGlow
{
public:
	void DrawModel(C_BaseEntity* entity, bool drawingmodels);
	void Run();

private:
	IMaterial* m_pMatGlowColor = nullptr;
	ITexture* m_pFullFrame = nullptr, *m_pRenderBuffer0 = nullptr, *m_pRenderBuffer1 = nullptr;
	IMaterial* m_pMatBlurX = nullptr, *m_pMatBlurY = nullptr;
	IMaterial* m_pMatHalo = nullptr;

	std::map<C_BaseEntity*, bool> m_mapGlowEntities;

public:
	inline bool IsGlowMaterial(IMaterial* material)
	{
		return material == m_pMatGlowColor ||
			material == m_pMatBlurX ||
			material == m_pMatBlurY ||
			material == m_pMatHalo;
	}

	bool m_bRendering = false;
	bool m_bDrawing = false;
};

MAKE_FEATURE(CGlow, Glow);