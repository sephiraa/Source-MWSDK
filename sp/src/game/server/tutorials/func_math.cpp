// ---------------------------------------------------------------------------------------
// Code written by Gareth Pugh, uses env_beam entities to display a mathematical function.
// ---------------------------------------------------------------------------------------
// Inefficient, but does the job! Might not work for more complex functions.
// ---------------------------------------------------------------------------------------

#include "cbase.h"			// Mandatory include.
#include "beam_shared.h"	// Needed for beam drawing.
#include "Sprite.h"			// Needed for sprite drawing at the end points.
#include "tier0/memdbgon.h"	// Last file to be included.

// -----------------------------------------------------------------------------------
// Creates an entity that uses env_beam entities to represent a mathematical function.
// May crash the game when too many entities are needed to create the visualizer!
// -----------------------------------------------------------------------------------
class CFuncMath : public CBaseEntity
{
public:
	DECLARE_CLASS(CFuncMath, CBaseEntity);
	DECLARE_DATADESC();

	void Precache(void);			 // Initialize any materials that will be used.
	void Spawn(void);				 // What happens when the entity is created?
	void DrawSprites(void);			 // This method creates the sprites at the end points of the visualizer.
	void Function(float A, float P); // This method handles the mathematical function calculations.
	void Think(void);				 // Example of a think function.

	void AddA(inputdata_t& inputdata); // Example of an input function.

protected:
	float sinCoefficient;		// Amplitude of sin wave.
	float sinTimeCoefficient;	// Speed of the sin wave.
	float length;				// How long the function spans in world units.
	float phase;				// Phase amount of the sin/cosine wave.
	Vector zeroPoint;			// Origin point of the entity.

	CSprite* pStartSprite;		// Sprite at the start point.
	CSprite* pEndSprite;		// Sprite at the end point.
};

LINK_ENTITY_TO_CLASS(func_math, CFuncMath);


BEGIN_DATADESC(CFuncMath)

// Keyfields need to be defined in the Hammer editor!
DEFINE_KEYFIELD(sinCoefficient, FIELD_FLOAT, "sinCoefficient"),
DEFINE_KEYFIELD(sinTimeCoefficient, FIELD_FLOAT, "sinTimeCoefficient"),
DEFINE_KEYFIELD(length, FIELD_FLOAT, "length"),
DEFINE_KEYFIELD(phase, FIELD_FLOAT, "phase"),

// Standard fields are defined like this.
DEFINE_FIELD(zeroPoint, FIELD_POSITION_VECTOR),

// This is how an input function is defined.
DEFINE_INPUTFUNC(FIELD_VOID, "AddA", AddA),

// This is how a think function is defined.
DEFINE_THINKFUNC(Think),

END_DATADESC()

// --------------------------
// Initialize materials here.
// --------------------------
void CFuncMath::Precache(void)
{
	BaseClass::Precache();
	PrecacheMaterial("sprites/laserbeam.vmt"); // The material choices are arbitrary.
	PrecacheMaterial("sprites/blueflare1.vmt");
}

// ----------------------
// Entity spawning stuff.
// ----------------------
void CFuncMath::Spawn(void)
{
	BaseClass::Spawn();
	zeroPoint = GetAbsOrigin();			// Acquire the origin of the entity.
	DrawSprites();						// Draw the end point sprites.
	Function(sinCoefficient, phase);	// Call our Function immediately!
	SetThink(&CFuncMath::Think);		// Set the Think function.
	SetNextThink(gpGlobals->curtime);	// Call the Think function immediately!
}

// ---------------------------------
// Create the start and end sprites.
// ---------------------------------
void CFuncMath::DrawSprites(void)
{
	pStartSprite = CSprite::SpriteCreate("sprites/blueflare1.vmt", zeroPoint, false);
	pStartSprite->SetScale(1); // Sprite scale amount is arbitrary.
	pStartSprite->SetTransparency(kRenderGlow, 0, 0, 255, 255, kRenderFxNoDissipation);

	pEndSprite = CSprite::SpriteCreate("sprites/blueflare1.vmt", zeroPoint, false);
	pEndSprite->SetScale(1); // Sprite scale amount is arbitrary.
	pEndSprite->SetTransparency(kRenderGlow, 0, 0, 255, 255, kRenderFxNoDissipation);
}

// ---------------------------------
// Mathematical calculation section!
// ---------------------------------
void CFuncMath::Function(float A, float P)
{
	const int subdivisions = 35;				 // The number of subdivisions is arbitrary, don't go too high!
	Vector positions[subdivisions + 1];			 // Defines an array of Vectors that the function will span across.
	const float spacing = length / subdivisions; // The spacing between the positions Vectors.

// ------------------------------
// Mathematical function section.
// ------------------------------
	for (int i = 0; i <= subdivisions; i++)
	{
		float angleToUse = i * spacing;				// How far along are we?
		positions[i].y = zeroPoint.y + angleToUse;	// Creates equidistant points in the y-axis.
		positions[i].x = zeroPoint.x;				// Keep x-axis positions constant.

// ----------------------------------------------------------------------
// Perform the mathematical function calculation here!
// Current functional form is z = A*sin(theta + phase).
// Indices can be used by using pow(base, exponent) i.e. pow(A, 3) = A^3.
// Uncomment and use cosBit if you want to.
// ----------------------------------------------------------------------
		float sinBit = A * sin(DEG2RAD(angleToUse + (sinTimeCoefficient * P * gpGlobals->curtime)));
//		float cosBit = A * cos(DEG2RAD(angleToUse - (sinTimeCoefficient * P * gpGlobals->curtime)));
		positions[i].z = zeroPoint.z + sinBit; // Set the z-axis positions to represent the mathematical function.
	}

// ---------------------
// Beam drawing section.
// ---------------------
	for (int i = 0; i < subdivisions; i++)
	{
		CBeam* pBeam = CBeam::BeamCreate("sprites/laserbeam.vmt", 1); // Make sure the material matches with what is in Precache!
		pBeam->PointsInit(positions[i], positions[i + 1]); // Feed in the points the beam will draw between.
		pBeam->RelinkBeam(); // Called when start/end positions change.

		// These parameters are all arbitrary!
		pBeam->SetBrightness(255);
		pBeam->SetColor(255, 255, 255);
		pBeam->LiveForTime(0.1f);
	}

// -------------------------
// Set the sprite positions.
// -------------------------
	pStartSprite->SetLocalOrigin(positions[0]);
	pEndSprite->SetLocalOrigin(positions[subdivisions]);
}

// --------------------------------------------------------------------
// Think function, calls methods on a basis determined by SetNextThink.
// --------------------------------------------------------------------
void CFuncMath::Think(void)
{
	Function(sinCoefficient, phase);
	SetNextThink(gpGlobals->curtime + 0.1);
}

// --------------------------------------------------------------
// Input functions can do a lot, like change amplitude/phase etc.
// Here, the sinCoefficient value is incremented by 1.
// --------------------------------------------------------------
void CFuncMath::AddA(inputdata_t& inputdata)
{
	sinCoefficient++;
}