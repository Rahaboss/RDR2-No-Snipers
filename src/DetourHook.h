#pragma once

#include "pch.h"

class DetourHook
{
public:
	void Create(void* Target, void* Detour);
	void Remove();

	template<typename T>
	inline T GetOriginal() { return reinterpret_cast<T>(m_Original); }

private:
	void* m_Target;
	void* m_Original;
};
