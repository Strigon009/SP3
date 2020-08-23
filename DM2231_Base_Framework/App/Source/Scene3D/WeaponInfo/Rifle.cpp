#include "Rifle.h"

/**
@brief Default Constructor
*/
CRifle::CRifle()
{
}

/**
@brief Default Destructor
*/
CRifle::~CRifle()
{
}

/**
@brief Initialise this instance to default values
*/
void CRifle::Init(void)
{
	// Call the parent's Init method
	CWeaponInfo::Init();

	type = CWeaponInfo::WeaponType::RIFLE;
	iAudioReload = 11;
	iAudioShoot = 21;
	// The number of ammunition in a magazine for this weapon
	iMagRounds = 30;
	// The maximum number of ammunition for this magazine for this weapon
	iMaxMagRounds = 30;
	// The current total number of rounds currently carried by this player
	iTotalRounds = 150;
	// The max total number of rounds currently carried by this player
	iMaxTotalRounds = 99;
	//	Weapon Stats
	reloadTime = 3.f;
	weaponDamage = 2.f;
	dTimeBetweenShots = 0.05;
	weaponWeight = 0.75f;
	autoFire = true;
	// The elapsed time (between shots)
	dElapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;
}
