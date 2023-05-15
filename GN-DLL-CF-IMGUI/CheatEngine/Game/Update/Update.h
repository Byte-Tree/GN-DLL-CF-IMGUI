#pragma once

//范围检测地址
#define PBC_calladdress 0x4F356
#define PBC_funcaddress 0x13E0A3
#define GDP_funcaddress 0x63980

//BASE
#define GlobalBaseFuncOffset 0x815844							//处理全局Base偏移
#define PassBaseCheckOffset 0x1D3460							//在扫描点下面下hook 效验线程
#define PassBaseAddressOffset 0x232B60							//在jmp上下hook
#define BASEVirtualAllocOffset 0x2B4358							//Base模块调用VirtualAlloc
#define BASEVirtualProtectOffset 0x2B4708						//Base模块调用VirtualProtect
#define BASESleepOffset 0x2B4208								//Base模块调用Sleep
#define BASECreateThreadOffset 0x2B41D0							//Base模块调用CreateThread
//#define BASEGetModuleHandleWOffset 0x2B41F8					//Base模块调用GetModuleHandleW
//#define BASECreateFileWOffset 0x2972B0						//Base模块调用CreateFileW
//#define BASEReadFileOffset 0x297360							//Base模块调用ReadFile

//ATS
#define ATS_CRC_One 0x4FE08E									//ATS_CRC 特征码：44 8A 02 44 88 07 48 BA ?? ?? ?? ?? ?? ?? ?? ?? 48 8D 3C 16 48 BA ?? ?? ?? ?? ?? ?? ?? ?? 48 8D 34 17 48 89 75 00
#define ATS_CRC_Two 0x4FE265
#define ATS_CRC_Three 0x504D67
#define ATS_CRC_Four 0x504F53
#define ATS_CRC_Five 0x4192D6
#define ATSGetCurrentProcessOffset 0x1401A0						//GetCurrentProcess
#define ATSGetModuleInformationOffset 0x140568					//GetModuleInformation
#define ATSGetModuleHandleAOffset 0x140160						//GetModuleHandleA

//CSI
#define CSIGetClassNameWOffset 0x4ED868							//CSI模块调用GetClassNameW
#define CSIEnumWindowsOffset 0x4ED888							//CSI模块调用EnumWindows
#define CSIEnumChildWindowsOffset 0x4ED890						//CSI模块调用EnumChildWindows
#define CSIVirtualAllocOffset 0x4B33A8							//CSI模块调用VirtualAlloc
#define CSIVirtualprotectOffset 0x4B3540						//CSI模块调用Virtualprotect
#define CSISleepOffset 0x4B33E8									//CSI模块调用Sleep
#define CSICreateFileWOffset 0x4B3190							//CSI模块调用CreateFileW
#define CSICreateWindowExWOffset 0x4B37E8						//CSI模块调用CreateWindowExW
#define CSICreateThreadOffset 0x4B34D0							//CSI模块调用CreateThread

//PBC
#define PassPBCCheckOffset 0x78AD0								//在函数头部下hook
#define PassPBCOne 0x3A0D39										//PBC检测瞬移
#define PassPBCTwo 0x57E06										//PBC检测瞬移  未更新
#define PBCCreateThreadOffset 0x9E048							//PBC模块调用CreateThread
#define PBCSleepOffset 0x97040									//PBC模块调用Sleep

//crossfireBase
#define PassCrossFireBaseCheckOffset 0xBBD10					//检测驱动加载				特征码：48 8B C4 55 41 54 41 55 41 56 41 57 48 8D 68 A1 48 81 EC A0 00 00 00 48 C7 45 27 FE FF FF FF 48 89 58 10 48 89 70 18 48 89 78 20 48 8B D9
#define PasscrossBaseFindFirstFileAOffset 0x334408				//crossfireBase模块调用FindFirstFileA

//3*4矩阵，矩阵头往下数8行的地址（不包括矩阵头）
//弹道拿到鼠标XY用动态地址查看访问，找到后地址+4
//无限喷漆没喷搜256 喷了搜257
//换弹搜5，没换搜2
//主武器0，副武器1，近战2，雷3
#define InjectHookOffset 0x1BC604								//dll注入点					特征码：45 33 C9 C7 44 24 ?? 01 00 00 00 45 33 C0 48 ?? ?? ?? 33 D2 FF 15 ?? ?? ?? ?? 85 C0 75 ?? E8 ?? ?? ?? ?? 85 C0
#define Mtrix 0x140525630										//矩阵						特征码：48 8B 0D ?? ?? ?? ?? 48 8D ?? ?? 41 B8 ?? ?? ?? ?? 48 8B 01 FF 90 ?? ?? ?? ??    mov rcx,[cshell_x64.dll+0xXXXXXXX] '矩阵地址 = (cshell_x64.dll+0xXXXXXXX)的值 + 0x2D00 - 0x10
//#define Mtrix 0x140525630										//矩阵						特征码：F3 0F 10 83 ?? ?? ?? ?? F3 0F 10 8B ?? ?? ?? ?? 48 8B 4B ?? 48 85 C9 0F 84 ?? ?? ?? ?? 44 8B 81 ?? ?? ?? ??  [rbx + 0x2D00] - 0x10  |  矩阵地址 = ((rbx的值 + 0x2D00(offset)) - 0x10)  |  注：0x2D00是个偏移，可能存在更新
#define ArraySizeOffset 0x1048									//数组大小
#define PlayerArrayBaseAddress 0x2A87378						//玩家数组
#define ModelOffset 0x2A873E0									//判断模式
#define ModelOffset2 0x2A872EF									//模式基址
#define ChallengeHitchaddress 0x14008EFAD						//挑战挂接点				特征码：8B D9 75 ?? 83 3D ?? ?? ?? ?? 00 74 ?? FF 15 ?? ?? ?? ?? 83 3D ?? ?? ?? ?? 01 7C ?? 4C 8D 0D ?? ?? ?? ?? 4C 8D 05 ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? B8 49 00 00 00 48 83 C4 20 5B C3 FF 15 ?? ?? ?? ?? 84 C0 74 ?? 90
#define Hitchaddress 0x1403B5894								//绘制挂接地址				特征码：45 33 C9 45 33 C0 33 D2 E9 ?? ?? ?? ?? FF 15 ?? ?? ?? ?? 8B D8 
#define DrawIndexedPrimitiveaddress 0x140254CD7					//渲染挂接地址				特征码：44 89 64 24 20 FF 90 ?? ?? 00 00 83 3D ?? ?? ?? ?? 02 7C ?? 8B 84 24 ?? ?? ?? ?? 按顺序数第十个地址
#define SilentTrackAddress 0x140235330 + 0x10					//静默追踪构造				特征码：48 83 EC 28 0F 28 C2 4C 8B CA F3 0F 10 54 24 ?? 
#define RedNameTrackAddress 0x140242418							//红名追踪地址				特征码：4C 89 44 24 ?? 48 89 54 24 ?? 48 89 4C 24 ?? 48 81 EC 98 00 00 00 48 C7 44 24 48 FE FF FF FF
#define RangeTrackAddressOne 0x17352D							//范围追踪1					特征码：F3 0F 11 52 ?? F3 0F 11 4A?? F3 0F 11 42 ?? F3 0F 10 92 ?? ?? ?? ?? F3 0F 10 8A ?? ?? ?? ?? F3 0F 10 82 ?? ?? ?? ?? F3 0F 58 92 ?? ?? ?? ?? F3 0F 58 8A ?? ?? ?? ?? F3 0F 58 82 ?? ?? ?? ?? F3 0F 11 52 ?? F3 0F 11 4A ?? F3 0F 11 42 ?? 0F B6 82 ?? ?? ?? ?? 
#define RangeTrackAddressTwo RangeTrackAddressOne + 0x27		//范围追踪2
#define RangeTrackAddressThree 0x23DC21							//范围追踪3					特征码：F3 0F 11 44 24 ?? 48 8D 4C 24 ?? E8 ?? ?? ?? ?? F3 0F 10 4C 24 ?? 0F 2F C8 76 ?? 
#define BarrierOffset 0x140050060								//障碍判断基址				特征码：4C 8B C9 4C 8B C2 48 8B ?? ?? ?? ?? ?? 49 8B D1 48 8B 01 48 FF ?? 18
#define KnifeDistanceBaseAddress 0x2C2ACA0						//刀距基址 | 武器基址
#define WeaponNumberBaseAddressOne 0x2B3AAC0					//刀距武器序列一 | 武器序列 可以不用更新了
#define WeaponNumberBaseAddressTwo 0x94							//刀距武器序列二
#define WeaponNumberArray 0x8									//刀距武器数组
#define CharacterBaseOffset 0x98								//人物基址偏移
#define SelfAddressOffset 0x289									//本人地址偏移 本人ID
#define CharacterDataOffset 0x290								//OBJECT | 人物数据
#define IsInGameOffset 0x8										//是否游戏
#define PersonalPerspectiveOffset 0x50							//人物基址-50
#define SelfPositionOffset 0x2C4B0B0							//自己位置
#define CLTClientOffset 0x3C8430								//CLTClient
#define CommonLTOffset 0x3CBBA8									//CommonLT
#define ContractingLabelOffset 0x2A1DAAF						//发包标签
#define UnlimitedPaintingBaseAddress 0x2C51284					//无限喷漆
#define SpaceContinuousJumpOffset 0x2C8EA78						//空格连跳
#define RadarOffsetOne 0x121938A								//雷达透视1					特征码：75 ?? 40 84 F6 75 ?? FF 15 ?? ?? ?? ?? 43 39 84 3E ?? ?? ?? ?? 0F 86 ?? ?? ?? ?? 43 83 BC 3E ?? ?? ?? ?? 00
#define RadarOffsetTwo 0x1219544								//雷达透视2					特征码：7E ?? 00 84 C0 ?? ?? ?? ??  00 00 8B 05 ?? ?? ?? ?? 83 C0 ?? 83 F8 01 77 ?? 48 8B 8C 24 ?? ?? ?? ?? 搜出来的地址+0x06
#define RadarOffsetThree 0x12195A4								//雷达透视3					特征码：7E ?? 00 84 C0 ?? ?? ?? ?? 00 00 48 8B 0D ?? ?? ?? ?? 48 8B 01 FF 90 ?? ?? ?? ?? 48 8B 94 24 ?? ?? ?? ?? 84 C0 74 ?? 48 8B 84 24 ?? ?? ?? ?? 搜出来的地址+0x06
#define CharacterUpperBodyActionBaseAddress 0x203E438			//人物上半身动作
#define CharacterLowerBodyActionBaseAddress 0x1F4AEF8			//人物下半身动作
#define NewThrowALittleBaseAddress 0x90FF1F						//新图散弹一点
#define OldThrowALittleBaseAddres 0x12C0650						//旧图散弹一点
#define NewThousandTimesTheRateOfFireBaseAddress 0x8DAEAF		//新图千倍射速基址
#define OldThousandTimesTheRateOfFireBaseAddress 0x12AA2E0		//旧图千倍射速基址
#define BallisticBaseSiteOne 0x917BF1 							//弹道基址普通模式Y  128	2120
#define BallisticBaseSiteTwo 0x917BE6							//弹道基址普通模式X  132	2124
#define BallisticBaseSiteThree 	0x12C79F9						//弹道基址特殊模式Y  128	2120
#define BallisticBaseSiteFour 0x12C79E8  						//弹道基址特殊模式X  132	2124
#define PursuitBallisticBaseSiteOne 0x1641F9F					//弹道基址追击模式Y  128    2120
#define PursuitBallisticBaseSiteTwo 0x1641F8E 					//弹道基址追击模式X  132    2124
#define PersonalBallisticBaseSiteOne 0x160CE6E					//弹道基址多人模式Y	 128    2120
#define PersonalBallisticBaseSiteTwo 0x160CE5D					//弹道基址多人模式X	 132    2124
#define RangeTrackBaseAddress 0x10677C7							//范围增伤基址
#define RangeTrackFuncOffset 0x10A9FC0							//范围增伤函数地址			特征码：4D 8B 5B ?? 48 8B 24 24 E8 ?? ?? ?? ?? 48 8D A4 24 ?? ?? ?? ?? 48 89 6C 24 ?? 48 89 E5 Cshell模块第19个地址下的call
#define InfiniteShieldBaseAddress 0x148F2FF						//圣拳护盾基址
#define InfiniteBackpackBaseAddress 0x24C58F0					//无限背包基址
#define IgnoreSmokeBaseAddress 0xF26445							//无视烟雾基址
#define NewDisconnectTeleportBaseAddress 0x7AFB88				//新图断网瞬移基址
#define OldDisconnectTeleportBaseAddress 0x142B078				//旧图断网瞬移基址
#define RedNameTrackRetAddress RedNameTrackAddress + 0xF		//红名追踪返回地址
#define TextDoesNotBleedBaseAddress 0x127CFE8					//文本不掉血基址 rez\Butes\%s_DZ.ltc
#define StaticDoesNotBleedBaseAddress 0x2668E30
#define ThreeSecondsEarlyBaseAddress 0x23F9B0C
#define ReleasePauseBaseAddressOne 0x1214678					//无视暂停
#define ReleasePauseBaseAddressTwo 0x252BB5D					//无视暂停
#define Code193One 0x9C056E										//代码193
#define Code193Two 0x90E499										//代码193
#define Code193Three 0x9E05F1									//代码193
#define Code193Four 0x129A97B									//代码193	未更新
#define Code193Five 0x8CA37E									//代码193	未更新
#define Code193Six 0x11D094B									//代码193	未更新
#define Code143One 0x90ECB4										//代码143
#define Code143Two 0x90EC12										//代码143
#define Code140One 0x916C68										//代码140	电锯
#define Code140Two 0x1626EEE	    							//代码140	电锯
#define Code141One 0x853717		    							//代码141	电锯
#define Code1_2One 0xA46440										//代码1_2   加速错误代码
#define Code1_2Two 0x67A90F										//代码1_2	未更新
#define Code243One 0x10CD474									//代码243   jmp
#define Code243Two 0x853562										//代码243   nop
#define Code2414 0x985B8E										//代码2414

///////////////////////Hook功能///////////////////////
//#define StaticAccelerationHookOffset 0x98F603											//静步加速Hook地址			特征码：F3 0F 10 83 ?? ?? ?? ?? F3 0F 59 41 ?? 48 8B CB 48 8B 03 F3 0F 11 45 ?? FF 90 ?? ?? ?? ??
//#define StaticAccelerationHookRetOffset StaticAccelerationHookOffset + 0x10				//静步加速Hook返回地址
//#define SquatAccelerationHookOffset 0x98F6B4											//下蹲加速Hook地址			特征码：F3 0F 10 83 ?? ?? ?? ?? F3 0F 59 41 ?? F3 0F 11 45 ?? EB ?? 0F 28 C6 F3 0F 11 45 ??
//#define SquatAccelerationHookRetOffset SquatAccelerationHookOffset + 0x12				//下蹲加速Hook返回地址
//#define BulletWithoutBackSeatHookOffset 0x98FE72										//静态无后Hook地址			特征码：F3 44 0F 10 05 ?? ?? ?? ?? 0F 28 F7 F3 0F 59 BC B7 ?? ?? ?? ?? F3 0F 59 B4 B7 ?? ?? ?? ?? F3 41 0F 59 F8 F3 41 0F 59 F0
//#define BulletWithoutBackSeatHookRetOffset BulletWithoutBackSeatHookOffset + 0x15		//静态无后Hook返回地址
//#define LeftKnifeHookOffset 0x9026C0													//左键千刀Hook地址			特征码：7D ?? F3 41 0F 10 B4 86 ?? ?? ?? ?? 8B 15 ?? ?? ?? ?? 83 FA ?? 77 ?? 0F A3 D5 72 ?? 83 FA ?? 74 ?? 8D ?? ?? 83 F8 01
//#define LeftKnifeHookRetOffset LeftKnifeHookOffset + 0x12								//左键千刀Hook返回地址
//#define RightKnifeHookOffset 0x9025C6													//右键千刀Hook地址			特征码：F3 41 0F 10 B6 ?? ?? ?? ?? E8 ?? ?? ?? ?? 41 0F B7 ?? 48 8B F0 E8 ?? ?? ?? ?? 48 8B D8 48 85 C0 0F 84 ?? ?? ?? ?? 48 63 15 ?? ?? ?? ?? 83 FA 39 77 ?? 48 ?? ?? ?? ?? ?? ?? ??
//#define RightKnifeHookRetOffset RightKnifeHookOffset + 0xE								//右键千刀Hook返回地址
//#define RightKnifeCallOffset 0x5539C0													//右键千刀Call地址			特征码：48 83 EC 38 48 C7 44 24 ?? ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 85 C0 75 ?? B9 F8 00 00 00 E8 ?? ?? ?? ?? 48 89 44 24 ?? 48 8B C8 E8 ?? ?? ?? ?? 90 48 89 05 ?? ?? ?? ?? 48 83 C4 38 C3
//#define SpaceJumpHookOffset 0x13F29B4													//空格连跳Hook地址			特征码：44 0F B6 3D ?? ?? ?? ?? 8B CB FF 90 ?? ?? ?? ?? 84 C0 0F 84 ?? ?? ?? ?? 44 38 B7 ?? ?? ?? ?? 0F 85 ?? ?? ?? ?? 44 38 77 ?? 0F 85 ?? ?? ?? ??
//#define SpaceJumpHookRetOffset SpaceJumpHookOffset + 0x10								//空格连跳Hook返回地址
//#define ZeroBulletChange_NewMapHookOffset 0x90BD9D										//零秒换弹新图Hook地址		特征码：41 8B 96 ?? ???? ?? 49 8B CE FF 90 ?? ?? ?? ?? 84 C0 0F ?? ?? ?? ?? ?? 49 8B 06 49 8B CE
//#define ZeroBulletChange_NewMapHookRetOffset ZeroBulletChange_NewMapHookOffset + 0x10	//零秒换弹新图Hook返回地址
//#define ZeroBulletChange_OldMapHookOffset 0x12BCC8E										//零秒换弹旧图Hook地址		特征码：41 8B 96 ?? ?? ?? ?? 49 8B CE FF 90 ?? ?? ?? ?? 84 C0 0F ?? ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 8D ?? ?? ?? ?? ?? FF 90 ?? ?? ?? ??
//#define ZeroBulletChange_OldMapHookRetOffset ZeroBulletChange_OldMapHookOffset + 0x10	//零秒换弹旧图Hook返回地址
//#define ThroughTheWallHookOffset 0x98D2CC												//人物穿墙Hook地址			特征码：F3 0F 11 89 ?? ?? ?? ?? F3 0F 11 99 ?? ?? ?? ?? F3 0F 11 81 ?? ?? ?? ?? C3
//#define ThroughTheWallHookRetOffset ThroughTheWallHookOffset + 0x10						//人物穿墙Hook返回地址
#define StaticAccelerationHookOffset 0x15F42E2											//静步加速Hook地址			特征码：F3 0F 10 83 ?? ?? ?? ?? F3 0F 59 41 ?? 48 8B CB 48 8B 03 F3 0F 11 45 ?? FF 90 ?? ?? ?? ??
#define SquatAccelerationHookOffset 0xA74094											//下蹲加速Hook地址			特征码：F3 0F 10 83 ?? ?? ?? ?? F3 0F 59 41 ?? F3 0F 11 45 ?? EB ?? 0F 28 C6 F3 0F 11 45 ??
#define BulletWithoutBackSeatHookOffset 0xA7481D										//静态无后Hook地址			特征码：F3 44 0F 10 05 ?? ?? ?? ?? 0F 28 F7 F3 0F 59 BC B7 ?? ?? ?? ?? F3 0F 59 B4 B7 ?? ?? ?? ?? F3 41 0F 59 F8 F3 41 0F 59 F0
#define ZeroBulletChange_NewMapHookOffset 0x9CF14D		//特征变化了								//零秒换弹新图Hook地址		特征码：41 8B 96 ?? ?? ?? ?? 49 8B CE FF 90 ?? ?? ?? ?? 84 C0 0F ?? ?? ?? ?? ?? 49 8B 06 49 8B CE
#define ZeroBulletChange_OldMapHookOffset 0x13802DE										//零秒换弹旧图Hook地址		特征码：41 8B 96 ?? ?? ?? ?? 49 8B CE FF 90 ?? ?? ?? ?? 84 C0 0F ?? ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 8D ?? ?? ?? ?? ?? FF 90 ?? ?? ?? ??
#define FlyOffset 0x232387																//空格飞天Hook地址			特征码：8B 82 ?? ?? ?? ?? 41 89 40 ?? 8B 82 ?? ?? ?? ?? 41 89 40 08 33 C0 48 83 C4 ?? C3 83 3D ?? ?? ?? ?? 00 74 ?? FF 15 ?? ?? ?? ?? 83 3D ?? ?? ?? ?? 01 
#define KillSelfFuncOffset 0xA50450	//变了													//卡不掉血Hook地址			特征码：48 89 5C 24 ?? 55 56 57 48 83 EC ?? 48 8B 0D ?? ?? ?? ?? 48 8D 54 24 ?? 0F 29 74 24 ?? 41 8B E8
#define WeaponFireHookOffset 0x137901E													//武器连发Hook地址			特征码：C6 86 ?? ?? ?? ?? 01 41 0F B7 0E 66 85 C9 78 ?? 8B 15 ?? ?? ?? ?? FF CA 0F BF C1 3B C2 7F ?? 
//未更新
#define ThroughTheWallHookOffset 0x98D2CC												//人物穿墙Hook地址			特征码：F3 0F 11 89 ?? ?? ?? ?? F3 0F 11 99 ?? ?? ?? ?? F3 0F 11 81 ?? ?? ?? ?? C3
#define LeftKnifeHookOffset 0x9026C0													//左键千刀Hook地址			特征码：7D ?? F3 41 0F 10 B4 86 ?? ?? ?? ?? 8B 15 ?? ?? ?? ?? 83 FA ?? 77 ?? 0F A3 D5 72 ?? 83 FA ?? 74 ?? 8D ?? ?? 83 F8 01
#define RightKnifeHookOffset 0x9025C6													//右键千刀Hook地址			特征码：F3 41 0F 10 B6 ?? ?? ?? ?? E8 ?? ?? ?? ?? 41 0F B7 ?? 48 8B F0 E8 ?? ?? ?? ?? 48 8B D8 48 85 C0 0F 84 ?? ?? ?? ?? 48 63 15 ?? ?? ?? ?? 83 FA 39 77 ?? 48 ?? ?? ?? ?? ?? ?? ??
#define SpaceJumpHookOffset 0x13F29B4													//空格连跳Hook地址			特征码：44 0F B6 3D ?? ?? ?? ?? 8B CB FF 90 ?? ?? ?? ?? 84 C0 0F 84 ?? ?? ?? ?? 44 38 B7 ?? ?? ?? ?? 0F 85 ?? ?? ?? ?? 44 38 77 ?? 0F 85 ?? ?? ?? ??



////////////////////////Pass28_3////////////////////////////
#define ByPass28_3 0x3EFB3C										//特征码：E8 ?? ?? ?? ?? 4C ?? ?? 48 ?? ?? 0F 84 ?? ?? ?? ?? F3
#define WeaponIndex 0x61C8										//特征码：48 05 ?? ?? ?? ?? 48 8D 52 08 49 83 E8 01 75 E5 89 3D ?? ?? ?? ?? 89 3D ?? ??
#define _WP_Amount 4335											//武器总数 可见 RB001.REZ
#define WeaponMrg 0x288DDD0										//特征码：48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 08 F3 0F 11 B1

////////////////////////功能偏移////////////////////////////
#define BiochemicalOffset 0x2A8									//生化阵营1
#define BiochemicalCampOffset 0x1143F							//生化阵营偏移 | 玩家阵营
#define BoneOffset 0x28E8										//骨骼偏移
#define ZeroSecondAmmunitionChangeOffset 0x0894					//零秒换弹偏移
#define CurrentWeaponOffset 0x2E4								//当前武器偏移
#define CurrentWeaponIDOffset 0x179C							//当前武器ID偏移 小刀搜：5 M4A1-A搜：2189 PMR-30搜：1414  搜出来地址拿偏移
#define SpaceflyOffset 0x01B4									//空格飞天偏移
#define WeaponFireOffset 0x8AC									//狙击连发偏移
#define StaticStepAccelerationOffset 0x5A4						//静步加速偏移
#define SquatStepAccelerationOffset StaticStepAccelerationOffset + 0x4	//蹲步加速偏移
#define ThroughTheWallOffsetOne 0x16D8									//人物穿墙偏移1
#define ThroughTheWallOffsetTwo ThroughTheWallOffsetOne + 0x08			//人物穿墙偏移2
#define PerspectiveOffset 0x98									//人称视角偏移
#define SelfLiveOffset 0x0C										//自己生存偏移

//人物坐标偏移
#define PlayerXCoordinateOffset 0x19C							//X坐标偏移
#define PlayerYCoordinateOffset 0x194							//Y坐标偏移
#define PlayerZCoordinateOffset 0x198							//Z坐标偏移

//追踪鼠标偏移
#define MouseYOffset 0x858										//鼠标Y轴偏移
#define MouseXOffset MouseYOffset + 0x4							//鼠标X轴偏移

//电锯偏移
#define ElectricSawOffsetOne 0x2F0								//千刀一级偏移
#define ElectricSawOffsetTwo 0x20								//千刀二级偏移
#define ElectricSawOffsetThree 0x1710							//千刀三级偏移
#define ElectricSawOffsetFour 0x8								//千刀四级偏移
#define ElectricSawOffsetFive 0x20								//千刀五级偏移
#define CurrentBulletOffset 0x2D4								//千刀当前子弹偏移
#define WeaponStatuOffset ElectricSawOffsetFive + 0x08			//武器状态偏移	

//浮点飞天偏移
#define MapOffset 0x558											//地图偏移
#define FloatFlayOffsetTwo 0x1B4								//浮点飞天二级偏移
#define FloatFlayControlDirectionOffset 0x8C4					//浮点飞天控制方向偏移

//刀距偏移
#define TapWieldingDistanceOffsetOne 0xF8C						//轻击挥刀距离偏移一
#define TapWieldingDistanceOffsetTwo 0xF90						//轻击挥刀距离偏移二
#define TapSpeedOffsetOne 0xFAC									//轻击速度偏移一
#define TapSpeedOffsetTwo 0xFB0									//轻击速度偏移二
#define TapRangeOffsetOne 0xF9C									//轻击范围偏移一
#define TapRangeOffsetTwo 0xFA0									//轻击范围偏移二
#define HitDistanceOffset 0xFBC									//重击距离偏移
#define HitSpeedOffset 0xFDC									//重击速度偏移
#define HitRangeOffset 0xFCC									//重击范围偏移
#define KnifeMarkDistanceOffset 0xC30							//刀痕距离偏移
#define WeaponNameOffset 0xE									//武器名字偏移

//玩家QQ
#define UserQQNumberOffset 0x38									//玩家QQ偏移

//敌人生存偏移
#define EnemyLiveOffset 0x270


