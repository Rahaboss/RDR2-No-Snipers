#pragma once

#include "pch.h"
#include "rage/scrNativeCallContext.h"
#include "DetourHook.h"

inline DetourHook ShootBulletHook;
namespace MISC
{
	// void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, int damage,
	//     BOOL p7, Hash weaponHash, Ped ownerPed, BOOL isAudible, BOOL isInvisible, float speed, BOOL p13)
	void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(scrNativeCallContext* Context);
}

inline DetourHook EntityInAreaHook;
namespace ENTITY
{
	// BOOL IS_ENTITY_IN_ANGLED_AREA(Entity entity, float originX, float originY, float originZ, float edgeX,
	//     float edgeY, float edgeZ, float angle, BOOL p8, BOOL p9, Any p10)
	BOOL IS_ENTITY_IN_ANGLED_AREA(scrNativeCallContext* Context);
}
