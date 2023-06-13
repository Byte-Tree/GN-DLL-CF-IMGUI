#pragma once
#include "../../pch.h"

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")

#include "Update/Update.h"
#include "DataStruct.h"
#include "../MemoryTools/MemoryTools.h"
#include "../CheatEngineApi/HookApi/HookApi.h"


class Game :public MemoryTools
{
private:
	DWORD game_processid = 0;								//进程PID

	//障碍判断结构
	IntersectInfo Info;
	IntersectQuery Query;
	//Driver* driver = nullptr;

public:
	WNDPROC original_proc = nullptr;						//原始游戏窗口回调句柄
	void SetGameProcessId(DWORD processid) { game_processid = processid; }
	DWORD GetGameProcessId() { return game_processid; }

public:
	bool aimbot = false;												//鼠标自瞄
	bool memory_aimbot = false;											//内存自瞄
	bool track = false;													//子弹追踪
	bool redname_track = false;											//红名追踪
	bool silence_track = false;											//静默追踪
	bool silence_track_switch = false;									//静默追踪开关
	bool range_track = false;											//范围追踪
	bool judgementbarrier = true;										//判断障碍
	bool no_backseat = false;											//子弹无后
	bool no_blood_loss = false;											//卡不掉血
	bool zero_second_reload = false;									//零秒换弹
	bool space_fly = false;												//空格飞天
	bool weapon_fire = false;											//武器连发
	bool teleport_track_enemy = false;									//瞬移追敌
	bool spacecontinuousjump = true;									//空格连跳

	bool seckill_monster = false;										//怪物秒杀
	bool destroyer_seckill = false;										//破坏者秒杀
	bool breakers_seckill = false;										//爆裂者秒杀
	bool is_average = false;											//平均分数
	bool absorb_monster = false;										//全图吸怪

	//功能数值
	int aim_speed = 18;													//自瞄速度
	int aim_hotkey = AIM_HOTKEY_MOUSE_RIGHT;							//瞄准热键
	int aim_position = AIM_POSITION_BODY;								//打击位置
	int track_range = 180;												//追踪范围
	float range_track_value = 80.0f;									//范围追踪范围
	int range_track_position = RANGE_TRACK_POSITION_CLAVICLE;			//范围追踪部位
	float static_acceleration_value = 1;								//静步加速值
	float squat_acceleration_value = 1;									//下蹲加速值
	float seckill_speed = 40.0f;										//秒杀速度

	//追踪变量
	__int64 m_distance = 0;												//距离
	__int64 m_locking_pawn;												//锁定pawn
	int m_lastdistance;													//上次距离
	int m_recentdistance;												//最近距离
	int m_locking_bone_id;												//锁定BoneID
	int m_currentdistance;												//当前距离
	bool FirstCallKnifeDistance = TRUE;									//第一次调用刀距

	m_D3DCoordinate m_silence_track_coordinates = { 0.0f };				//静默追踪打击坐标
	BaseAddress GameBase = { NULL };

public:
	Game();
	~Game();
	//void GetDriver(Driver* drv) { driver = drv; }						//获取驱动
	void BaseAddressInit();												//基址初始化
	void ByPassACE();													//处理ACE
	void ACE_Base();
	void ACE_ATS();
	void ACE_PBC();
	void ACE_CSI();
	static void PassThread();
	void PassErrorCode();
	BOOL WorldToScreen2(m_D3DCoordinate view_, D3DXVECTOR2* RetCoordinates);
	BOOL WorldToScreen(m_D3DCoordinate EnemyCoordinates, m_D3DCoordinate* RetCoordinates);
	bool IsInGaming();
	int GetSelfPosition();
	int GetCharacterNumber();
	void GetSelfData(m_D3DCoordinate* RetData);
	bool GetEnemyCoordinate(__int64 id, m_D3DCoordinate* b);
	bool GetBiochemicalModel(int SelfPosition, int PlayerPosition);
	__int64 GetSelfLive();
	char* GetEnemyName(__int64 id);
	bool GetEnemyLive(__int64 id);
	int GetUserQQNumber(int id);
	__int64 GetCharacterBlood(__int64 id);
	bool IsC4(int id);
	int GetCurrentWeaponID();
	LPCSTR JudgeMentMap();
	void TrackingRange(m_D3DCoordinate Data, int Target, int gamewidth, int gameheight);
	int CalulateEnemyDistance(m_D3DCoordinate self_coordinate, m_D3DCoordinate enemy_coordinate);
	void CalculateDistance(m_D3DCoordinate ScreenCoordinates, __int64 EnemyID, __int64 BoneID, int gamecent_x, int gamecent_y);
	BOOL IsVisible(m_D3DCoordinate SelfPos, m_D3DCoordinate TargetPos);
	void MouseAimbot(m_D3DCoordinate Output, int gamecent_x, int gamecent_y, int gamewidth, int gameheight);
	m_D3DCoordinate AutomaticAimingAlgorithm(m_D3DCoordinate EnemyCoordinates);
	m_D3DCoordinate VectorToRotation(m_D3DCoordinate SelfCoordinates, m_D3DCoordinate b);
	int RandomPosition();
	void ModifyTrajectory();
	void ReductionTrajectory();
	void TrackDeployment(m_D3DCoordinate AimCoordinates);
	void WriteMouse(m_D3DCoordinate enemy);
	bool GetBoneCoordinate(__int64 ID, m_D3DCoordinate* Deposit, __int64 Position);
	void DrawBone(int Addr, int color, int LineSize);
	void WriteSilenceTrack(m_D3DCoordinate aim_coordinates);

	void UnlimitedPaintingSwitch();
	bool ChangeKnifeDistance(float KnifeWieldingDistance, float TapSpeed, float HitSpeed, float TapRange, float HitRange);
	bool ReductionKnifeDistance();
	void TeleportToTrackTheEnemyFunc(DWORD id);
	void SpaceContinuousJumpFunc();
	void HookRedNameTrackFunc(__int64 pointer, __int64 judgement_pointer);
	bool TraversingBinaryTree(__int64 object, std::vector<__int64>* pvector);
	void TraverseMonsterArray();
	void SendSecKillPacket(std::vector<__int64>* pmonster_list);
	void SendPacket();

};


