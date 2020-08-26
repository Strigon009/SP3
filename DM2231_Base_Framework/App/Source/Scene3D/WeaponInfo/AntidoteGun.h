#pragma once

#include "WeaponInfo.h"

class CAntidoteGun :	public CWeaponInfo
{
public:
	// Default Constructor
	CAntidoteGun(void);
	// Destructor
	virtual ~CAntidoteGun(void);

	// Initialise this instance to default values
	void Init(void);
};

