//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Handling for the suit batteries. Added dynamic lights.
//
// $NoKeywords: $FixedByTheMaster974
//=============================================================================//

#include "cbase.h"
#include "hl2_player.h"
#include "basecombatweapon.h"
#include "gamerules.h"
#include "items.h"
#include "engine/IEngineSound.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CItemBattery : public CItem
{
public:
	DECLARE_CLASS( CItemBattery, CItem );
	DECLARE_SERVERCLASS() // Addition.
	DECLARE_DATADESC() // Addition.

	void Spawn( void )
	{ 
		Precache( );
		SetModel( "models/items/battery.mdl" );
		batteryPos = GetAbsOrigin(); // Addition.
		SetThink(&CItemBattery::Think); // Addition.
		SetNextThink(gpGlobals->curtime); // Addition.
		BaseClass::Spawn( );
	}
	void Precache( void )
	{
		PrecacheModel ("models/items/battery.mdl");

		PrecacheScriptSound( "ItemBattery.Touch" );

	}
	bool MyTouch( CBasePlayer *pPlayer )
	{
		CHL2_Player *pHL2Player = dynamic_cast<CHL2_Player *>( pPlayer );
		return ( pHL2Player && pHL2Player->ApplyBattery() );
	}
// ----------
// Additions.
// ----------
	void Think(void)
	{
		batteryPos = GetAbsOrigin();
// ---------------------------------------------------------------------------------------------
// For some reason, batteries that are created by breaking item crates have buggy hit detection,
// so this check allows these batteries to be collected like normal.
// ---------------------------------------------------------------------------------------------
		float distance = CollisionProp()->CalcDistanceFromPoint(UTIL_GetLocalPlayer()->GetAbsOrigin());
		if (distance < 20)
		{
			bool isTouching = MyTouch(UTIL_GetLocalPlayer());
			if (isTouching)
			{
				UTIL_Remove(this);
				SetNextThink(NULL);
			}
		}
		SetNextThink(gpGlobals->curtime + TICK_INTERVAL);
	}

	CNetworkVar(Vector, batteryPos); // Position to be networked to the Client.
};

// -----------------------------
// Declare a Datadesc like this.
// -----------------------------
BEGIN_DATADESC(CItemBattery)
// Standard fields are defined like this.
DEFINE_FIELD(batteryPos, FIELD_POSITION_VECTOR),

// This is how a think function is defined.
DEFINE_THINKFUNC(Think),
END_DATADESC()

// --------------------------------
// Declare a Serverclass like this.
// --------------------------------
IMPLEMENT_SERVERCLASS_ST(CItemBattery, DT_ItemBattery)
// You can SENDINFO like this.
SendPropVector(SENDINFO(batteryPos), -1, SPROP_COORD),
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(item_battery, CItemBattery);
PRECACHE_REGISTER(item_battery);

