/**
 CScene3D
 By: Toh Da Jun
 Date: Mar 2020
 */
#pragma once

// Include SingletonTemplate
#include "DesignPatterns\SingletonTemplate.h"
// Include CStructure3D
#include "Structure3D.h"
#include "Structure3D_2.h"
#include "Structure3D_Tower.h"
// Include shader
#include "RenderControl\shader.h"

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

// Include TextRenderer
#include "RenderControl\TextRenderer.h"

// Include Keyboard controller
#include "Inputs\KeyboardController.h"
// Include Mouse controller
#include "Inputs\MouseController.h"
// Include Joystick controller
#include "Inputs\JoystickController.h"

// FPS Counter
#include "TimeControl\FPSCounter.h"

// Include SoundController
#include "..\SoundController\SoundController.h"

// Include EntityManager
#include "EntityManager.h"

// Include Player3D
#include "Player3D.h"
// Include Enemy3D
#include "Enemy3D.h"
#include "Enemy3D2.h"
#include "Enemy3D3.h"
#include "EnemyBoss3D.h"
// Include Camera
#include "Camera.h"

// Include SkyBox
#include "SkyBox.h"
// Include GroundMap
#include "GroundMap.h"

// Include CameraEffects
#include "../CameraEffects/CameraEffects.h"
// Include ProgressBar
#include "../CameraEffects/HealthBar.h"
#include "../CameraEffects/ArmorBar.h"
// Include Minimap
#include "..\Minimap\Minimap.h"
// Include CrossHair
#include "CrossHair\CrossHair.h"

#include "WeaponInfo/WeaponInfo.h"
// Include Pickups
#include "ArmorPickup.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class CSettings;

class CScene3D : public CSingletonTemplate<CScene3D>
{
	friend CSingletonTemplate<CScene3D>;
public:
	// Init
	bool Init(void);

	// Update
	void Update(const double dElapsedTime);

	// PreRender
	void PreRender(void);

	// Render
	void Render(void);

	// PostRender
	void PostRender(void);

	// Handler to the Shader Program instance
	Shader* cShader;
	// Handler to the LineShader Program instance
	Shader* cSimpleShader;
	// Handler to the Text Shader Program instance
	Shader* textShader;
	// Handler to the SkyBox ShaderProgram instance
	Shader* skyBoxShader;
	// Handler to the groundShader Shader Program instance
	Shader* groundShader;
	// Handler to the GUIShader Shader Program instance
	Shader* cGUIShader;
	// Handler to the GUISimpleShader Shader Program instance
	Shader* cGUISimpleShader;
	// Handler to the RenderToTexture Shader Program instance
	Shader* cRenderToTextureShader;

protected:
	// The handler to the CSettings
	CSettings* cSettings;

	// The handler containing the instance of the CTextRenderer
	CTextRenderer* cTextRenderer;

	// Keyboard Controller singleton instance
	CKeyboardController* cKeyboardController;

	// Mouse Controller singleton instance
	CMouseController* cMouseController;

	// Joystick Controller singleton instance
	CJoystickController* cJoystickController;

	// A transformation matrix for controlling where to render the entities
	glm::mat4 transform;

	// FPS Control
	CFPSCounter* cFPSCounter;

	// Handler to the CSoundController
	CSoundController* cSoundController;

	// Handler to the EntityManager class
	CEntityManager* cEntityManager;

	// Handler to the Player3D class
	CPlayer3D* cPlayer3D;
	// Handler to the camera class
	CCamera* cCamera;

	// Handler to the Player3D class
	//CEnemy3D* cEnemy3D;

	// Handler to the CSkyBox
	CSkyBox* cSkyBox;
	// Handler to the CGround
	CGroundMap* cGroundMap;

	// Handler to the CMinimap
	CCameraEffects* cCameraEffects;
	// Handler to the ProgressBar
	CHealthBar* cHealthBar;
	CArmorBar* cArmorBar;
	// Handler to the CMinimap
	CMinimap* cMinimap;
	// Handler to the CCrossHair
	CCrossHair* cCrossHair;
	CWeaponInfo* cWeaponInfo;
	CArmorPickup* cArmorPickup;

	//CPhysics3D cPhysics3D;

	int wave_count;
	int zombieCount;
	int crawlerCount;
	int scrakeCount;

	int wave1_count;

	bool wave2_start;
	bool wave3_start;
	bool wave4_start;
	bool boss_start;
	bool bossDED;

	float spawnZTimer;
	float spawnCTimer;
	float spawnSTimer;

	bool printLoseScreen;
	bool printWinScreen;

	void AddEnemy(CEnemy3D* cEnemy3D, glm::vec3 pos, glm::vec3 scale);
	void AddEnemy2(CEnemy3D2* cEnemy3D2, glm::vec3 pos, glm::vec3 scale);
	void AddEnemy3(CEnemy3D3* cEnemy3D3, glm::vec3 pos, glm::vec3 scale);
	void AddWall(CStructure3D* cStructure3D, glm::vec3 pos, glm::vec3 scale);
	void AddPillar(CStructure2_3D* cStructure3D, glm::vec3 pos, glm::vec3 scale);
	void AddArmorPickUp(CArmorPickup* cArmorPickup, glm::vec3 pos, glm::vec3 scale);
	
	// Constructor
	CScene3D(void);
	// Destructor
	virtual ~CScene3D(void);
};

