#pragma once

#pragma warning(disable:4996)

#include <Windows.h>
#include "iltcsbase.h"
#include "ltbasedefs.h"
#include "ltvector.h"
#include "ltbasetypes.h"
#include "iltcommon.h"

#undef FLAG_VISIBLE
#define FLAG_VISIBLE 0x1
#undef FLAG_RAYHIT
#define FLAG_RAYHIT 0x1000
#undef FLAG_SOLID
#define FLAG_SOLID 0x2000
#undef FLAG_GRAVITY
#define FLAG_GRAVITY 0x60000
#define USRFLG_CHARACTER 0x1000
#define USRFLG_HITBOX 0x1000000
//#define OFT_User 2
#define DISABLE_ASSERTS
#define GAMEMODE_NONE 5

#define MID_WEAPON_FIRE 130

class CCommonLT;
class CPhysicsLT;
class CModelLT;
class CLTDrawPrim;
class CLTTransform;

struct CAIntersectQuery
{
	LTVector Start;						//0x0000
	LTVector End;						//0x000C
	char unknown24[12];					//0x0018
	uint32 Flags;						//0x0024
	//ObjectFilterFn FilterFn;			//0x0028
	void* FilterIntersectParam;			//0x002C
	//ObjectFilterFn FilterIntersectFn;	//0x0030
	void* FilterParam;					//0x0034
	void* PolyFilterParam;				//0x0038
	PolyFilterFn PolyFilterFn;			//0x003C
};

struct CAIntersectInfo
{
	LTVector vImpactPos;				//0x0000
	LTPlane ImpactPlane;				//0x000C
	HOBJECT hObjImpact;					//0x001C
	DWORD nSomething;					//0x0020
	DWORD nSomething2;					//0x0024
	DWORD nSomething3;					//0x0028
};

class CLTBase
{
public:
	virtual void function0();			//0x0000
	LTRESULT (*GetTcpIpAddress)(char* sAddress, uint32 BuffSize, uint16& HostPost);	//0x0004
	void (*function2)();				//0x0008
	void (*function3)();				//0x000C
	void (*function4)();				//0x0010
	void (*function5)();				//0x0014
	void (*function6)();				//0x0018
	void (*function7)();				//0x001C
	void (*function8)();				//0x0020
	void (*function9)();				//0x0024
	void (*function10)();				//0x0028
	void (*function11)();				//0x002C
	void (*function12)();				//0x0030
	void (*function13)();				//0x0034
	void (*function14)();				//0x0038
	void (*function15)();				//0x003C
	void (*function16)();				//0x0040
	void (*function17)();				//0x0044
	void (*function18)();				//0x0048
	void (*function19)();				//0x004C
	void (*function20)();				//0x0050
	void (*function21)();				//0x0054
	void (*function22)();				//0x0058
	void (*function23)();				//0x005C
	void (*function24)();				//0x0060
	bool (*IntersectSegment)(const CAIntersectQuery& IQuery, CAIntersectInfo* pInfo);	//0x0064
	void (*function26)();				//0x0068
	void (*function27)();				//0x006C
	void (*function28)();				//0x0070
	void (*function29)();				//0x0074
	void (*function30)();				//0x0078
	LTRESULT (*GetGameMode)(int* Mode);	//0x007C
	LTRESULT (*StartGame)(StartGameRequest* pRequest);	//0x0080
	void (*GetLocalID)(unsigned int* LocalID);	//0x0084
	void (*Disconnect)();				//0x0088
	bool (*IsConnected)();				//0x008C
	void (*Shutdown)();					//0x0090
	void (*ShutdownWithMessage)(const char* pMsg, ...);	//0x0094
	void (*function38)();				//0x0098
	LTRESULT (*Start3D)();				//0x009C
	void (*function40)();				//0x00A0
	void (*function41)();				//0x00A4
	void (*function42)();				//0x00A8
	void (*function43)();				//0x00AC
	void (*function44)();				//0x00B0
	void (*function45)();				//0x00B4
	void (*function46)();				//0x00B8
	void (*function47)();				//0x00BC
	LTRESULT (*End3D)();				//0x00C0
	void (*function49)();				//0x00C4
	void (*function50)();				//0x00C8
	void (*function51)();				//0x00CC
	void (*function52)();				//0x00D0
	void (*function53)();				//0x00D4
	void (*function54)();				//0x00D8
	void (*function55)();				//0x00DC
	void (*function56)();				//0x00E0
	void (*function57)();				//0x00E4
	void (*function58)();				//0x00E8
	void (*function59)();				//0x00EC
	void (*function60)();				//0x00F0
	void (*function61)();				//0x00F4
	void (*function62)();				//0x00F8
	LTRESULT (*RegisterConsoleProgram)(const char* pName, ConsoleProgramFn fn);	//0x00FC
	LTRESULT (*UnregisterConsoleProgram)(const char* pName);	//0x0100
	HCONSOLEVAR (*GetConsoleVariable)(const char* pName);	//0x0104
	void (*function66)();				//0x0108
	void (*function67)();				//0x010C
	void (*function68)();				//0x0110
	void (*function69)();				//0x0114
	void (*function70)();				//0x0118
	void (*function71)();				//0x011C
	void (*function72)();				//0x0120
	void (*function73)();				//0x0124
	void (*function74)();				//0x0128
	void (*function75)();				//0x012C
	void (*function76)();				//0x0130
	void (*function77)();				//0x0134
	void (*function78)();				//0x0138
	void (*function79)();				//0x013C
	void (*function80)();				//0x0140
	void (*function81)();				//0x0144
	void (*function82)();				//0x0148
	void (*function83)();				//0x014C
	void (*function84)();				//0x0150
	void (*function85)();				//0x0154
	void (*function86)();				//0x0158
	void (*function87)();				//0x015C
	void (*function88)();				//0x0160
	void (*function89)();				//0x0164
	void (*function90)();				//0x0168
	void (*function91)();				//0x016C
	void (*function92)();				//0x0170
	void (*function93)();				//0x0174
	void (*function94)();				//0x0178
	void (*function95)();				//0x017C
	void (*function96)();				//0x0180
	void (*function97)();				//0x0184
	void (*function98)();				//0x0188
	void (*function99)();				//0x018C
	void (*function100)();				//0x0190
	void (*function101)();				//0x0194
	void (*function102)();				//0x0198
	void (*function103)();				//0x019C
	void (*function104)();				//0x01A0
	void (*function105)();				//0x01A4
	void (*function106)();				//0x01A8
	void (*function107)();				//0x01AC
	void (*function108)();				//0x01B0
	void (*function109)();				//0x01B4
	void (*function110)();				//0x01B8
	void (*function111)();				//0x01BC
	void (*function112)();				//0x01C0
	void (*function113)();				//0x01C4
	void (*function114)();				//0x01C8
	void (*function115)();				//0x01CC
	void (*function116)();				//0x01D0
	void (*function117)();				//0x01D4
	void (*function118)();				//0x01D8
	void (*function119)();				//0x01DC
	void (*function120)();				//0x01E0
	void (*function121)();				//0x01E4
	void (*function122)();				//0x01E8
	void (*function123)();				//0x01EC
	void (*function124)();				//0x01F0
	void (*function125)();				//0x01F4
	void (*function126)();				//0x01F8
	void (*function127)();				//0x01FC
	void (*function128)();				//0x0200
	void (*function129)();				//0x0204
	LTRESULT (*PushToConsole)(const char* Command);	//0x0208
	HOBJECT (*GetPlayer)();				//0x020C
	void (*function132)();				//0x0210
	void (*function133)();				//0x0214
	void (*function134)();				//0x0218
	LTRESULT (*CreateObject)(ObjectCreateStruct* ocs);	//0x021C
	void (*function136)();				//0x0220
	void (*function137)();				//0x0224
};

class CLTClient : public CLTBase
{
public:
	virtual void function0();				//0x0000
	virtual CCommonLT* Common();			//0x0008
	virtual CPhysicsLT* Physics();					//0x0008
	virtual CLTTransform* GetTransform();	//0x000C
	virtual CModelLT* GetModelLT();			//0x0010
	virtual ILTSoundMgr* CSoundMgr();		//0x0014
	virtual void function6();				//0x0018
	virtual void function7();				//0x001C
	virtual void function8();				//0x0020
	virtual void function9();				//0x0024
	virtual void function10();				//0x0028
	virtual void function11();				//0x002C
	virtual void function12();				//0x0030
	virtual void function13();				//0x0034
	virtual void function14();				//0x0038
	virtual void function15();				//0x003C
	virtual void function16();				//0x0040
	virtual void function17();				//0x0044
	virtual void function18();				//0x0048
	virtual void function19();				//0x004C
	virtual void function20();				//0x0050
	virtual void function21();				//0x0054
	virtual void function22();				//0x0058
	virtual float GetConsoleVariableFloat(HCONSOLEVAR hVar);	//0x005C
	virtual void function24();				//0x0060
	virtual void function25();				//0x0064
	virtual void function26();				//0x0068
	virtual void function27();				//0x006C
	virtual LTRESULT GetSourceWorldOffset(LTVector& vVector);//0x0070
	virtual LTRESULT RemoveObject(HOBJECT hObj);	//0x0074
	virtual void function30();				//0x0078
	virtual void function31();				//0x007C
	virtual void function32();				//0x0080
	virtual void function33();				//0x0084
	virtual void function34();				//0x0088
	virtual void function35();				//0x008C
	virtual void function36();				//0x0090
	virtual void function37();				//0x0094
	virtual void function38();				//0x0098
	virtual void GetObjectRotation(HLOCALOBJ hObj, LTRotation* Rot);	//0x009C
	virtual void GetObjectPos(HLOCALOBJ hObj, LTVector* vPos);	//0x00A0
	virtual void function41();				//0x00A4
	virtual void function42();				//0x00A8
	virtual void function43();				//0x00AC
	virtual void function44();				//0x00B0
	virtual void function45();				//0x00B4
	virtual void function46();				//0x00B8
	virtual void function47();				//0x00BC
	virtual void function48();				//0x00C0
	virtual void SetObjectPos(HLOCALOBJ hObj, LTVector* vPos, float fUnk);	//0x00C4
	virtual void function50();				//0x00C8
	virtual void function51();				//0x00CC
	virtual CLTDrawPrim* GetDrawPrim();	//0x00D0
	virtual void function53();				//0x00D4
	virtual void function54();				//0x00D8
	virtual void function55();				//0x00DC
	virtual void function56();				//0x00E0
	virtual void function57();				//0x00E4
	virtual void function58();				//0x00E8
	virtual void function59();				//0x00EC
	virtual void function60();				//0x00F0
	virtual void function61();				//0x00F4
	virtual void function62();				//0x00F8
	virtual void function63();				//0x00FC
	virtual void function64();				//0x0100
	virtual void function65();				//0x0104
	virtual void function66();				//0x0108
	virtual void function67();				//0x010C
	virtual void function68();				//0x0110
	virtual void function69();				//0x0114
	virtual void function70();				//0x0118
	virtual void function71();				//0x011C
	virtual void function72();				//0x0120
	virtual void function73();				//0x0124
	virtual void function74();				//0x0128
	virtual void function75();				//0x012C
	virtual void function76();				//0x0130
	virtual LTRESULT GetSConValueFloat(const char* Name, float& Val);	//0x0134
	virtual LTRESULT GetSConValueString(const char* Name, char* ValBuff, int BuffLen);	//0x0138
	virtual void function79();				//0x013C
	virtual void function80();				//0x0140
	virtual void function81();				//0x0144
	virtual void function82();				//0x0148
	virtual void function83();				//0x014C
	virtual void function84();				//0x0150
	virtual void function85();				//0x0154
	virtual void function86();				//0x0158
	virtual void function87();				//0x015C
	virtual void function88();				//0x0160
	virtual void function89();				//0x0164
	virtual void function90();				//0x0168
	virtual void function91();				//0x016C
	virtual void function92();				//0x0170
	virtual void function93();				//0x0174
	virtual void function94();				//0x0178
	virtual void function95();				//0x017C
	virtual void function96();				//0x0180
	virtual void function97();				//0x0184
	virtual void function98();				//0x0188
	virtual void function99();				//0x018C
	virtual void function100();			//0x0190
	virtual void function101();			//0x0194
	virtual void function102();			//0x0198
	virtual void function103();			//0x019C
	virtual void function104();			//0x01A0
	virtual void function105();			//0x01A4
	virtual void function106();			//0x01A8
	virtual void function107();			//0x01AC
	virtual void function108();			//0x01B0
	virtual void function109();			//0x01B4
	virtual void function110();			//0x01B8
	virtual void function111();			//0x01BC
	virtual void function112();			//0x01C0
	virtual void function113();			//0x01C4
	virtual void function114();			//0x01C8
	virtual void function115();			//0x01CC
	virtual void function116();			//0x01D0
	virtual void function117();			//0x01D4
	virtual void function118();			//0x01D8
	virtual void function119();			//0x01DC
	virtual void function120();			//0x01E0
	virtual void function121();			//0x01E4
	virtual void function122();			//0x01E8
	virtual void function123();			//0x01EC
	virtual void function124();			//0x01F0
	virtual void function125();			//0x01F4
	virtual void function126();			//0x01F8
	virtual void function127();			//0x01F8站位
	virtual LTRESULT SendToServer(ILTMessage_Read* pMsg, uint32 Flags);	//0x01FC
	virtual LTRESULT GetServerIPAddress(uint8 pAddr[4], uint16* pPort);	//0x0200
//	virtual void function0();				//0x0000
//	virtual CCommonLT* Common();			//0x0004
//	virtual CPhysicsLT* Physics();			//0x0008
//	virtual CLTTransform* GetTransform();	//0x000C
//	virtual CModelLT* GetModelLT();			//0x0010
//	virtual void function5();				//0x0014
//	virtual void function6();				//0x0018
//	virtual void function7();				//0x001C
//	virtual void function8();				//0x0020
//	virtual void function9();				//0x0024
//	virtual void function10();				//0x0028
//	virtual void function11();				//0x002C
//	virtual void function12();				//0x0030
//	virtual void function13();				//0x0034
//	virtual void function14();				//0x0038
//	virtual void function15();				//0x003C
//	virtual void function16();				//0x0040
//	virtual void function17();				//0x0044
//	virtual void function18();				//0x0048
//	virtual void function19();				//0x004C
//	virtual void function20();				//0x0050
//	virtual void function21();				//0x0054
//	virtual void function22();				//0x0058
//	virtual float GetConsoleVariableFloat(HCONSOLEVAR hVar);	//0x005C
//	virtual void function24();				//0x0060
//	virtual void function25();				//0x0064
//	virtual void function26();				//0x0068
//	virtual void function27();				//0x006C
//	virtual void function28();				//0x0070
//	virtual void GetSourceWorldOffset(LTVector& vOffset);	//0x0074
//	virtual LTRESULT RemoveObject(HOBJECT hObj);	//0x0078
//	virtual void function31();				//0x007C
//	virtual void function32();				//0x0080
//	virtual void function33();				//0x0084
//	virtual void function34();				//0x0088
//	virtual void function35();				//0x008C
//	virtual void function36();				//0x0090
//	virtual void function37();				//0x0094
//	virtual void function38();				//0x0098
//	virtual void GetObjectRotation(HLOCALOBJ hObj, LTRotation* Rot);	//0x009C
//	virtual void GetObjectPos(HLOCALOBJ hObj, LTVector* vPos);	//0x00A0
//	virtual void function41();				//0x00A4
//	virtual void function42();				//0x00A8
//	virtual void function43();				//0x00AC
//	virtual void function44();				//0x00B0
//	virtual void function45();				//0x00B4
//	virtual void function46();				//0x00B8
//	virtual void function47();				//0x00BC
//	virtual void function48();				//0x00C0
//	virtual void SetObjectPos(HLOCALOBJ hObj, LTVector* vPos, float fUnk);	//0x00C4
//	virtual void function50();				//0x00C8
//	virtual void function51();				//0x00CC
//	virtual CLTDrawPrim* GetDrawPrim();		//0x00D0
//	virtual void function53();				//0x00D4
//	virtual void function54();				//0x00D8
//	virtual void function55();				//0x00DC
//	virtual void function56();				//0x00E0
//	virtual void function57();				//0x00E4
//	virtual void function58();				//0x00E8
//	virtual void function59();				//0x00EC
//	virtual void function60();				//0x00F0
//	virtual void function61();				//0x00F4
//	virtual void function62();				//0x00F8
//	virtual void function63();				//0x00FC
//	virtual void function64();				//0x0100
//	virtual void function65();				//0x0104
//	virtual void function66();				//0x0108
//	virtual void function67();				//0x010C
//	virtual void function68();				//0x0110
//	virtual void function69();				//0x0114
//	virtual void function70();				//0x0118
//	virtual void function71();				//0x011C
//	virtual void function72();				//0x0120
//	virtual void function73();				//0x0124
//	virtual void function74();				//0x0128
//	virtual void function75();				//0x012C
//	virtual void function76();				//0x0130
//	virtual LTRESULT GetSConValueFloat(const char* Name, float& Val);	//0x0134
//	virtual LTRESULT GetSConValueString(const char* Name, char* ValBuff, int BuffLen);	//0x0138
//	virtual void function79();				//0x013C
//	virtual void function80();				//0x0140
//	virtual void function81();				//0x0144
//	virtual void function82();				//0x0148
//	virtual void function83();				//0x014C
//	virtual void function84();				//0x0150
//	virtual void function85();				//0x0154
//	virtual LTRESULT SendToServer(ILTMessage_Read* pMsg, uint32 Flags);	//0x0158
//	virtual void function87();				//0x015C
};

bool IsVisible(const LTVector& StartPos, const LTVector& EndPos);

class CCommonLT
{
public:
	virtual void function0();				//0x0000
	virtual void function1();				//0x0008
	virtual void function2();				//0x0010
	virtual void function3();				//0x0018
	virtual void function4();				//0x0020
	virtual void function5();				//0x0028
	virtual void function6();				//0x0030
	virtual void function7();				//0x0038
	virtual void function8();				//0x0040
	virtual LTRESULT CreateMessage(ILTMessage_Write*& pMsg);	//0x0048
	virtual void function10();				//0x0050
	virtual void function11();				//0x0058
	virtual void function12();				//0x0060
	virtual void function13();				//0x0068
	virtual void function14();				//0x0070
	virtual void function15();				//0x0078
	virtual void function16();				//0x0080
	virtual void GetObjectFlags(const HOBJECT hObj, const ObjFlagType flagType, uint32& dwFlags);	//0x0088
	virtual void SetObjectFlags(HOBJECT hObj, const ObjFlagType flagType, uint32 dwFlags, uint32 dwMask);	//0x0090
};