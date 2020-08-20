#pragma once

// Include Entity3D
#include <Primitives/Entity3D.h>

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

#include "..\Scene3D\Player3D.h"

#include "..\Scene3D\ArmorPickup.h"

class CArmorBar : public CEntity3D
{
public:
	// Constructor
	CArmorBar(void);
	// Destructor
	virtual ~CArmorBar(void);

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

	bool GetArmorBarState();
	void SetArmorBarState(bool state);

	void SetArmorDmgMultiplier(float dmg);


	float GetArmorBarLength();
	void SetArmourBarLength(float length);

protected:
	// A transformation matrix for controlling where to render the entities
	glm::mat4 transform;
	bool armorBar;

	float fHeight, fWidth;

	float armorDmgMultiplier;

	// Handler to the Player3D class
	CPlayer3D* cPlayer3D;

	CArmorPickup* cArmorPickup;

};
