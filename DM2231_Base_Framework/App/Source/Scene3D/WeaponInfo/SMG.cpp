#include "SMG.h"

/**
@brief Default Constructor
*/
CSMG::CSMG()
{
}

/**
@brief Default Destructor
*/
CSMG::~CSMG()
{
}

/**
@brief Initialise this instance to default values
*/
void CSMG::Init(void)
{
	// Call the parent's Init method
	CWeaponInfo::Init();

	type = CWeaponInfo::WeaponType::RIFLE;
	iAudioReload = 11;
	iAudioShoot = 21;
	// The number of ammunition in a magazine for this weapon
	iMagRounds = 25;
	// The maximum number of ammunition for this magazine for this weapon
	iMaxMagRounds = 25;
	// The current total number of rounds currently carried by this player
	iTotalRounds = 75;
	// The max total number of rounds currently carried by this player
	iMaxTotalRounds = 150;
	// Weapon Stats
	reloadTime = 1.8f;
	weaponDamage = 2.f;
	dTimeBetweenShots = 0.05;
	weaponWeight = 0.85f;
	autoFire = true;
	iMaxOriMaxRounds = iMaxMagRounds;
	weaponRecoil = 0.12f;
	weaponOriRecoil = weaponRecoil;
	// The elapsed time (between shots)
	dElapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;
}
