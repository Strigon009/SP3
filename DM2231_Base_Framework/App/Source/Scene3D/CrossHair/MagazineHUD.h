#pragma once

// Include SingletonTemplate
#include "DesignPatterns\SingletonTemplate.h"

// Include Entity3D
#include <Primitives/Entity3D.h>

#include "../WeaponInfo/WeaponInfo.h"

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

class CMagazineHUD : public CSingletonTemplate<CMagazineHUD>, public CEntity3D
{
	friend class CSingletonTemplate<CMagazineHUD>;

public:
	// Initialise this class instance
	bool Init(void);

	// Set model
	virtual void SetModel(glm::mat4 model);
	// Set view
	virtual void SetView(glm::mat4 view);
	// Set projection
	virtual void SetProjection(glm::mat4 projection);

	// Set crosshair on or off
	virtual void SetStatus(const bool bStatus);
	// Get crosshair status
	virtual bool GetStatus(void) const;

	// Update this class instance
	virtual void Update(const double dElapsedTime);

	// Render
	virtual void Render(void);
	// PreRender
	virtual void PreRender(void);
	// PostRender
	virtual void PostRender(void);

protected:
	// A transformation matrix for controlling where to render the entities
	glm::mat4 transform;

	bool bActive;
	// Constructor
	CMagazineHUD(void);
	// Destructor
	virtual ~CMagazineHUD(void);
};
