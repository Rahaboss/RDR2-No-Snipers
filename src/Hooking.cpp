#include "pch.h"
#include "Hooking.h"

// No Snipers for New Austin
void MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(scrNativeCallContext* Context)
{
	constexpr Hash WEAPON_SNIPERRIFLE_CARCANO = joaat("WEAPON_SNIPERRIFLE_CARCANO");

#ifdef _DEBUG
		const float x1 = Context->GetArg<float>(0);
		const float y1 = Context->GetArg<float>(1);
		const float z1 = Context->GetArg<float>(2);
		const float x2 = Context->GetArg<float>(3);
		const float y2 = Context->GetArg<float>(4);
		const float z2 = Context->GetArg<float>(5);
		const int damage = Context->GetArg<int>(6);
		const BOOL p7 = Context->GetArg<BOOL>(7);
		const Hash weaponHash = Context->GetArg<Hash>(8);
		const Ped ownerPed = Context->GetArg<Ped>(9);
		const BOOL isAudible = Context->GetArg<BOOL>(10);
		const BOOL isInvisible = Context->GetArg<BOOL>(11);
		const float speed = Context->GetArg<float>(12);
		const BOOL p13 = Context->GetArg<BOOL>(13);

		printf(__FUNCTION__"(%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %d, %s, %u, %u, %s, %s, %.2f, %s)\n",
			x1, y1, z1, x2, y2, z2, damage, (p7 ? "TRUE" : "FALSE"), weaponHash, ownerPed, (isAudible ? "TRUE" : "FALSE"),
			(isInvisible ? "TRUE" : "FALSE"), speed, (p13 ? "TRUE" : "FALSE")
		);
#endif
	
	// Block the function from running
	if (Context && Context->GetArg<Hash>(8) == WEAPON_SNIPERRIFLE_CARCANO)
		return;

	ShootBulletHook.GetOriginal<decltype(&SHOOT_SINGLE_BULLET_BETWEEN_COORDS)>()(Context);
}

// No Snipers for Guarma
BOOL ENTITY::IS_ENTITY_IN_ANGLED_AREA(scrNativeCallContext* Context)
{
	constexpr uint32_t _originX = 0x44BBD654; // 1502.69775391f

#ifdef _DEBUG
	const Entity entity = Context->GetArg<Entity>(0);
	const float originX = Context->GetArg<float>(1);
	const float originY = Context->GetArg<float>(2);
	const float originZ = Context->GetArg<float>(3);
	const float edgeX = Context->GetArg<float>(4);
	const float edgeY = Context->GetArg<float>(5);
	const float edgeZ = Context->GetArg<float>(6);
	const float angle = Context->GetArg<float>(7);
	const BOOL p8 = Context->GetArg<BOOL>(8);
	const BOOL p9 = Context->GetArg<BOOL>(9);
	const Any p10 = Context->GetArg<Any>(10);

	printf(__FUNCTION__"(%u, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %s, %s, %d)\n",
		entity, originX, originY, originZ, edgeX, edgeY, edgeZ, angle, (p8 ? "TRUE" : "FALSE"),
		(p9 ? "TRUE" : "FALSE"), p10
	);
#endif

	// Spoof the return value
	if (Context && Context->GetArg<uint32_t>(1) == _originX)
	{
		Context->SetRet(static_cast<BOOL>(FALSE));

		return FALSE;
	}

	return EntityInAreaHook.GetOriginal<decltype(&IS_ENTITY_IN_ANGLED_AREA)>()(Context);
}
