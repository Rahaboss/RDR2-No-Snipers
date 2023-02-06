#include "pch.h"
#include "DetourHook.h"

void DetourHook::Create(void* Target, void* Detour)
{
	m_Target = Target;
	assert(m_Target);
	assert(Detour);
	assert(MH_CreateHook(m_Target, Detour, &m_Original) == MH_OK);
}

void DetourHook::Remove()
{
	assert(MH_RemoveHook(m_Target) == MH_OK);
}
