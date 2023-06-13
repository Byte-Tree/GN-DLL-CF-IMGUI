#pragma once

struct m_D2DCoordinate
{
	float x;
	float y;
};

struct m_D3DCoordinate
{
	float x;
	float y;
	float z;
};

struct ScreenCoordinates
{
	__int64 X;
	__int64 Y;
	__int64 W;
	__int64 H;
};

//范围追踪部位宏
#define RANGE_TRACK_POSITION_GOLDEN_HEAD 0x41000000		//金头
#define RANGE_TRACK_POSITION_SILVER_HEAD 0x41880000		//银头
#define RANGE_TRACK_POSITION_NECK 0x41140000			//颈部
#define RANGE_TRACK_POSITION_CLAVICLE 0x41900000		//锁骨
#define RANGE_TRACK_POSITION_HAND 0x41200000			//手
#define RANGE_TRACK_POSITION_FOOT 0x41400000			//脚

//瞄准部位宏
#define AIM_POSITION_HEAD	1
#define AIM_POSITION_BODY	0

//瞄准热键宏
#define AIM_HOTKEY_MOUSE_LEFT			0
#define AIM_HOTKEY_MOUSE_RIGHT			1
#define AIM_HOTKEY_KEYBOARD_ALT			2

//游戏障碍判断结构
typedef struct _IntersectInfo
{
	float vImpactPosX;
	float vImpactPosY;
	float vImpactPosZ;
	char spacer00[32];
	__int64 hObjImpact;
	unsigned long unk1;
	unsigned long unk2;
	unsigned long unk3;
}IntersectInfo;
typedef struct _IntersectQuery
{
	float m_FromX;
	float m_FromY;
	float m_FromZ;
	float m_ToX;
	float m_ToY;
	float m_ToZ;
	__int64 m_Flags;
	void* m_FilterFn;
	__int64 m_FilterActualIntersectFn;
	__int64 m_PolyFilterFn;
	void* m_pUserData;
	void* m_pActualIntersectUserData;
}IntersectQuery;

struct HookFuncAddress
{
	/////////////////////////////////////Hook静步加速/////////////////////////////////////
	BYTE OriginalStaticAccelerationCode[14];		//静步加速原始代码
	__int64 MyStaticAccelerationAddress;			//我的静步加速地址
	__int64 StaticAccelerationHookAddress;			//静步加速Hook地址
	__int64 StaticAccelerationHookRetAddress;		//静步加速Hook返回地址
	__int64 StaticAccelerationValueAddress;			//静步加速值
	/////////////////////////////////////Hook下蹲加速/////////////////////////////////////
	BYTE OriginalSquatAccelerationCode[14];			//下蹲加速原始代码
	__int64 MySquatAccelerationAddress;				//我的下蹲加速地址
	__int64 SquatAccelerationHookAddress;			//下蹲加速Hook地址
	__int64 SquatAccelerationHookRetAddress;		//下蹲加速Hook返回地址
	__int64 SquatAccelerationValueAddress;			//下蹲加速值
	/////////////////////////////////////Hook静态无后/////////////////////////////////////
	BYTE OriginalBulletWithoutBackSeatCode[14];		//静态无后原始代码
	__int64 MyBulletWithoutBackSeatAddress;			//我的静态无后地址
	__int64 BulletWithoutBackSeatHookAddress;		//静态无后Hook地址
	__int64 BulletWithoutBackSeatHookRetAddress;	//静态无后Hook返回地址
	__int64 BulletWithoutBackSeatValueAddress;		//静态无后值
	/////////////////////////////////////Hook左键千刀/////////////////////////////////////
	BYTE OriginalLeftKnifeCode[14];					//左键千刀原始代码
	__int64 MyLeftKnifeAddress;						//我的左键千刀地址
	__int64 LeftKnifeHookAddress;					//左键千刀Hook地址
	__int64 LeftKnifeHookRetAddress;				//左键千刀Hook返回地址
	__int64 LeftKnifeValueAddress;					//左键千刀值
	/////////////////////////////////////Hook右键千刀/////////////////////////////////////
	BYTE OriginalRightKnifeCode[14];				//右键千刀原始代码
	__int64 MyRightKnifeAddress;					//我的右键千刀地址
	__int64 RightKnifeHookAddress;					//右键千刀Hook地址
	__int64 RightKnifeHookRetAddress;				//右键千刀Hook返回地址
	__int64 RightKnifeCallAddress;					//右键千刀Call地址
	__int64 RightKnifeValueAddress;					//右键千刀值
	/////////////////////////////////////Hook空格连跳/////////////////////////////////////
	BYTE OriginalSpaceJumpCode[14];					//空格连跳原始代码
	__int64 MySpaceJumpAddress;						//我的空格连跳地址
	__int64 SpaceJumpHookAddress;					//空格连跳Hook地址
	__int64 SpaceJumpHookRetAddress;				//空格连跳Hook返回地址
	__int64 SpaceJumpValueAddress;					//空格连跳值
	///////////////////////////////////Hook零秒换弹新图///////////////////////////////////
	BYTE OriginalZeroBulletChangeCode_NewMap[14];	//零秒换弹新图原始代码
	__int64 MyZeroBulletChange_NewMapAddress;		//我的零秒换弹新图地址
	__int64 ZeroBulletChange_NewMapHookAddress;		//零秒换弹新图Hook地址
	__int64 ZeroBulletChange_NewMapHookRetAddress;	//零秒换弹新图Hook返回地址
	__int64 ZeroBulletChange_NewMapValueAddress;	//零秒换弹新图值
	///////////////////////////////////Hook零秒换弹旧图///////////////////////////////////
	BYTE OriginalZeroBulletChangeCode_OldMap[14];	//零秒换弹旧图原始代码
	__int64 MyZeroBulletChange_OldMapAddress;		//我的零秒换弹旧图地址
	__int64 ZeroBulletChange_OldMapHookAddress;		//零秒换弹旧图Hook地址
	__int64 ZeroBulletChange_OldMapHookRetAddress;	//零秒换弹旧图Hook返回地址
	__int64 ZeroBulletChange_OldMapValueAddress;	//零秒换弹旧图值
	/////////////////////////////////////Hook人物穿墙/////////////////////////////////////
	BYTE OriginalThroughTheWallCode[14];			//人物穿墙原始代码
	__int64 MyThroughTheWallAddress;				//我的人物穿墙地址
	__int64 ThroughTheWallHookAddress;				//人物穿墙Hook地址
	__int64 ThroughTheWallHookRetAddress;			//人物穿墙Hook返回地址
	__int64 ThroughTheWallValueAddress;				//人物穿墙值

};

struct BaseAddress
{
	__int64 Cshell;
	__int64 CshellEndAddress;
	__int64 ACE_BASE64;
	__int64 ACE_BASE64End;
	__int64 ACE_PBC_GAME64;
	__int64 ACE_PBC_GAME64End;
	__int64 ACE_ATS64;
	__int64 ACE_DRV64;
	__int64 ACE_GDP64;
	__int64 ACE_GDP64End;
	__int64 ACE_DFS64;
	__int64 ACE_CSI64;
	__int64 ACE_CSI64End;
	__int64 ACE_MMS64;
	__int64 SGuard64;
	__int64 ACE_GDPServer64;
	__int64 ACE_Tips64;
	__int64 TerSafe;
	__int64 D3D9;
	__int64 D3D9End;
	__int64 dxgi;
	__int64 dxgiEnd;
	__int64 MySelfDLL;							//自身DLL
	__int64 Cross;
	__int64 CrossEndAddress;
	__int64 CrossFireBase;
	__int64 PlayerArray;						//玩家数组
	__int64 FOVAddress;							//视角地址
	__int64 CharacterData;						//人物数据
	__int64 CharacterBase;						//人物基址
	__int64 ArraySize;							//数组大小
	__int64 MatrixBase;							//矩阵基址
	__int64 SelfAddress;						//本人地址
	__int64 ContractingLabel = 0;				//发包标签
	__int64 SelfPosition = 0;					//自己位置
	__int64 CLTClient = 0;						//CLTClient
	__int64 JudgmentMode;						//判断模式
	__int64 ModeAddress;						//模式地址
	__int64 ModeAddress2;						//模式地址2
	__int64 IsInGame;							//是否游戏
	__int64 IgnoreSmokeAddress;					//无视烟雾
	__int64 DisconnectTeleportAddress[2];		//断网瞬移
	__int64 StaticNoBackseat;					//静态无后
	__int64 UnlimitedPainting;					//无限喷漆
	__int64 SpaceContinuousJump;				//空格连跳
	__int64 SniperFireAddress;					//狙击连发
	__int64 ThousandTimesTheRateOfFire[2];		//千倍射速
	__int64 PersonalPerspective;				//人称视角
	__int64 ActionBaseAddress[2];				//动作基址
	__int64 NewThrowALittle;					//新散弹一点
	__int64 OldThrowALittle;					//旧散弹一点
	__int64 ElectricSaw;						//千刀电锯
	__int64 SpaceFlying;						//空格飞天
	__int64 ThreeSecondsEarly;					//早出三秒
	__int64 StaticStepAcceleration;				//静步加速
	__int64 RadarAddress[3];					//雷达透视
	__int64 BarrierBaseAddress;					//障碍基址
	__int64 InfiniteBackpack;					//无限背包
	__int64 InfiniteShield;						//无限护盾
	__int64 TextDoesNotBleed;					//文本不掉血
	__int64 StaticDoesNotBleed;					//静态不掉血
	__int64 DynamicDoesNotBleed;				//动态不掉血
	__int64 ReleasePauseBase[3];				//解除暂停基址
	__int64 KickPlayerAllocAddress = 0;			//代码踢人
	__int64 ZeroSecondAmmunitionChangeAddress;	//零秒换弹
	__int64 RangeTrackBase;						//范围追踪
	__int64 BallisticBaseSite[8];				//弹道基址
	__int64 SilentTrackBaseAddress[2];			//静默追踪基址
	__int64 ModifyAttribute;					//修改属性
	__int64 ModifyAttributeEx;
	__int64 Win32U;
	__int64 Win32UEnd;
	__int64 Gdi32;
	__int64 Gdi32End;
	__int64 UserGetRawInputData;
	__int64 PassAimBotAddress;
	BYTE PassAimBotValue[2];
	__int64 PassDrawTesting[2];
	__int64 kernelbaseLoadLibraryExW;
	__int64 IMM32;
	__int64 NVida;
	__int64 kernel32;
	//刀距结构
	__int64 KnifeDistanceBase;
	__int64 KnifeDistancePassACEAddress;
	bool KnifeIsChanged = FALSE;
	__int64 WeaponNumber;
	float TapDistanceValue[2];//轻击距离原始值
	float TapSpeedValue[2];//轻击速度原始值
	float TapRangeValue[2];//轻击范围原始值
	float HitDistanceValue;//重击距离
	float HitSpeedValue;//重击速度
	float HitRangeValue;//重击范围
	float KnifeMarkDistanceValue;//刀痕距离
	char WeaponNameValue[MAX_PATH];//武器名称
	char LastWeaponNameValue[MAX_PATH];//上一个武器名称

	DWORD64 PassReadNameTrack = 0;
	BYTE* DrawTesting;//绘制检测
	__int64 FuncTesting;//功能检测
	__int64 StructureATSAddress;//ATS构造地址

	__int64 test1;

	//HookFuncAddress HookFunc;
};

typedef struct _basedata {
	__int64 inject_offset;
	__int64 mtrix;								//矩阵
	__int64 array_size_offset;					//数组大小
	__int64 barrier_offset;						//障碍判基址
	__int64 player_array_offset;				//玩家数组
	__int64 judgment_mode_offset;				//判断模式
	__int64 characterbase_offset;				//人物基址偏移
	__int64 self_address_ffset;					//本人地址
	__int64 character_data_offset;				//人物数据
	__int64 is_ingame_offset;					//是否游戏
	__int64 personal_perspective_offset;		//人称视角
	__int64 unlimited_painting_offset;			//无限喷漆
	__int64 newthousandr_ateoffire_offset;		//新图千倍射速
	__int64 oldthousandr_ateoffire_offset;		//旧图千倍射速
	__int64 character_upperbody_action_offset;	//人物上半身动作
	__int64 character_lowerbody_action_offset;	//人物下半身动作
	__int64 newthrowalittle_offset;				//新图散弹一点
	__int64 oldthrowalittle_offset;				//旧图散弹一点
	__int64 radar_offsetone;					//雷达透视1
	__int64 radar_offsettwo;					//雷达透视2
	__int64 radar_offsetthree;					//雷达透视3
	__int64 kill_self_func_offset;				//自杀函数
	__int64 range_track_func_offset;			//范围增伤函数
	__int64 space_jump_hook_offset;				//空格连跳hook地址
	__int64 static_acceleration_hook_offset;	//静步加速hook地址
	__int64 squat_acceleration_hook_offset;		//下蹲加速hook地址
	__int64 bullet_without_backseat_hook_offset;//子弹无后hook地址
	__int64 left_knife_hook_offset;				//左键千刀hook地址
	__int64 right_knife_hook_offset;			//右键千刀hook地址
	__int64 right_knife_call_offset;			//右键千刀call地址
	__int64 zerobulletchange_newmaphook_offset;	//零秒换弹新图hook地址
	__int64 zerobulletchange_oldmaphook_offset;	//零秒换弹旧图hook地址
	__int64 throughthewall_hook_offset;			//人物穿墙hook地址
	__int64 ballistic_offset1;					//弹道基址1
	__int64 ballistic_offset2;					//弹道基址2
	__int64 ballistic_offset3;					//弹道基址3
	__int64 ballistic_offset4;					//弹道基址4
	__int64 ballistic_offset5;					//弹道基址5
	__int64 ballistic_offset6;					//弹道基址6
	__int64 ballistic_offset7;					//弹道基址7
	__int64 ballistic_offset8;					//弹道基址8
	__int64 code_193_1;							//代码193
	__int64 code_193_2;							//代码193
	__int64 code_193_3;							//代码193
	__int64 code_193_4;							//代码193
	__int64 code_193_5;							//代码193
	__int64 code_193_6;							//代码193
	__int64 code_140_1;							//代码140
	__int64 code_140_2;							//代码140
	__int64 code_141_1;							//代码141
	__int64 code_143_1;							//代码143
	__int64 code_143_2;							//代码143
	__int64 code_1_2_1;							//代码1_2
	__int64 code_1_2_2;							//代码1_2
	__int64 code_243_1;							//代码243
	__int64 code_243_2;							//代码243
	__int64 code_2414_1;						//代码2414
} basedata, * pbasedata;



