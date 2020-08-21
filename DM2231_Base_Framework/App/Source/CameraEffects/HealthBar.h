#pragma once

// Include Entity3D
#include <Primitives/Entity3D.h>

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

#include "..\Scene3D\Player3D.h"

#include "..\Scene3D\HealthPickup.h"

class CHealthBar : public CEntity3D
{
public:
	// Constructor
	CHealthBar(void);
	// Destructor
	virtual ~CHealthBar(void);

	// Initialise this class instance
	bool Init(glm::vec3 pos, glm::vec4 color);

	// Set model
	virtual void SetModel(glm::mat4 model);
	// Set view
	virtual void SetView(glm::mat4 view);
	// Set projection
	virtual void SetProjection(glm::mat4 projection);

	// Update this class instance
	virtual void Update(const double dElapsedTime);

	// PreRender
	virtual void PreRender(void);
	// Render
	virtual void Render(void);
	// PostRender
	virtual void PostRender(void);

	bool GetHealthBarState();
	void SetHealthBarState(bool state);

	void SetDmgMultiplier(float dmg);

	void AddHealth(float health);
	
	float GetHealthBarLength();
	void SetHealthBarLength(float length);

protected:
	// A transformation matrix for controlling where to render the entities
	glm::mat4 transform;
	bool healthBar;

	float fHeight, fWidth;
	float dmgmultiplier;

	// Handler to the Player3D class
	CPlayer3D* cPlayer3D;

	CHealthPickup* cHealthPickup;
};
