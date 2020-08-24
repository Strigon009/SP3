#pragma once

#include "WeaponInfo.h"

class CMinigun :	public CWeaponInfo
{
public:
	// Default Constructor
	CMinigun(void);
	// Destructor
	virtual ~CMinigun(void);

	// Initialise this instance to default values
	void Init(void);
};

