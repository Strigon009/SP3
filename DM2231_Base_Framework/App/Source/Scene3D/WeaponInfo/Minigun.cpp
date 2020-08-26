#include "Minigun.h"

/**
@brief Default Constructor
*/
CMinigun::CMinigun()
{
}

/**
@brief Default Destructor
*/
CMinigun::~CMinigun()
{
}

/**
@brief Initialise this instance to default values
*/
void CMinigun::Init(void)
{
	// Call the parent's Init method
	CWeaponInfo::Init();

	type = CWeaponInfo::WeaponType::MINIGUN;
	iAudioReload = 14;
	iAudioShoot = 24;
	// The number of ammunition in a magazine for this weapon
	iMagRounds = 50;
	// The maximum number of ammunition for this magazine for this weapon
	iMaxMagRounds = 50;
	// The current total number of rounds currently carried by this player
	iTotalRounds = 150;
	// The max total number of rounds currently carried by this player
	iMaxTotalRounds = 300;
	// Weapon Stats
	reloadTime = 5.f;
	weaponDamage = 4.f;
	dTimeBetweenShots = 0.05;
	weaponWeight = 0.65f;
	autoFire = true;
	iMaxOriMaxRounds = iMaxMagRounds;
	weaponRecoil = 0.5f;

	weaponOriRecoil = weaponRecoil;
	// The elapsed time (between shots)
	dElapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;
}
