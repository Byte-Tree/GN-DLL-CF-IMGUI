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
	DWORD game_processid = 0;								//����PID

	//�ϰ��жϽṹ
	IntersectInfo Info;
	IntersectQuery Query;
	//Driver* driver = nullptr;

public:
	WNDPROC original_proc = nullptr;						//ԭʼ��Ϸ���ڻص����
	void SetGameProcessId(DWORD processid) { game_processid = processid; }
	DWORD GetGameProcessId() { return game_processid; }

public:
	bool aimbot = false;												//�������
	bool memory_aimbot = false;											//�ڴ�����
	bool track = false;													//�ӵ�׷��
	bool redname_track = false;											//����׷��
	bool silence_track = false;											//��Ĭ׷��
	bool silence_track_switch = false;									//��Ĭ׷�ٿ���
	bool range_track = false;											//��Χ׷��
	bool judgementbarrier = true;										//�ж��ϰ�
	bool no_backseat = false;											//�ӵ��޺�
	bool no_blood_loss = false;											//������Ѫ
	bool zero_second_reload = false;									//���뻻��
	bool space_fly = false;												//�ո����
	bool weapon_fire = false;											//��������
	bool teleport_track_enemy = false;									//˲��׷��
	bool spacecontinuousjump = true;									//�ո�����

	bool seckill_monster = false;										//������ɱ
	bool destroyer_seckill = false;										//�ƻ�����ɱ
	bool breakers_seckill = false;										//��������ɱ
	bool is_average = false;											//ƽ������
	bool absorb_monster = false;										//ȫͼ����

	//������ֵ
	int aim_speed = 18;													//�����ٶ�
	int aim_hotkey = AIM_HOTKEY_MOUSE_RIGHT;							//��׼�ȼ�
	int aim_position = AIM_POSITION_BODY;								//���λ��
	int track_range = 180;												//׷�ٷ�Χ
	float range_track_value = 80.0f;									//��Χ׷�ٷ�Χ
	int range_track_position = RANGE_TRACK_POSITION_CLAVICLE;			//��Χ׷�ٲ�λ
	float static_acceleration_value = 1;								//��������ֵ
	float squat_acceleration_value = 1;									//�¶׼���ֵ
	float seckill_speed = 40.0f;										//��ɱ�ٶ�

	//׷�ٱ���
	__int64 m_distance = 0;												//����
	__int64 m_locking_pawn;												//����pawn
	int m_lastdistance;													//�ϴξ���
	int m_recentdistance;												//�������
	int m_locking_bone_id;												//����BoneID
	int m_currentdistance;												//��ǰ����
	bool FirstCallKnifeDistance = TRUE;									//��һ�ε��õ���

	m_D3DCoordinate m_silence_track_coordinates = { 0.0f };				//��Ĭ׷�ٴ������
	BaseAddress GameBase = { NULL };

public:
	Game();
	~Game();
	//void GetDriver(Driver* drv) { driver = drv; }						//��ȡ����
	void BaseAddressInit();												//��ַ��ʼ��
	void ByPassACE();													//����ACE
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


