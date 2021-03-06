#include "Pistol.h"

/**
@brief Default Constructor
*/
CPistol::CPistol()
{
}

/**
@brief Default Destructor
*/
CPistol::~CPistol()
{
}

/**
@brief Initialise this instance to default values
*/
void CPistol::Init(void)
{
	// Call the parent's Init method
	CWeaponInfo::Init();

	type = CWeaponInfo::WeaponType::PISTOL;
	iAudioReload = 12;
	iAudioShoot = 22;
	// The number of ammunition in a magazine for this weapon
	iMagRounds = 8;
	// The maximum number of ammunition for this magazine for this weapon
	iMaxMagRounds = 8;
	// The current total number of rounds currently carried by this player
	iTotalRounds = INT_MAX;
	// The max total number of rounds currently carried by this player
	iMaxTotalRounds = INT_MAX;
	// Weapon Stats
	reloadTime = 0.7f;
	weaponDamage = 15.f;
	weaponWeight = 1.f;
	dTimeBetweenShots = 0.3333;
	autoFire = false;
	iMaxOriMaxRounds = iMaxMagRounds;
	weaponRecoil = 0.1f;
	weaponOriRecoil = weaponRecoil;
	// The elapsed time (between shots)
	dElapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;
}
