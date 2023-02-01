#pragma once

#include "pch.h"
#include "joaat.h"

class scrVector
{
public:
	__declspec(align(8)) float x, y, z;

	scrVector() = default;

	constexpr scrVector(float _x, float _y, float _z) :
		x(_x), y(_y), z(_z)
	{
	}
}; //Size: 0x0018
static_assert(sizeof(scrVector) == 24);

class __declspec(align(16)) scrVec3N
{
public:
	float x, y, z;
}; //Size: 0x0010
static_assert(sizeof(scrVec3N) == 16);

class scrNativeCallContext
{
public:
	void* m_ReturnValue; //0x0000
	uint32_t m_ArgCount; //0x0008
	uint64_t* m_Args; //0x0010
	uint32_t m_DataCount; //0x0018
	scrVector* m_OutVectors[4]; //0x0020
	scrVec3N m_InVectors[4]; //0x0040
	uint8_t pad[96]; //0x0080

	template<typename T>
	T& GetArg(size_t Index)
	{
		return *(T*)(&(m_Args[Index]));
	}

	template<typename T>
	void SetArg(size_t Index, T Arg)
	{
		GetArg<T>(Index) = Arg;
	}

	template<typename T>
	T& GetRet()
	{
		return *(T*)(m_ReturnValue);
	}

	template<typename T>
	void SetRet(size_t Index, T Ret)
	{
		GetRet<T>(Index) = Ret;
	}
}; //Size: 0x00E0
static_assert(sizeof(scrNativeCallContext) == 0xE0);

typedef int32_t Any;
typedef int32_t Blip;
typedef int32_t Cam;
typedef int32_t Entity;
typedef int32_t FireId;
typedef joaat_t Hash;
typedef int32_t Interior;
typedef int32_t ItemSet;
typedef Entity Object;
typedef Entity Ped;
typedef Object Pickup;
typedef int32_t Player;
typedef Entity ScrHandle;
typedef Entity Vehicle;

typedef int32_t AnimScene;
typedef int32_t PersChar;
typedef int32_t PopZone;
typedef int32_t Prompt;
typedef int32_t PropSet;
typedef int32_t Volume;

typedef scrVector Vector3;

typedef void (*scrNativeHandler)(scrNativeCallContext*);
