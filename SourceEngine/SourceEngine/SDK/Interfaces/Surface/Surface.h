#pragma once
#include "../../Includes/Includes.h"

#undef CreateFont
#undef PlaySound

enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,
	IMAGE_FORMAT_NV_DST16,
	IMAGE_FORMAT_NV_DST24,
	IMAGE_FORMAT_NV_INTZ,
	IMAGE_FORMAT_NV_RAWZ,
	IMAGE_FORMAT_ATI_DST16,
	IMAGE_FORMAT_ATI_DST24,
	IMAGE_FORMAT_NV_NULL,
	IMAGE_FORMAT_ATI2N,
	IMAGE_FORMAT_ATI1N,
	IMAGE_FORMAT_DXT1_RUNTIME,
	IMAGE_FORMAT_DXT5_RUNTIME,
	NUM_IMAGE_FORMATS
};


class C_Surface
{
public:
	void SetDrawColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* FN)(PVOID, int, int, int, int);
		GetVFunc<FN>(this, 11)(this, r, g, b, a);
	}

	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* FN)(PVOID, int, int, int, int);
		GetVFunc<FN>(this, 12)(this, x0, y0, x1, y1);
	}

	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* FN)(PVOID, int, int, int, int);
		GetVFunc<FN>(this, 14)(this, x0, y0, x1, y1);
	}

	void SetTextFont(unsigned long font)
	{
		typedef void(__thiscall* FN)(PVOID, unsigned long);
		GetVFunc<FN>(this, 17)(this, font);
	}

	void SetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* FN)(PVOID, int, int, int, int);
		GetVFunc<FN>(this, 19)(this, r, g, b, a);
	}

	void SetTextPos(int x, int y)
	{
		typedef void(__thiscall* FN)(PVOID, int, int);
		GetVFunc<FN>(this, 20)(this, x, y);
	}

	void PrintText(const wchar_t* text, int text_len)
	{
		typedef void(__thiscall* FN)(PVOID, const wchar_t*, int, int);
		return GetVFunc<FN>(this, 22)(this, text, text_len, 0);
	}

	void DrawLine(int x, int y, int x1, int y1)
	{
		typedef void(__thiscall* FN)(PVOID, int, int, int, int);
		return GetVFunc<FN>(this, 15)(this, x, y, x1, y1);
	}

	unsigned long CreateFont()
	{
		typedef unsigned int(__thiscall* FN)(PVOID);
		return GetVFunc<FN>(this, 66)(this);
	}

	void SetFontGlyphSet(unsigned long& font, const char* windows_font_name, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* FN)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
		GetVFunc<FN>(this, 67)(this, font, windows_font_name, tall, weight, blur, scanlines, flags, 0, 0);
	}

	void GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall)
	{
		typedef void(__thiscall* FN)(PVOID, unsigned long, const wchar_t*, int&, int&);
		GetVFunc<FN>(this, 75)(this, font, text, wide, tall);
	}

	void GetCursorPos(int& x_out, int& y_out)
	{
		typedef void(__thiscall* FN)(PVOID, int&, int&);
		GetVFunc<FN>(this, 96)(this, x_out, y_out);
	}

	void SetCursorAlwaysVisible(bool b)
	{
		typedef void(__thiscall* FN)(PVOID, bool);
		GetVFunc<FN>(this, 52)(this, b);
	}

	bool IsCursorVisible()
	{
		typedef bool(__thiscall* FN)(PVOID);
		return GetVFunc<FN>(this, 53)(this);
	}

	void DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool horizontal)
	{
		typedef void(__thiscall* FN)(PVOID, int, int, int, int, unsigned int, unsigned int, bool);
		GetVFunc<FN>(this, 118)(this, x0, y0, x1, y1, alpha0, alpha1, horizontal);
	}

	void DrawSetTextureRGBAEx(int id, const unsigned char* rgba, int wide, int tall, ImageFormat imageFormat)
	{
		typedef void(__thiscall* FN)(PVOID, int id, const unsigned char* rgba, int wide, int tall, ImageFormat imageFormat);
		GetVFunc<FN>(this, 119)(this, id, rgba, wide, tall, imageFormat);
	}

	void DrawSetTextureRGBAExSig(int id, const unsigned char* rgba, int wide, int tall, ImageFormat imageFormat)
	{
		static auto FN = reinterpret_cast<void(__thiscall*)(PVOID, int, const unsigned char*, int, int, ImageFormat)>(G::Pattern.Find("vguimatsurface.dll", "55 8B EC E8 ? ? ? ? 6A ? FF 75 ? 8B C8 FF 75"));
		FN(this, id, rgba, wide, tall, imageFormat);
	}

	void DrawOutlinedCircle(int x, int y, float radius, int segments)
	{
		typedef void(__thiscall* FN)(PVOID, int, int, float, int);
		GetVFunc<FN>(this, 99)(this, x, y, radius, segments); //doesn work?
	}

	void UnlockCursor()
	{
		typedef void(__thiscall* FN)(PVOID);
		return GetVFunc<FN>(this, 61)(this);
	}

	void LockCursor()
	{
		typedef void(__thiscall* FN)(PVOID);
		return GetVFunc<FN>(this, 62)(this);
	}

	int CreateNewTextureID(bool procedural = true) {
		typedef int(__thiscall* FN)(PVOID, bool);
		return GetVFunc<FN>(this, 37)(this, procedural);
	}

	bool DrawGetTextureFile(int id, char* filename, int maxlen) {
		typedef bool(__thiscall* FN)(PVOID, int, char*, int);
		return GetVFunc<FN>(this, 29)(this, id, filename, maxlen);
	};

	void DrawSetTextureFile(int id, const char* filename, int hardwareFilter, bool forceReload) {
		typedef void(__thiscall* FN)(PVOID, int, const char*, int, bool);
		return GetVFunc<FN>(this, 30)(this, id, filename, hardwareFilter, forceReload);
	};

	void DrawSetTextureRGBA(int id, unsigned char const* rgba, int wide, int tall, int hardwareFilter = 0, bool forceReload = false) {
		typedef void(__thiscall* FN)(PVOID, int, unsigned char const*, int, int, int, bool);
		return GetVFunc<FN>(this, 31)(this, id, rgba, wide, tall, hardwareFilter, forceReload);
	}

	void DrawSetTexture(int id) {
		typedef void(__thiscall* FN)(PVOID, int);
		return GetVFunc<FN>(this, 32)(this, id);
	}

	void DrawGetTextureSize(int id, int& wide, int& tall) {
		typedef void(__thiscall* FN)(PVOID, int, int&, int&);
		return GetVFunc<FN>(this, 33)(this, id, wide, tall);
	};

	bool IsTextureIDValid(int id) {
		typedef bool(__thiscall* FN)(PVOID, int);
		return GetVFunc<FN>(this, 35)(this, id);
	}

	void DrawTexturedRect(int x, int y, int w, int h) {
		typedef void(__thiscall* FN)(PVOID, int, int, int, int);
		return GetVFunc<FN>(this, 34)(this, x, y, x + w, y + h);
	}

	void PlaySound(const char* szFile)
	{
		typedef void(__thiscall* FN)(PVOID, const char*);
		return GetVFunc<FN>(this, 78)(this, szFile);
	}
};

using HCursor = unsigned long;
using HTexture = unsigned long;
using HFont = unsigned long;
using VPANEL = unsigned int;

class IImage;
class Image;
class Point;
class IHTML;
class IHTMLEvents;
class IVguiMatInfo;

struct IntRect
{
	int x0;
	int y0;
	int x1;
	int y1;
};

enum SurfaceFeature_e
{
	ANTIALIASED_FONTS = 1,
	DROPSHADOW_FONTS = 2,
	ESCAPE_KEY = 3,
	OPENING_NEW_HTML_WINDOWS = 4,
	FRAME_MINIMIZE_MAXIMIZE = 5,
	OUTLINE_FONTS = 6,
	DIRECT_HWND_RENDER = 7,
};

struct Vertex_t
{
	Vec2 m_Position;
	Vec2 m_TexCoord;
};

struct CharRenderInfo
{
	int				x, y;
	Vertex_t* verts;
	int				textureId;
	int				abcA;
	int				abcB;
	int				abcC;
	int				fontTall;
	HFont			currentFont;
	FontDrawType_t	drawType;
	wchar_t			ch;
	bool			valid;
	bool			shouldclip;
};

class ISurface : public IAppSystem
{
public:
	virtual void Test() = 0;
	virtual void Shutdown() = 0;
	virtual void RunFrame() = 0;
	virtual VPANEL GetEmbeddedPanel() = 0;
	virtual void SetEmbeddedPanel(VPANEL pPanel) = 0;
	virtual void PushMakeCurrent(VPANEL panel, bool useInsets) = 0;
	virtual void PopMakeCurrent(VPANEL panel) = 0;
	virtual void DrawSetColor(int r, int g, int b, int a) = 0;
	virtual void DrawSetColor(Color_t col) = 0;
	virtual void DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
	virtual void DrawFilledRectArray(IntRect* pRects, int numRects) = 0;
	virtual void DrawOutlinedRect(int x0, int y0, int x1, int y1) = 0;
	virtual void DrawLine(int x0, int y0, int x1, int y1) = 0;
	virtual void DrawPolyLine(int* px, int* py, int numPoints) = 0;
	virtual void DrawSetTextFont(HFont font) = 0;
	virtual void DrawSetTextColor(int r, int g, int b, int a) = 0;
	virtual void DrawSetTextColor(Color_t col) = 0;
	virtual void DrawSetTextPos(int x, int y) = 0;
	virtual void DrawGetTextPos(int& x, int& y) = 0;
	virtual void DrawPrintText(const wchar_t* text, int textLen, FontDrawType_t drawType) = 0;
	virtual void DrawUnicodeChar(wchar_t wch, FontDrawType_t drawType) = 0;
	virtual void DrawFlushText() = 0;
	virtual IHTML* CreateHTMLWindow(IHTMLEvents* events, VPANEL context) = 0;
	virtual void PaintHTMLWindow(IHTML* htmlwin) = 0;
	virtual void DeleteHTMLWindow(IHTML* htmlwin) = 0;
	virtual int	 DrawGetTextureId(char const* filename) = 0;
	virtual bool DrawGetTextureFile(int id, char* filename, int maxlen) = 0;
	virtual void DrawSetTextureFile(int id, const char* filename, int hardwareFilter, bool forceReload) = 0;
	virtual void DrawSetTextureRGBA(int id, const unsigned char* rgba, int wide, int tall, int hardwareFilter, bool forceReload) = 0;
	virtual void DrawSetTexture(int id) = 0;
	virtual void DrawGetTextureSize(int id, int& wide, int& tall) = 0;
	virtual void DrawTexturedRect(int x0, int y0, int x1, int y1) = 0;
	virtual bool IsTextureIDValid(int id) = 0;
	virtual bool DeleteTextureByID(int id) = 0;
	virtual int CreateNewTextureID(bool procedural = false) = 0;
	virtual void GetScreenSize(int& wide, int& tall) = 0;
	virtual void SetAsTopMost(VPANEL panel, bool state) = 0;
	virtual void BringToFront(VPANEL panel) = 0;
	virtual void SetForegroundWindow(VPANEL panel) = 0;
	virtual void SetPanelVisible(VPANEL panel, bool state) = 0;
	virtual void SetMinimized(VPANEL panel, bool state) = 0;
	virtual bool IsMinimized(VPANEL panel) = 0;
	virtual void FlashWindow(VPANEL panel, bool state) = 0;
	virtual void SetTitle(VPANEL panel, const wchar_t* title) = 0;
	virtual void SetAsToolBar(VPANEL panel, bool state) = 0;
	virtual void CreatePopup(VPANEL panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true) = 0;
	virtual void SwapBuffers(VPANEL panel) = 0;
	virtual void Invalidate(VPANEL panel) = 0;
	virtual void SetCursor(HCursor cursor) = 0;
	virtual void SetCursorAlwaysVisible(bool visible) = 0;
	virtual bool IsCursorVisible() = 0;
	virtual void ApplyChanges() = 0;
	virtual bool IsWithin(int x, int y) = 0;
	virtual bool HasFocus() = 0;
	virtual bool SupportsFeature(SurfaceFeature_e feature) = 0;
	virtual void RestrictPaintToSinglePanel(VPANEL panel) = 0;
	virtual void SetModalPanel(VPANEL) = 0;
	virtual VPANEL GetModalPanel() = 0;
	virtual void UnlockCursor() = 0;
	virtual void LockCursor() = 0;
	virtual void SetTranslateExtendedKeys(bool state) = 0;
	virtual VPANEL GetTopmostPopup() = 0;
	virtual void SetTopLevelFocus(VPANEL panel) = 0;
	virtual HFont CreateFont() = 0;
	virtual bool SetFontGlyphSet(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0) = 0;
	virtual bool AddCustomFontFile(const char* fontName, const char* fontFileName) = 0;
	virtual int GetFontTall(HFont font) = 0;
	virtual int GetFontTallRequested(HFont font) = 0;
	virtual int GetFontAscent(HFont font, wchar_t wch) = 0;
	virtual bool IsFontAdditive(HFont font) = 0;
	virtual void GetCharABCwide(HFont font, int ch, int& a, int& b, int& c) = 0;
	virtual int GetCharacterWidth(HFont font, int ch) = 0;
	virtual void GetTextSize(HFont font, const wchar_t* text, int& wide, int& tall) = 0;
	virtual VPANEL GetNotifyPanel() = 0;
	virtual void SetNotifyIcon(VPANEL context, HTexture icon, VPANEL panelToReceiveMessages, const char* text) = 0;
	virtual void PlaySound(const char* fileName) = 0;
	virtual int GetPopupCount() = 0;
	virtual VPANEL GetPopup(int index) = 0;
	virtual bool ShouldPaintChildPanel(VPANEL childPanel) = 0;
	virtual bool RecreateContext(VPANEL panel) = 0;
	virtual void AddPanel(VPANEL panel) = 0;
	virtual void ReleasePanel(VPANEL panel) = 0;
	virtual void MovePopupToFront(VPANEL panel) = 0;
	virtual void MovePopupToBack(VPANEL panel) = 0;
	virtual void SolveTraverse(VPANEL panel, bool forceApplySchemeSettings = false) = 0;
	virtual void PaintTraverse(VPANEL panel) = 0;
	virtual void EnableMouseCapture(VPANEL panel, bool state) = 0;
	virtual void GetWorkspaceBounds(int& x, int& y, int& wide, int& tall) = 0;
	virtual void GetAbsoluteWindowBounds(int& x, int& y, int& wide, int& tall) = 0;
	virtual void GetProportionalBase(int& width, int& height) = 0;
	virtual void CalculateMouseVisible() = 0;
	virtual bool NeedKBInput() = 0;
	virtual bool HasCursorPosFunctions() = 0;
	virtual void SurfaceGetCursorPos(int& x, int& y) = 0;
	virtual void SurfaceSetCursorPos(int x, int y) = 0;
	virtual void DrawTexturedLine(const Vertex_t& a, const Vertex_t& b) = 0;
	virtual void DrawOutlinedCircle(int x, int y, int radius, int segments) = 0;
	virtual void DrawTexturedPolyLine(const Vertex_t* p, int n) = 0;
	virtual void DrawTexturedSubRect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
	virtual void DrawTexturedPolygon(int n, Vertex_t* pVertice, bool bClipVertices = true) = 0;
	virtual const wchar_t* GetTitle(VPANEL panel) = 0;
	virtual bool IsCursorLocked(void) const = 0;
	virtual void SetWorkspaceInsets(int left, int top, int right, int bottom) = 0;
	virtual bool DrawGetUnicodeCharRenderInfo(wchar_t ch, CharRenderInfo& info) = 0;
	virtual void DrawRenderCharFromInfo(const CharRenderInfo& info) = 0;
	virtual void DrawSetAlphaMultiplier(float alpha) = 0;
	virtual float DrawGetAlphaMultiplier() = 0;
	virtual void SetAllowHTMLJavaScript(bool state) = 0;
	virtual void OnScreenSizeChanged(int nOldWidth, int nOldHeight) = 0;
	virtual HCursor CreateCursorFromFile(char const* curOrAniFile, char const* pPathID = 0) = 0;
	virtual IVguiMatInfo* DrawGetTextureMatInfoFactory(int id) = 0;
	virtual void PaintTraverseEx(VPANEL panel, bool paintPopups = false) = 0;
	virtual float GetZPos() const = 0;
	virtual void SetPanelForInput(VPANEL vpanel) = 0;
	virtual void DrawFilledRectFastFade(int x0, int y0, int x1, int y1, int fadeStartPt, int fadeEndPt, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
	virtual void DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
	virtual void DrawSetTextureRGBAEx(int id, const unsigned char* rgba, int wide, int tall, ImageFormat imageFormat) = 0;
	virtual void DrawSetTextScale(float sx, float sy) = 0;
	virtual bool SetBitmapFontGlyphSet(HFont font, const char* windowsFontName, float scalex, float scaley, int flags) = 0;
	virtual bool AddBitmapFontFile(const char* fontFileName) = 0;
	virtual void SetBitmapFontName(const char* pName, const char* pFontFilename) = 0;
	virtual const char* GetBitmapFontName(const char* pName) = 0;
	virtual void ClearTemporaryFontCache(void) = 0;
	virtual IImage* GetIconImageForFullPath(char const* pFullPath) = 0;
	virtual void DrawUnicodeString(const wchar_t* pwString, FontDrawType_t drawType) = 0;
	virtual void PrecacheFontCharacters(HFont font, const wchar_t* pCharacters) = 0;
	virtual const char* GetResolutionKey(void) const = 0;
	virtual const char* GetFontName(HFont font) = 0;
	virtual const char* GetFontFamilyName(HFont font) = 0;
	virtual void GetKernedCharWidth(HFont font, wchar_t ch, wchar_t chBefore, wchar_t chAfter, float& wide, float& abcA) = 0;
	virtual bool ForceScreenSizeOverride(bool bState, int wide, int tall) = 0;
	virtual bool ForceScreenPosOffset(bool bState, int x, int y) = 0;
	virtual void OffsetAbsPos(int& x, int& y) = 0;
	virtual void ResetFontCaches() = 0;
	virtual int GetTextureNumFrames(int id) = 0;
	virtual void DrawSetTextureFrame(int id, int nFrame, unsigned int* pFrameCache) = 0;
	virtual bool IsScreenSizeOverrideActive(void) = 0;
	virtual bool IsScreenPosOverrideActive(void) = 0;
	virtual void DestroyTextureID(int id) = 0;
	virtual void DrawUpdateRegionTextureRGBA(int nTextureID, int x, int y, const unsigned char* pchData, int wide, int tall, ImageFormat imageFormat) = 0;
	virtual bool BHTMLWindowNeedsPaint(IHTML* htmlwin) = 0;
	virtual const char* GetWebkitHTMLUserAgentString() = 0;
	virtual void* Deprecated_AccessChromeHTMLController() = 0;
	virtual void SetFullscreenViewport(int x, int y, int w, int h) = 0;
	virtual void GetFullscreenViewport(int& x, int& y, int& w, int& h) = 0;
	virtual void PushFullscreenViewport() = 0;
	virtual void PopFullscreenViewport() = 0;
	virtual void SetSoftwareCursor(bool bUseSoftwareCursor) = 0;
	virtual void PaintSoftwareCursor() = 0;
};

class IVTFTexture;
class ITexture;
struct Rect_t { int x, y, w, h; };

enum NormalDecodeMode_t
{
	NORMAL_DECODE_NONE = 0
};

class ITextureRegenerator
{
public:
	virtual void RegenerateTextureBits(ITexture* pTexture, IVTFTexture* pVTFTexture, Rect_t* pRect) = 0;
	virtual void Release() = 0;
};

class ITexture
{
public:
	virtual const char* GetName(void) const = 0;
	virtual int GetMappingWidth() const = 0;
	virtual int GetMappingHeight() const = 0;
	virtual int GetActualWidth() const = 0;
	virtual int GetActualHeight() const = 0;
	virtual int GetNumAnimationFrames() const = 0;
	virtual bool IsTranslucent() const = 0;
	virtual bool IsMipmapped() const = 0;
	virtual void GetLowResColorSample(float s, float t, float* color) const = 0;
	virtual void* GetResourceData(uint32_t eDataType, size_t* pNumBytes) const = 0;
	virtual void IncrementReferenceCount(void) = 0;
	virtual void DecrementReferenceCount(void) = 0;
	inline void AddRef() { IncrementReferenceCount(); }
	inline void Release() { DecrementReferenceCount(); }
	virtual void SetTextureRegenerator(ITextureRegenerator* pTextureRegen) = 0;
	virtual void Download(Rect_t* pRect = 0, int nAdditionalCreationFlags = 0) = 0;
	virtual int GetApproximateVidMemBytes(void) const = 0;
	virtual bool IsError() const = 0;
	virtual bool IsVolumeTexture() const = 0;
	virtual int GetMappingDepth() const = 0;
	virtual int GetActualDepth() const = 0;
	virtual ImageFormat GetImageFormat() const = 0;
	virtual NormalDecodeMode_t GetNormalDecodeMode() const = 0;
	virtual bool IsRenderTarget() const = 0;
	virtual bool IsCubeMap() const = 0;
	virtual bool IsNormalMap() const = 0;
	virtual bool IsProcedural() const = 0;
	virtual void DeleteIfUnreferenced() = 0;
	virtual void SwapContents(ITexture* pOther) = 0;
	virtual unsigned int GetFlags(void) const = 0;
	virtual void ForceLODOverride(int iNumLodsOverrideUpOrDown) = 0;
	virtual bool SaveToFile(const char* fileName) = 0;
	virtual void CopyToStagingTexture(ITexture* pDstTex) = 0;
	virtual void SetErrorTexture(bool bIsErrorTexture) = 0;
};

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_MULTIPASS = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_IGNORE_ALPHA_MODULATION = (1 << 30),
};

enum MaterialVarType_t
{
	MATERIAL_VAR_TYPE_FLOAT = 0,
	MATERIAL_VAR_TYPE_STRING,
	MATERIAL_VAR_TYPE_VECTOR,
	MATERIAL_VAR_TYPE_TEXTURE,
	MATERIAL_VAR_TYPE_INT,
	MATERIAL_VAR_TYPE_FOURCC,
	MATERIAL_VAR_TYPE_UNDEFINED,
	MATERIAL_VAR_TYPE_MATRIX,
	MATERIAL_VAR_TYPE_MATERIAL,
};

enum PreviewImageRetVal_t
{
	MATERIAL_PREVIEW_IMAGE_BAD = 0,
	MATERIAL_PREVIEW_IMAGE_OK,
	MATERIAL_NO_PREVIEW_IMAGE,
};

enum MaterialPropertyTypes_t
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,
	MATERIAL_PROPERTY_OPACITY,
	MATERIAL_PROPERTY_REFLECTIVITY,
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS
};

typedef unsigned short MaterialVarSym_t;
typedef uint64_t VertexFormat_t;
typedef uint32_t MorphFormat_t;


class Vector4D
{
public:
	float x, y, z, w;
};

class IMaterial;

class IMaterialVar
{
public:
	typedef unsigned long FourCC;

	char* m_pStringVal;
	int m_intVal;
	Vector4D m_VecVal;

	uint8_t m_Type;
	uint8_t m_nNumVectorComps;
	uint8_t m_bFakeMaterialVar;
	uint8_t m_nTempIndex;
	//CUtlSymbol m_Name;

public:
	virtual ITexture* GetTextureValue(void) = 0;
	virtual char const* GetName(void) const = 0;
	virtual MaterialVarSym_t GetNameAsSymbol() const = 0;
	virtual void SetFloatValue(float val) = 0;
	virtual void SetIntValue(int val) = 0;
	virtual void SetStringValue(char const* val) = 0;
	virtual char const* GetStringValue(void) const = 0;
	virtual void SetFourCCValue(FourCC type, void* pData) = 0;
	virtual void GetFourCCValue(FourCC* type, void** ppData) = 0;
	virtual void SetVecValue(float const* val, int numcomps) = 0;
	virtual void SetVecValue(float x, float y) = 0;
	virtual void SetVecValue(float x, float y, float z) = 0;
	virtual void SetVecValue(float x, float y, float z, float w) = 0;
	virtual void GetLinearVecValue(float* val, int numcomps) const = 0;
	virtual void SetTextureValue(ITexture*) = 0;
	virtual IMaterial* GetMaterialValue(void) = 0;
	virtual void SetMaterialValue(IMaterial*) = 0;
	virtual bool IsDefined() const = 0;
	virtual void SetUndefined() = 0;
	virtual void SetMatrixValue(VMatrix const& matrix) = 0;
	virtual const VMatrix& GetMatrixValue() = 0;
	virtual bool MatrixIsIdentity() const = 0;
	virtual void CopyFrom(IMaterialVar* pMaterialVar) = 0;
	virtual void SetValueAutodetectType(char const* val) = 0;
	virtual IMaterial* GetOwningMaterial() = 0;
	virtual void SetVecComponentValue(float fVal, int nComponent) = 0;
	virtual int GetIntValueInternal(void) const = 0;
	virtual float GetFloatValueInternal(void) const = 0;
	virtual float const* GetVecValueInternal() const = 0;
	virtual void GetVecValueInternal(float* val, int numcomps) const = 0;
	virtual int VectorSizeInternal() const = 0;
};


class IMaterial
{
public:
	virtual const char* GetName() const = 0;
	virtual const char* GetTextureGroupName() const = 0;
	virtual PreviewImageRetVal_t GetPreviewImageProperties(int* width, int* height, ImageFormat* imageFormat, bool* isTranslucent) const = 0;
	virtual PreviewImageRetVal_t GetPreviewImage(unsigned char* data, int width, int height, ImageFormat imageFormat) const = 0;
	virtual int GetMappingWidth() = 0;
	virtual int GetMappingHeight() = 0;
	virtual int GetNumAnimationFrames() = 0;
	virtual bool InMaterialPage(void) = 0;
	virtual	void GetMaterialOffset(float* pOffset) = 0;
	virtual void GetMaterialScale(float* pScale) = 0;
	virtual IMaterial* GetMaterialPage(void) = 0;
	virtual IMaterialVar* FindVar(const char* varName, bool* found, bool complain = true) = 0;
	virtual void IncrementReferenceCount(void) = 0;
	virtual void DecrementReferenceCount(void) = 0;
	virtual int GetEnumerationID(void) const = 0;
	virtual void GetLowResColorSample(float s, float t, float* color) const = 0;
	virtual void RecomputeStateSnapshots() = 0;
	virtual bool IsTranslucent() = 0;
	virtual bool IsAlphaTested() = 0;
	virtual bool IsVertexLit() = 0;
	virtual VertexFormat_t GetVertexFormat() const = 0;
	virtual bool HasProxy(void) const = 0;
	virtual bool UsesEnvCubemap(void) = 0;
	virtual bool NeedsTangentSpace(void) = 0;
	virtual bool NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool NeedsSoftwareSkinning(void) = 0;
	virtual void AlphaModulate(float alpha) = 0;
	virtual void ColorModulate(float r, float g, float b) = 0;
	virtual void SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool GetMaterialVarFlag(MaterialVarFlags_t flag) const = 0;
	virtual void GetReflectivity(Vec3& reflect) = 0;
	virtual bool GetPropertyFlag(MaterialPropertyTypes_t type) = 0;
	virtual bool IsTwoSided() = 0;
	virtual void SetShader(const char* pShaderName) = 0;
	virtual int GetNumPasses(void) = 0;
	virtual int GetTextureMemoryBytes(void) = 0;
	virtual void Refresh() = 0;
	virtual bool NeedsLightmapBlendAlpha(void) = 0;
	virtual bool NeedsSoftwareLighting(void) = 0;
	virtual int ShaderParamCount() const = 0;
	virtual IMaterialVar** GetShaderParams(void) = 0;
	virtual bool IsErrorMaterial() const = 0;
	virtual void SetUseFixedFunctionBakedLighting(bool bEnable) = 0;
	virtual float GetAlphaModulation() = 0;
	virtual void GetColorModulation(float* r, float* g, float* b) = 0;
	virtual MorphFormat_t GetMorphFormat() const = 0;
	virtual IMaterialVar* FindVarFast(char const* pVarName, unsigned int* pToken) = 0;
	virtual void			SetShaderAndParams(void* pKeyValues) = 0;
	virtual const char* GetShaderName() const = 0;
	virtual void			DeleteIfUnreferenced() = 0;
	virtual bool			IsSpriteCard() = 0;
	virtual void			CallBindProxy(void* proxyData) = 0;
	virtual IMaterial* CheckProxyReplacement(void* proxyData) = 0;
	virtual void			RefreshPreservingMaterialVars() = 0;
	virtual bool			WasReloadedFromWhitelist() = 0;
	virtual bool			IsPrecached() const = 0;
};

struct InputEvent_t
{
	int m_nType;				// Type of the event (see InputEventType_t)
	int m_nTick;				// Tick on which the event occurred
	int m_nData;				// Generic 32-bit data, what it contains depends on the event
	int m_nData2;				// Generic 32-bit data, what it contains depends on the event
	int m_nData3;				// Generic 32-bit data, what it contains depends on the event
};


typedef void (*GetMouseCallback_t)(int& x, int& y);
typedef void (*SetMouseCallback_t)(int x, int y);
typedef void (*PlaySoundFunc_t)(const char* pFileName);

class IMatSystemSurface : public ISurface
{
public:
	virtual void AttachToWindow(void* hwnd, bool bLetAppDriveInput = false) = 0;
	virtual void EnableWindowsMessages(bool bEnable) = 0;
	virtual void Begin3DPaint(int iLeft, int iTop, int iRight, int iBottom, bool bRenderToTexture = true) = 0;
	virtual void End3DPaint() = 0;
	virtual void DisableClipping(bool bDisable) = 0;
	virtual void GetClippingRect(int& left, int& top, int& right, int& bottom, bool& bClippingDisabled) = 0;
	virtual void SetClippingRect(int left, int top, int right, int bottom) = 0;
	virtual bool IsCursorLocked() const = 0;
	virtual void SetMouseCallbacks(GetMouseCallback_t getFunc, SetMouseCallback_t setFunc) = 0;
	virtual void InstallPlaySoundFunc(PlaySoundFunc_t soundFunc) = 0;
	virtual void DrawColoredCircle(int centerx, int centery, float radius, int r, int g, int b, int a) = 0;
	virtual int DrawColoredText(HFont font, int x, int y, int r, int g, int b, int a, const char* fmt, ...) = 0;
	virtual void DrawColoredTextRect(HFont font, int x, int y, int w, int h, int r, int g, int b, int a, const char* fmt, ...) = 0;
	virtual void DrawTextHeight(HFont font, int w, int& h, const char* fmt, ...) = 0;
	virtual int	DrawTextLen(HFont font, const char* fmt, ...) = 0;
	virtual void DrawPanelIn3DSpace(VPANEL pRootPanel, const VMatrix& panelCenterToWorld, int nPixelWidth, int nPixelHeight, float flWorldWidth, float flWorldHeight) = 0;
	virtual void DrawSetTextureMaterial(int id, IMaterial* pMaterial) = 0;
	virtual bool HandleInputEvent(const InputEvent_t& event) = 0;
	virtual void Set3DPaintTempRenderTarget(const char* pRenderTargetName) = 0;
	virtual void Reset3DPaintTempRenderTarget(void) = 0;
	virtual IMaterial* DrawGetTextureMaterial(int id) = 0;
	virtual void GetFullscreenViewportAndRenderTarget(int& x, int& y, int& w, int& h, ITexture** ppRenderTarget) = 0;
	virtual void SetFullscreenViewportAndRenderTarget(int x, int y, int w, int h, ITexture* pRenderTarget) = 0;
	virtual int  DrawGetTextureId(ITexture* pTexture) = 0;
	virtual void BeginSkinCompositionPainting() = 0;
	virtual void EndSkinCompositionPainting() = 0;
};

#define VGUI_SURFACE_INTERFACE_VERSION "VGUI_Surface030"