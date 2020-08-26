#pragma once

// Include SingletonTemplate
#include "DesignPatterns\SingletonTemplate.h"

// Include Entity3D
#include <Primitives/Entity3D.h>
#include <cmath>
#include <exception>
#include <ctime>
#include <cstdlib>

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

// Include list
#include <list>

#include "Enemy3D.h"
#include "EnemyBoss3D.h"
#include "Enemy3DBoss.h"
#include "../CameraEffects/HealthBar.h"
#include "../CameraEffects/ArmorBar.h"
#include "../CameraEffects/ExperienceBar.h"
#include "../CameraEffects/InfectionBar.h"
#include "WeaponInfo/WeaponInfo.h"
// Include CrossHair
#include "CrossHair/CrossHair.h"
#include "WeaponInfo/WeaponInfo.h"
#include "WeaponInfo/BarrelAttachment.h"
#include "WeaponInfo/MagazineAttachment.h"
#include "CrossHair/BarrelHUD.h"
#include "CrossHair/MagazineHUD.h"
// Include Pickups
#include "ArmorPickup.h"
#include "HealthPickup.h"
#include "AmmoPickup.h"
#include "Invincibility.h"
#include "FreezeMovement.h"

#include "SMGPickup.h"
#include "RiflePickup.h"
#include "MinigunPickup.h"
#include "../SoundController/SoundController.h"

class CEntityManager : public CSingletonTemplate<CEntityManager>
{
	friend class CSingletonTemplate<CEntityManager>;

public:
	// Initialise this class instance
	bool Init(void);

	// Set model
	virtual void SetModel(glm::mat4 model);
	// Set view
	virtual void SetView(glm::mat4 view);
	// Set projection
	virtual void SetProjection(glm::mat4 projection);

	// Add a CEntity3D* to this class instance
	virtual void Add(CEntity3D* cEntity3D);
	// Remove a CEntity3D* from this class instance
	virtual bool Erase(CEntity3D* cEntity3D);

	// Collision Check for a CEntity3D*
	//virtual bool CollisionCheck(CEntity3D* cEntity3D);
	virtual int CollisionCheck(CEntity3D* cEntity3D);

	// Update this class instance
	virtual int Update(const double dElapsedTime);

	// CleanUp all CEntity3Ds which are marked for deletion
	virtual void CleanUp(void);

	// Render this class instance
	virtual void Render(void);

	int get_enemy_deathCount();
	void set_enemy_deathCount(int x);

	void SetHealthBar(CHealthBar* pBar);

	void SetArmorBar(CArmorBar* pBar);

	void SetExpBar(CExperienceBar* pBar);

	void SetInfectionBar(CInfectionBar* pBar);

	bool get_moveTo();
	void set_moveTo(bool b);

	virtual bool GetInvincibility();
	virtual void SetInvincibility(bool bInvincibility);

	virtual bool GetFreezeMovement();
	virtual void SetFreezeMovement(bool bFreezeMovement);

	void LootDrop(glm::vec3 pos);

	virtual void AddArmorPickUp(CArmorPickup* cArmorPickup, glm::vec3 pos, glm::vec3 scale);
	virtual void AddHealthPickUp(CHealthPickup* cHealthPickup, glm::vec3 pos, glm::vec3 scale);
	virtual void AddAmmoPickUp(CAmmoPickup* cAmmoPickup, glm::vec3 pos, glm::vec3 scale);
	virtual void AddInvincibility(CInvincibility* cInvincibility, glm::vec3 pos, glm::vec3 scale);
	virtual void AddFreezeMovement(CFreezeMovement* cFreezeMovement, glm::vec3 pos, glm::vec3 scale);

	virtual void AddBarrelPickup(CBarrelAttachment* cBarrelAttachment, glm::vec3 pos, glm::vec3 scale);
	virtual void AddMagazinePickup(CMagazineAttachment* cMagazineAttachment, glm::vec3 pos, glm::vec3 scale);
	virtual void AddRiflePickup(CRiflePickup* cRiflePickup, glm::vec3 pos, glm::vec3 scale);
	virtual void AddMinigunPickup(CMinigunPickup* cRiflePickup, glm::vec3 pos, glm::vec3 scale);
	virtual void AddSMGPickup(CSMGPickup* cRiflePickup, glm::vec3 pos, glm::vec3 scale);


	inline void InitRNG(void)
	{
		srand(static_cast<unsigned> (time(0)));
	}//end of InitRNG function

	inline int RandIntMinMax(int min, int max)
	{
		int num = rand() % (max - min + 1);
		return (num + min);
	}//end of RandIntMinMax function
protected:
	// Render Settings
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	// List of CEntity3D
	std::list<CEntity3D*> lEntity3D;

	//CEnemy3D* cEnemy3D;

	//CEnemyBoss3D cEnemyBoss3D;

	// Handler to the Shader Program instance
	Shader* cShader;
	// Handler to the LineShader Program instance
	Shader* cSimpleShader;
	// Handler to the GUIShader Shader Program instance
	Shader* cGUIShader;
	// Handler to the GUISimpleShader Shader Program instance
	Shader* cGUISimpleShader;

	CHealthBar* cHealthBar;
	CArmorBar* cArmorBar;
	CExperienceBar* cExpBar;
	CInfectionBar* cInfectBar;

	CPlayer3D* cPlayer3D;

	CSoundController* cSoundController;

	CWeaponInfo* cPrimaryWeapon;
	CWeaponInfo* cSecondaryWeapon;
	CWeaponInfo* cCurrentWeapon;

	CWeaponInfo* cWeaponInfo;
	CArmorPickup* cArmorPickup;
	CHealthPickup* cHealthPickup;
	CAmmoPickup* cAmmoPickup;
	CInvincibility* cInvincibility;
	CFreezeMovement* cFreezeMovement;

	// Handler to the EntityManager class
	CEntityManager* cEntityManager;

	int enemy_deathCount;

	bool moveTo_Tower;

	bool bInvincibility;
	bool iFrames;
	bool iFramesTower;

	float lastTime, lastTime2, lastTime3;
	float currentTime;
	bool bFreezeMovement;

		// Default Constructor
	CEntityManager(void);
	// Destructor
	virtual ~CEntityManager(void);
};
