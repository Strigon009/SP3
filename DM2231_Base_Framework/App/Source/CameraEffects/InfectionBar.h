#pragma once

// Include Entity3D
#include <Primitives/Entity3D.h>
#include "DesignPatterns/SingletonTemplate.h"
// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

#include "..\Scene3D\Player3D.h"
#include "..\Scene3D\Structure3D_Tower.h"

class CInfectionBar : public CSingletonTemplate<CInfectionBar> , public CEntity3D
{
	friend class CSingletonTemplate<CInfectionBar>;
public:
	// Constructor
	CInfectionBar(void);
	// Destructor
	virtual ~CInfectionBar(void);

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
	
	virtual void SetiTowerHealth(int towerhp);
	float GetiTowerHealth();
	float GetiTowerMaxHealth();
protected:
	// A transformation matrix for controlling where to render the entities
	glm::mat4 transform;
	bool infectionBar;
	float fHeight, fWidth;
	float iTowerHealth, iTowerMaxHealth;
	// Handler to the Player3D class
	CPlayer3D* cPlayer3D;
	

};
