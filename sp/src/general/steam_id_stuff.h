// ------------------------------------------------------------------------------------------------------------------------------------------
// Code written by Gareth Pugh, demonstrates how to use a player's Steam ID number to create a personalized experience. #TheSunIsLeaking lol
// ------------------------------------------------------------------------------------------------------------------------------------------
// WARNING: DO NOT USE THIS FOR NEFARIOUS PURPOSES, OR THERE WILL BE UNFORESEEN CONSEQUENCES!!! Please use this for a good purpose instead :) 
// ------------------------------------------------------------------------------------------------------------------------------------------

#ifndef STEAM_ID_STUFF_H
#define STEAM_ID_STUFF_H

#include "cbase.h"				// Mandatory include.
#include "steam/steam_api.h"	// Needed to obtain Steam ID numbers.

// ---------------------------
// Player index starts from 1.
// ---------------------------
CSteamID steamID = GetSteamIDForPlayerIndex(1);

// ----------------------------------------------------
// 32-bit unsigned integer associated with the steamID.
// ----------------------------------------------------
AccountID_t accountNumber = steamID.GetAccountID();

// -------------------------------------------
// Do something (good/bad) if we find a match!
// -------------------------------------------
void DoSomethingWithSteamIDNumber()
{
// -----------------------------------------------------------------------------
// This is my Steam ID number, however you can change this to whatever you want.
// -----------------------------------------------------------------------------
	if (accountNumber == 92262148)
	{
		Msg("I like your videos!\n");
	}
}
#endif // STEAM_ID_STUFF_H