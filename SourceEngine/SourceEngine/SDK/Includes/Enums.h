#pragma once

enum EClientClass
{
	CTFWrench = 230,
	CTFSyringeGun = 214,
	CSniperDot = 94,
	CTFSniperRifle = 212,
	CTFSMG_Medic = 210,
	CTFSMG_Scout = 211,
	CTFSMG = 209,
	CTFShovel = 208,
	CTFShotgun_Scout = 206,
	CTFShotgun_Pyro = 205,
	CTFShotgun_HWG = 204,
	CTFShotgun_Soldier = 207,
	CTFShotgun = 203,
	CTFRocketLauncher = 202,
	CTFRevolver = 201,
	CTFPistol_Spy = 194,
	CTFPistol = 193,
	CTFPipebombLauncher = 192,
	CTFWeaponPDA_Spy = 229,
	CTFWeaponPDA_Engineer_Destroy = 228,
	CTFWeaponPDA_Engineer_Build = 227,
	CTFWeaponPDA = 226,
	CTFMinigun = 188,
	CWeaponMedigun = 238,
	CTFKnife = 187,
	CTFWeaponInvis = 225,
	CTFGrenadeLauncher = 175,
	CTFFlameThrower = 164,
	CTFCubemap = 163,
	CTFClub = 162,
	CTFBottle = 160,
	CTFBat = 159,
	CTFWeaponBuilder = 224,
	CTFBaseRocket = 158,
	CTFWeaponBaseMelee = 223,
	CTFWeaponBaseGun = 222,
	CTFWeaponBaseGrenadeProj = 221,
	CTFWeaponBase = 219,
	CTFBaseProjectile = 157,
	CTFProjectile_FlameRocket = 197,
	CTFProjectile_Rocket = 198,
	CTFViewModel = 218,
	CBaseObjectUpgrade = 10,
	CTFItem = 186,
	CTFGameRulesProxy = 165,
	CTETFParticleEffect = 154,
	CTETFExplosion = 153,
	CCaptureFlagReturnIcon = 23,
	CCaptureFlag = 22,
	CTFTeam = 215,
	CTFPlayerResource = 196,
	CTFPlayer = 195,
	CTFRagdoll = 200,
	CTEPlayerAnimEvent = 141,
	CTFObjectiveResource = 190,
	CTEFireBullets = 129,
	CTFAmmoPack = 156,
	CObjectTeleporter = 70,
	CObjectSentrygun = 68,
	CTFProjectile_SentryRocket = 199,
	CObjectSapper = 67,
	CObjectCartDispenser = 65,
	CObjectDispenser = 66,
	CFuncRespawnRoomVisualizer = 54,
	CFuncRespawnRoom = 53,
	CCaptureZone = 24,
	CBaseObject = 9,
	CTestTraceline = 152,
	CTEWorldDecal = 155,
	CTESpriteSpray = 150,
	CTESprite = 149,
	CTESparks = 148,
	CTESmoke = 147,
	CTEShowLine = 145,
	CTEProjectedDecal = 143,
	CTEPlayerDecal = 142,
	CTEPhysicsProp = 140,
	CTEParticleSystem = 139,
	CTEMuzzleFlash = 138,
	CTELargeFunnel = 136,
	CTEKillPlayerAttachments = 135,
	CTEImpact = 134,
	CTEGlowSprite = 133,
	CTEShatterSurface = 144,
	CTEFootprintDecal = 131,
	CTEFizz = 130,
	CTEExplosion = 128,
	CTEEnergySplash = 127,
	CTEEffectDispatch = 126,
	CTEDynamicLight = 125,
	CTEDecal = 123,
	CTEClientProjectile = 122,
	CTEBubbleTrail = 121,
	CTEBubbles = 120,
	CTEBSPDecal = 119,
	CTEBreakModel = 118,
	CTEBloodStream = 117,
	CTEBloodSprite = 116,
	CTEBeamSpline = 115,
	CTEBeamRingPoint = 114,
	CTEBeamRing = 113,
	CTEBeamPoints = 112,
	CTEBeamLaser = 111,
	CTEBeamFollow = 110,
	CTEBeamEnts = 109,
	CTEBeamEntPoint = 108,
	CTEBaseBeam = 107,
	CTEArmorRicochet = 106,
	CTEMetalSparks = 137,
	CSteamJet = 99,
	CSmokeStack = 93,
	DustTrail = 240,
	CFireTrail = 42,
	SporeTrail = 246,
	SporeExplosion = 245,
	RocketTrail = 243,
	SmokeTrail = 244,
	CPropVehicleDriveable = 85,
	ParticleSmokeGrenade = 242,
	CParticleFire = 71,
	MovieExplosion = 241,
	CTEGaussExplosion = 132,
	CEnvQuadraticBeam = 36,
	CEmbers = 29,
	CEnvWind = 40,
	CPrecipitation = 84,
	CBaseTempEntity = 16,
	CTFUmbrella = 217,
	CTFTranq = 216,
	CTFSyringe = 213,
	CTFPipe = 191,
	CTFNailgun = 189,
	CTFBrandingIron = 161,
	CTFGrenadePipebombProjectile = 185,
	CTFGrenadeNormalProjectile = 184,
	CTFGrenadeNormal = 183,
	CTFGrenadeNapalmEffect = 181,
	CTFGrenadeNapalmProjectile = 182,
	CTFGrenadeNapalm = 180,
	CTFGrenadeNailProjectile = 179,
	CTFGrenadeNail = 178,
	CTFGrenadeMirvProjectile = 177,
	CTFGrenadeMirv = 176,
	CTFGrenadeHeal = 174,
	CTFGasGrenadeEffect = 166,
	CTFGrenadeGasProjectile = 173,
	CTFGrenadeGas = 172,
	CTFGrenadeEmp = 171,
	CTFGrenadeConcussionProjectile = 170,
	CTFGrenadeConcussion = 169,
	CTFGrenadeCaltropProjectile = 168,
	CTFGrenadeCaltrop = 167,
	CTFWeaponBaseGrenade = 220,
	CObjectSpawnroomTurret = 69,
	CTeamControlPoint = 102,
	CWeaponIFMSteadyCam = 237,
	CWeaponIFMBaseCamera = 236,
	CWeaponIFMBase = 235,
	CHandleTest = 59,
	CTeamplayRoundBasedRulesProxy = 103,
	CTeamRoundTimer = 104,
	CSpriteTrail = 98,
	CSpriteOriented = 97,
	CSprite = 96,
	CRagdollPropAttached = 88,
	CRagdollProp = 87,
	CPoseController = 83,
	CGameRulesProxy = 58,
	CInfoLadderDismount = 60,
	CFuncLadder = 49,
	CEnvDetailController = 33,
	CWorld = 239,
	CWaterLODControl = 234,
	CWaterBullet = 233,
	CVoteController = 232,
	CVGuiScreen = 231,
	CPropJeep = 0,
	CPropVehicleChoreoGeneric = 0,
	CTest_ProxyToggle_Networkable = 151,
	CTesla = 146,
	CTeamTrainWatcher = 105,
	CBaseTeamObjectiveResource = 15,
	CTeam = 101,
	CSun = 100,
	CParticlePerformanceMonitor = 72,
	CSpotlightEnd = 95,
	CSlideshowDisplay = 92,
	CShadowControl = 91,
	CSceneEntity = 90,
	CRopeKeyframe = 89,
	CRagdollManager = 86,
	CPhysicsPropMultiplayer = 77,
	CPhysBoxMultiplayer = 75,
	CBasePropDoor = 14,
	CDynamicProp = 28,
	CPointCommentaryNode = 82,
	CPointCamera = 81,
	CPlayerResource = 80,
	CPlasma = 79,
	CPhysMagnet = 78,
	CPhysicsProp = 76,
	CPhysBox = 74,
	CParticleSystem = 73,
	CMaterialModifyControl = 64,
	CLightGlow = 63,
	CInfoOverlayAccessor = 62,
	CFuncTrackTrain = 57,
	CFuncSmokeVolume = 56,
	CFuncRotating = 55,
	CFuncReflectiveGlass = 52,
	CFuncOccluder = 51,
	CFuncMonitor = 50,
	CFunc_LOD = 46,
	CTEDust = 124,
	CFunc_Dust = 45,
	CFuncConveyor = 48,
	CBreakableSurface = 21,
	CFuncAreaPortalWindow = 47,
	CFish = 43,
	CEntityFlame = 31,
	CFireSmoke = 41,
	CEnvTonemapController = 39,
	CEnvScreenEffect = 37,
	CEnvScreenOverlay = 38,
	CEnvProjectedTexture = 35,
	CEnvParticleScript = 34,
	CFogController = 44,
	CEntityParticleTrail = 32,
	CEntityDissolve = 30,
	CDynamicLight = 27,
	CColorCorrectionVolume = 26,
	CColorCorrection = 25,
	CBreakableProp = 20,
	CBasePlayer = 12,
	CBaseFlex = 7,
	CBaseEntity = 6,
	CBaseDoor = 5,
	CBaseCombatCharacter = 3,
	CBaseAnimatingOverlay = 2,
	CBoneFollower = 19,
	CBaseAnimating = 1,
	CInfoLightingRelative = 61,
	CAI_BaseNPC = 0,
	CBeam = 18,
	CBaseViewModel = 17,
	CBaseProjectile = 13,
	CBaseParticleEntity = 11,
	CBaseGrenade = 8,
	CBaseCombatWeapon = 4,
};

enum EClassNumbers
{
	CLASS_SCOUT = 1,
	CLASS_SNIPER,
	CLASS_SOLDIER,
	CLASS_DEMO,
	CLASS_MEDIC,
	CLASS_HEAVY,
	CLASS_PYRO,
	CLASS_SPY,
	CLASS_ENGINEER
};

enum ETFHitboxes
{
	HITBOX_HEAD,
	HITBOX_PELVIS,
	HITBOX_SPINE_0,
	HITBOX_SPINE_1,
	HITBOX_SPINE_2,
	HITBOX_SPINE_3,
	HITBOX_UPPERARM_L,
	HITBOX_LOWERARM_L,
	HITBOX_HAND_L,
	HITBOX_UPPERARM_R,
	HITBOX_LOWERARM_R,
	HITBOX_HAND_R,
	HITBOX_HIP_L,
	HITBOX_KNEE_L,
	HITBOX_FOOT_L,
	HITBOX_HIP_R,
	HITBOX_KNEE_R,
	HITBOX_FOOT_R,
	HITBOX_MAX
};

enum EWeaponSlots
{
	SLOT_PRIMARY,
	SLOT_SECONDARY,
	SLOT_MELEE
};


enum class TraceType_t
{
	TRACE_EVERYTHING,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

enum SurfaceFlags_t
{
	DISPSURF_FLAG_SURFACE          = (1 << 0),
	DISPSURF_FLAG_WALKABLE         = (1 << 1),
	DISPSURF_FLAG_BUILDABLE        = (1 << 2),
	DISPSURF_FLAG_SURFPROP1        = (1 << 3),
	DISPSURF_FLAG_SURFPROP2        = (1 << 4),
};

enum class FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT              = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT           = 2,
};

enum class ClientFrameStage_t
{
	FRAME_UNDEFINED                = -1,
	FRAME_START,

	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,

	FRAME_RENDER_START,
	FRAME_RENDER_END
};

enum StereoEye_t
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};

enum PlayerControls_t
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_AL1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),
	IN_SPEED = (1 << 17),
	IN_WALK = (1 << 18),
	IN_ZOOM = (1 << 19),
	IN_WEAPON1 = (1 << 20),
	IN_WEAPON2 = (1 << 21),
	IN_BULLRUSH = (1 << 22),
	IN_GRENADE1 = (1 << 23),
	IN_GRENADE2 = (1 << 24),
	IN_ATTACK3 = (1 << 25),
};

enum class ConVarFlags_t
{
	FCVAR_NONE = 0, // The default, no flags at all

	FCVAR_UNREGISTERED = (1 << 0), // If this is set, don't add to linked list, etc.
	FCVAR_DEVELOPMENT_ONLY = (1 << 1), // Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
	FCVAR_GAME_DLL = (1 << 2), // defined by the game DLL
	FCVAR_CLIENT_DLL = (1 << 3), // defined by the client DLL
	FCVAR_HIDDEN = (1 << 4), // Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.

	FCVAR_PROTECTED = (1 << 5),  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
	FCVAR_SP_ONLY = (1 << 6),  // This cvar cannot be changed by clients connected to a multiplayer server.
	FCVAR_ARCHIVE = (1 << 7),  // set to cause it to be saved to vars.rc
	FCVAR_NOTIFY = (1 << 8),  // notifies players when changed
	FCVAR_USER_INFO = (1 << 9),  // changes the client's info string
	FCVAR_CHEAT = (1 << 14), // Only useable in singleplayer / debug / multiplayer & sv_cheats

	FCVAR_PRINTABLE_ONLY = (1 << 10), // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
	FCVAR_UN_LOGGED = (1 << 11), // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
	FCVAR_NEVER_AS_STRING = (1 << 12), // never try to print that cvar

	FCVAR_REPLICATED = (1 << 13), // server setting enforced on clients, TODO rename to FCAR_SERVER at some time
	FCVAR_DEMO = (1 << 16), // record this cvar when starting a demo file
	FCVAR_DONT_RECORD = (1 << 17), // don't record these command in demofiles
	FCVAR_RELOAD_MATERIALS = (1 << 20), // If this cvar changes, it forces a material reload
	FCVAR_RELOAD_TEXTURES = (1 << 21), // If this cvar changes, if forces a texture reload

	FCVAR_NOT_CONNECTED = (1 << 22), // cvar cannot be changed by a client that is connected to a server
	FCVAR_MATERIAL_SYSTEM_THREAD = (1 << 23), // Indicates this cvar is read from the material system thread
	FCVAR_ARCHIVE_XBOX = (1 << 24), // cvar written to config.cfg on the Xbox

	FCVAR_ACCESSIBLE_FROM_THREADS = (1 << 25), // used as a debugging tool necessary to check material system thread convars

	FCVAR_SERVER_CAN_EXECUTE = (1 << 28), // the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
	FCVAR_SERVER_CANNOT_QUERY = (1 << 29), // If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
	FCVAR_CLIENT_CMD_CAN_EXECUTE = (1 << 30), // IVEngineClient::ClientCmd is allowed to execute this command.

	FCVAR_MATERIAL_THREAD_MASK = (FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD)
};

enum RenderGroup_t
{
	RENDER_GROUP_OPAQUE_STATIC_HUGE = 0,		// Huge static prop
	RENDER_GROUP_OPAQUE_ENTITY_HUGE = 1,		// Huge opaque entity
	RENDER_GROUP_OPAQUE_STATIC = RENDER_GROUP_OPAQUE_STATIC_HUGE + (4 - 1) * 2, //RENDER_GROUP_CFG_NUM_OPAQUE_ENT_BUCKETS = 4
	RENDER_GROUP_OPAQUE_ENTITY,					// Opaque entity (smallest size, or default)

	RENDER_GROUP_TRANSLUCENT_ENTITY,
	RENDER_GROUP_TWOPASS,						// Implied opaque and translucent in two passes
	RENDER_GROUP_VIEW_MODEL_OPAQUE,				// Solid weapon view models
	RENDER_GROUP_VIEW_MODEL_TRANSLUCENT,		// Transparent overlays etc

	RENDER_GROUP_OPAQUE_BRUSH,					// Brushes

	RENDER_GROUP_OTHER,							// Unclassfied. Won't get drawn.

	// This one's always gotta be last
	RENDER_GROUP_COUNT
};

enum FontFlags_t
{
	FONTFLAG_NONE = 0x000,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400
};

enum VGuiPanel_t
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

enum PaintMode_t
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
	PAINT_CURSOR = (1 << 2)
};

enum EObserverModes
{
	OBS_MODE_NONE = 0,		// not in spectator mode
	OBS_MODE_DEATHCAM,		// special mode for death cam animation
	OBS_MODE_FREEZECAM,		// zooms to a target, and freeze-frames on them
	OBS_MODE_FIXED,			// view from a fixed camera position
	OBS_MODE_FIRSTPERSON,	// follow a player in first person view
	OBS_MODE_THIRDPERSON,	// follow a player in third person view
	OBS_MODE_ROAMING,		// free roaming
};