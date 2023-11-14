#define DECLARE_F(x, addr) \
x##_t x = (x##_t)(addr)

#define DEFINE_F(return_type, x, ...) \
typedef return_type (*x##_t)(__VA_ARGS__); \
extern x##_t x

#define VectorLength xtn_VectorLength
#define ProjectPointOnPlane xtn_ProjectPointOnPlane
#define MatrixMultiply xtn_MatrixMultiply
#define Q_rsqrt xtn_Q_rsqrt
#define AngleSubtract xtn_AngleSubtract
#define Q_rand xtn_Q_rand
#define AngleNormalize180 xtn_AngleNormalize180
#define Q_random xtn_Q_random
#define AngleVectors xtn_AngleVectors
#define RotatePointAroundVector xtn_RotatePointAroundVector
#define AngleNormalize360 xtn_AngleNormalize360
#define VectorNormalize xtn_VectorNormalize
#define PerpendicularVector xtn_PerpendicularVector
#define _Cmd_AddCommand xtn__Cmd_AddCommand
#define _VectorLengthSquared xtn__VectorLengthSquared
#define Q_strupr xtn_Q_strupr
#define Cmd_AddCommand xtn_Cmd_AddCommand
#define CoDExtended xtn_CoDExtended
#define _AnglesSubtract xtn__AnglesSubtract
#define _AngleNormalize180 xtn__AngleNormalize180
#define crash_handler xtn_crash_handler
#define COM_BitClear xtn_COM_BitClear
#define cl_allowDownload xtn_cl_allowDownload
#define SV_GentityNum xtn_SV_GentityNum
#define uCoDExtended xtn_uCoDExtended
#define BG_EvaluateTrajectory xtn_BG_EvaluateTrajectory
#define sv_showloss xtn_sv_showloss
#define _MatrixMultiply xtn__MatrixMultiply
#define _VectorLength xtn__VectorLength
#define _vectoangles xtn__vectoangles
#define sv_running xtn_sv_running
#define _AngleNormalize360 xtn__AngleNormalize360
#define SV_ConnectionlessPacket xtn_SV_ConnectionlessPacket
#define NET_AdrToString xtn_NET_AdrToString
#define BigLong xtn_BigLong
#define va xtn_va
#define _AngleSubtract xtn__AngleSubtract
#define _DistanceSquared xtn__DistanceSquared
#define g_gametype xtn_g_gametype
#define sv_floodProtect xtn_sv_floodProtect
#define _Distance xtn__Distance
#define MSG_BeginReading xtn_MSG_BeginReading
#define is_good_string xtn_is_good_string
#define _RotateAroundDirection xtn__RotateAroundDirection
#define _RadiusFromBounds xtn__RadiusFromBounds
#define _ClampChar xtn__ClampChar
#define sv_allowAnonymous xtn_sv_allowAnonymous
#define startsWith xtn_startsWith
#define rconPassword xtn_rconPassword
#define _ClearBounds xtn__ClearBounds
#define _VectorNormalize xtn__VectorNormalize
#define SV_VerifyPaks_f xtn_SV_VerifyPaks_f
#define _VectorInverse xtn__VectorInverse
#define Info_SetValueForKey xtn_Info_SetValueForKey
#define _AngleMod xtn__AngleMod
#define Scr_GetAnim xtn_Scr_GetAnim
#define _DirToByte xtn__DirToByte
#define filesize xtn_filesize
#define LittleShort xtn_LittleShort
#define _AngleDelta xtn__AngleDelta
#define Info_RemoveKey_Big xtn_Info_RemoveKey_Big
#define sv_padPackets xtn_sv_padPackets
#define Q_CleanStr xtn_Q_CleanStr
#define protocol xtn_protocol
#define codextended_module_load xtn_codextended_module_load
#define stricmp xtn_stricmp
#define FS_FileIsInPAK xtn_FS_FileIsInPAK
#define sv_showAverageBPS xtn_sv_showAverageBPS
#define _PREFX xtn__PREFX
#define _AxisClear xtn__AxisClear
#define masterAddress xtn_masterAddress
#define Q_strrchr xtn_Q_strrchr
#define sv_pure xtn_sv_pure
#define Cmd_TokenizeString xtn_Cmd_TokenizeString
#define COD_Destructor xtn_COD_Destructor
#define COM_BitCheck xtn_COM_BitCheck
#define dedicated xtn_dedicated
#define LittleLong xtn_LittleLong
#define sv_showCommands xtn_sv_showCommands
#define Com_sprintf xtn_Com_sprintf
#define sv_maxRate xtn_sv_maxRate
#define Scr_Continue xtn_Scr_Continue
#define _ColorBytes3 xtn__ColorBytes3
#define pml xtn_pml
#define _ColorBytes4 xtn__ColorBytes4
#define check_filex xtn_check_filex
#define Scr_AddSourceBuffer xtn_Scr_AddSourceBuffer
#define _VectorRotate xtn__VectorRotate
#define Cmd_ArgvBuffer xtn_Cmd_ArgvBuffer
#define g_entities xtn_g_entities
#define sv_killserver xtn_sv_killserver
#define _VectorNormalize2 xtn__VectorNormalize2
#define BigFloat xtn_BigFloat
#define Scr_GetAnimsIndex xtn_Scr_GetAnimsIndex
#define shortversion xtn_shortversion
#define modNames xtn_modNames
#define _MakeNormalVectors xtn__MakeNormalVectors
#define sv_timeout xtn_sv_timeout
#define Cvar_VariableString xtn_Cvar_VariableString
#define SV_DropClient xtn_SV_DropClient
#define _AnglesToAxis xtn__AnglesToAxis
#define _GetPerpendicularViewVector xtn__GetPerpendicularViewVector
#define Q_isalpha xtn_Q_isalpha
#define sv_master1 xtn_sv_master1
#define sv_master2 xtn_sv_master2
#define sv_master3 xtn_sv_master3
#define sv_master4 xtn_sv_master4
#define sv_master5 xtn_sv_master5
#define Scr_GetCustomFunction xtn_Scr_GetCustomFunction
#define _Q_rsqrt xtn__Q_rsqrt
#define Q_strcat xtn_Q_strcat
#define T_LinkEntity xtn_T_LinkEntity
#define Q_isforfilename xtn_Q_isforfilename
#define Q_islower xtn_Q_islower
#define get_client_number xtn_get_client_number
#define MSG_ReadLong xtn_MSG_ReadLong
#define sv_onlyVisibleClients xtn_sv_onlyVisibleClients
#define Huff_Decompress xtn_Huff_Decompress
#define _AngleVectors xtn__AngleVectors
#define _ByteToDir xtn__ByteToDir
#define g_clients xtn_g_clients
#define _PerpendicularVector xtn__PerpendicularVector
#define VM_Call xtn_VM_Call
#define T_UnlinkEntity xtn_T_UnlinkEntity
#define sv_maxclients xtn_sv_maxclients
#define SV_ExecuteClientMessage xtn_SV_ExecuteClientMessage
#define _Q_fabs xtn__Q_fabs
#define BG_EvaluateTrajectoryDelta xtn_BG_EvaluateTrajectoryDelta
#define Cbuf_Init xtn_Cbuf_Init
#define T_SetBrushModel xtn_T_SetBrushModel
#define SV_DirectConnect xtn_SV_DirectConnect
#define _RotatePointAroundVector xtn__RotatePointAroundVector
#define sv_mapRotationCurrent xtn_sv_mapRotationCurrent
#define xentities xtn_xentities
#define Sys_GetPacket xtn_Sys_GetPacket
#define sv_minPing xtn_sv_minPing
#define codextended_load xtn_codextended_load
#define set_game_ptr xtn_set_game_ptr
#define Com_Printf xtn_Com_Printf
#define setuserinfo xtn_setuserinfo
#define Scr_GetCustomMethod xtn_Scr_GetCustomMethod
#define Q_strncmp xtn_Q_strncmp
#define sv_mapRotation xtn_sv_mapRotation
#define Q_stristr xtn_Q_stristr
#define BigShort xtn_BigShort
#define Q_strlwr xtn_Q_strlwr
#define sv_maxPing xtn_sv_maxPing
#define Q_isprint xtn_Q_isprint
#define sv_allowDownload xtn_sv_allowDownload
#define SV_AuthorizeIpPacket xtn_SV_AuthorizeIpPacket
#define getclient xtn_getclient
#define _Q_random xtn__Q_random
#define level xtn_level
#define _AxisCopy xtn__AxisCopy
#define sv_serverid xtn_sv_serverid
#define pm xtn_pm
#define Cmd_Argc xtn_Cmd_Argc
#define _AddPointToBounds xtn__AddPointToBounds
#define _LerpAngle xtn__LerpAngle
#define Q_stricmp xtn_Q_stricmp
#define Com_Error xtn_Com_Error
#define _NormalizeColor xtn__NormalizeColor
#define _LerpPosition xtn__LerpPosition
#define mapname xtn_mapname
#define gamelib xtn_gamelib
#define Cmd_Argv xtn_Cmd_Argv
#define base xtn_base
#define _VectorDistance xtn__VectorDistance
#define _vectoyaw xtn__vectoyaw
#define _Q_crandom xtn__Q_crandom
#define str_replace xtn_str_replace
#define _ProjectPointOntoVector xtn__ProjectPointOntoVector
#define Info_Print xtn_Info_Print
#define Q_stricmpn xtn_Q_stricmpn
#define sv_fps xtn_sv_fps
#define authorizeAddress xtn_authorizeAddress
#define Q_isnumeric xtn_Q_isnumeric
#define _VectorCompare xtn__VectorCompare
#define COM_BitSet xtn_COM_BitSet
#define sv_zombietime xtn_sv_zombietime
#define sv_privatePassword xtn_sv_privatePassword
#define Sys_LoadDll xtn_Sys_LoadDll
#define _end xtn__end
#define Q_strncpyz xtn_Q_strncpyz
#define LittleFloat xtn_LittleFloat
#define _ClampShort xtn__ClampShort
#define Info_RemoveKey xtn_Info_RemoveKey
#define NET_StringToAdr xtn_NET_StringToAdr
#define Cvar_Get xtn_Cvar_Get
#define sv_hostname xtn_sv_hostname
#define sv_privateClients xtn_sv_privateClients
#define _Vector4Scale xtn__Vector4Scale
#define clients xtn_clients
#define Info_SetValueForKey_Big xtn_Info_SetValueForKey_Big
#define Info_ValueForKey xtn_Info_ValueForKey
#define Q_isalphanumeric xtn_Q_isalphanumeric
#define getuserinfo xtn_getuserinfo
#define NET_OutOfBandPrint xtn_NET_OutOfBandPrint
#define Q_isupper xtn_Q_isupper
#define sv_reconnectlimit xtn_sv_reconnectlimit
#define _ProjectPointOnPlane xtn__ProjectPointOnPlane
#define SV_Init xtn_SV_Init
#define sv_master xtn_sv_master
#define _Q_rand xtn__Q_rand
#define Cvar_Set xtn_Cvar_Set
