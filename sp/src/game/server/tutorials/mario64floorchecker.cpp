// -------------------------------------------------------------------------------
// Code written by Gareth Pugh, highlights what happens when a variable overflows.
// -------------------------------------------------------------------------------
// Includes an exaggerated example of integer overflow from Super Mario 64.
// -------------------------------------------------------------------------------

#include "cbase.h"			// Mandatory include.
#include "tier0/memdbgon.h" // Last file to be included.

// --------------------------------------------------------------------------
// Creates an entity that checks to see if the player is close to the origin.
// --------------------------------------------------------------------------
class CMario64FloorCheck : public CBaseEntity
{
public:
	DECLARE_CLASS(CMario64FloorCheck, CBaseEntity);
	DECLARE_DATADESC();
	void Spawn(void); // What happens when the entity is created?
	void Think(void); // Example of a think function.

private:
	Vector playerPos; // This is the player's position that this entity will use!
};

BEGIN_DATADESC(CMario64FloorCheck)
// Standard fields are defined like this.
DEFINE_FIELD(playerPos, FIELD_POSITION_VECTOR),

// This is how a think function is defined.
DEFINE_THINKFUNC(Think),
END_DATADESC()

LINK_ENTITY_TO_CLASS(mario64floorchecker, CMario64FloorCheck);

// -----------------
// Spawn the entity.
// -----------------
void CMario64FloorCheck::Spawn(void)
{
	BaseClass::Spawn();
	playerPos = vec3_origin;				// Set a stock value to this variable.
	SetThink(&CMario64FloorCheck::Think);	// Set the think function.
	SetNextThink(gpGlobals->curtime);		// Call the Think method immediately!
}

void CMario64FloorCheck::Think(void)
{
// ------------------
// Obtain the player!
// ------------------
	CBasePlayer* pPlayer = UTIL_GetLocalPlayer();
	if (!pPlayer)
		return;

// --------------------------
// Get the player's position.
// --------------------------
	short xPos = pPlayer->GetAbsOrigin().x;
	short yPos = pPlayer->GetAbsOrigin().y;
//	short zPos = pPlayer->GetAbsOrigin().z; // No z-pos as this is vertical height.

// ------------------------
// Where the magic happens!
// ------------------------
	int8 xPos_trun = (int8)xPos;
	int8 yPos_trun = (int8)yPos;

// -----------------------------
// Are we in the level's bounds?
// -----------------------------
	if (xPos_trun >= -128 && xPos_trun < 128 && yPos_trun >= -128 && yPos_trun < 128)
	{
		Msg("The player is in bounds! Is at %i, %i\n", xPos_trun, yPos_trun);
	}
	else
	{
		Warning("The player is NOT in bounds!\n");
	}
	SetNextThink(gpGlobals->curtime + 2); // Next think time is arbitrary.
}