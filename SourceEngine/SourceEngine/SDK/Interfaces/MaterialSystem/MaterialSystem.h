#pragma once

#include "../Surface/Surface.h"

struct MorphWeight_t;
struct MaterialPrimitiveType_t;
struct MaterialNonInteractiveMode_t;
struct MaterialMatrixMode_t;
struct MaterialIndexFormat_t;
struct IMesh;
struct MaterialHeightClipMode_t;
struct MaterialFogMode_t;
struct MaterialCullMode_t;
struct IVertexBuffer;
struct IMorph;
struct IIndexBuffer;
struct ICallQueue;
struct IAsyncTextureOperationReceiver;
struct FlashlightState_t;
struct DeformationBase_t;
struct ColorCorrectionHandle_t;

enum LightType_t
{
	MATERIAL_LIGHT_DISABLE = 0,
	MATERIAL_LIGHT_POINT,
	MATERIAL_LIGHT_DIRECTIONAL,
	MATERIAL_LIGHT_SPOT,
};

struct LightDesc_t
{
	LightType_t m_Type;
	Vec3 m_Color;
	Vec3 m_Position;
	Vec3 m_Direction;
	float  m_Range;
	float m_Falloff;
	float m_Attenuation0;
	float m_Attenuation1;
	float m_Attenuation2;
	float m_Theta;
	float m_Phi;
	float m_ThetaDot;
	float m_PhiDot;
	unsigned int m_Flags;
	float OneOver_ThetaDot_Minus_PhiDot;
	float m_RangeSquared;
};

using OcclusionQueryObjectHandle_t = void*;

enum StencilOperation_t
{
	STENCILOPERATION_KEEP = 1,
	STENCILOPERATION_ZERO = 2,
	STENCILOPERATION_REPLACE = 3,
	STENCILOPERATION_INCRSAT = 4,
	STENCILOPERATION_DECRSAT = 5,
	STENCILOPERATION_INVERT = 6,
	STENCILOPERATION_INCR = 7,
	STENCILOPERATION_DECR = 8,
	STENCILOPERATION_FORCE_DWORD = 0x7fffffff
};

enum StencilComparisonFunction_t
{
	STENCILCOMPARISONFUNCTION_NEVER = 1,
	STENCILCOMPARISONFUNCTION_LESS = 2,
	STENCILCOMPARISONFUNCTION_EQUAL = 3,
	STENCILCOMPARISONFUNCTION_LESSEQUAL = 4,
	STENCILCOMPARISONFUNCTION_GREATER = 5,
	STENCILCOMPARISONFUNCTION_NOTEQUAL = 6,
	STENCILCOMPARISONFUNCTION_GREATEREQUAL = 7,
	STENCILCOMPARISONFUNCTION_ALWAYS = 8,
	STENCILCOMPARISONFUNCTION_FORCE_DWORD = 0x7fffffff
};

enum ShaderStencilFunc_t
{
	SHADER_STENCILFUNC_NEVER = 0,
	SHADER_STENCILFUNC_LESS,
	SHADER_STENCILFUNC_EQUAL,
	SHADER_STENCILFUNC_LEQUAL,
	SHADER_STENCILFUNC_GREATER,
	SHADER_STENCILFUNC_NOTEQUAL,
	SHADER_STENCILFUNC_GEQUAL,
	SHADER_STENCILFUNC_ALWAYS,
};

enum ShaderStencilOp_t
{
	SHADER_STENCILOP_KEEP = 0,
	SHADER_STENCILOP_ZERO,
	SHADER_STENCILOP_SET_TO_REFERENCE,
	SHADER_STENCILOP_INCREMENT_CLAMP,
	SHADER_STENCILOP_DECREMENT_CLAMP,
	SHADER_STENCILOP_INVERT,
	SHADER_STENCILOP_INCREMENT_WRAP,
	SHADER_STENCILOP_DECREMENT_WRAP,
};



class IRefCounted
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
};

class IMatRenderContext : public IRefCounted
{
public:
	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;
	virtual void Flush(bool flushHardware = false) = 0;
	virtual void BindLocalCubemap(ITexture* pTexture) = 0;
	virtual void SetRenderTarget(ITexture* pTexture) = 0;
	virtual ITexture* GetRenderTarget(void) = 0;
	virtual void GetRenderTargetDimensions(int& width, int& height) const = 0;
	virtual void Bind(IMaterial* material, void* proxyData = 0) = 0;
	virtual void BindLightmapPage(int lightmapPageID) = 0;
	virtual void DepthRange(float zNear, float zFar) = 0;
	virtual void ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil = false) = 0;
	virtual void ReadPixels(int x, int y, int width, int height, unsigned char* data, ImageFormat dstFormat) = 0;
	virtual void SetAmbientLight(float r, float g, float b) = 0;
	virtual void SetLight(int lightNum, const LightDesc_t& desc) = 0;
	virtual void SetAmbientLightCube(Vector4D cube[6]) = 0;
	virtual void CopyRenderTargetToTexture(ITexture* pTexture) = 0;
	virtual void SetFrameBufferCopyTexture(ITexture* pTexture, int textureIndex = 0) = 0;
	virtual ITexture* GetFrameBufferCopyTexture(int textureIndex) = 0;
	virtual void MatrixMode(MaterialMatrixMode_t matrixMode) = 0;
	virtual void PushMatrix(void) = 0;
	virtual void PopMatrix(void) = 0;
	virtual void LoadMatrix(VMatrix const& matrix) = 0;
	virtual void LoadMatrix(matrix3x4 const& matrix) = 0;
	virtual void MultMatrix(VMatrix const& matrix) = 0;
	virtual void MultMatrix(matrix3x4 const& matrix) = 0;
	virtual void MultMatrixLocal(VMatrix const& matrix) = 0;
	virtual void MultMatrixLocal(matrix3x4 const& matrix) = 0;
	virtual void GetMatrix(MaterialMatrixMode_t matrixMode, VMatrix* matrix) = 0;
	virtual void GetMatrix(MaterialMatrixMode_t matrixMode, matrix3x4* matrix) = 0;
	virtual void LoadIdentity(void) = 0;
	virtual void Ortho(double left, double top, double right, double bottom, double zNear, double zFar) = 0;
	virtual void PerspectiveX(double fovx, double aspect, double zNear, double zFar) = 0;
	virtual void PickMatrix(int x, int y, int width, int height) = 0;
	virtual void Rotate(float angle, float x, float y, float z) = 0;
	virtual void Translate(float x, float y, float z) = 0;
	virtual void Scale(float x, float y, float z) = 0;
	virtual void Viewport(int x, int y, int width, int height) = 0;
	virtual void GetViewport(int& x, int& y, int& width, int& height) const = 0;
	virtual void CullMode(MaterialCullMode_t cullMode) = 0;
	virtual void SetHeightClipMode(MaterialHeightClipMode_t nHeightClipMode) = 0;
	virtual void SetHeightClipZ(float z) = 0;
	virtual void FogMode(MaterialFogMode_t fogMode) = 0;
	virtual void FogStart(float fStart) = 0;
	virtual void FogEnd(float fEnd) = 0;
	virtual void SetFogZ(float fogZ) = 0;
	virtual MaterialFogMode_t	GetFogMode(void) = 0;
	virtual void FogColor3f(float r, float g, float b) = 0;
	virtual void FogColor3fv(float const* rgb) = 0;
	virtual void FogColor3ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void FogColor3ubv(unsigned char const* rgb) = 0;
	virtual void GetFogColor(unsigned char* rgb) = 0;
	virtual void SetNumBoneWeights(int numBones) = 0;
	virtual IMesh* CreateStaticMesh(VertexFormat_t fmt, const char* pTextureBudgetGroup, IMaterial* pMaterial = NULL) = 0;
	virtual void DestroyStaticMesh(IMesh* mesh) = 0;
	virtual IMesh* GetDynamicMesh(bool buffered = true, IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0, IMaterial* pAutoBind = 0) = 0;
	virtual IVertexBuffer* CreateStaticVertexBuffer(VertexFormat_t fmt, int nVertexCount, const char* pTextureBudgetGroup) = 0;
	virtual IIndexBuffer* CreateStaticIndexBuffer(MaterialIndexFormat_t fmt, int nIndexCount, const char* pTextureBudgetGroup) = 0;
	virtual void DestroyVertexBuffer(IVertexBuffer*) = 0;
	virtual void DestroyIndexBuffer(IIndexBuffer*) = 0;
	virtual IVertexBuffer* GetDynamicVertexBuffer(int streamID, VertexFormat_t vertexFormat, bool bBuffered = true) = 0;
	virtual IIndexBuffer* GetDynamicIndexBuffer(MaterialIndexFormat_t fmt, bool bBuffered = true) = 0;
	virtual void BindVertexBuffer(int streamID, IVertexBuffer* pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount, VertexFormat_t fmt, int nRepetitions = 1) = 0;
	virtual void BindIndexBuffer(IIndexBuffer* pIndexBuffer, int nOffsetInBytes) = 0;
	virtual void Draw(MaterialPrimitiveType_t primitiveType, int firstIndex, int numIndices) = 0;
	virtual int  SelectionMode(bool selectionMode) = 0;
	virtual void SelectionBuffer(unsigned int* pBuffer, int size) = 0;
	virtual void ClearSelectionNames() = 0;
	virtual void LoadSelectionName(int name) = 0;
	virtual void PushSelectionName(int name) = 0;
	virtual void PopSelectionName() = 0;
	virtual void ClearColor3ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
	virtual void OverrideDepthEnable(bool bEnable, bool bDepthEnable) = 0;
	virtual void DrawScreenSpaceQuad(IMaterial* pMaterial) = 0;
	virtual void SyncToken(const char* pToken) = 0;
	virtual float ComputePixelWidthOfSphere(const Vec3& origin, float flRadius) = 0;
	virtual OcclusionQueryObjectHandle_t CreateOcclusionQueryObject(void) = 0;
	virtual void DestroyOcclusionQueryObject(OcclusionQueryObjectHandle_t) = 0;
	virtual void BeginOcclusionQueryDrawing(OcclusionQueryObjectHandle_t) = 0;
	virtual void EndOcclusionQueryDrawing(OcclusionQueryObjectHandle_t) = 0;
	virtual int OcclusionQuery_GetNumPixelsRendered(OcclusionQueryObjectHandle_t) = 0;
	virtual void SetFlashlightMode(bool bEnable) = 0;
	virtual void SetFlashlightState(const FlashlightState_t& state, const VMatrix& worldToTexture) = 0;
	virtual MaterialHeightClipMode_t GetHeightClipMode() = 0;
	virtual float ComputePixelDiameterOfSphere(const Vec3& vecAbsOrigin, float flRadius) = 0;
	virtual void EnableUserClipTransformOverride(bool bEnable) = 0;
	virtual void UserClipTransform(const VMatrix& worldToView) = 0;
	virtual bool GetFlashlightMode() const = 0;
	virtual void ResetOcclusionQueryObject(OcclusionQueryObjectHandle_t) = 0;
	virtual void Unused3() {}
	virtual IMorph* CreateMorph(MorphFormat_t format, const char* pDebugName) = 0;
	virtual void DestroyMorph(IMorph* pMorph) = 0;
	virtual void BindMorph(IMorph* pMorph) = 0;
	virtual void SetFlexWeights(int nFirstWeight, int nCount, const MorphWeight_t* pWeights) = 0;
	virtual void Unused4() {};
	virtual void Unused5() {};
	virtual void Unused6() {};
	virtual void Unused7() {};
	virtual void Unused8() {};
	virtual void ReadPixelsAndStretch(Rect_t* pSrcRect, Rect_t* pDstRect, unsigned char* pBuffer, ImageFormat dstFormat, int nDstStride) = 0;
	virtual void GetWindowSize(int& width, int& height) const = 0;
	virtual void DrawScreenSpaceRectangle(
		IMaterial* pMaterial,
		int destx, int desty,
		int width, int height,
		float src_texture_x0, float src_texture_y0,
		float src_texture_x1, float src_texture_y1,
		int src_texture_width, int src_texture_height,
		void* pClientRenderable = NULL,
		int nXDice = 1,
		int nYDice = 1) = 0;
	virtual void LoadBoneMatrix(int boneIndex, const matrix3x4& matrix) = 0;
	virtual void PushRenderTargetAndViewport() = 0;
	virtual void PushRenderTargetAndViewport(ITexture* pTexture) = 0;
	virtual void PushRenderTargetAndViewport(ITexture* pTexture, int nViewX, int nViewY, int nViewW, int nViewH) = 0;
	virtual void PushRenderTargetAndViewport(ITexture* pTexture, ITexture* pDepthTexture, int nViewX, int nViewY, int nViewW, int nViewH) = 0;
	virtual void PopRenderTargetAndViewport(void) = 0;
	virtual void BindLightmapTexture(ITexture* pLightmapTexture) = 0;
	virtual void CopyRenderTargetToTextureEx(ITexture* pTexture, int nRenderTargetID, Rect_t* pSrcRect, Rect_t* pDstRect = NULL) = 0;
	virtual void CopyTextureToRenderTargetEx(int nRenderTargetID, ITexture* pTexture, Rect_t* pSrcRect, Rect_t* pDstRect = NULL) = 0;
	virtual void PerspectiveOffCenterX(double fovx, double aspect, double zNear, double zFar, double bottom, double top, double left, double right) = 0;
	virtual void SetFloatRenderingParameter(int parm_number, float value) = 0;
	virtual void SetIntRenderingParameter(int parm_number, int value) = 0;
	virtual void SetVectorRenderingParameter(int parm_number, Vec3 const& value) = 0;
	virtual void SetStencilEnable(bool onoff) = 0;
	virtual void SetStencilFailOperation(StencilOperation_t op) = 0;
	virtual void SetStencilZFailOperation(StencilOperation_t op) = 0;
	virtual void SetStencilPassOperation(StencilOperation_t op) = 0;
	virtual void SetStencilCompareFunction(StencilComparisonFunction_t cmpfn) = 0;
	virtual void SetStencilReferenceValue(int ref) = 0;
	virtual void SetStencilTestMask(uint32_t msk) = 0;
	virtual void SetStencilWriteMask(uint32_t msk) = 0;
	virtual void ClearStencilBufferRectangle(int xmin, int ymin, int xmax, int ymax, int value) = 0;
	virtual void SetRenderTargetEx(int nRenderTargetID, ITexture* pTexture) = 0;
	virtual void PushCustomClipPlane(const float* pPlane) = 0;
	virtual void PopCustomClipPlane(void) = 0;
	virtual void GetMaxToRender(IMesh* pMesh, bool bMaxUntilFlush, int* pMaxVerts, int* pMaxIndices) = 0;
	virtual int GetMaxVerticesToRender(IMaterial* pMaterial) = 0;
	virtual int GetMaxIndicesToRender() = 0;
	virtual void DisableAllLocalLights() = 0;
	virtual int CompareMaterialCombos(IMaterial* pMaterial1, IMaterial* pMaterial2, int lightMapID1, int lightMapID2) = 0;
	virtual IMesh* GetFlexMesh() = 0;
	virtual void SetFlashlightStateEx(const FlashlightState_t& state, const VMatrix& worldToTexture, ITexture* pFlashlightDepthTexture) = 0;
	virtual ITexture* GetLocalCubemap() = 0;
	virtual void ClearBuffersObeyStencil(bool bClearColor, bool bClearDepth) = 0;
	virtual bool EnableClipping(bool bEnable) = 0;
	virtual void GetFogDistances(float* fStart, float* fEnd, float* fFogZ) = 0;
	virtual void BeginPIXEvent(unsigned long color, const char* szName) = 0;
	virtual void EndPIXEvent() = 0;
	virtual void SetPIXMarker(unsigned long color, const char* szName) = 0;
	virtual void BeginBatch(IMesh* pIndices) = 0;
	virtual void BindBatch(IMesh* pVertices, IMaterial* pAutoBind = NULL) = 0;
	virtual void DrawBatch(int firstIndex, int numIndices) = 0;
	virtual void EndBatch() = 0;
	virtual ICallQueue* GetCallQueue() = 0;
	virtual void GetWorldSpaceCameraPosition(Vec3* pCameraPos) = 0;
	virtual void GetWorldSpaceCameraVectors(Vec3* pVecForward, Vec3* pVecRight, Vec3* pVecUp) = 0;
	virtual void ResetToneMappingScale(float monoscale) = 0;
	virtual void SetGoalToneMappingScale(float monoscale) = 0;
	virtual void TurnOnToneMapping() = 0;
	virtual void SetToneMappingScaleLinear(const Vec3& scale) = 0;
	virtual Vec3 GetToneMappingScaleLinear(void) = 0;
	virtual void SetShadowDepthBiasFactors(float fSlopeScaleDepthBias, float fDepthBias) = 0;
	virtual void PerformFullScreenStencilOperation(void) = 0;
	virtual void SetLightingOrigin(Vec3 vLightingOrigin) = 0;
	virtual void SetScissorRect(const int nLeft, const int nTop, const int nRight, const int nBottom, const bool bEnableScissor) = 0;
	virtual void BeginMorphAccumulation() = 0;
	virtual void EndMorphAccumulation() = 0;
	virtual void AccumulateMorph(IMorph* pMorph, int nMorphCount, const MorphWeight_t* pWeights) = 0;
	virtual void PushDeformation(DeformationBase_t const* Deformation) = 0;
	virtual void PopDeformation() = 0;
	virtual int	GetNumActiveDeformations() const = 0;
	virtual bool GetMorphAccumulatorTexCoord(Vec2* pTexCoord, IMorph* pMorph, int nVertex) = 0;
	virtual IMesh* GetDynamicMeshEx(VertexFormat_t vertexFormat, bool bBuffered = true,
									IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0, IMaterial* pAutoBind = 0) = 0;
	virtual void FogMaxDensity(float flMaxDensity) = 0;
	virtual IMaterial* GetCurrentMaterial() = 0;
	virtual int  GetCurrentNumBones() const = 0;
	virtual void* GetCurrentProxy() = 0;
	virtual void EnableColorCorrection(bool bEnable) = 0;
	virtual ColorCorrectionHandle_t AddLookup(const char* pName) = 0;
	virtual bool RemoveLookup(ColorCorrectionHandle_t handle) = 0;
	virtual void LockLookup(ColorCorrectionHandle_t handle) = 0;
	virtual void LoadLookup(ColorCorrectionHandle_t handle, const char* pLookupName) = 0;
	virtual void UnlockLookup(ColorCorrectionHandle_t handle) = 0;
	virtual void SetLookupWeight(ColorCorrectionHandle_t handle, float flWeight) = 0;
	virtual void ResetLookupWeights() = 0;
	virtual void SetResetable(ColorCorrectionHandle_t handle, bool bResetable) = 0;
	virtual void SetFullScreenDepthTextureValidityFlag(bool bIsValid) = 0;
	virtual void SetNonInteractivePacifierTexture(ITexture* pTexture, float flNormalizedX, float flNormalizedY, float flNormalizedSize) = 0;
	virtual void SetNonInteractiveTempFullscreenBuffer(ITexture* pTexture, MaterialNonInteractiveMode_t mode) = 0;
	virtual void EnableNonInteractiveMode(MaterialNonInteractiveMode_t mode) = 0;
	virtual void RefreshFrontBufferNonInteractive() = 0;
	virtual void* LockRenderData(int nSizeInBytes) = 0;
	virtual void UnlockRenderData(void* pData) = 0;
	virtual void AddRefRenderData() = 0;
	virtual void ReleaseRenderData() = 0;
	virtual bool IsRenderData(const void* pData) const = 0;
	virtual void PrintfVA(char* fmt, va_list vargs) = 0;
	virtual void Printf(const char* fmt, ...) = 0;
	virtual float Knob(char* knobname, float* setvalue = NULL) = 0;
	virtual void OverrideAlphaWriteEnable(bool bEnable, bool bAlphaWriteEnable) = 0;
	virtual void OverrideColorWriteEnable(bool bOverrideEnable, bool bColorWriteEnable) = 0;
	virtual void ClearBuffersObeyStencilEx(bool bClearColor, bool bClearAlpha, bool bClearDepth) = 0;
	virtual void AsyncCreateTextureFromRenderTarget(ITexture* pSrcRt, const char* pDstName, ImageFormat dstFmt, bool bGenMips, int nAdditionalCreationFlags, IAsyncTextureOperationReceiver* pRecipient, void* pExtraArgs) = 0;
};

struct ShaderStencilState_t
{
	bool                        m_bEnable;
	StencilOperation_t          m_FailOp;
	StencilOperation_t          m_ZFailOp;
	StencilOperation_t          m_PassOp;
	StencilComparisonFunction_t m_CompareFunc;
	int                         m_nReferenceValue;
	uint32_t                      m_nTestMask;
	uint32_t                      m_nWriteMask;

	ShaderStencilState_t()
	{
		m_bEnable = false;
		m_PassOp = m_FailOp = m_ZFailOp = STENCILOPERATION_KEEP;
		m_CompareFunc = STENCILCOMPARISONFUNCTION_ALWAYS;
		m_nReferenceValue = 0;
		m_nTestMask = m_nWriteMask = 0xFFFFFFFF;
	}
	void SetStencilState(IMatRenderContext* pRenderContext)
	{
		pRenderContext->SetStencilEnable(m_bEnable);
		pRenderContext->SetStencilFailOperation(m_FailOp);
		pRenderContext->SetStencilZFailOperation(m_ZFailOp);
		pRenderContext->SetStencilPassOperation(m_PassOp);
		pRenderContext->SetStencilCompareFunction(m_CompareFunc);
		pRenderContext->SetStencilReferenceValue(m_nReferenceValue);
		pRenderContext->SetStencilTestMask(m_nTestMask);
		pRenderContext->SetStencilWriteMask(m_nWriteMask);
	}
};


class IMaterialSystemHardwareConfig;
class MaterialSystem_Config_t;
class MaterialAdapterInfo_t;
class MaterialVideoMode_t;
class ModeChangeCallbackFunc_t;
class MaterialSystemHardwareIdentifier_t;
class HDRType_t;
class MaterialBufferReleaseFunc_t;
class MaterialBufferRestoreFunc_t;
class MaterialSystem_SortInfo_t;
class MaterialLock_t;
class MaterialContextType_t;
class ITextureCompositor;
class IShader;
class IFileList;
typedef unsigned short MaterialHandle_t;

class IMaterialProxy;

class IMaterialProxyFactory
{
public:
	virtual IMaterialProxy* CreateProxy(const char* proxyName) = 0;
	virtual void DeleteProxy(IMaterialProxy* pProxy) = 0;
};

enum MaterialThreadMode_t
{
	MATERIAL_SINGLE_THREADED,
	MATERIAL_QUEUED_SINGLE_THREADED,
	MATERIAL_QUEUED_THREADED
};

enum MaterialRenderTargetDepth_t
{
	MATERIAL_RT_DEPTH_SHARED = 0x0,
	MATERIAL_RT_DEPTH_SEPARATE = 0x1,
	MATERIAL_RT_DEPTH_NONE = 0x2,
	MATERIAL_RT_DEPTH_ONLY = 0x3,
};

enum RenderTargetSizeMode_t
{
	RT_SIZE_NO_CHANGE = 0,
	RT_SIZE_DEFAULT = 1,
	RT_SIZE_PICMIP = 2,
	RT_SIZE_HDR = 3,
	RT_SIZE_FULL_FRAME_BUFFER = 4,
	RT_SIZE_OFFSCREEN = 5,
	RT_SIZE_FULL_FRAME_BUFFER_ROUNDED_UP = 6,
	RT_SIZE_REPLAY_SCREENSHOT = 7,
	RT_SIZE_LITERAL = 8,
	RT_SIZE_LITERAL_PICMIP = 9

};

enum CompiledVtfFlags
{
	TEXTUREFLAGS_POINTSAMPLE = 0x00000001,
	TEXTUREFLAGS_TRILINEAR = 0x00000002,
	TEXTUREFLAGS_CLAMPS = 0x00000004,
	TEXTUREFLAGS_CLAMPT = 0x00000008,
	TEXTUREFLAGS_ANISOTROPIC = 0x00000010,
	TEXTUREFLAGS_HINT_DXT5 = 0x00000020,
	TEXTUREFLAGS_SRGB = 0x00000040,
	TEXTUREFLAGS_NORMAL = 0x00000080,
	TEXTUREFLAGS_NOMIP = 0x00000100,
	TEXTUREFLAGS_NOLOD = 0x00000200,
	TEXTUREFLAGS_ALL_MIPS = 0x00000400,
	TEXTUREFLAGS_PROCEDURAL = 0x00000800,
	TEXTUREFLAGS_ONEBITALPHA = 0x00001000,
	TEXTUREFLAGS_EIGHTBITALPHA = 0x00002000,
	TEXTUREFLAGS_ENVMAP = 0x00004000,
	TEXTUREFLAGS_RENDERTARGET = 0x00008000,
	TEXTUREFLAGS_DEPTHRENDERTARGET = 0x00010000,
	TEXTUREFLAGS_NODEBUGOVERRIDE = 0x00020000,
	TEXTUREFLAGS_SINGLECOPY = 0x00040000,
	TEXTUREFLAGS_STAGING_MEMORY = 0x00080000,
	TEXTUREFLAGS_IMMEDIATE_CLEANUP = 0x00100000,
	TEXTUREFLAGS_IGNORE_PICMIP = 0x00200000,
	TEXTUREFLAGS_UNUSED_00400000 = 0x00400000,
	TEXTUREFLAGS_NODEPTHBUFFER = 0x00800000,
	TEXTUREFLAGS_UNUSED_01000000 = 0x01000000,
	TEXTUREFLAGS_CLAMPU = 0x02000000,
	TEXTUREFLAGS_VERTEXTEXTURE = 0x04000000,
	TEXTUREFLAGS_SSBUMP = 0x08000000,
	TEXTUREFLAGS_UNUSED_10000000 = 0x10000000,
	TEXTUREFLAGS_BORDER = 0x20000000,
	TEXTUREFLAGS_STREAMABLE_COARSE = 0x40000000,
	TEXTUREFLAGS_STREAMABLE_FINE = 0x80000000,
	TEXTUREFLAGS_STREAMABLE = (TEXTUREFLAGS_STREAMABLE_COARSE | TEXTUREFLAGS_STREAMABLE_FINE)
};


#define CREATERENDERTARGETFLAGS_HDR				0x00000001
#define CREATERENDERTARGETFLAGS_AUTOMIPMAP		0x00000002
#define CREATERENDERTARGETFLAGS_UNFILTERABLE_OK 0x00000004

#include "../ConVar/ConVar.h"
#include "../KeyValues/KeyValues.h"

class IMaterialSystem : public IAppSystem
{
public:

	// Placeholder for API revision
	virtual bool Connect(CreateInterfaceFn factory) = 0;
	virtual void Disconnect() = 0;
	virtual void* QueryInterface(const char* pInterfaceName) = 0;
	virtual InitReturnVal_t Init() = 0;
	virtual void Shutdown() = 0;

	//---------------------------------------------------------
	// Initialization and shutdown
	//---------------------------------------------------------

	// Call this to initialize the material system
	// returns a method to create interfaces in the shader dll
	virtual CreateInterfaceFn	Init(char const* pShaderAPIDLL,
									 IMaterialProxyFactory* pMaterialProxyFactory,
									 CreateInterfaceFn fileSystemFactory,
									 CreateInterfaceFn cvarFactory = NULL) = 0;

								 // Call this to set an explicit shader version to use 
								 // Must be called before Init().
	virtual void				SetShaderAPI(char const* pShaderAPIDLL) = 0;

	// Must be called before Init(), if you're going to call it at all...
	virtual void				SetAdapter(int nAdapter, int nFlags) = 0;

	// Call this when the mod has been set up, which may occur after init
	// At this point, the game + gamebin paths have been set up
	virtual void				ModInit() = 0;
	virtual void				ModShutdown() = 0;

	//---------------------------------------------------------
	//
	//---------------------------------------------------------
	virtual void					SetThreadMode(MaterialThreadMode_t mode, int nServiceThread = -1) = 0;
	virtual MaterialThreadMode_t	GetThreadMode() = 0;
	virtual bool					IsRenderThreadSafe() = 0;
	virtual void					ExecuteQueued() = 0;

	//---------------------------------------------------------
	// Config management
	//---------------------------------------------------------

	virtual IMaterialSystemHardwareConfig* GetHardwareConfig(const char* pVersion, int* returnCode) = 0;


	// Call this before rendering each frame with the current config
	// for the material system.
	// Will do whatever is necessary to get the material system into the correct state
	// upon configuration change. .doesn't much else otherwise.
	virtual bool				UpdateConfig(bool bForceUpdate) = 0;

	// Force this to be the config; update all material system convars to match the state
	// return true if lightmaps need to be redownloaded
	virtual bool				OverrideConfig(const MaterialSystem_Config_t& config, bool bForceUpdate) = 0;

	// Get the current config for this video card (as last set by UpdateConfig)
	virtual const MaterialSystem_Config_t& GetCurrentConfigForVideoCard() const = 0;

	// Gets *recommended* configuration information associated with the display card, 
	// given a particular dx level to run under. 
	// Use dxlevel 0 to use the recommended dx level.
	// The function returns false if an invalid dxlevel was specified

	// UNDONE: To find out all convars affected by configuration, we'll need to change
	// the dxsupport.pl program to output all column headers into a single keyvalue block
	// and then we would read that in, and send it back to the client
	virtual bool				GetRecommendedConfigurationInfo(int nDXLevel, KeyValues* pKeyValues) = 0;


	// -----------------------------------------------------------
	// Device methods
	// -----------------------------------------------------------

	// Gets the number of adapters...
	virtual int					GetDisplayAdapterCount() const = 0;

	// Returns the current adapter in use
	virtual int					GetCurrentAdapter() const = 0;

	// Returns info about each adapter
	virtual void				GetDisplayAdapterInfo(int adapter, MaterialAdapterInfo_t& info) const = 0;

	// Returns the number of modes
	virtual int					GetModeCount(int adapter) const = 0;

	// Returns mode information..
	virtual void				GetModeInfo(int adapter, int mode, MaterialVideoMode_t& info) const = 0;

	virtual void				AddModeChangeCallBack(ModeChangeCallbackFunc_t func) = 0;

	// Returns the mode info for the current display device
	virtual void				GetDisplayMode(MaterialVideoMode_t& mode) const = 0;

	// Sets the mode...
	virtual bool				SetMode(void* hwnd, const MaterialSystem_Config_t& config) = 0;

	virtual bool				SupportsMSAAMode(int nMSAAMode) = 0;

	// FIXME: REMOVE! Get video card identitier
	virtual const MaterialSystemHardwareIdentifier_t& GetVideoCardIdentifier(void) const = 0;

	// Use this to spew information about the 3D layer 
	virtual void				SpewDriverInfo() const = 0;

	virtual void				GetDXLevelDefaults(unsigned int& max_dxlevel, unsigned int& recommended_dxlevel) = 0;

	// Get the image format of the back buffer. . useful when creating render targets, etc.
	virtual void				GetBackBufferDimensions(int& width, int& height) const = 0;
	virtual ImageFormat			GetBackBufferFormat() const = 0;

	virtual bool				SupportsHDRMode(HDRType_t nHDRModede) = 0;


	// -----------------------------------------------------------
	// Window methods
	// -----------------------------------------------------------

	// Creates/ destroys a child window
	virtual bool				AddView(void* hwnd) = 0;
	virtual void				RemoveView(void* hwnd) = 0;

	// Sets the view
	virtual void				SetView(void* hwnd) = 0;


	// -----------------------------------------------------------
	// Control flow
	// -----------------------------------------------------------

	virtual void				BeginFrame(float frameTime) = 0;
	virtual void				EndFrame() = 0;
	virtual void				Flush(bool flushHardware = false) = 0;

	/// FIXME: This stuff needs to be cleaned up and abstracted.
	// Stuff that gets exported to the launcher through the engine
	virtual void				SwapBuffers() = 0;

	// Flushes managed textures from the texture cacher
	virtual void				EvictManagedResources() = 0;

	virtual void				ReleaseResources(void) = 0;
	virtual void				ReacquireResources(void) = 0;


	// -----------------------------------------------------------
	// Device loss/restore
	// -----------------------------------------------------------

	// Installs a function to be called when we need to release vertex buffers + textures
	virtual void				AddReleaseFunc(MaterialBufferReleaseFunc_t func) = 0;
	virtual void				RemoveReleaseFunc(MaterialBufferReleaseFunc_t func) = 0;

	// Installs a function to be called when we need to restore vertex buffers
	virtual void				AddRestoreFunc(MaterialBufferRestoreFunc_t func) = 0;
	virtual void				RemoveRestoreFunc(MaterialBufferRestoreFunc_t func) = 0;

	// Release temporary HW memory...
	virtual void				ResetTempHWMemory(bool bExitingLevel = false) = 0;

	// For dealing with device lost in cases where SwapBuffers isn't called all the time (Hammer)
	virtual void				HandleDeviceLost() = 0;


	// -----------------------------------------------------------
	// Shaders
	// -----------------------------------------------------------

	// Used to iterate over all shaders for editing purposes
	// GetShaders returns the number of shaders it actually found
	virtual int					ShaderCount() const = 0;
	virtual int					GetShaders(int nFirstShader, int nMaxCount, IShader** ppShaderList) const = 0;

	// FIXME: Is there a better way of doing this?
	// Returns shader flag names for editors to be able to edit them
	virtual int					ShaderFlagCount() const = 0;
	virtual const char* ShaderFlagName(int nIndex) const = 0;

	// Gets the actual shader fallback for a particular shader
	virtual void				GetShaderFallback(const char* pShaderName, char* pFallbackShader, int nFallbackLength) = 0;


	// -----------------------------------------------------------
	// Material proxies
	// -----------------------------------------------------------

	virtual IMaterialProxyFactory* GetMaterialProxyFactory() = 0;

	// Sets the material proxy factory. Calling this causes all materials to be uncached.
	virtual void				SetMaterialProxyFactory(IMaterialProxyFactory* pFactory) = 0;


	// -----------------------------------------------------------
	// Editor mode
	// -----------------------------------------------------------

	// Used to enable editor materials. Must be called before Init.
	virtual void				EnableEditorMaterials() = 0;


	// -----------------------------------------------------------
	// Stub mode mode
	// -----------------------------------------------------------

	// Force it to ignore Draw calls.
	virtual void				SetInStubMode(bool bInStubMode) = 0;


	//---------------------------------------------------------
	// Debug support
	//---------------------------------------------------------

	virtual void				DebugPrintUsedMaterials(const char* pSearchSubString, bool bVerbose) = 0;
	virtual void				DebugPrintUsedTextures(void) = 0;

	virtual void				ToggleSuppressMaterial(char const* pMaterialName) = 0;
	virtual void				ToggleDebugMaterial(char const* pMaterialName) = 0;


	//---------------------------------------------------------
	// Misc features
	//---------------------------------------------------------
	//returns whether fast clipping is being used or not - needed to be exposed for better per-object clip behavior
	virtual bool				UsingFastClipping(void) = 0;

	virtual int					StencilBufferBits(void) = 0; //number of bits per pixel in the stencil buffer


	//---------------------------------------------------------
	// Material and texture management
	//---------------------------------------------------------

	// uncache all materials. .  good for forcing reload of materials.
	virtual void				UncacheAllMaterials() = 0;

	// Remove any materials from memory that aren't in use as determined
	// by the IMaterial's reference count.
	virtual void				UncacheUnusedMaterials(bool bRecomputeStateSnapshots = false) = 0;

	// Load any materials into memory that are to be used as determined
	// by the IMaterial's reference count.
	virtual void				CacheUsedMaterials() = 0;

	// Force all textures to be reloaded from disk.
	virtual void				ReloadTextures() = 0;

	// Reloads materials
	virtual void				ReloadMaterials(const char* pSubString = NULL) = 0;

	// Create a procedural material. The keyvalues looks like a VMT file
	virtual IMaterial* CreateMaterial(const char* pMaterialName, KeyValues* pVMTKeyValues) = 0;

	// Find a material by name.
	// The name of a material is a full path to 
	// the vmt file starting from "hl2/materials" (or equivalent) without
	// a file extension.
	// eg. "dev/dev_bumptest" refers to somethign similar to:
	// "d:/hl2/hl2/materials/dev/dev_bumptest.vmt"
	//
	// Most of the texture groups for pTextureGroupName are listed in texture_group_names.h.
	// 
	// Note: if the material can't be found, this returns a checkerboard material. You can 
	// find out if you have that material by calling IMaterial::IsErrorMaterial().
	// (Or use the global IsErrorMaterial function, which checks if it's null too).
	virtual IMaterial* FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = NULL) = 0;

	// Query whether a material is loaded (eg, whether FindMaterial will be nonblocking)
	virtual bool				IsMaterialLoaded(char const* pMaterialName) = 0;

	//---------------------------------
	// This is the interface for knowing what materials are available
	// is to use the following functions to get a list of materials.  The
	// material names will have the full path to the material, and that is the 
	// only way that the directory structure of the materials will be seen through this
	// interface.
	// NOTE:  This is mostly for worldcraft to get a list of materials to put
	// in the "texture" browser.in Worldcraft
	virtual MaterialHandle_t	FirstMaterial() const = 0;

	// returns InvalidMaterial if there isn't another material.
	// WARNING: you must call GetNextMaterial until it returns NULL, 
	// otherwise there will be a memory leak.
	virtual MaterialHandle_t	NextMaterial(MaterialHandle_t h) const = 0;

	// This is the invalid material
	virtual MaterialHandle_t	InvalidMaterial() const = 0;

	// Returns a particular material
	virtual IMaterial* GetMaterial(MaterialHandle_t h) const = 0;

	// Get the total number of materials in the system.  These aren't just the used
	// materials, but the complete collection.
	virtual int					GetNumMaterials() const = 0;

	//---------------------------------

	virtual void				SetAsyncTextureLoadCache(void* hFileCache) = 0;

	virtual ITexture* FindTexture(char const* pTextureName, const char* pTextureGroupName, bool complain = true, int nAdditionalCreationFlags = 0) = 0;

	// Checks to see if a particular texture is loaded
	virtual bool				IsTextureLoaded(char const* pTextureName) const = 0;

	// Creates a procedural texture
	virtual ITexture* CreateProceduralTexture(const char* pTextureName,
											  const char* pTextureGroupName,
											  int w,
											  int h,
											  ImageFormat fmt,
											  int nFlags) = 0;

										  //
										  // Render targets
										  //
	virtual void				BeginRenderTargetAllocation() = 0;
	virtual void				EndRenderTargetAllocation() = 0; // Simulate an Alt-Tab in here, which causes a release/restore of all resources

	// Creates a render target
	// If depth == true, a depth buffer is also allocated. If not, then
	// the screen's depth buffer is used.
	// Creates a texture for use as a render target
	virtual ITexture* CreateRenderTargetTexture(int w,
												int h,
												RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
												ImageFormat	format,
												MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED) = 0;

	virtual ITexture* CreateNamedRenderTargetTextureEx(const char* pRTName,				// Pass in NULL here for an unnamed render target.
													   int w,
													   int h,
													   RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
													   ImageFormat format,
													   MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED,
													   unsigned int textureFlags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
													   unsigned int renderTargetFlags = 0) = 0;

	virtual ITexture* CreateNamedRenderTargetTexture(const char* pRTName,
													 int w,
													 int h,
													 RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
													 ImageFormat format,
													 MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED,
													 bool bClampTexCoords = true,
													 bool bAutoMipMap = false) = 0;

												 // Must be called between the above Begin-End calls!
	virtual ITexture* CreateNamedRenderTargetTextureEx2(const char* pRTName,				// Pass in NULL here for an unnamed render target.
														int w,
														int h,
														RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
														ImageFormat format,
														MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED,
														unsigned int textureFlags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
														unsigned int renderTargetFlags = 0) = 0;

													// -----------------------------------------------------------
													// Lightmaps
													// -----------------------------------------------------------

													// To allocate lightmaps, sort the whole world by material twice.
													// The first time through, call AllocateLightmap for every surface.
													// that has a lightmap.
													// The second time through, call AllocateWhiteLightmap for every 
													// surface that expects to use shaders that expect lightmaps.
	virtual void				BeginLightmapAllocation() = 0;
	virtual void				EndLightmapAllocation() = 0;

	// returns the sorting id for this surface
	virtual int 				AllocateLightmap(int width, int height,
												 int offsetIntoLightmapPage[2],
												 IMaterial* pMaterial) = 0;
											 // returns the sorting id for this surface
	virtual int					AllocateWhiteLightmap(IMaterial* pMaterial) = 0;

	// lightmaps are in linear color space
	// lightmapPageID is returned by GetLightmapPageIDForSortID
	// lightmapSize and offsetIntoLightmapPage are returned by AllocateLightmap.
	// You should never call UpdateLightmap for a lightmap allocated through
	// AllocateWhiteLightmap.
	virtual void				UpdateLightmap(int lightmapPageID, int lightmapSize[2],
											   int offsetIntoLightmapPage[2],
											   float* pFloatImage, float* pFloatImageBump1,
											   float* pFloatImageBump2, float* pFloatImageBump3) = 0;

										   // fixme: could just be an array of ints for lightmapPageIDs since the material
										   // for a surface is already known.
	virtual int					GetNumSortIDs() = 0;
	virtual void				GetSortInfo(MaterialSystem_SortInfo_t* sortInfoArray) = 0;

	// Read the page size of an existing lightmap by sort id (returned from AllocateLightmap())
	virtual void				GetLightmapPageSize(int lightmap, int* width, int* height) const = 0;

	virtual void				ResetMaterialLightmapPageInfo() = 0;



	virtual void				ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil = false) = 0;

	// -----------------------------------------------------------
	// X360 specifics
	// -----------------------------------------------------------

#if defined( _X360 )
	virtual void				ListUsedMaterials(void) = 0;
	virtual HXUIFONT			OpenTrueTypeFont(const char* pFontname, int tall, int style) = 0;
	virtual void				CloseTrueTypeFont(HXUIFONT hFont) = 0;
	virtual bool				GetTrueTypeFontMetrics(HXUIFONT hFont, XUIFontMetrics* pFontMetrics, XUICharMetrics charMetrics[256]) = 0;
	// Render a sequence of characters and extract the data into a buffer
	// For each character, provide the width+height of the font texture subrect,
	// an offset to apply when rendering the glyph, and an offset into a buffer to receive the RGBA data
	virtual bool				GetTrueTypeGlyphs(HXUIFONT hFont, int numChars, wchar_t* pWch, int* pOffsetX, int* pOffsetY, int* pWidth, int* pHeight, unsigned char* pRGBA, int* pRGBAOffset) = 0;
	virtual void				PersistDisplay() = 0;
	virtual void* GetD3DDevice() = 0;
	virtual bool				OwnGPUResources(bool bEnable) = 0;
#endif

	// -----------------------------------------------------------
	// Access the render contexts
	// -----------------------------------------------------------
	virtual IMatRenderContext* GetRenderContext() = 0;

	virtual bool				SupportsShadowDepthTextures(void) = 0;
	virtual void				BeginUpdateLightmaps(void) = 0;
	virtual void				EndUpdateLightmaps(void) = 0;

	// -----------------------------------------------------------
	// Methods to force the material system into non-threaded, non-queued mode
	// -----------------------------------------------------------
	virtual MaterialLock_t		Lock() = 0;
	virtual void				Unlock(MaterialLock_t) = 0;

	// Vendor-dependent shadow depth texture format
	virtual ImageFormat			GetShadowDepthTextureFormat() = 0;

	virtual bool				SupportsFetch4(void) = 0;

	// Create a custom render context. Cannot be used to create MATERIAL_HARDWARE_CONTEXT
	virtual IMatRenderContext* CreateRenderContext(MaterialContextType_t type) = 0;

	// Set a specified render context to be the global context for the thread. Returns the prior context.
	virtual IMatRenderContext* SetRenderContext(IMatRenderContext*) = 0;

	virtual bool				SupportsCSAAMode(int nNumSamples, int nQualityLevel) = 0;

	virtual void				RemoveModeChangeCallBack(ModeChangeCallbackFunc_t func) = 0;

	// Finds or create a procedural material.
	virtual IMaterial* FindProceduralMaterial(const char* pMaterialName, const char* pTextureGroupName, KeyValues* pVMTKeyValues) = 0;

	virtual ImageFormat			GetNullTextureFormat() = 0;

	virtual void				AddTextureAlias(const char* pAlias, const char* pRealName) = 0;
	virtual void				RemoveTextureAlias(const char* pAlias) = 0;

	// returns a lightmap page ID for this allocation, -1 if none available
	// frameID is a number that should be changed every frame to prevent locking any textures that are
	// being used to draw in the previous frame
	virtual int					AllocateDynamicLightmap(int lightmapSize[2], int* pOutOffsetIntoPage, int frameID) = 0;

	virtual void				SetExcludedTextures(const char* pScriptName) = 0;
	virtual void				UpdateExcludedTextures(void) = 0;

	virtual bool				IsInFrame() const = 0;

	virtual void				CompactMemory() = 0;

	// For sv_pure mode. The filesystem figures out which files the client needs to reload to be "pure" ala the server's preferences.
	virtual void ReloadFilesInList(IFileList* pFilesToReload) = 0;
	virtual	bool				AllowThreading(bool bAllow, int nServiceThread) = 0;

	// Extended version of FindMaterial().
	// Contains context in so it can make decisions (i.e. if it's a model, ignore certain cheat parameters)
	virtual IMaterial* FindMaterialEx(char const* pMaterialName, const char* pTextureGroupName, int nContext, bool complain = true, const char* pComplainPrefix = NULL) = 0;

#ifdef DX_TO_GL_ABSTRACTION
	virtual void				DoStartupShaderPreloading(void) = 0;
#endif	

	// Sets the override sizes for all render target size tests. These replace the frame buffer size.
	// Set them when you are rendering primarily to something larger than the frame buffer (as in VR mode).
	virtual void				SetRenderTargetFrameBufferSizeOverrides(int nWidth, int nHeight) = 0;

	// Returns the (possibly overridden) framebuffer size for render target sizing.
	virtual void				GetRenderTargetFrameBufferDimensions(int& nWidth, int& nHeight) = 0;

	// returns the display device name that matches the adapter index we were started with
	virtual char* GetDisplayDeviceName() const = 0;
};


#define MATERIAL_SYSTEM_INTERFACE_VERSION		"VMaterialSystem080"

enum class EOverrideType
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};

struct StudioData_t;
struct StudioDecalHandle_t;

struct DrawModelState_t
{
	studiohdr_t* m_pStudioHdr;
	StudioData_t* m_pStudioData;
	void* m_pRenderable;
	const matrix3x4* m_pModelToWorld;
	StudioDecalHandle_t* m_hDecals;
	int					 m_DrawFlags;
	int					 m_Lod;
};

typedef unsigned short ModelInstanceHandle_t;

struct ModelRenderInfo_t
{
	Vec3			      m_vOrigin;
	Vec3			      m_vAngles;
	void* m_pRenderable;
	const model_t* m_pModel;
	const matrix3x4* m_pModelToWorld;
	const matrix3x4* m_pLightingOffset;
	const Vec3* m_pLightingOrigin;
	int				      m_nFlags;
	int				      m_nEntIndex;
	int				      m_nSkin;
	int					  m_nBody;
	int				      m_nHitboxSet;
	ModelInstanceHandle_t m_hMdlInstance;

	ModelRenderInfo_t()
	{
		m_pModelToWorld = NULL;
		m_pLightingOffset = NULL;
		m_pLightingOrigin = NULL;
	}
};


class CModelRender
{
public:
	void ForcedMaterialOverride(IMaterial* mat, EOverrideType type = EOverrideType::OVERRIDE_NORMAL)
	{
		typedef void(__thiscall* FN)(PVOID, IMaterial*, EOverrideType);
		return GetVFunc<FN>(this, 1)(this, mat, type);
	}

	void DrawModelExecute(const DrawModelState_t& pState, const ModelRenderInfo_t& pInfo, matrix3x4* pBoneToWorld)
	{
		typedef void(__thiscall* FN)(PVOID, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4*);
		return GetVFunc<FN>(this, 19)(this, pState, pInfo, pBoneToWorld);
	}
};

#define VENGINE_MODELRENDER_INTERFACE "VEngineModel016"


#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_RUNTIME_COMPOSITE				"Runtime Composite"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

#define STUDIO_NONE						0x00000000
#define STUDIO_RENDER					0x00000001
#define STUDIO_VIEWXFORMATTACHMENTS		0x00000002
#define STUDIO_DRAWTRANSLUCENTSUBMODELS 0x00000004
#define STUDIO_TWOPASS					0x00000008
#define STUDIO_STATIC_LIGHTING			0x00000010
#define STUDIO_WIREFRAME				0x00000020
#define STUDIO_ITEM_BLINK				0x00000040
#define STUDIO_NOSHADOWS				0x00000080
#define STUDIO_WIREFRAME_VCOLLIDE		0x00000100
#define STUDIO_NO_OVERRIDE_FOR_ATTACH	0x00000200

// Not a studio flag, but used to flag when we want studio stats
#define STUDIO_GENERATE_STATS			0x01000000

// Not a studio flag, but used to flag model as using shadow depth material override
#define STUDIO_SSAODEPTHTEXTURE			0x08000000

// Not a studio flag, but used to flag model as using shadow depth material override
#define STUDIO_SHADOWDEPTHTEXTURE		0x40000000

// Not a studio flag, but used to flag model as a non-sorting brush model
#define STUDIO_TRANSPARENCY				0x80000000

#define MAX_SPHERE_QUERY	512