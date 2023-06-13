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

//��Χ׷�ٲ�λ��
#define RANGE_TRACK_POSITION_GOLDEN_HEAD 0x41000000		//��ͷ
#define RANGE_TRACK_POSITION_SILVER_HEAD 0x41880000		//��ͷ
#define RANGE_TRACK_POSITION_NECK 0x41140000			//����
#define RANGE_TRACK_POSITION_CLAVICLE 0x41900000		//����
#define RANGE_TRACK_POSITION_HAND 0x41200000			//��
#define RANGE_TRACK_POSITION_FOOT 0x41400000			//��

//��׼��λ��
#define AIM_POSITION_HEAD	1
#define AIM_POSITION_BODY	0

//��׼�ȼ���
#define AIM_HOTKEY_MOUSE_LEFT			0
#define AIM_HOTKEY_MOUSE_RIGHT			1
#define AIM_HOTKEY_KEYBOARD_ALT			2

//��Ϸ�ϰ��жϽṹ
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
	/////////////////////////////////////Hook��������/////////////////////////////////////
	BYTE OriginalStaticAccelerationCode[14];		//��������ԭʼ����
	__int64 MyStaticAccelerationAddress;			//�ҵľ������ٵ�ַ
	__int64 StaticAccelerationHookAddress;			//��������Hook��ַ
	__int64 StaticAccelerationHookRetAddress;		//��������Hook���ص�ַ
	__int64 StaticAccelerationValueAddress;			//��������ֵ
	/////////////////////////////////////Hook�¶׼���/////////////////////////////////////
	BYTE OriginalSquatAccelerationCode[14];			//�¶׼���ԭʼ����
	__int64 MySquatAccelerationAddress;				//�ҵ��¶׼��ٵ�ַ
	__int64 SquatAccelerationHookAddress;			//�¶׼���Hook��ַ
	__int64 SquatAccelerationHookRetAddress;		//�¶׼���Hook���ص�ַ
	__int64 SquatAccelerationValueAddress;			//�¶׼���ֵ
	/////////////////////////////////////Hook��̬�޺�/////////////////////////////////////
	BYTE OriginalBulletWithoutBackSeatCode[14];		//��̬�޺�ԭʼ����
	__int64 MyBulletWithoutBackSeatAddress;			//�ҵľ�̬�޺��ַ
	__int64 BulletWithoutBackSeatHookAddress;		//��̬�޺�Hook��ַ
	__int64 BulletWithoutBackSeatHookRetAddress;	//��̬�޺�Hook���ص�ַ
	__int64 BulletWithoutBackSeatValueAddress;		//��̬�޺�ֵ
	/////////////////////////////////////Hook���ǧ��/////////////////////////////////////
	BYTE OriginalLeftKnifeCode[14];					//���ǧ��ԭʼ����
	__int64 MyLeftKnifeAddress;						//�ҵ����ǧ����ַ
	__int64 LeftKnifeHookAddress;					//���ǧ��Hook��ַ
	__int64 LeftKnifeHookRetAddress;				//���ǧ��Hook���ص�ַ
	__int64 LeftKnifeValueAddress;					//���ǧ��ֵ
	/////////////////////////////////////Hook�Ҽ�ǧ��/////////////////////////////////////
	BYTE OriginalRightKnifeCode[14];				//�Ҽ�ǧ��ԭʼ����
	__int64 MyRightKnifeAddress;					//�ҵ��Ҽ�ǧ����ַ
	__int64 RightKnifeHookAddress;					//�Ҽ�ǧ��Hook��ַ
	__int64 RightKnifeHookRetAddress;				//�Ҽ�ǧ��Hook���ص�ַ
	__int64 RightKnifeCallAddress;					//�Ҽ�ǧ��Call��ַ
	__int64 RightKnifeValueAddress;					//�Ҽ�ǧ��ֵ
	/////////////////////////////////////Hook�ո�����/////////////////////////////////////
	BYTE OriginalSpaceJumpCode[14];					//�ո�����ԭʼ����
	__int64 MySpaceJumpAddress;						//�ҵĿո�������ַ
	__int64 SpaceJumpHookAddress;					//�ո�����Hook��ַ
	__int64 SpaceJumpHookRetAddress;				//�ո�����Hook���ص�ַ
	__int64 SpaceJumpValueAddress;					//�ո�����ֵ
	///////////////////////////////////Hook���뻻����ͼ///////////////////////////////////
	BYTE OriginalZeroBulletChangeCode_NewMap[14];	//���뻻����ͼԭʼ����
	__int64 MyZeroBulletChange_NewMapAddress;		//�ҵ����뻻����ͼ��ַ
	__int64 ZeroBulletChange_NewMapHookAddress;		//���뻻����ͼHook��ַ
	__int64 ZeroBulletChange_NewMapHookRetAddress;	//���뻻����ͼHook���ص�ַ
	__int64 ZeroBulletChange_NewMapValueAddress;	//���뻻����ͼֵ
	///////////////////////////////////Hook���뻻����ͼ///////////////////////////////////
	BYTE OriginalZeroBulletChangeCode_OldMap[14];	//���뻻����ͼԭʼ����
	__int64 MyZeroBulletChange_OldMapAddress;		//�ҵ����뻻����ͼ��ַ
	__int64 ZeroBulletChange_OldMapHookAddress;		//���뻻����ͼHook��ַ
	__int64 ZeroBulletChange_OldMapHookRetAddress;	//���뻻����ͼHook���ص�ַ
	__int64 ZeroBulletChange_OldMapValueAddress;	//���뻻����ͼֵ
	/////////////////////////////////////Hook���ﴩǽ/////////////////////////////////////
	BYTE OriginalThroughTheWallCode[14];			//���ﴩǽԭʼ����
	__int64 MyThroughTheWallAddress;				//�ҵ����ﴩǽ��ַ
	__int64 ThroughTheWallHookAddress;				//���ﴩǽHook��ַ
	__int64 ThroughTheWallHookRetAddress;			//���ﴩǽHook���ص�ַ
	__int64 ThroughTheWallValueAddress;				//���ﴩǽֵ

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
	__int64 MySelfDLL;							//����DLL
	__int64 Cross;
	__int64 CrossEndAddress;
	__int64 CrossFireBase;
	__int64 PlayerArray;						//�������
	__int64 FOVAddress;							//�ӽǵ�ַ
	__int64 CharacterData;						//��������
	__int64 CharacterBase;						//�����ַ
	__int64 ArraySize;							//�����С
	__int64 MatrixBase;							//�����ַ
	__int64 SelfAddress;						//���˵�ַ
	__int64 ContractingLabel = 0;				//������ǩ
	__int64 SelfPosition = 0;					//�Լ�λ��
	__int64 CLTClient = 0;						//CLTClient
	__int64 JudgmentMode;						//�ж�ģʽ
	__int64 ModeAddress;						//ģʽ��ַ
	__int64 ModeAddress2;						//ģʽ��ַ2
	__int64 IsInGame;							//�Ƿ���Ϸ
	__int64 IgnoreSmokeAddress;					//��������
	__int64 DisconnectTeleportAddress[2];		//����˲��
	__int64 StaticNoBackseat;					//��̬�޺�
	__int64 UnlimitedPainting;					//��������
	__int64 SpaceContinuousJump;				//�ո�����
	__int64 SniperFireAddress;					//�ѻ�����
	__int64 ThousandTimesTheRateOfFire[2];		//ǧ������
	__int64 PersonalPerspective;				//�˳��ӽ�
	__int64 ActionBaseAddress[2];				//������ַ
	__int64 NewThrowALittle;					//��ɢ��һ��
	__int64 OldThrowALittle;					//��ɢ��һ��
	__int64 ElectricSaw;						//ǧ�����
	__int64 SpaceFlying;						//�ո����
	__int64 ThreeSecondsEarly;					//�������
	__int64 StaticStepAcceleration;				//��������
	__int64 RadarAddress[3];					//�״�͸��
	__int64 BarrierBaseAddress;					//�ϰ���ַ
	__int64 InfiniteBackpack;					//���ޱ���
	__int64 InfiniteShield;						//���޻���
	__int64 TextDoesNotBleed;					//�ı�����Ѫ
	__int64 StaticDoesNotBleed;					//��̬����Ѫ
	__int64 DynamicDoesNotBleed;				//��̬����Ѫ
	__int64 ReleasePauseBase[3];				//�����ͣ��ַ
	__int64 KickPlayerAllocAddress = 0;			//��������
	__int64 ZeroSecondAmmunitionChangeAddress;	//���뻻��
	__int64 RangeTrackBase;						//��Χ׷��
	__int64 BallisticBaseSite[8];				//������ַ
	__int64 SilentTrackBaseAddress[2];			//��Ĭ׷�ٻ�ַ
	__int64 ModifyAttribute;					//�޸�����
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
	//����ṹ
	__int64 KnifeDistanceBase;
	__int64 KnifeDistancePassACEAddress;
	bool KnifeIsChanged = FALSE;
	__int64 WeaponNumber;
	float TapDistanceValue[2];//�������ԭʼֵ
	float TapSpeedValue[2];//����ٶ�ԭʼֵ
	float TapRangeValue[2];//�����Χԭʼֵ
	float HitDistanceValue;//�ػ�����
	float HitSpeedValue;//�ػ��ٶ�
	float HitRangeValue;//�ػ���Χ
	float KnifeMarkDistanceValue;//���۾���
	char WeaponNameValue[MAX_PATH];//��������
	char LastWeaponNameValue[MAX_PATH];//��һ����������

	DWORD64 PassReadNameTrack = 0;
	BYTE* DrawTesting;//���Ƽ��
	__int64 FuncTesting;//���ܼ��
	__int64 StructureATSAddress;//ATS�����ַ

	__int64 test1;

	//HookFuncAddress HookFunc;
};

typedef struct _basedata {
	__int64 inject_offset;
	__int64 mtrix;								//����
	__int64 array_size_offset;					//�����С
	__int64 barrier_offset;						//�ϰ��л�ַ
	__int64 player_array_offset;				//�������
	__int64 judgment_mode_offset;				//�ж�ģʽ
	__int64 characterbase_offset;				//�����ַƫ��
	__int64 self_address_ffset;					//���˵�ַ
	__int64 character_data_offset;				//��������
	__int64 is_ingame_offset;					//�Ƿ���Ϸ
	__int64 personal_perspective_offset;		//�˳��ӽ�
	__int64 unlimited_painting_offset;			//��������
	__int64 newthousandr_ateoffire_offset;		//��ͼǧ������
	__int64 oldthousandr_ateoffire_offset;		//��ͼǧ������
	__int64 character_upperbody_action_offset;	//�����ϰ�����
	__int64 character_lowerbody_action_offset;	//�����°�����
	__int64 newthrowalittle_offset;				//��ͼɢ��һ��
	__int64 oldthrowalittle_offset;				//��ͼɢ��һ��
	__int64 radar_offsetone;					//�״�͸��1
	__int64 radar_offsettwo;					//�״�͸��2
	__int64 radar_offsetthree;					//�״�͸��3
	__int64 kill_self_func_offset;				//��ɱ����
	__int64 range_track_func_offset;			//��Χ���˺���
	__int64 space_jump_hook_offset;				//�ո�����hook��ַ
	__int64 static_acceleration_hook_offset;	//��������hook��ַ
	__int64 squat_acceleration_hook_offset;		//�¶׼���hook��ַ
	__int64 bullet_without_backseat_hook_offset;//�ӵ��޺�hook��ַ
	__int64 left_knife_hook_offset;				//���ǧ��hook��ַ
	__int64 right_knife_hook_offset;			//�Ҽ�ǧ��hook��ַ
	__int64 right_knife_call_offset;			//�Ҽ�ǧ��call��ַ
	__int64 zerobulletchange_newmaphook_offset;	//���뻻����ͼhook��ַ
	__int64 zerobulletchange_oldmaphook_offset;	//���뻻����ͼhook��ַ
	__int64 throughthewall_hook_offset;			//���ﴩǽhook��ַ
	__int64 ballistic_offset1;					//������ַ1
	__int64 ballistic_offset2;					//������ַ2
	__int64 ballistic_offset3;					//������ַ3
	__int64 ballistic_offset4;					//������ַ4
	__int64 ballistic_offset5;					//������ַ5
	__int64 ballistic_offset6;					//������ַ6
	__int64 ballistic_offset7;					//������ַ7
	__int64 ballistic_offset8;					//������ַ8
	__int64 code_193_1;							//����193
	__int64 code_193_2;							//����193
	__int64 code_193_3;							//����193
	__int64 code_193_4;							//����193
	__int64 code_193_5;							//����193
	__int64 code_193_6;							//����193
	__int64 code_140_1;							//����140
	__int64 code_140_2;							//����140
	__int64 code_141_1;							//����141
	__int64 code_143_1;							//����143
	__int64 code_143_2;							//����143
	__int64 code_1_2_1;							//����1_2
	__int64 code_1_2_2;							//����1_2
	__int64 code_243_1;							//����243
	__int64 code_243_2;							//����243
	__int64 code_2414_1;						//����2414
} basedata, * pbasedata;



