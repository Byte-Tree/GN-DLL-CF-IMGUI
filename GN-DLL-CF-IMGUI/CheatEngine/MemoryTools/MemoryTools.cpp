#include "MemoryTools.h"

int MemoryTools::ReadInt(__int64 Address)
{
	if (IsBadReadPtr((VOID*)Address, 4))
		return 0;
	return *(DWORD*)Address;
}

__int64 MemoryTools::ReadLong(__int64 Address)
{
	if (IsBadReadPtr((VOID*)Address, 8))
		return 0;
	return *(ULONG64*)Address;
}

float MemoryTools::ReadFloat(__int64 Address)
{
	if (IsBadReadPtr((VOID*)Address, 8))
		return 0;
	return *(float*)Address;
}

BYTE MemoryTools::ReadByte(__int64 Address)
{
	if (IsBadReadPtr((VOID*)Address, 1))
		return 0;
	return *(BYTE*)Address;
}

char* MemoryTools::ReadChar(__int64 Address)
{
	if (IsBadReadPtr((VOID*)Address, 4))
		return 0;
	return (char*)Address;
}

BYTE* MemoryTools::ReadBytes(__int64 Address, int ReadSize)
{
	BYTE ReturnValue[] = { NULL };
	if (IsBadReadPtr((VOID*)Address, ReadSize))
		return { 0x00 };
	for (int i = 0; i < ReadSize; i++)
		ReturnValue[i] = *(BYTE*)Address++;
	return ReturnValue;
}

vector<BYTE> MemoryTools::ReadVecBytes(__int64 Address, int ReadSize)
{
	vector<BYTE> ReturnValue;
	if (IsBadReadPtr((VOID*)Address, ReadSize))
		return {};
	for (unsigned int i = 0; i < ReadSize; i++)
		ReturnValue.insert(ReturnValue.end(), *(BYTE*)Address++);
	return ReturnValue;
}


bool MemoryTools::WriteInt(__int64 Address, int Data)
{
	DWORD OldProtect;
	VirtualProtect((PVOID)Address, sizeof(int), 64, &OldProtect);
	if (IsBadWritePtr((VOID*)Address, 4))
	{
		VirtualProtect((PVOID)Address, sizeof(int), OldProtect, &OldProtect);
		return FALSE;
	}
	*(ULONG64*)Address = Data;
	VirtualProtect((PVOID)Address, sizeof(int), OldProtect, &OldProtect);
	return TRUE;
}

bool MemoryTools::WriteInt2(__int64 Address, int Data)
{
	DWORD OldProtect;
	VirtualProtect((LPVOID)Address, 4, 64, &OldProtect);
	if (IsBadWritePtr((VOID*)Address, 4))
	{
		VirtualProtect((LPVOID)Address, 4, OldProtect, &OldProtect);
		return FALSE;
	}
	*(ULONG64*)Address = Data;
	VirtualProtect((LPVOID)Address, 4, OldProtect, &OldProtect);
	return TRUE;
}

bool MemoryTools::WriteLong(__int64 Address, __int64 Data)
{
	//DWORD OldProtect;
	//VirtualProtect((LPVOID)Address, 8, 64, &OldProtect);
	//if (IsBadReadPtr((VOID*)Address, 8))
	//{
	//	VirtualProtect((LPVOID)Address, 8, OldProtect, &OldProtect);
	//	return FALSE;
	//}
	//*(ULONG64*)Address = Data;
	//VirtualProtect((LPVOID)Address, 8, OldProtect, &OldProtect);
	//return TRUE;
	DWORD OldProtect;
	VirtualProtect((PVOID)Address, sizeof(__int64), 64, &OldProtect);
	if (IsBadWritePtr((VOID*)Address, 8))
	{
		VirtualProtect((PVOID)Address, sizeof(__int64), OldProtect, &OldProtect);
		return FALSE;
	}
	*(ULONG64*)Address = Data;
	VirtualProtect((PVOID)Address, sizeof(__int64), OldProtect, &OldProtect);
	return TRUE;
}

bool MemoryTools::WriteFloat(__int64 Address, float Data)
{
	DWORD OldProtect;
	VirtualProtect((PVOID)Address, sizeof(float), 64, &OldProtect);
	if (IsBadWritePtr((VOID*)Address, 4))
	{
		VirtualProtect((PVOID)Address, sizeof(float), OldProtect, &OldProtect);
		return FALSE;
	}
	*(float*)Address = Data;
	VirtualProtect((PVOID)Address, sizeof(float), OldProtect, &OldProtect);
	return TRUE;
}

bool MemoryTools::WriteFloat2(__int64 Address, float Data)
{
	DWORD OldProtect;
	VirtualProtect((PVOID)Address, sizeof(Data), 64, &OldProtect);
	if (IsBadWritePtr((VOID*)Address, sizeof(float)))
	{
		VirtualProtect((PVOID)Address, sizeof(Data), OldProtect, &OldProtect);
		return FALSE;
	}
	*(float*)Address = Data;
	VirtualProtect((PVOID)Address, sizeof(Data), OldProtect, &OldProtect);
	return TRUE;
}

bool MemoryTools::WriteChar(__int64 Address, const char* Data)
{
	DWORD OldProtect;
	VirtualProtect((PVOID)Address, strlen(Data), 64, &OldProtect);
	if (IsBadWritePtr((VOID*)Address, strlen(Data)))
	{
		//printf("没有权限写入\n");
		VirtualProtect((PVOID)Address, strlen(Data), OldProtect, &OldProtect);
		return FALSE;
	}
	strcpy((char*)Address, Data);
	VirtualProtect((PVOID)Address, strlen(Data), OldProtect, &OldProtect);
	return TRUE;
}

bool MemoryTools::WriteBytes(__int64 Address, BYTE Data[], int Size)
{
	DWORD OldProtect;
	VirtualProtect((PVOID)Address, Size, 64, &OldProtect);
	if (IsBadWritePtr((VOID*)Address, Size))
	{
		VirtualProtect((PVOID)Address, Size, OldProtect, &OldProtect);
		return FALSE;
	}
	memcpy((__int64*)Address, Data, Size);
	VirtualProtect((PVOID)Address, Size, OldProtect, &OldProtect);
	return TRUE;
}

bool MemoryTools::WriteVecBytes(__int64 Address, vector<BYTE> Data)
{
	DWORD old_protect;
	VirtualProtect((LPVOID)Address, Data.size(), 64, &old_protect);//修改内存属性
	if (IsBadReadPtr((VOID*)Address, Data.size()))
	{
		VirtualProtect((LPVOID)Address, Data.size(), old_protect, &old_protect);//还原内存属性
		return FALSE;
	}
	for (size_t i = 0; i < Data.size(); i++)
	{
		*(BYTE*)Address++ = Data[i];
	}
	VirtualProtect((LPVOID)Address, Data.size(), old_protect, &old_protect);//还原内存属性
	return TRUE;
}

