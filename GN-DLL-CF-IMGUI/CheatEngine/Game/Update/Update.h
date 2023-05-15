#pragma once

//��Χ����ַ
#define PBC_calladdress 0x4F356
#define PBC_funcaddress 0x13E0A3
#define GDP_funcaddress 0x63980

//BASE
#define GlobalBaseFuncOffset 0x815844							//����ȫ��Baseƫ��
#define PassBaseCheckOffset 0x1D3460							//��ɨ���������hook Ч���߳�
#define PassBaseAddressOffset 0x232B60							//��jmp����hook
#define BASEVirtualAllocOffset 0x2B4358							//Baseģ�����VirtualAlloc
#define BASEVirtualProtectOffset 0x2B4708						//Baseģ�����VirtualProtect
#define BASESleepOffset 0x2B4208								//Baseģ�����Sleep
#define BASECreateThreadOffset 0x2B41D0							//Baseģ�����CreateThread
//#define BASEGetModuleHandleWOffset 0x2B41F8					//Baseģ�����GetModuleHandleW
//#define BASECreateFileWOffset 0x2972B0						//Baseģ�����CreateFileW
//#define BASEReadFileOffset 0x297360							//Baseģ�����ReadFile

//ATS
#define ATS_CRC_One 0x4FE08E									//ATS_CRC �����룺44 8A 02 44 88 07 48 BA ?? ?? ?? ?? ?? ?? ?? ?? 48 8D 3C 16 48 BA ?? ?? ?? ?? ?? ?? ?? ?? 48 8D 34 17 48 89 75 00
#define ATS_CRC_Two 0x4FE265
#define ATS_CRC_Three 0x504D67
#define ATS_CRC_Four 0x504F53
#define ATS_CRC_Five 0x4192D6
#define ATSGetCurrentProcessOffset 0x1401A0						//GetCurrentProcess
#define ATSGetModuleInformationOffset 0x140568					//GetModuleInformation
#define ATSGetModuleHandleAOffset 0x140160						//GetModuleHandleA

//CSI
#define CSIGetClassNameWOffset 0x4ED868							//CSIģ�����GetClassNameW
#define CSIEnumWindowsOffset 0x4ED888							//CSIģ�����EnumWindows
#define CSIEnumChildWindowsOffset 0x4ED890						//CSIģ�����EnumChildWindows
#define CSIVirtualAllocOffset 0x4B33A8							//CSIģ�����VirtualAlloc
#define CSIVirtualprotectOffset 0x4B3540						//CSIģ�����Virtualprotect
#define CSISleepOffset 0x4B33E8									//CSIģ�����Sleep
#define CSICreateFileWOffset 0x4B3190							//CSIģ�����CreateFileW
#define CSICreateWindowExWOffset 0x4B37E8						//CSIģ�����CreateWindowExW
#define CSICreateThreadOffset 0x4B34D0							//CSIģ�����CreateThread

//PBC
#define PassPBCCheckOffset 0x78AD0								//�ں���ͷ����hook
#define PassPBCOne 0x3A0D39										//PBC���˲��
#define PassPBCTwo 0x57E06										//PBC���˲��  δ����
#define PBCCreateThreadOffset 0x9E048							//PBCģ�����CreateThread
#define PBCSleepOffset 0x97040									//PBCģ�����Sleep

//crossfireBase
#define PassCrossFireBaseCheckOffset 0xBBD10					//�����������				�����룺48 8B C4 55 41 54 41 55 41 56 41 57 48 8D 68 A1 48 81 EC A0 00 00 00 48 C7 45 27 FE FF FF FF 48 89 58 10 48 89 70 18 48 89 78 20 48 8B D9
#define PasscrossBaseFindFirstFileAOffset 0x334408				//crossfireBaseģ�����FindFirstFileA

//3*4���󣬾���ͷ������8�еĵ�ַ������������ͷ��
//�����õ����XY�ö�̬��ַ�鿴���ʣ��ҵ����ַ+4
//��������û����256 ������257
//������5��û����2
//������0��������1����ս2����3
#define InjectHookOffset 0x1BC604								//dllע���					�����룺45 33 C9 C7 44 24 ?? 01 00 00 00 45 33 C0 48 ?? ?? ?? 33 D2 FF 15 ?? ?? ?? ?? 85 C0 75 ?? E8 ?? ?? ?? ?? 85 C0
#define Mtrix 0x140525630										//����						�����룺48 8B 0D ?? ?? ?? ?? 48 8D ?? ?? 41 B8 ?? ?? ?? ?? 48 8B 01 FF 90 ?? ?? ?? ??    mov rcx,[cshell_x64.dll+0xXXXXXXX] '�����ַ = (cshell_x64.dll+0xXXXXXXX)��ֵ + 0x2D00 - 0x10
//#define Mtrix 0x140525630										//����						�����룺F3 0F 10 83 ?? ?? ?? ?? F3 0F 10 8B ?? ?? ?? ?? 48 8B 4B ?? 48 85 C9 0F 84 ?? ?? ?? ?? 44 8B 81 ?? ?? ?? ??  [rbx + 0x2D00] - 0x10  |  �����ַ = ((rbx��ֵ + 0x2D00(offset)) - 0x10)  |  ע��0x2D00�Ǹ�ƫ�ƣ����ܴ��ڸ���
#define ArraySizeOffset 0x1048									//�����С
#define PlayerArrayBaseAddress 0x2A87378						//�������
#define ModelOffset 0x2A873E0									//�ж�ģʽ
#define ModelOffset2 0x2A872EF									//ģʽ��ַ
#define ChallengeHitchaddress 0x14008EFAD						//��ս�ҽӵ�				�����룺8B D9 75 ?? 83 3D ?? ?? ?? ?? 00 74 ?? FF 15 ?? ?? ?? ?? 83 3D ?? ?? ?? ?? 01 7C ?? 4C 8D 0D ?? ?? ?? ?? 4C 8D 05 ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? B8 49 00 00 00 48 83 C4 20 5B C3 FF 15 ?? ?? ?? ?? 84 C0 74 ?? 90
#define Hitchaddress 0x1403B5894								//���ƹҽӵ�ַ				�����룺45 33 C9 45 33 C0 33 D2 E9 ?? ?? ?? ?? FF 15 ?? ?? ?? ?? 8B D8 
#define DrawIndexedPrimitiveaddress 0x140254CD7					//��Ⱦ�ҽӵ�ַ				�����룺44 89 64 24 20 FF 90 ?? ?? 00 00 83 3D ?? ?? ?? ?? 02 7C ?? 8B 84 24 ?? ?? ?? ?? ��˳������ʮ����ַ
#define SilentTrackAddress 0x140235330 + 0x10					//��Ĭ׷�ٹ���				�����룺48 83 EC 28 0F 28 C2 4C 8B CA F3 0F 10 54 24 ?? 
#define RedNameTrackAddress 0x140242418							//����׷�ٵ�ַ				�����룺4C 89 44 24 ?? 48 89 54 24 ?? 48 89 4C 24 ?? 48 81 EC 98 00 00 00 48 C7 44 24 48 FE FF FF FF
#define RangeTrackAddressOne 0x17352D							//��Χ׷��1					�����룺F3 0F 11 52 ?? F3 0F 11 4A?? F3 0F 11 42 ?? F3 0F 10 92 ?? ?? ?? ?? F3 0F 10 8A ?? ?? ?? ?? F3 0F 10 82 ?? ?? ?? ?? F3 0F 58 92 ?? ?? ?? ?? F3 0F 58 8A ?? ?? ?? ?? F3 0F 58 82 ?? ?? ?? ?? F3 0F 11 52 ?? F3 0F 11 4A ?? F3 0F 11 42 ?? 0F B6 82 ?? ?? ?? ?? 
#define RangeTrackAddressTwo RangeTrackAddressOne + 0x27		//��Χ׷��2
#define RangeTrackAddressThree 0x23DC21							//��Χ׷��3					�����룺F3 0F 11 44 24 ?? 48 8D 4C 24 ?? E8 ?? ?? ?? ?? F3 0F 10 4C 24 ?? 0F 2F C8 76 ?? 
#define BarrierOffset 0x140050060								//�ϰ��жϻ�ַ				�����룺4C 8B C9 4C 8B C2 48 8B ?? ?? ?? ?? ?? 49 8B D1 48 8B 01 48 FF ?? 18
#define KnifeDistanceBaseAddress 0x2C2ACA0						//�����ַ | ������ַ
#define WeaponNumberBaseAddressOne 0x2B3AAC0					//������������һ | �������� ���Բ��ø�����
#define WeaponNumberBaseAddressTwo 0x94							//�����������ж�
#define WeaponNumberArray 0x8									//������������
#define CharacterBaseOffset 0x98								//�����ַƫ��
#define SelfAddressOffset 0x289									//���˵�ַƫ�� ����ID
#define CharacterDataOffset 0x290								//OBJECT | ��������
#define IsInGameOffset 0x8										//�Ƿ���Ϸ
#define PersonalPerspectiveOffset 0x50							//�����ַ-50
#define SelfPositionOffset 0x2C4B0B0							//�Լ�λ��
#define CLTClientOffset 0x3C8430								//CLTClient
#define CommonLTOffset 0x3CBBA8									//CommonLT
#define ContractingLabelOffset 0x2A1DAAF						//������ǩ
#define UnlimitedPaintingBaseAddress 0x2C51284					//��������
#define SpaceContinuousJumpOffset 0x2C8EA78						//�ո�����
#define RadarOffsetOne 0x121938A								//�״�͸��1					�����룺75 ?? 40 84 F6 75 ?? FF 15 ?? ?? ?? ?? 43 39 84 3E ?? ?? ?? ?? 0F 86 ?? ?? ?? ?? 43 83 BC 3E ?? ?? ?? ?? 00
#define RadarOffsetTwo 0x1219544								//�״�͸��2					�����룺7E ?? 00 84 C0 ?? ?? ?? ??  00 00 8B 05 ?? ?? ?? ?? 83 C0 ?? 83 F8 01 77 ?? 48 8B 8C 24 ?? ?? ?? ?? �ѳ����ĵ�ַ+0x06
#define RadarOffsetThree 0x12195A4								//�״�͸��3					�����룺7E ?? 00 84 C0 ?? ?? ?? ?? 00 00 48 8B 0D ?? ?? ?? ?? 48 8B 01 FF 90 ?? ?? ?? ?? 48 8B 94 24 ?? ?? ?? ?? 84 C0 74 ?? 48 8B 84 24 ?? ?? ?? ?? �ѳ����ĵ�ַ+0x06
#define CharacterUpperBodyActionBaseAddress 0x203E438			//�����ϰ�����
#define CharacterLowerBodyActionBaseAddress 0x1F4AEF8			//�����°�����
#define NewThrowALittleBaseAddress 0x90FF1F						//��ͼɢ��һ��
#define OldThrowALittleBaseAddres 0x12C0650						//��ͼɢ��һ��
#define NewThousandTimesTheRateOfFireBaseAddress 0x8DAEAF		//��ͼǧ�����ٻ�ַ
#define OldThousandTimesTheRateOfFireBaseAddress 0x12AA2E0		//��ͼǧ�����ٻ�ַ
#define BallisticBaseSiteOne 0x917BF1 							//������ַ��ͨģʽY  128	2120
#define BallisticBaseSiteTwo 0x917BE6							//������ַ��ͨģʽX  132	2124
#define BallisticBaseSiteThree 	0x12C79F9						//������ַ����ģʽY  128	2120
#define BallisticBaseSiteFour 0x12C79E8  						//������ַ����ģʽX  132	2124
#define PursuitBallisticBaseSiteOne 0x1641F9F					//������ַ׷��ģʽY  128    2120
#define PursuitBallisticBaseSiteTwo 0x1641F8E 					//������ַ׷��ģʽX  132    2124
#define PersonalBallisticBaseSiteOne 0x160CE6E					//������ַ����ģʽY	 128    2120
#define PersonalBallisticBaseSiteTwo 0x160CE5D					//������ַ����ģʽX	 132    2124
#define RangeTrackBaseAddress 0x10677C7							//��Χ���˻�ַ
#define RangeTrackFuncOffset 0x10A9FC0							//��Χ���˺�����ַ			�����룺4D 8B 5B ?? 48 8B 24 24 E8 ?? ?? ?? ?? 48 8D A4 24 ?? ?? ?? ?? 48 89 6C 24 ?? 48 89 E5 Cshellģ���19����ַ�µ�call
#define InfiniteShieldBaseAddress 0x148F2FF						//ʥȭ���ܻ�ַ
#define InfiniteBackpackBaseAddress 0x24C58F0					//���ޱ�����ַ
#define IgnoreSmokeBaseAddress 0xF26445							//���������ַ
#define NewDisconnectTeleportBaseAddress 0x7AFB88				//��ͼ����˲�ƻ�ַ
#define OldDisconnectTeleportBaseAddress 0x142B078				//��ͼ����˲�ƻ�ַ
#define RedNameTrackRetAddress RedNameTrackAddress + 0xF		//����׷�ٷ��ص�ַ
#define TextDoesNotBleedBaseAddress 0x127CFE8					//�ı�����Ѫ��ַ rez\Butes\%s_DZ.ltc
#define StaticDoesNotBleedBaseAddress 0x2668E30
#define ThreeSecondsEarlyBaseAddress 0x23F9B0C
#define ReleasePauseBaseAddressOne 0x1214678					//������ͣ
#define ReleasePauseBaseAddressTwo 0x252BB5D					//������ͣ
#define Code193One 0x9C056E										//����193
#define Code193Two 0x90E499										//����193
#define Code193Three 0x9E05F1									//����193
#define Code193Four 0x129A97B									//����193	δ����
#define Code193Five 0x8CA37E									//����193	δ����
#define Code193Six 0x11D094B									//����193	δ����
#define Code143One 0x90ECB4										//����143
#define Code143Two 0x90EC12										//����143
#define Code140One 0x916C68										//����140	���
#define Code140Two 0x1626EEE	    							//����140	���
#define Code141One 0x853717		    							//����141	���
#define Code1_2One 0xA46440										//����1_2   ���ٴ������
#define Code1_2Two 0x67A90F										//����1_2	δ����
#define Code243One 0x10CD474									//����243   jmp
#define Code243Two 0x853562										//����243   nop
#define Code2414 0x985B8E										//����2414

///////////////////////Hook����///////////////////////
//#define StaticAccelerationHookOffset 0x98F603											//��������Hook��ַ			�����룺F3 0F 10 83 ?? ?? ?? ?? F3 0F 59 41 ?? 48 8B CB 48 8B 03 F3 0F 11 45 ?? FF 90 ?? ?? ?? ??
//#define StaticAccelerationHookRetOffset StaticAccelerationHookOffset + 0x10				//��������Hook���ص�ַ
//#define SquatAccelerationHookOffset 0x98F6B4											//�¶׼���Hook��ַ			�����룺F3 0F 10 83 ?? ?? ?? ?? F3 0F 59 41 ?? F3 0F 11 45 ?? EB ?? 0F 28 C6 F3 0F 11 45 ??
//#define SquatAccelerationHookRetOffset SquatAccelerationHookOffset + 0x12				//�¶׼���Hook���ص�ַ
//#define BulletWithoutBackSeatHookOffset 0x98FE72										//��̬�޺�Hook��ַ			�����룺F3 44 0F 10 05 ?? ?? ?? ?? 0F 28 F7 F3 0F 59 BC B7 ?? ?? ?? ?? F3 0F 59 B4 B7 ?? ?? ?? ?? F3 41 0F 59 F8 F3 41 0F 59 F0
//#define BulletWithoutBackSeatHookRetOffset BulletWithoutBackSeatHookOffset + 0x15		//��̬�޺�Hook���ص�ַ
//#define LeftKnifeHookOffset 0x9026C0													//���ǧ��Hook��ַ			�����룺7D ?? F3 41 0F 10 B4 86 ?? ?? ?? ?? 8B 15 ?? ?? ?? ?? 83 FA ?? 77 ?? 0F A3 D5 72 ?? 83 FA ?? 74 ?? 8D ?? ?? 83 F8 01
//#define LeftKnifeHookRetOffset LeftKnifeHookOffset + 0x12								//���ǧ��Hook���ص�ַ
//#define RightKnifeHookOffset 0x9025C6													//�Ҽ�ǧ��Hook��ַ			�����룺F3 41 0F 10 B6 ?? ?? ?? ?? E8 ?? ?? ?? ?? 41 0F B7 ?? 48 8B F0 E8 ?? ?? ?? ?? 48 8B D8 48 85 C0 0F 84 ?? ?? ?? ?? 48 63 15 ?? ?? ?? ?? 83 FA 39 77 ?? 48 ?? ?? ?? ?? ?? ?? ??
//#define RightKnifeHookRetOffset RightKnifeHookOffset + 0xE								//�Ҽ�ǧ��Hook���ص�ַ
//#define RightKnifeCallOffset 0x5539C0													//�Ҽ�ǧ��Call��ַ			�����룺48 83 EC 38 48 C7 44 24 ?? ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 85 C0 75 ?? B9 F8 00 00 00 E8 ?? ?? ?? ?? 48 89 44 24 ?? 48 8B C8 E8 ?? ?? ?? ?? 90 48 89 05 ?? ?? ?? ?? 48 83 C4 38 C3
//#define SpaceJumpHookOffset 0x13F29B4													//�ո�����Hook��ַ			�����룺44 0F B6 3D ?? ?? ?? ?? 8B CB FF 90 ?? ?? ?? ?? 84 C0 0F 84 ?? ?? ?? ?? 44 38 B7 ?? ?? ?? ?? 0F 85 ?? ?? ?? ?? 44 38 77 ?? 0F 85 ?? ?? ?? ??
//#define SpaceJumpHookRetOffset SpaceJumpHookOffset + 0x10								//�ո�����Hook���ص�ַ
//#define ZeroBulletChange_NewMapHookOffset 0x90BD9D										//���뻻����ͼHook��ַ		�����룺41 8B 96 ?? ???? ?? 49 8B CE FF 90 ?? ?? ?? ?? 84 C0 0F ?? ?? ?? ?? ?? 49 8B 06 49 8B CE
//#define ZeroBulletChange_NewMapHookRetOffset ZeroBulletChange_NewMapHookOffset + 0x10	//���뻻����ͼHook���ص�ַ
//#define ZeroBulletChange_OldMapHookOffset 0x12BCC8E										//���뻻����ͼHook��ַ		�����룺41 8B 96 ?? ?? ?? ?? 49 8B CE FF 90 ?? ?? ?? ?? 84 C0 0F ?? ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 8D ?? ?? ?? ?? ?? FF 90 ?? ?? ?? ??
//#define ZeroBulletChange_OldMapHookRetOffset ZeroBulletChange_OldMapHookOffset + 0x10	//���뻻����ͼHook���ص�ַ
//#define ThroughTheWallHookOffset 0x98D2CC												//���ﴩǽHook��ַ			�����룺F3 0F 11 89 ?? ?? ?? ?? F3 0F 11 99 ?? ?? ?? ?? F3 0F 11 81 ?? ?? ?? ?? C3
//#define ThroughTheWallHookRetOffset ThroughTheWallHookOffset + 0x10						//���ﴩǽHook���ص�ַ
#define StaticAccelerationHookOffset 0x15F42E2											//��������Hook��ַ			�����룺F3 0F 10 83 ?? ?? ?? ?? F3 0F 59 41 ?? 48 8B CB 48 8B 03 F3 0F 11 45 ?? FF 90 ?? ?? ?? ??
#define SquatAccelerationHookOffset 0xA74094											//�¶׼���Hook��ַ			�����룺F3 0F 10 83 ?? ?? ?? ?? F3 0F 59 41 ?? F3 0F 11 45 ?? EB ?? 0F 28 C6 F3 0F 11 45 ??
#define BulletWithoutBackSeatHookOffset 0xA7481D										//��̬�޺�Hook��ַ			�����룺F3 44 0F 10 05 ?? ?? ?? ?? 0F 28 F7 F3 0F 59 BC B7 ?? ?? ?? ?? F3 0F 59 B4 B7 ?? ?? ?? ?? F3 41 0F 59 F8 F3 41 0F 59 F0
#define ZeroBulletChange_NewMapHookOffset 0x9CF14D		//�����仯��								//���뻻����ͼHook��ַ		�����룺41 8B 96 ?? ?? ?? ?? 49 8B CE FF 90 ?? ?? ?? ?? 84 C0 0F ?? ?? ?? ?? ?? 49 8B 06 49 8B CE
#define ZeroBulletChange_OldMapHookOffset 0x13802DE										//���뻻����ͼHook��ַ		�����룺41 8B 96 ?? ?? ?? ?? 49 8B CE FF 90 ?? ?? ?? ?? 84 C0 0F ?? ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 8D ?? ?? ?? ?? ?? FF 90 ?? ?? ?? ??
#define FlyOffset 0x232387																//�ո����Hook��ַ			�����룺8B 82 ?? ?? ?? ?? 41 89 40 ?? 8B 82 ?? ?? ?? ?? 41 89 40 08 33 C0 48 83 C4 ?? C3 83 3D ?? ?? ?? ?? 00 74 ?? FF 15 ?? ?? ?? ?? 83 3D ?? ?? ?? ?? 01 
#define KillSelfFuncOffset 0xA50450	//����													//������ѪHook��ַ			�����룺48 89 5C 24 ?? 55 56 57 48 83 EC ?? 48 8B 0D ?? ?? ?? ?? 48 8D 54 24 ?? 0F 29 74 24 ?? 41 8B E8
#define WeaponFireHookOffset 0x137901E													//��������Hook��ַ			�����룺C6 86 ?? ?? ?? ?? 01 41 0F B7 0E 66 85 C9 78 ?? 8B 15 ?? ?? ?? ?? FF CA 0F BF C1 3B C2 7F ?? 
//δ����
#define ThroughTheWallHookOffset 0x98D2CC												//���ﴩǽHook��ַ			�����룺F3 0F 11 89 ?? ?? ?? ?? F3 0F 11 99 ?? ?? ?? ?? F3 0F 11 81 ?? ?? ?? ?? C3
#define LeftKnifeHookOffset 0x9026C0													//���ǧ��Hook��ַ			�����룺7D ?? F3 41 0F 10 B4 86 ?? ?? ?? ?? 8B 15 ?? ?? ?? ?? 83 FA ?? 77 ?? 0F A3 D5 72 ?? 83 FA ?? 74 ?? 8D ?? ?? 83 F8 01
#define RightKnifeHookOffset 0x9025C6													//�Ҽ�ǧ��Hook��ַ			�����룺F3 41 0F 10 B6 ?? ?? ?? ?? E8 ?? ?? ?? ?? 41 0F B7 ?? 48 8B F0 E8 ?? ?? ?? ?? 48 8B D8 48 85 C0 0F 84 ?? ?? ?? ?? 48 63 15 ?? ?? ?? ?? 83 FA 39 77 ?? 48 ?? ?? ?? ?? ?? ?? ??
#define SpaceJumpHookOffset 0x13F29B4													//�ո�����Hook��ַ			�����룺44 0F B6 3D ?? ?? ?? ?? 8B CB FF 90 ?? ?? ?? ?? 84 C0 0F 84 ?? ?? ?? ?? 44 38 B7 ?? ?? ?? ?? 0F 85 ?? ?? ?? ?? 44 38 77 ?? 0F 85 ?? ?? ?? ??



////////////////////////Pass28_3////////////////////////////
#define ByPass28_3 0x3EFB3C										//�����룺E8 ?? ?? ?? ?? 4C ?? ?? 48 ?? ?? 0F 84 ?? ?? ?? ?? F3
#define WeaponIndex 0x61C8										//�����룺48 05 ?? ?? ?? ?? 48 8D 52 08 49 83 E8 01 75 E5 89 3D ?? ?? ?? ?? 89 3D ?? ??
#define _WP_Amount 4335											//�������� �ɼ� RB001.REZ
#define WeaponMrg 0x288DDD0										//�����룺48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 08 F3 0F 11 B1

////////////////////////����ƫ��////////////////////////////
#define BiochemicalOffset 0x2A8									//������Ӫ1
#define BiochemicalCampOffset 0x1143F							//������Ӫƫ�� | �����Ӫ
#define BoneOffset 0x28E8										//����ƫ��
#define ZeroSecondAmmunitionChangeOffset 0x0894					//���뻻��ƫ��
#define CurrentWeaponOffset 0x2E4								//��ǰ����ƫ��
#define CurrentWeaponIDOffset 0x179C							//��ǰ����IDƫ�� С���ѣ�5 M4A1-A�ѣ�2189 PMR-30�ѣ�1414  �ѳ�����ַ��ƫ��
#define SpaceflyOffset 0x01B4									//�ո����ƫ��
#define WeaponFireOffset 0x8AC									//�ѻ�����ƫ��
#define StaticStepAccelerationOffset 0x5A4						//��������ƫ��
#define SquatStepAccelerationOffset StaticStepAccelerationOffset + 0x4	//�ײ�����ƫ��
#define ThroughTheWallOffsetOne 0x16D8									//���ﴩǽƫ��1
#define ThroughTheWallOffsetTwo ThroughTheWallOffsetOne + 0x08			//���ﴩǽƫ��2
#define PerspectiveOffset 0x98									//�˳��ӽ�ƫ��
#define SelfLiveOffset 0x0C										//�Լ�����ƫ��

//��������ƫ��
#define PlayerXCoordinateOffset 0x19C							//X����ƫ��
#define PlayerYCoordinateOffset 0x194							//Y����ƫ��
#define PlayerZCoordinateOffset 0x198							//Z����ƫ��

//׷�����ƫ��
#define MouseYOffset 0x858										//���Y��ƫ��
#define MouseXOffset MouseYOffset + 0x4							//���X��ƫ��

//���ƫ��
#define ElectricSawOffsetOne 0x2F0								//ǧ��һ��ƫ��
#define ElectricSawOffsetTwo 0x20								//ǧ������ƫ��
#define ElectricSawOffsetThree 0x1710							//ǧ������ƫ��
#define ElectricSawOffsetFour 0x8								//ǧ���ļ�ƫ��
#define ElectricSawOffsetFive 0x20								//ǧ���弶ƫ��
#define CurrentBulletOffset 0x2D4								//ǧ����ǰ�ӵ�ƫ��
#define WeaponStatuOffset ElectricSawOffsetFive + 0x08			//����״̬ƫ��	

//�������ƫ��
#define MapOffset 0x558											//��ͼƫ��
#define FloatFlayOffsetTwo 0x1B4								//����������ƫ��
#define FloatFlayControlDirectionOffset 0x8C4					//���������Ʒ���ƫ��

//����ƫ��
#define TapWieldingDistanceOffsetOne 0xF8C						//����ӵ�����ƫ��һ
#define TapWieldingDistanceOffsetTwo 0xF90						//����ӵ�����ƫ�ƶ�
#define TapSpeedOffsetOne 0xFAC									//����ٶ�ƫ��һ
#define TapSpeedOffsetTwo 0xFB0									//����ٶ�ƫ�ƶ�
#define TapRangeOffsetOne 0xF9C									//�����Χƫ��һ
#define TapRangeOffsetTwo 0xFA0									//�����Χƫ�ƶ�
#define HitDistanceOffset 0xFBC									//�ػ�����ƫ��
#define HitSpeedOffset 0xFDC									//�ػ��ٶ�ƫ��
#define HitRangeOffset 0xFCC									//�ػ���Χƫ��
#define KnifeMarkDistanceOffset 0xC30							//���۾���ƫ��
#define WeaponNameOffset 0xE									//��������ƫ��

//���QQ
#define UserQQNumberOffset 0x38									//���QQƫ��

//��������ƫ��
#define EnemyLiveOffset 0x270


