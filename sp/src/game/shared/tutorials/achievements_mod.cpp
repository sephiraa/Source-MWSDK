// -------------------------------------------------------------------------------------------------------------------------
// Code written by Gareth Pugh, this file adds custom achievements into a Source 2013 mod.
// -------------------------------------------------------------------------------------------------------------------------
// To add an achievement, you need an ID number, a name (i.e. everything after ACHIEVEMENT_) and a gamerscore point value.
// -------------------------------------------------------------------------------------------------------------------------
// Achievements that use the DECLARE_MAP_EVENT... macro requires a logic_achievement in a Hammer map to unlock them.
// In Hammer, the logic_achievement's FireEvent Input must be triggered and the Achievement Event must start with
// ACHIEVEMENT_EVENT_ followed by the achievement's name i.e. MOD_HIT_TRIGGER.
// -------------------------------------------------------------------------------------------------------------------------
// To add achievement names/descriptions, they must be added to your mod's mod_english.txt (or mod_language.txt) file
// as "<achievement name>_NAME" "<name>" and "<achievement name>_DESC" "description". This will be in the resource folder.
// -------------------------------------------------------------------------------------------------------------------------
// Achievement icons must be placed in your mod's materials/vgui/achievements folder as <achievement name>.vtf. The .vmt
// files must be included as well. The .vtf file needs to have the SRGB, No Mipmap and No Level Of Detail flags selected (if
// you use VTFEdit). The icons must be 64x64 in size and the .vmt file must contain the following:
// "UnlitGeneric" { "$baseTexture" "vgui\achievements/<achievement name>" }
// -------------------------------------------------------------------------------------------------------------------------
// Locked achievement icons (that are not the default padlock) can be added by adding _bw at the end of the .vtf/.vmt files.
// i.e. <achievement name>_bw.vtf. In addition, the .vmt file must also have "$vertexalpha" "1" included.
// -------------------------------------------------------------------------------------------------------------------------
// If the gamepadui is enabled, achievement icons must be placed in the materials/gamepadui/achievements folder.
// These icons can be 128x128 in size and the .vtf file must have the SRGB flag selected. The above points also apply.
// -------------------------------------------------------------------------------------------------------------------------
#include "cbase.h"

#if GAME_DLL

#include "achievementmgr.h"
#include "baseachievement.h"

CAchievementMgr g_AchievementMgrMod; // Global achievement mgr for Mod.

// ------------------------------------------------------------------------
// This is a list of achievement IDs, replace these with whatever you want!
// ------------------------------------------------------------------------
#define ACHIEVEMENT_MOD_HIT_TRIGGER 1
#define ACHIEVEMENT_MOD_GOT_SECRET_WEAPON 2
#define ACHIEVEMENT_MOD_GOT_COP_KILLS 3

// -------------------------------------------------------------------
// We can add a simple achievement, like hitting a trigger, like this.
// -------------------------------------------------------------------
DECLARE_MAP_EVENT_ACHIEVEMENT(ACHIEVEMENT_MOD_HIT_TRIGGER, "MOD_HIT_TRIGGER", 5);

// --------------------------------------------------------------------------------------------
// This will add a secret achievement! They won't show up in the achievements list when locked.
// --------------------------------------------------------------------------------------------
DECLARE_MAP_EVENT_ACHIEVEMENT_HIDDEN(ACHIEVEMENT_MOD_GOT_SECRET_WEAPON, "MOD_GOT_SECRET_WEAPON", 5);

// -----------------------------------------------------------
// For more complex achievements, they can be added like this.
// -----------------------------------------------------------
class CAchievementModCopKills : public CBaseAchievement
{
	void Init()
	{
		SetFlags(ACH_LISTEN_PLAYER_KILL_ENEMY_EVENTS | ACH_SAVE_WITH_GAME);
		SetVictimFilter("npc_metropolice");
		SetGoal(5);
	}
};
DECLARE_ACHIEVEMENT(CAchievementModCopKills, ACHIEVEMENT_MOD_GOT_COP_KILLS, "MOD_GOT_COP_KILLS", 5);
#endif

/*
* -------------------------------------------------------------------------------------------------------------------
* Here is an example of an achievement that has components. As far as I can tell, you need to have the following:
* 1. class <classname> : public CBaseAchievement [Create a class for the achievement.]
* 2. virtual void Init() [This will contain the next few parts.]
* 3. static const char* szComponents[] = { "<prefix>_item1", "<prefix>_item2", ... }; [Array of components.]
* 4. SetFlags(ACH_HAS_COMPONENTS | ACH_LISTEN_COMPONENT_EVENTS | ACH_SAVE_GLOBAL); [Set the appropriate flags.]
* 5. m_pszComponentNames = szComponents; [Set the component names.]
* 6. m_iNumComponents = ARRAYSIZE(szComponents); [Obtain the total number of components.]
* 7. SetComponentPrefix("<prefix>"); [Set the prefix.]
* 8. SetGoal(m_iNumComponents); [Set the goal.]
* 9. DECLARE_ACHIEVEMENT(<class>, <achievement ID>, <achievement name>, <gamerscore point value>); [Add achievement.]
* -------------------------------------------------------------------------------------------------------------------
class CAchievementHL2FindAllLambdas : public CBaseAchievement
{
	virtual void Init()
	{
		static const char *szComponents[] =
		{
			"HL2_LAMDACACHE_KLEINERSLAB", "HL2_LAMDACACHE_CANALSSTATION", "HL2_LAMDACACHE_VENTCRAWL", "HL2_LAMDACACHE_CANALSTUNNEL",
			"HL2_LAMDACACHE_SEWERGRATE", "HL2_LAMDACACHE_STEAMPIPE", "HL2_LAMDACACHE_CURVEDROOM", "HL2_LAMDACACHE_SHANTYTOWN",
			"HL2_LAMDACACHE_TUNNELLADDER", "HL2_LAMDACACHE_REDBARN", "HL2_LAMDACACHE_ZOMBIEAMBUSH", "HL2_LAMDACACHE_BELOWAPCS",
			"HL2_LAMDACACHE_COUNTERWEIGHT", "HL2_LAMDACACHE_RAILWAYBRIDGE", "HL2_LAMDACACHE_TUNNELPLATFORMS", "HL2_LAMDACACHE_BANKEDCANAL",
			"HL2_LAMDACACHE_CANALWALL", "HL2_LAMDACACHE_CHANNELSPLIT", "HL2_LAMDACACHE_BMEDOCK", "HL2_LAMDACACHE_GENERATORS",
			"HL2_LAMDACACHE_CARCRUSHERARENA", "HL2_LAMDACACHE_RAVENHOLMATTIC", "HL2_LAMDACACHE_MINETUNNELEXIT",
			"HL2_LAMDACACHE_COASTSHACK", "HL2_LAMDACACHE_POISONSHACK", "HL2_LAMDACACHE_GUNSHIPVAN", "HL2_LAMDACACHE_SUICIDECITIZEN",
			"HL2_LAMDACACHE_RAILROADSHACK", "HL2_LAMDACACHE_COASTABOVEBATTERY", "HL2_LAMDACACHE_SANDSHACK", "HL2_LAMDACACHE_GMANCACHE",
			"HL2_LAMDACACHE_CELLCACHE", "HL2_LAMDACACHE_POISONLAUNDRY", "HL2_LAMDACACHE_SODAMACHINE",
			"HL2_LAMDACACHE_STREETWARDOGWALL", "HL2_LAMDACACHE_STREETWARSHACK", "HL2_LAMDACACHE_STREETWARFENCE", "HL2_LAMDACACHE_FREEWAYTUNNEL", "HL2_LAMDACACHE_DRAWBRIDGE",
			"HL2_LAMDACACHE_PLAZAFENCE", "HL2_LAMDACACHE_SEWERSCATWALKS", "HL2_LAMDACACHE_POISONZOMBIEALCOVE", "HL2_LAMDACACHE_PIPEHOPTUNNEL",
			"HL2_LAMDACACHE_ENDOFC1712B", "HL2_LAMDACACHE_EXITCATWALK"
		};
		SetFlags( ACH_HAS_COMPONENTS | ACH_LISTEN_COMPONENT_EVENTS | ACH_SAVE_GLOBAL );
		m_pszComponentNames = szComponents;
		m_iNumComponents = ARRAYSIZE( szComponents );
		SetComponentPrefix( "HL2_LAMDACACHE" );
		SetGoal( m_iNumComponents );
	}
};
DECLARE_ACHIEVEMENT( CAchievementHL2FindAllLambdas, ACHIEVEMENT_HL2_FIND_ALLLAMBDAS, "HL2_FIND_ALLLAMBDAS", 15 );
* -------------------------------------------------------------------------------------------------------------------
* To unlock a component, follow the logic_achievement guidance outlined above. However, the Achievement Event must
* contain ACHIEVEMENT_EVENT_<prefix>_<item>. When all components are triggered, the achievement will unlock.
* -------------------------------------------------------------------------------------------------------------------
* -------------------------------------------------------------------------------------------------------------------
* Failable achievements are complicated, but here's an example from Episode One. As far as I can tell, you need:
* 1. class <classname> : public CFailableAchievement [Create a class for the achievement.]
* 2. void Init() [that contains] SetFlags(ACH_LISTEN_MAP_EVENTS | ACH_SAVE_WITH_GAME); [at least] and SetGoal(1);
* 3. virtual const char* GetActivationEventName() { return "<achievement name>_START"; } [Start point.]
* 4. virtual const char* GetEvaluationEventName() { return "<achievement name>_END"; } [End point.]
* 5. Other code that determines if the player has failed the achievement, could be anything!
* 6. DECLARE_ACHIEVEMENT(<class>, <achievement ID>, <achievement name>, <gamerscore point value>); [Add achievement.]
* -------------------------------------------------------------------------------------------------------------------
* class CAchievementEp1BeatCitizenEscortNoCitizenDeaths : public CFailableAchievement
{
protected:

	void Init() 
	{
		SetFlags( ACH_LISTEN_MAP_EVENTS | ACH_LISTEN_KILL_EVENTS | ACH_SAVE_WITH_GAME );
		SetGameDirFilter( "episodic" );
		SetGoal( 1 );
		SetVictimFilter( "npc_citizen" );
	}

	virtual void Event_EntityKilled( CBaseEntity *pVictim, CBaseEntity *pAttacker, CBaseEntity *pInflictor, IGameEvent *event ) 
	{
		// if any citizens die while this achievement is active, achievement fails
		SetFailed();
	}

	// map event where achievement is activated
	virtual const char *GetActivationEventName() { return "EP1_BEAT_CITIZENESCORT_NOCITIZENDEATHS_START"; }
	// map event where achievement is evaluated for success
	virtual const char *GetEvaluationEventName() { return "EP1_BEAT_CITIZENESCORT_NOCITIZENDEATHS_END"; }
};
DECLARE_ACHIEVEMENT( CAchievementEp1BeatCitizenEscortNoCitizenDeaths, ACHIEVEMENT_EP1_BEAT_CITIZENESCORT_NOCITIZENDEATHS, "EP1_BEAT_CITIZENESCORT_NOCITIZENDEATHS", 15 );
* --------------------------------------------------------------------------------------------------------------------------------------------------
* Failable achievements use two logic_achievement entities, one which activates the achievement and the other is for when the end point is reached.
* Follow the logic_achievement guidance outlined above to add the start/end points. The first logic_achievement's Achievement Event must contain
* ACHIEVEMENT_EVENT_<achievement name>_START and for the end point (the second logic_achievement), the Achievement Event must contain
* ACHIEVEMENT_EVENT_<achievement name>_END. The achievement will lock (thus failing the achievement) if a condition is triggered i.e. a citizen dies
* when all citizens must survive, otherwise the achievement will unlock when the end point is reached.
* --------------------------------------------------------------------------------------------------------------------------------------------------
*/