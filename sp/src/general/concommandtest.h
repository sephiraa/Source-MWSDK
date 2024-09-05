// ---------------------------------------------------------------------
// Code written by Gareth Pugh, demonstrates how to create a ConCommand.
// ---------------------------------------------------------------------
// A ConCommand needs the following: name, function, help string, flags. 
// ---------------------------------------------------------------------

#ifndef CONCOMMANDTEST_H
#define CONCOMMANDTEST_H

#include "cbase.h"					// Mandatory include.
#ifndef CLIENT_DLL
#include "props.h"					// Needed for spawnflag.
#endif
#include "datacache/imdlcache.h"	// Needed to precache the model to spawn.

// -----------------------------------------------------------------------
// Spawns an explosive barrel at the position where the player is looking.
// -----------------------------------------------------------------------
void SpawnExplosiveBarrel(void)
{
#ifndef CLIENT_DLL // Don't do this on the Client! This should only be done on the Server.
	MDLCACHE_CRITICAL_SECTION(); // Needed to precache model to be spawned.

	bool allowPrecache = CBaseEntity::IsPrecacheAllowed(); // Should we precache?
	CBaseEntity::SetAllowPrecache(true); // Allow precache.

// ---------------------------------------------------------
// Create a prop_physics entity and give it some properties.
// ---------------------------------------------------------
	CBaseEntity* entity = dynamic_cast<CBaseEntity*>(CreateEntityByName("prop_physics"));
	if (entity)
	{
		entity->PrecacheModel("models/props_c17/oildrum001_explosive.mdl"); // Model to spawn is arbitrary.
		entity->SetModel("models/props_c17/oildrum001_explosive.mdl");
		entity->SetName(MAKE_STRING("barrel")); // Name of the prop is arbitrary.
		entity->AddSpawnFlags(SF_PHYSPROP_ENABLE_PICKUP_OUTPUT); // Allow the prop to be picked up.
		entity->Precache();		// Precache the model of the prop.
		DispatchSpawn(entity);	// Spawn the prop.

		CBasePlayer* pPlayer = UTIL_GetCommandClient(); // Find the player!
		trace_t tr;		// Needed for tracing stuff.
		Vector forward; // Create a Vector that will be given a value.
		pPlayer->EyeVectors(&forward); // Get the direction that points away from the player.
		
// ---------------------------------------------------------
// Create a trace from the player to where they are looking,
// then spawn the prop if the end point is valid.
// ---------------------------------------------------------
		UTIL_TraceLine(pPlayer->EyePosition(), pPlayer->EyePosition() + forward * MAX_TRACE_LENGTH, MASK_SOLID, pPlayer, COLLISION_GROUP_NONE, &tr);

		if (tr.fraction != 1.0)
		{
			tr.endpos.z += 12; // Shift the z-pos up a little bit, so the prop doesn't spawn inside of the floor.
			entity->Teleport(&tr.endpos, NULL, NULL); // Teleport the prop to the position where the player is looking.
			UTIL_DropToFloor(entity, MASK_SOLID); // Drop the prop.
		}
	}
	CBaseEntity::SetAllowPrecache(allowPrecache); // Should we precache?
#endif
}

// -----------------------------------------------------------------
// This is an example of a ConCommand that passes through no inputs.
// -----------------------------------------------------------------
static ConCommand ent_create_explosive_barrel("ent_create_explosive_barrel", SpawnExplosiveBarrel, "Creates an explosive barrel at the location the player is looking.", FCVAR_GAMEDLL | FCVAR_CHEAT);
#endif // CONCOMMANDTEST_H
