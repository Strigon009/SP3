#include "AntidoteGun.h"

/**
@brief Default Constructor
*/
CAntidoteGun::CAntidoteGun()
{
}

/**
@brief Default Destructor
*/
CAntidoteGun::~CAntidoteGun()
{
}

/**
@brief Initialise this instance to default values
*/
void CAntidoteGun::Init(void)
{
	// Call the parent's Init method
	CWeaponInfo::Init();

	type = CWeaponInfo::WeaponType::ANTIDOTEGUN;
	iAudioReload = 15;
	iAudioShoot = 25;
	// The number of ammunition in a magazine for this weapon
	iMagRounds = 1;
	// The maximum number of ammunition for this magazine for this weapon
	iMaxMagRounds = 1;
	// The current total number of rounds currently carried by this player
	iTotalRounds = INT_MAX;
	// The max total number of rounds currently carried by this player
	iMaxTotalRounds = INT_MAX;
	// Weapon Stats
	reloadTime = 10.f;
	weaponDamage = 75.f;
	weaponWeight = 1.f;
	dTimeBetweenShots = 0.3333;
	autoFire = false;
	iMaxOriMaxRounds = iMaxMagRounds;
	weaponRecoil = 50.f;
	// The elapsed time (between shots)
	dElapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;
}
