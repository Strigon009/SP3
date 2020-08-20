#include "Scene3D.h"
#include <iostream>
using namespace std;

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "System\filesystem.h"

// Include this for glm::to_string() function
#define GLM_ENABLE_EXPERIMENTAL
#include <includes/gtx/string_cast.hpp>

// Include Pistol
#include "WeaponInfo\Pistol.h"


#include "WeaponInfo/Rifle.h"

void CScene3D::AddEnemy(CEnemy3D* cEnemy3D, glm::vec3 pos, glm::vec3 scale)
{
	cEnemy3D = new CEnemy3D(pos);
	cEnemy3D->SetShader(cShader);
	cEnemy3D->SetScale(scale);
	cEnemy3D->SetColliderScale(scale);
	cEnemy3D->Init();
	cEnemy3D->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cEnemy3D);
}

void CScene3D::AddEnemy2(CEnemy3D2* cEnemy3D2, glm::vec3 pos, glm::vec3 scale)
{
	cEnemy3D2 = new CEnemy3D2(pos);
	cEnemy3D2->SetShader(cShader);
	cEnemy3D2->SetScale(scale);
	cEnemy3D2->SetColliderScale(scale);
	cEnemy3D2->Init();
	cEnemy3D2->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cEnemy3D2);
}

void CScene3D::AddEnemy3(CEnemy3D3* cEnemy3D3, glm::vec3 pos, glm::vec3 scale)
{
	cEnemy3D3 = new CEnemy3D3(pos);
	cEnemy3D3->SetShader(cShader);
	cEnemy3D3->SetScale(scale);
	cEnemy3D3->SetColliderScale(scale);
	cEnemy3D3->Init();
	cEnemy3D3->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cEnemy3D3);
}
void CScene3D::AddWall(CStructure3D* cStructure3D, glm::vec3 pos, glm::vec3 scale)
{
	cStructure3D = new CStructure3D(pos);
	cStructure3D->SetShader(cShader);
	cStructure3D->Init();
	cStructure3D->SetScale(scale);
	cStructure3D->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cStructure3D);

}

void CScene3D::AddPillar(CStructure2_3D* cStructure3D, glm::vec3 pos, glm::vec3 scale)
{
	cStructure3D = new CStructure2_3D(pos);

	cStructure3D->SetShader(cShader);
	cStructure3D->Init();
	cStructure3D->SetScale(scale);
	cStructure3D->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cStructure3D);

}

void CScene3D::AddArmorPickUp(CArmorPickup* cArmorPickup, glm::vec3 pos, glm::vec3 scale)
{
	cArmorPickup = new CArmorPickup(pos);

	cArmorPickup->SetShader(cShader);
	cArmorPickup->Init();
	cArmorPickup->SetScale(scale);
	cArmorPickup->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cArmorPickup);

}

void CScene3D::AddHealthPickUp(CHealthPickup* cHealthPickup, glm::vec3 pos, glm::vec3 scale)
{
	cHealthPickup = new CHealthPickup(pos);

	cHealthPickup->SetShader(cShader);
	cHealthPickup->Init();
	cHealthPickup->SetScale(scale);
	cHealthPickup->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cHealthPickup);
}

void CScene3D::AddPowerUp(CPowerUp* cPowerUp, glm::vec3 pos, glm::vec3 scale)
{
	cPowerUp = new CPowerUp(pos);

	cPowerUp->SetShader(cShader);
	cPowerUp->Init();
	cPowerUp->SetScale(scale);
	cPowerUp->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cPowerUp);
}

/**
 @brief Constructor This constructor has protected access modifier as this class will be a Singleton
 */
CScene3D::CScene3D(void)
	: cSettings(NULL)
	, cShader(NULL)
	, cSimpleShader(NULL)
	, cTextRenderer(NULL)
	, cGUIShader(NULL)
	, cGUISimpleShader(NULL)
	, cRenderToTextureShader(NULL)
	, cKeyboardController(NULL)
	, cMouseController(NULL)
	, cJoystickController(NULL)
	, cFPSCounter(NULL)
	, cSoundController(NULL)
	, cEntityManager(NULL)
	, cPlayer3D(NULL)
	, cCamera(NULL)
	, cSkyBox(NULL)
	, cGroundMap(NULL)
	, cCameraEffects(NULL)
	, cHealthBar(NULL)
	, cArmorBar(NULL)
	, cExpBar(NULL)
	, cMinimap(NULL)
	, cCrossHair(NULL)
	, cWeaponInfo(NULL)
	, cArmorPickup(NULL)
	, cHealthPickup(NULL)
	, cPowerUp(NULL)
	, renderBoss(false)
	, printLoseScreen(false)
	, printWinScreen(false)
	, bossDED(false)
{
	wave_count = 0;
	zombieCount = crawlerCount = scrakeCount = 0;

	wave2_start = wave3_start = wave4_start = boss_start = false;

	spawnZTimer = spawnCTimer = spawnSTimer = 0;
	
	bossDED = false;

	printLoseScreen, printWinScreen = false;
}

/**
 @brief Destructor
 */
CScene3D::~CScene3D(void)
{
	// Destroy the cMinimap
	if (cCrossHair)
	{
		cCrossHair->Destroy();
		cCrossHair = NULL;
	}

	// Destroy the cMinimap
	if (cMinimap)
	{
		cMinimap->Destroy();
		cMinimap = NULL;
	}
	
	// Destroy the cCameraEffects
	if (cHealthBar)
	{
		delete cHealthBar;
		cHealthBar = NULL;
	}
	// Destroy the cCameraEffects
	if (cArmorBar)
	{
		delete cArmorBar;
		cArmorBar = NULL;
	}
	// Destroy the cCameraEffects
	if (cExpBar)
	{
		delete cExpBar;
		cExpBar = NULL;
	}

	// Destroy the cCameraEffects
	if (cCameraEffects)
	{
		cCameraEffects->Destroy();
		cCameraEffects = NULL;
	}

	// Destroy the cGroundMap
	if (cGroundMap)
	{
		cGroundMap->Destroy();
		cGroundMap = NULL;
	}

	// Destroy the cSkyBox
	if (cSkyBox)
	{
		cSkyBox->Destroy();
		cSkyBox = NULL;
	}

	// Destroy the camera
	if (cCamera)
	{
		cCamera->Destroy();
		cCamera = NULL;
	}

	// Destroy the cPlayer3D
	if (cPlayer3D)
	{
		cPlayer3D->Destroy();
		cPlayer3D = NULL;
	}

	// Destroy the cEntityManager
	if (cEntityManager)
	{
		cEntityManager->Destroy();
		cEntityManager = NULL;
	}
	// Destroy the cSoundController
	if (cSoundController)
	{
		cSoundController->Destroy();
		cSoundController = NULL;
	}

	// We won't delete this since it was created elsewhere
	cFPSCounter = NULL;

	// Destroy the cJoystickController
	if (cJoystickController)
	{
		cJoystickController->Destroy();
		cJoystickController = NULL;
	}

	// We won't delete this since it was created elsewhere
	cMouseController = NULL;

	// We won't delete this since it was created elsewhere
	cKeyboardController = NULL;
	

	if (cTextRenderer)
	{
		cTextRenderer->Destroy();
		cTextRenderer = NULL;
	}

	if (cRenderToTextureShader)
	{
		delete cRenderToTextureShader;
		cRenderToTextureShader = NULL;
	}
	if (cGUISimpleShader)
	{
		delete cGUISimpleShader;
		cGUISimpleShader = NULL;
	}
	if (cGUIShader)
	{
		delete cGUIShader;
		cGUIShader = NULL;
	}
	if (groundShader)
	{
		delete groundShader;
		groundShader = NULL;
	}
	if (skyBoxShader)
	{
		delete skyBoxShader;
		skyBoxShader = NULL;
	}
	if (textShader)
	{
		delete textShader;
		textShader = NULL;
	}

	if (cSimpleShader)
	{
		delete cSimpleShader;
		cSimpleShader = NULL;
	}

	if (cShader)
	{
		delete cShader;
		cShader = NULL;
	}

	if (cWeaponInfo)
	{
		cWeaponInfo = NULL;
	}

	// We won't delete this since it was created elsewhere
	cSettings = NULL;
	cArmorPickup = NULL;

	cHealthPickup = NULL;

	cPowerUp = NULL;
}

/**
 @brief Init Initialise this instance
 @return true if the initialisation is successful, else false
 */ 
bool CScene3D::Init(void)
{
	cSettings = CSettings::GetInstance();

	srand(time(NULL));

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Setup the shaders
	cShader = new Shader("Shader//Scene3D.vs", "Shader//Scene3D.fs");
	// Setup the shaders
	cSimpleShader = new Shader("Shader//SimpleShader.vs", "Shader//SimpleShader.fs");
	// Setup the shaders
	textShader = new Shader("Shader//text.vs", "Shader//text.fs");
	// Setup the shaders
	skyBoxShader = new Shader("Shader//SkyBox.vs", "Shader//SkyBox.fs");
	// Setup the shaders
	groundShader = new Shader("Shader//Ground.vs", "Shader//Ground.fs");
	// Setup the shaders
	cGUIShader = new Shader("Shader//GUIShader.vs", "Shader//GUIShader.fs");
	// Setup the shaders
	cGUISimpleShader = new Shader("Shader//GUISimpleShader.vs", "Shader//GUISimpleShader.fs");
	// Setup the shaders
	cRenderToTextureShader = new Shader("Shader//RenderToTexture.vs", "Shader//RenderToTexture.fs");

	// Configure the camera
	cCamera = CCamera::GetInstance();
	cCamera->vec3Position = glm::vec3(0.0f, 0.5f, 3.0f);

	// Store the keyboard controller singleton instance here
	cKeyboardController = CKeyboardController::GetInstance();

	// Store the mouse controller singleton instance here
	cMouseController = CMouseController::GetInstance();

	// Store the joystick controller singleton instance here
	cJoystickController = CJoystickController::GetInstance();
	// Initialise the joystick controller. It will help us to find a joystick connected to your computer
	cJoystickController->Init();

	// Store the CFPSCounter singleton instance here
	cFPSCounter = CFPSCounter::GetInstance();

	// Load the sounds into CSoundController
	cSoundController = CSoundController::GetInstance();
	cSoundController->Init();

	cSoundController->LoadSound(FileSystem::getPath("Sounds\\damage.ogg"), 1, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\wallbump.ogg"), 2, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\pistolshot.ogg"), 3, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\rifle.ogg"), 4, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\losesound.ogg"), 5, true, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\winsound.ogg"), 6, true, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\bossmusic.ogg"), 7, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\pistolreload.ogg"), 8, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\riflereload.ogg"), 9, true);

	// Initialise the EntityManager
	cEntityManager = CEntityManager::GetInstance();
	cEntityManager->Init();

	// Initialise the cPlayer3D
	cPlayer3D = CPlayer3D::GetInstance();
	cPlayer3D->SetShader(cShader);
	cPlayer3D->Init();
	cPlayer3D->AttachCamera(cCamera);
	//cPlayer3D->SetScale(glm::vec3(0.5f));
	cPlayer3D->ActivateCollider(cSimpleShader);
	// Assign a cPistol to the cPlayer3D
	CPistol* cPistol = new CPistol();
	cPistol->Init();
	cPistol->SetShader(cSimpleShader);
	cPlayer3D->SetWeapon(0, cPistol);

	CRifle* cRifle = new CRifle();
	cRifle->Init();
	cRifle->SetShader(cSimpleShader);
	cPlayer3D->SetWeapon(1, cRifle);

	// Initialise the cEnemy3D
	// CEnemy3D == Crawler zombie
	// CEnemy3D2 == Basic zombie
	// CEnemy3D3 == Scrake, big nigga
	
	srand(time(NULL));

	++wave_count;
	for (int i = 1; i <= 12; ++i)
	{
		int switchPos = rand() % 4 + 1;

		glm::vec3 spawnPos;

		switch (switchPos)
		{
			case 1:
			{
				spawnPos = glm::vec3(8, 2, 8);
				break;
			}
			case 2:
			{
				spawnPos = glm::vec3(-8, 2, 8);
				break;
			}
			case 3:
			{
				spawnPos = glm::vec3(8, 2, -8);
				break;
			}
			case 4:
			{
				spawnPos = glm::vec3(-8, 2, -8);
				break;
			}
		}

		CEnemy3D2* cEnemy3D2 = new CEnemy3D2();
		AddEnemy2(cEnemy3D2, spawnPos, glm::vec3(0.5, 0.5, 0.5));
	}

	CStructureTower* cTower = new CStructureTower(glm::vec3(5, 0, 0));

	cTower->SetShader(cShader);
	cTower->Init();
	cTower->SetScale(glm::vec3(0.5, 0.5, 0.5));
	cTower->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cTower);

	CArmorPickup* cArmorPickup = new CArmorPickup();

	AddArmorPickUp(cArmorPickup, glm::vec3(3.5f, 0.25f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	CHealthPickup* cHealthPickup = new CHealthPickup();

	AddHealthPickUp(cHealthPickup, glm::vec3(3.5f, 0.25f, -3.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	CPowerUp* cPowerUp = new CPowerUp();

	AddPowerUp(cPowerUp, glm::vec3(-3.5f, 0.25f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	// Load the SkyBox
	cSkyBox = CSkyBox::GetInstance();
	// Set a shader to this class instance of CSkyBox
	cSkyBox->SetShader(skyBoxShader);
	cSkyBox->Init();

	// Load the Ground
	cGroundMap = CGroundMap::GetInstance();
	cGroundMap->SetShader(groundShader);
	cGroundMap->Init(glm::vec3(50.0f, 1.0f, 50.0f), glm::i32vec3(10, 1, 10));
	// Set a shader to this class instance of CSkyBox
	cGroundMap->ReCalculate();

	// Create and initialise the TextRenderer
	cTextRenderer = CTextRenderer::GetInstance();
	// Set a shader to this class
	cTextRenderer->SetShader(textShader);
	// Initialise the instance
	if (cTextRenderer->Init() == false)
	{
		cout << "Failed to load CTextRenderer" << endl;
		return false;
	}

	// Load the CameraEffects
	cCameraEffects = CCameraEffects::GetInstance();
	// Set a shader to this class instance of CameraEffects
	cCameraEffects->SetShader(cGUIShader);
	cCameraEffects->Init();
	
	// Load the ProgressBar
	cHealthBar = new CHealthBar();
	// Set a shader to this class instance of CameraEffects
	cHealthBar->SetShader(cGUISimpleShader);
	cHealthBar->Init(glm::vec3(-1.0f + 0.0333f, -1.0f + 0.0333f * 58, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));

	cEntityManager->SetHealthBar(cHealthBar);

	// Load the ProgressBar
	cArmorBar = new CArmorBar();
	// Set a shader to this class instance of CameraEffects
	cArmorBar->SetShader(cGUISimpleShader);
	cArmorBar->Init(glm::vec3(-1.0f + 0.0333f, -1.1f + 0.0333f * 58, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f));

	cEntityManager->SetArmorBar(cArmorBar);
	// Load the ProgressBar
	cExpBar = new CExperienceBar();
	// Set a shader to this class instance of CameraEffects
	cExpBar->SetShader(cGUISimpleShader);
	cExpBar->Init(glm::vec3(-1.f + 0.0333f, -2.85f + 0.0333f * 58, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	cEntityManager->SetExpBar(cExpBar);

	// Load the Minimap
	cMinimap = CMinimap::GetInstance();
	// Set a shader to this class instance of Minimap
	cMinimap->SetShader(cRenderToTextureShader);
	cMinimap->Init();

	// Load the cCrossHair
	cCrossHair = CCrossHair::GetInstance();
	// Set a shader to this class instance of CameraEffects
	cCrossHair->SetShader(cGUIShader);
	cCrossHair->Init();

	return true;
}

/**
@brief Update Update this instance
*/
void CScene3D::Update(const double dElapsedTime)
{
	if (CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_0))
	{
		if (cPlayer3D->IsCameraAttached())
			cPlayer3D->AttachCamera();
		else
			cPlayer3D->AttachCamera(cCamera);

		// Reset the key so that it will not repeat until the key is released and pressed again
		CKeyboardController::GetInstance()->ResetKey(GLFW_KEY_0);
	}
	if (CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_9))
	{
		// Toggle the crosshair on or off
		if (cCrossHair->GetStatus() == false)
			cCrossHair->SetStatus(true);
		else
			cCrossHair->SetStatus(false);
		
		// Reset the key so that it will not repeat until the key is released and pressed again
		CKeyboardController::GetInstance()->ResetKey(GLFW_KEY_9);
	}

	if (printLoseScreen == true || printWinScreen == true)
	{
		cSoundController->LoadSound(FileSystem::getPath("Sounds\\dud.ogg"), 1, true);
		cSoundController->LoadSound(FileSystem::getPath("Sounds\\dud.ogg"), 2, true);
		cSoundController->LoadSound(FileSystem::getPath("Sounds\\dud.ogg"), 3, true);
		cSoundController->LoadSound(FileSystem::getPath("Sounds\\dud.ogg"), 4, true);
		cSoundController->LoadSound(FileSystem::getPath("Sounds\\dud.ogg"), 7, true);
	}

	// Store the current position, if rollback is needed.
	cPlayer3D->StorePositionForRollback();

	// Update the joystick
	cJoystickController->Update(cJoystickController->GetJoystickID());

	// Get keyboard updates for player3D
	if ((CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_W))
		|| (cJoystickController->IsJoystickActivated(CJoystickController::FORWARD)))
		cPlayer3D->ProcessMovement(CPlayer3D::FORWARD, (float)dElapsedTime);
	if ((CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_S))
		|| (cJoystickController->IsJoystickActivated(CJoystickController::BACKWARD)))
		cPlayer3D->ProcessMovement(CPlayer3D::BACKWARD, (float)dElapsedTime);
	if ((CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_A))
		|| (cJoystickController->IsJoystickActivated(CJoystickController::LEFT)))
		cPlayer3D->ProcessMovement(CPlayer3D::LEFT, (float)dElapsedTime);
	if ((CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_D))
		|| (cJoystickController->IsJoystickActivated(CJoystickController::RIGHT)))
		cPlayer3D->ProcessMovement(CPlayer3D::RIGHT, (float)dElapsedTime);
	if ((CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_W) && CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		|| (cJoystickController->IsJoystickActivated(CJoystickController::FORWARD)))
		cPlayer3D->ProcessMovement(CPlayer3D::SPRINT, (float)dElapsedTime);
	if ((CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_SPACE))
		|| (cJoystickController->IsButtonDown(0))) // Button 0 is the A button on the GamePad
		cPlayer3D->SetToJump();
	if ((CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_X))) // Button 0 is the A button on the GamePad
		cPlayer3D->SetToDodge();
	// Get keyboard updates for camera
	if (!cPlayer3D->IsCameraAttached())
	{
		if (CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_I))
			cCamera->ProcessKeyboard(CCamera::FORWARD, (float)dElapsedTime);
		if (CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_K))
			cCamera->ProcessKeyboard(CCamera::BACKWARD, (float)dElapsedTime);
		if (CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_J))
			cCamera->ProcessKeyboard(CCamera::LEFT, (float)dElapsedTime);
		if (CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_L))
			cCamera->ProcessKeyboard(CCamera::RIGHT, (float)dElapsedTime);
	}

	if (cPlayer3D->IsCameraAttached())
	{
		// Get mouse updates
		cPlayer3D->ProcessRotate((float)cMouseController->GetMouseDeltaX(), (float)cMouseController->GetMouseDeltaY());
		cCamera->ProcessMouseScroll((float)cMouseController->GetMouseScrollStatus(CMouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET));
	}
	else
	{
		// Get mouse updates
		cCamera->ProcessMouseMovement((float)cMouseController->GetMouseDeltaX(), (float)cMouseController->GetMouseDeltaY());
		cCamera->ProcessMouseScroll((float)cMouseController->GetMouseScrollStatus(CMouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET));
	}

	if (CKeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_1))
	{
		cPlayer3D->SetCurrentWeapon(0);
	}
	if (CKeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_2))
	{
		cPlayer3D->SetCurrentWeapon(1);
	}
	if (CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_R))
	{
		cPlayer3D->GetWeapon()->Reload();
	}

	// Get mouse button updates
	if ((cMouseController->IsButtonDown(CMouseController::BUTTON_TYPE::LMB))
		|| (cJoystickController->IsButtonDown(2))) // Button 2 is the X button on the GamePad
	{
		// Try to create a projectile using the primary weapon, 0
		CProjectile* cProjectile = cPlayer3D->DischargeWeapon();
		// If the projectile was successfully created then add to the EntityManager
		if (cProjectile)
			cEntityManager->Add(cProjectile);
	}
	else if (cMouseController->IsButtonDown(CMouseController::BUTTON_TYPE::RMB))
	{
		cCamera->fZoom = 25.f;
		// Scope mode
	}
	else if (cMouseController->IsButtonUp(CMouseController::BUTTON_TYPE::RMB))
	{
		cCamera->fZoom = 45.f;
	}

	srand(time(NULL));

	spawnZTimer += dElapsedTime;
	spawnSTimer += dElapsedTime;
	spawnCTimer += dElapsedTime;
	//cout << cEntityManager->get_enemy_deathCount() << endl;

	//WAVE 2 LOGIC
	if (wave_count == 1 && cEntityManager->get_enemy_deathCount() >= 12 && wave2_start == false)
	{
		cEntityManager->set_enemy_deathCount(0);
		wave2_start = true;
		cPlayer3D->SetPosition(glm::vec3(0, 0.5, 0));
	}
	if (wave2_start == true)
	{
		// basic zombie spawning
		if (zombieCount != 14)
		{
			if (spawnZTimer >= 1.4f)
			{
				int switchPos = rand() % 4 + 1;

				glm::vec3 spawnPos;

				switch (switchPos)
				{
				case 1:
				{
					spawnPos = glm::vec3(10, 2, 10);
					break;
				}
				case 2:
				{
					spawnPos = glm::vec3(-10, 2, 10);
					break;
				}
				case 3:
				{
					spawnPos = glm::vec3(10, 2, -10);
					break;
				}
				case 4:
				{
					spawnPos = glm::vec3(-10, 2, -10);
					break;
				}
				}

				CEnemy3D2* cEnemy3D2 = new CEnemy3D2();
				AddEnemy2(cEnemy3D2, spawnPos, glm::vec3(0.5, 0.5, 0.5));

				++zombieCount;

				spawnZTimer = 0;
			}
		}

		// crawler spawning
		if (crawlerCount != 6)
		{
			if (spawnCTimer >= 1.4f)
			{
				int switchPos = rand() % 4 + 1;

				glm::vec3 spawnPos;

				switch (switchPos)
				{
				case 1:
				{
					spawnPos = glm::vec3(10, 2, 10);
					break;
				}
				case 2:
				{
					spawnPos = glm::vec3(-10, 2, 10);
					break;
				}
				case 3:
				{
					spawnPos = glm::vec3(10, 2, -10);
					break;
				}
				case 4:
				{
					spawnPos = glm::vec3(-10, 2, -10);
					break;
				}
				}

				CEnemy3D* cEnemy3D = new CEnemy3D();
				AddEnemy(cEnemy3D, spawnPos, glm::vec3(0.5, 0.5, 0.5));

				++crawlerCount;

				spawnCTimer = 0;
			}
		}

		cout << cEntityManager->get_enemy_deathCount() << endl;

		if (zombieCount == 14 && crawlerCount == 6)
		{
			wave2_start = false;
			++wave_count;
		}
	}

	//WAVE 3 LOGIC
	if (wave_count == 2 && cEntityManager->get_enemy_deathCount() > 19 && wave3_start == false)
	{
		cEntityManager->set_enemy_deathCount(0);
		wave3_start = true;
		cPlayer3D->SetPosition(glm::vec3(0, 0.5, 0));
	}
	if (wave3_start == true)
	{
		// basic zombie spawning
		if (zombieCount != 16)
		{
			if (spawnZTimer >= 1.4f)
			{
				int switchPos = rand() % 4 + 1;

				glm::vec3 spawnPos;

				switch (switchPos)
				{
				case 1:
				{
					spawnPos = glm::vec3(10, 2, 10);
					break;
				}
				case 2:
				{
					spawnPos = glm::vec3(-10, 2, 10);
					break;
				}
				case 3:
				{
					spawnPos = glm::vec3(10, 2, -10);
					break;
				}
				case 4:
				{
					spawnPos = glm::vec3(-10, 2, -10);
					break;
				}
				}

				CEnemy3D2* cEnemy3D2 = new CEnemy3D2();
				AddEnemy2(cEnemy3D2, spawnPos, glm::vec3(0.5, 0.5, 0.5));

				++zombieCount;

				spawnZTimer = 0;
			}
		}

		// crawler spawning
		if (crawlerCount != 8)
		{
			if (spawnCTimer >= 1.4f)
			{
				int switchPos = rand() % 4 + 1;

				glm::vec3 spawnPos;

				switch (switchPos)
				{
				case 1:
				{
					spawnPos = glm::vec3(10, 2, 10);
					break;
				}
				case 2:
				{
					spawnPos = glm::vec3(-10, 2, 10);
					break;
				}
				case 3:
				{
					spawnPos = glm::vec3(10, 2, -10);
					break;
				}
				case 4:
				{
					spawnPos = glm::vec3(-10, 2, -10);
					break;
				}
				}

				CEnemy3D* cEnemy3D = new CEnemy3D();
				AddEnemy(cEnemy3D, spawnPos, glm::vec3(0.5, 0.5, 0.5));

				++crawlerCount;

				spawnCTimer = 0;
			}
		}
		
		// big nigga spawning
		if (scrakeCount != 4)
		{
			if (spawnSTimer >= 1.4f)
			{
				int switchPos = rand() % 4 + 1;

				glm::vec3 spawnPos;

				switch (switchPos)
				{
				case 1:
				{
					spawnPos = glm::vec3(10, 2, 10);
					break;
				}
				case 2:
				{
					spawnPos = glm::vec3(-10, 2, 10);
					break;
				}
				case 3:
				{
					spawnPos = glm::vec3(10, 2, -10);
					break;
				}
				case 4:
				{
					spawnPos = glm::vec3(-10, 2, -10);
					break;
				}
				}

				CEnemy3D3* cEnemy3D = new CEnemy3D3();
				AddEnemy3(cEnemy3D, spawnPos, glm::vec3(0.5, 0.5, 0.5));

				++scrakeCount;

				spawnSTimer = 0;
			}
		}

		if (zombieCount == 16 && crawlerCount == 8 && scrakeCount == 4)
		{
			wave3_start = false;
			++wave_count;
		}
	}
	
	// WAVE 4 LOGIC
	if (wave_count == 3 && cEntityManager->get_enemy_deathCount() > 28)
	{
		cEntityManager->set_enemy_deathCount(0);
		wave4_start = true;
		cPlayer3D->SetPosition(glm::vec3(0, 0.5, 0));
	}
	if (wave4_start == true)
	{
		// basic zombie spawning
		if (zombieCount != 18)
		{
			if (spawnZTimer >= 1.4f)
			{
				int switchPos = rand() % 4 + 1;

				glm::vec3 spawnPos;

				switch (switchPos)
				{
				case 1:
				{
					spawnPos = glm::vec3(10, 2, 10);
					break;
				}
				case 2:
				{
					spawnPos = glm::vec3(-10, 2, 10);
					break;
				}
				case 3:
				{
					spawnPos = glm::vec3(10, 2, -10);
					break;
				}
				case 4:
				{
					spawnPos = glm::vec3(-10, 2, -10);
					break;
				}
				}

				CEnemy3D2* cEnemy3D2 = new CEnemy3D2();
				AddEnemy2(cEnemy3D2, spawnPos, glm::vec3(0.5, 0.5, 0.5));

				++zombieCount;

				spawnZTimer = 0;
			}
		}

		// crawler spawning
		if (crawlerCount != 10)
		{
			if (spawnCTimer >= 1.4f)
			{
				int switchPos = rand() % 4 + 1;

				glm::vec3 spawnPos;

				switch (switchPos)
				{
				case 1:
				{
					spawnPos = glm::vec3(10, 2, 10);
					break;
				}
				case 2:
				{
					spawnPos = glm::vec3(-10, 2, 10);
					break;
				}
				case 3:
				{
					spawnPos = glm::vec3(10, 2, -10);
					break;
				}
				case 4:
				{
					spawnPos = glm::vec3(-10, 2, -10);
					break;
				}
				}

				CEnemy3D* cEnemy3D = new CEnemy3D();
				AddEnemy(cEnemy3D, spawnPos, glm::vec3(0.5, 0.5, 0.5));

				++crawlerCount;

				spawnCTimer = 0;
			}
		}

		// big nigga spawning
		if (scrakeCount != 6)
		{
			if (spawnSTimer >= 1.4f)
			{
				int switchPos = rand() % 4 + 1;

				glm::vec3 spawnPos;

				switch (switchPos)
				{
				case 1:
				{
					spawnPos = glm::vec3(10, 2, 10);
					break;
				}
				case 2:
				{
					spawnPos = glm::vec3(-10, 2, 10);
					break;
				}
				case 3:
				{
					spawnPos = glm::vec3(10, 2, -10);
					break;
				}
				case 4:
				{
					spawnPos = glm::vec3(-10, 2, -10);
					break;
				}
				}

				CEnemy3D3* cEnemy3D = new CEnemy3D3();
				AddEnemy3(cEnemy3D, spawnPos, glm::vec3(0.5, 0.5, 0.5));

				++scrakeCount;

				spawnSTimer = 0;
			}
		}

		if (zombieCount == 18 && crawlerCount == 10 && scrakeCount == 6)
		{
			wave4_start = false;
			boss_start = true;
			++wave_count;
		}
	}

	// WIN LOSE CONDITIONS
	//if (cEntityManager->get_enemy_deathCount() > 1 && bossDED == true && printWinScreen == false)
	//{
	//	//cSoundController->PlaySoundByID(6);
	//	printWinScreen = true;
	//}

	//if (static_cast<CHealthBar*>(cHealthBar)->GetHealthBarLength() <= 0 && printLoseScreen == false)
	//{
	//	//cSoundController->PlaySoundByID(5);
	//	printLoseScreen = true;
	//}

	// Post Update the mouse controller
	cMouseController->PostUpdate();

	// Update the Entities
	cEntityManager->Update(dElapsedTime);

	// Check for Player3D colliding with Entities
	switch (cEntityManager->CollisionCheck(cPlayer3D))
	{
	case 1:
		cCameraEffects->Activate_BloodScreen();
		if (cPlayer3D->GetArmor() > 0)
		{
			cPlayer3D->SetArmor(cPlayer3D->GetArmor() - 5);
		}
		else if (cPlayer3D->GetHealth() > 0)
		{
			cPlayer3D->SetHealth(cPlayer3D->GetHealth() - 2);
		}
				//cCameraEffects->Activate_BloodScreen();
		cPlayer3D->GainExp(5);
		break;
	case 4:
		if (cPlayer3D->GetHealth() == 100)
		{
			// Do nothing
		}
		else
		{
			cPlayer3D->SetHealth(cPlayer3D->GetHealth() + 30);
		}

		break;
	case 5:
		if (cPlayer3D->GetArmor() == 100)
		{
			// Do nothing
		}
		else
		{
			cPlayer3D->SetArmor(cPlayer3D->GetArmor() + 30);
		}
		break;
	case 6:
		/*if (cPlayer3D->GetArmor() > 0)
		{
			cPlayer3D->SetArmor(cPlayer3D->GetArmor() - 0);
			cout << "You got yeeted" << endl;
		}
		else if (cPlayer3D->GetHealth() > 0)
		{
			cPlayer3D->SetHealth(cPlayer3D->GetHealth() - 0);
		}*/
		break;
	default:
		break;
	}

	// Clean up the deleted CEntity3D in the entity manager
	cEntityManager->CleanUp();

	// Update the player3D
	cPlayer3D->Update(dElapsedTime);

	// Update camera effects
	cCameraEffects->Update(dElapsedTime);

	// Update progress bar
	//if(static_cast<CArmorBar*>(cArmorBar)->GetArmorBarLength() >= 0)
		cArmorBar->Update(dElapsedTime);
	//else
		cHealthBar->Update(dElapsedTime);

		cExpBar->Update(dElapsedTime);

	cWeaponInfo = cPlayer3D->GetWeapon();
}

/**
 @brief PreRender Set up the OpenGL display environment before rendering
 */
void CScene3D::PreRender(void)
{
	// Reset the OpenGL rendering environment
	glLoadIdentity();

	// Clear the screen and buffer
	glClearColor(0.0f, 0.1f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 @brief Render Render this instance
 */
void CScene3D::Render(void)
{
	// Part 1: Render for the minimap by binding to framebuffer and render to color texture
	//         But the camera is move to top-view of the scene

	// Backup some key settings for the camera and player
	glm::vec3 storePlayerPosition = cPlayer3D->GetPosition();
	float storeCameraYaw = cCamera->fYaw;
	float storeCameraPitch = cCamera->fPitch;
	glm::vec3 storeCameraPosition = cCamera->vec3Position;
	// Adjust camera yaw and pitch so that it is looking from a top-view of the terrain
	cCamera->fYaw += 180.0f;
	cCamera->fPitch = -90.0f;
	// We store the player's position into the camera as we want the minimap to focus on the player
	cCamera->vec3Position = glm::vec3(storePlayerPosition.x, 10.0f, storePlayerPosition.z);
	// Recalculate all the camera vectors. 
	// We disable pitch constrains for this specific case as we want the camera to look straight down
	cCamera->ProcessMouseMovement(0, 0, false);
	// Generate the view and projection
	glm::mat4 playerView = cCamera->GetViewMatrix();
	glm::mat4 playerProjection = glm::perspective(	glm::radians(45.0f),
													(float)cSettings->iWindowWidth / (float)cSettings->iWindowHeight,
													0.1f, 1000.0f);

	// Set the camera parameters back to the previous values
	cCamera->fYaw = storeCameraYaw;
	cCamera->fPitch = storeCameraPitch;
	cCamera->vec3Position = storeCameraPosition;
	cCamera->ProcessMouseMovement(0, 0, true); // call this to make sure it updates its camera vectors, note that we disable pitch constrains for this specific case (otherwise we can't reverse camera's pitch values)

	// Activate the minimap system
	cMinimap->Activate();
	// Setup the rendering environment
	cMinimap->PreRender();

	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	// Render the Ground for the minimap
	cGroundMap->SetView(playerView);
	cGroundMap->SetProjection(playerProjection);
	cGroundMap->PreRender();
	cGroundMap->Render();
	cGroundMap->PostRender();

	// Render the entities for the minimap
	cEntityManager->SetView(playerView);
	cEntityManager->SetProjection(playerProjection);
	cEntityManager->Render();

	// Render the player for the minimap
	cPlayer3D->SetView(playerView);
	cPlayer3D->SetProjection(playerProjection);
	cPlayer3D->PreRender();
	cPlayer3D->Render();
	cPlayer3D->PostRender();

	// Deactivate the cMinimap so that we can render as per normal
	cMinimap->Deactivate();

	// Part 2: Render the entire scene as per normal
	// Get the camera view and projection
	glm::mat4 view = CCamera::GetInstance()->GetViewMatrix();;
	glm::mat4 projection = glm::perspective(	glm::radians(CCamera::GetInstance()->fZoom),
												(float)cSettings->iWindowWidth / (float)cSettings->iWindowHeight,
												0.1f, 1000.0f);
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render the SkyBox
	cSkyBox->SetView(view);
	cSkyBox->SetProjection(projection);
	cSkyBox->PreRender();
	cSkyBox->Render();
	cSkyBox->PostRender();

	// Render the Ground
	cGroundMap->SetView(view);
	cGroundMap->SetProjection(projection);
	cGroundMap->PreRender();
	cGroundMap->Render();
	cGroundMap->PostRender();

	// Render the entities
	cEntityManager->SetView(view);
	cEntityManager->SetProjection(projection);
	cEntityManager->Render();

	// Render the player
	cPlayer3D->SetView(view);
	cPlayer3D->SetProjection(projection);
	cPlayer3D->PreRender();
	cPlayer3D->Render();
	cPlayer3D->PostRender();

	// now draw the mirror quad with screen texture
	// --------------------------------------------
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

	cCameraEffects->PreRender();
	cCameraEffects->Render();
	cCameraEffects->PostRender();

	cHealthBar->PreRender();
	cHealthBar->Render();
	cHealthBar->PostRender();

	cArmorBar->PreRender();
	cArmorBar->Render();
	cArmorBar->PostRender();
	
	cExpBar->PreRender();
	cExpBar->Render();
	cExpBar->PostRender();

	cCrossHair->PreRender();
	cCrossHair->Render();
	cCrossHair->PostRender();

	cMinimap->Render();

	// Call the cTextRenderer's PreRender()
	cTextRenderer->PreRender();

	// Call the CTextRenderer's Render()
	textShader->use();

	if (cPlayer3D->GetWeapon())
	{
		string ammo;
		ammo += "Mag ammo: ";
		ammo += to_string(cPlayer3D->GetWeapon()->GetMagRound());
		cTextRenderer->Render(ammo, 550.f, 10.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	}
	if (cPlayer3D->GetWeapon())
	{
		string ammo;
		ammo += "Total ammo: ";
		ammo += to_string(cPlayer3D->GetWeapon()->GetTotalRound());
		cTextRenderer->Render(ammo, 550.f, 40.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	}
	string currentWeap;
	currentWeap += "Current Weap: ";
	if (cPlayer3D->GetCurrentWeaponIndex() == 0)
	{

		currentWeap += "Pistol";
		cTextRenderer->Render(currentWeap, 550.f, 70.0f, 0.5f, glm::vec3(0.3f, 0.6f, 1.0f));
	}
	if (cPlayer3D->GetCurrentWeaponIndex() == 1)
	{
		currentWeap += "Minigun";
		cTextRenderer->Render(currentWeap, 550.f, 70.0f, 0.5f, glm::vec3(1.f, 0.f, 0.f));
	}
	string level;
	level += "Level: ";
	level += to_string(cPlayer3D->GetCurrentPlayerLevel());
	cTextRenderer->Render(level, 10.f, 40.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
	// Call the cTextRenderer's PostRender()
	cTextRenderer->PostRender();

	return;
}

/**
 @brief PostRender Set up the OpenGL display environment after rendering.
 */
void CScene3D::PostRender(void)
{
}