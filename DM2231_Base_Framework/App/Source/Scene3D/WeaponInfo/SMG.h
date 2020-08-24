#pragma once

#include "WeaponInfo.h"

class CSMG :	public CWeaponInfo
{
public:
	// Default Constructor
	CSMG(void);
	// Destructor
	virtual ~CSMG(void);

	// Initialise this instance to default values
	void Init(void);
};

