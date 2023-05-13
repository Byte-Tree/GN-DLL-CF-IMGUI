#pragma once
#include "../../pch.h"


class MemoryTools
{
private:

public:
	template<class T> T Read(__int64 address)
	{
		if (!IsBadReadPtr((void*)address, sizeof(T)))
			return *(T*)address;
		return {};
	}
	template<class T> bool Write(__int64 address, const T data)
	{
		if (!IsBadHugeWritePtr((void*)address, sizeof(T)))
		{
			*reinterpret_cast<T*>(address) = data;
			return true;
		}
		return false;
	}

public:
	int ReadInt(__int64 Address);
	__int64 ReadLong(__int64 Address);
	float ReadFloat(__int64 Address);
	BYTE ReadByte(__int64 Address);
	char* ReadChar(__int64 Address);
	BYTE* ReadBytes(__int64 Address, int ReadSize);
	vector<BYTE> ReadVecBytes(__int64 Address, int ReadSize);

	bool WriteInt(__int64 Address, int Data);
	bool WriteInt2(__int64 Address, int Data);
	bool WriteLong(__int64 Address, __int64 Data);
	bool WriteFloat(__int64 Address, float Data);
	bool WriteFloat2(__int64 Address, float Data);
	bool WriteChar(__int64 Address, const char* Data);
	bool WriteBytes(__int64 Address, BYTE Data[], int Size);
	bool WriteVecBytes(__int64 Address, vector<BYTE> Data);

};
