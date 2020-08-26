#include "EntityManager.h"

#include "../Application.h"

#include <iostream>
using namespace std;

/**
 @brief Default Constructor
 */
CEntityManager::CEntityManager(void)
	: model(glm::mat4(1.0f))
	, view(glm::mat4(1.0f))
	, projection(glm::mat4(1.0f))
	, enemy_deathCount(0)
	, moveTo_Tower(false)
	, cCurrentWeapon(NULL)
	, cArmorBar(NULL)
	, cExpBar(NULL)
	, cHealthBar(NULL)
	, cInfectBar(NULL)
	, cSoundController(NULL)
	, cPrimaryWeapon(NULL)
	, cSecondaryWeapon(NULL)
	, currentTime(GetTickCount64() * 0.001f)
	, cPlayer3D(NULL)
{
}

/**
 @brief Destructor
 */
CEntityManager::~CEntityManager(void)
{
	// Remove all CEntity3D
	std::list<CEntity3D*>::iterator it = lEntity3D.begin(), end = lEntity3D.end();
	while (it != end)
	{
		// Delete if done
		delete *it;
		it = lEntity3D.erase(it);
	}
}

/**
 @brief Initialise this class instance
 */
bool CEntityManager::Init(void)
{
	//enemyHealth = 8;
	enemy_deathCount = 0;

	cSoundController = CSoundController::GetInstance();
	cSoundController->Init();
	cPlayer3D = CPlayer3D::GetInstance();
	cCurrentWeapon = CPlayer3D::GetInstance()->GetWeapon();
	cEntityManager = CEntityManager::GetInstance();
	//cShader = Shader::GetInstance();
	//cSimpleShader = Shader::GetInstance();

	// Setup the shaders
	cShader = new Shader("Shader//Scene3D.vs", "Shader//Scene3D.fs");
	// Setup the shaders
	cSimpleShader = new Shader("Shader//SimpleShader.vs", "Shader//SimpleShader.fs");
	//cSoundController->LoadSound("../Sounds/damage.ogg", 1);

	lEntity3D.clear();
	return true;
}

/**
 @brief Set model
 @param model A glm::mat4 variable containing the model for this class instance
 */
void CEntityManager::SetModel(glm::mat4 model)
{
	this->model = model;
}

/**
 @brief Set view
 @param view A glm::mat4 variable containing the model for this class instance
 */
void CEntityManager::SetView(glm::mat4 view)
{
	this->view = view;
}

/**
 @brief Set projection
 @param projection A glm::mat4 variable containing the model for this class instance
 */
void CEntityManager::SetProjection(glm::mat4 projection)
{
	this->projection = projection;
}

/**
@brief Add a CEntity3D* to this class instance
*/
void CEntityManager::Add(CEntity3D* cEntity3D)
{
	lEntity3D.push_back(cEntity3D);
}

/**
@brief Remove a CEntity3D* from this class instance
*/
bool CEntityManager::Erase(CEntity3D* cEntity3D)
{
	// Find the entity's iterator
	std::list<CEntity3D*>::iterator findIter = std::find(lEntity3D.begin(), lEntity3D.end(), cEntity3D);

	// Delete the entity if found
	if (findIter != lEntity3D.end())
	{
		// Delete the CEntity3D
		delete *findIter;
		// Go to the next iteration after erasing from the list
		findIter = lEntity3D.erase(findIter);
		return true;
	}
	// Return false if not found
	return false;
}

/**
@brief Collision Check for a CEntity3D*
*/
int CEntityManager::CollisionCheck(CEntity3D* cEntity3D)
{

	int bResult = 0;
		
	std::list<CEntity3D*>::iterator it, end;
	end = lEntity3D.end();
	for (it = lEntity3D.begin(); it != end; ++it)
	{
		// Check for collisions between the 2 entities
		if (cEntity3D->CheckForCollision(*it) == true)
		{
			

			if ((*it)->GetType2() == CEntity3D::ENEMYTYPE::CRAWLER)
			{

				cout << "** Collision between Player and NPC2 ***" << endl;

				if (bInvincibility || iFrames)
				{
					bResult = 1;
				}
				else if (!bInvincibility && !iFrames)
				{
					
					bResult = 2;
					(*it)->RollbackPosition();
					lastTime2 = currentTime;
					iFrames = true;
				}

				break;
			}	
			else if ((*it)->GetType2() == CEntity3D::ENEMYTYPE::BASIC)
			{

				cout << "** Collision between Player and NPC2 ***" << endl;

				if (bInvincibility || iFrames)
				{
					bResult = 1;
				}
				else if (!bInvincibility && !iFrames)
				{
					
					bResult = 3;
					(*it)->RollbackPosition();
					lastTime2 = currentTime;
					iFrames = true;
				}

				break;
			}
			else if ((*it)->GetType2() == CEntity3D::ENEMYTYPE::SCRAKE)
			{

				static_cast<CEnemy3D*>(*it)->SetEnemyDamage(static_cast<CEnemy3D*>(*it)->GetEnemyDamage());
				cout << "** Collision between Player and NPC2 ***" << endl;

				if (bInvincibility || iFrames)
				{

					bResult = 1;
				}
				else if (!bInvincibility && !iFrames)
				{

					bResult = 4;
					(*it)->RollbackPosition();
					lastTime2 = currentTime;
					iFrames = true;
				}

				break;
			}
			else if ((*it)->GetType2() == CEntity3D::ENEMYTYPE::BOSS)
			{

				cout << "** Collision between Player and NPC2 ***" << endl;

				if (bInvincibility || iFrames)
				{
					bResult = 1;
				}
				else if (!bInvincibility && !iFrames)
				{
					
					bResult = 5;
					(*it)->RollbackPosition();
					lastTime2 = currentTime;
					iFrames = true;
				}

				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::PROJECTILE)
			{
				// Mark the projectile for deletion
				(*it)->SetToDelete(true);
				cout << "** Collision between Player and Projectile ***" << endl;
				bResult = 6;
				// Quit this loop since a collision has been found
				
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::STRUCTURE)
			{
				// Rollback the cEntity3D's position
				cEntity3D->RollbackPosition();

				cout << "** Collision between Player and Structure ***" << endl;
				bResult = 7;
				// Quit this loop since a collision has been found
				
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::HEALTH_PICKUP)
			{
				// Rollback the cEntity3D's position
				(*it)->SetToDelete(true);
				//static_cast<CHealthBar*>(cHealthBar)->AddHealth(30);
				cout << "** Collision between Player and Health_PickUp ***" << endl;
				// Quit this loop since a collision has been found

				bResult = 8;
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::ARMOR_PICKUP)
			{
				(*it)->SetToDelete(true);

				//static_cast<CArmorBar*>(cArmorBar)->AddArmor(30);
				cout << "** Collision between Player and Armor_PickUp ***" << endl;
				
				// Quit this loop since a collision has been found
				bResult = 9;
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::AMMO_PICKUP)
			{
				(*it)->SetToDelete(true);

				if (static_cast<CPlayer3D*>(cEntity3D)->GetCurrentWeaponIndex() != 0)
				{
					static_cast<CPlayer3D*>(cEntity3D)->GetWeapon()->AddRounds(50);
				}

				cout << "** Collision between Player and Ammo_PickUp ***" << endl;
				bResult = 10;
				// Quit this loop since a collision has been found

				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::INVINCIBILITY)
			{
				// Rollback the cEntity3D's position
				(*it)->SetToDelete(true);

				bInvincibility = true;
				lastTime = currentTime;
				cout << "** Collision between Player and Invincibility ***" << endl;
				bResult = 11;
				// Quit this loop since a collision has been found
				
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::BARREL_PICKUP)
			{
				// Rollback the cEntity3D's position
				(*it)->RollbackPosition();

				cout << "** Collision between Player and Barrel ***" << endl;
				bResult = 12;
				// Quit this loop since a collision has been found
				
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::MAGAZINE_PICKUP)
			{
				// Rollback the cEntity3D's position
				(*it)->RollbackPosition();

				cout << "** Collision between Player and Magazine ***" << endl;
				bResult = 13;
				// Quit this loop since a collision has been found
				
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::MINIGUN_PICKUP)
			{
				// Rollback the cEntity3D's position
				cout << "** Collision between Player and Minigun ***" << endl;
				if (cPlayer3D->GetWeaponInfo() == NULL && CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_F))
				{
					(*it)->SetToDelete(true);
					bResult = 14;
				}
				else if (cPlayer3D->GetWeaponInfo() != NULL && CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_F))
				{
					(*it)->SetToDelete(true);
					bResult = 15;
				}
				// Quit this loop since a collision has been found
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::RIFLE_PICKUP)
			{
				cout << "** Collision between Player and Rifle ***" << endl;
				if (cPlayer3D->GetWeaponInfo() == NULL && CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_F))
				{
					(*it)->SetToDelete(true);
					bResult = 16;
				}
				else if (cPlayer3D->GetWeaponInfo() != NULL && CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_F))
				{
					(*it)->SetToDelete(true);
					bResult = 17;
				}
				// Quit this loop since a collision has been found
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::SMG_PICKUP)
			{
				cout << "** Collision between Player and SMG ***" << endl;
				if (cPlayer3D->GetWeaponInfo() == NULL && CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_F))
				{
					(*it)->SetToDelete(true);
					bResult = 18;
				}
				else if (cPlayer3D->GetWeaponInfo() != NULL && CKeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_F))
				{
					(*it)->SetToDelete(true);
					bResult = 19;
				}
				// Quit this loop since a collision has been found
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::TOWER)
			{
				cout << "** Collision between Player and Tower ***" << endl;
				
				// Quit this loop since a collision has been found
				break;
			}

		}
	}
	return bResult;
}

/**
 @brief Update this class instance
 */
int CEntityManager::Update(const double dElapsedTime)
{
	//static_cast<CExperienceBar*>(cExpBar)->SetExpMultiplier(1.f);
	std::list<CEntity3D*>::iterator it, end;
	std::list<CEntity3D*>::iterator it_other;
	cCurrentWeapon = CPlayer3D::GetInstance()->GetWeapon();
	currentTime = GetTickCount64() * 0.001f;

	int iResult = 0;

	// Update all CEntity3D
	end = lEntity3D.end();

	for (it = lEntity3D.begin(); it != end; ++it)
	{
		(*it)->Update(dElapsedTime);
	}

	if (bInvincibility)
	{
		if (currentTime - lastTime > 5)
			bInvincibility = false;
			//cout << "yeet" << endl;
	}
	if (iFrames)
	{
		if (currentTime - lastTime2 > 0.75f)
			iFrames = false;
	}
	if (bFreezeMovement)
	{
		if (currentTime - lastTime3 > 5)
			bFreezeMovement = false;
	}
	// Check for collisions among them
	end = lEntity3D.end();
	for (it = lEntity3D.begin(); it != end; ++it)
	{
		for (it_other = it; it_other != end; ++it_other)
		{
			// If the 2 entities to check are the same, then skip this iteration
			if (it_other == it)
				continue;

			// to chnage where enemy will move towards
			if (glm::length((*it)->GetPosition() - (*it_other)->GetPosition()) <= 5)
			{
				if (((*it)->GetType() == CEntity3D::TYPE::NPC) && ((*it_other)->GetType() == CEntity3D::TYPE::TOWER) ||
					((*it)->GetType() == CEntity3D::TYPE::TOWER) && ((*it_other)->GetType() == CEntity3D::TYPE::NPC))
				{
					moveTo_Tower = true;
				}
			}
			else if (glm::length((*it)->GetPosition() - (*it_other)->GetPosition()) > 5)
			{
				if (((*it)->GetType() == CEntity3D::TYPE::NPC) && ((*it_other)->GetType() == CEntity3D::TYPE::TOWER) ||
					((*it)->GetType() == CEntity3D::TYPE::TOWER) && ((*it_other)->GetType() == CEntity3D::TYPE::NPC))
				{
					moveTo_Tower = false;
				}
			}

			if (((*it)->GetType() == CEntity3D::TYPE::NPC))
			{
				if (bFreezeMovement == true)
				{
					static_cast<CEntity3D*>(*it)->SetMovementSpeed(0.0f);
				}
				else
				{
					static_cast<CEntity3D*>(*it)->SetMovementSpeed(2.5f);
				}
			}

			// Check for collisions between the 2 entities
			if ((*it)->CheckForCollision(*it_other) == true)
			{
				if (((*it)->GetType2() == CEntity3D::ENEMYTYPE::CRAWLER) && ((*it_other)->GetType() == CEntity3D::TYPE::PROJECTILE))
				{
					
					(*it_other)->SetToDelete(true);
					if (static_cast<CEnemy3D*>(*it)->GetEnemyHealth() > 0)
					{
						(*it)->RollbackPosition();
						static_cast<CEnemy3D*>(*it)->SetEnemyHealth(static_cast<CEnemy3D*>(*it)->GetEnemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
					}
					else
					{
						(*it)->SetToDelete(true);
						static_cast<CExperienceBar*>(cExpBar)->SetiExp(static_cast<CExperienceBar*>(cExpBar)->GetiExp() + static_cast<CEnemy3D*>(*it)->GetEnemyExp());
						LootDrop((*it)->GetPosition());
						++enemy_deathCount;
						iResult = 6;
					}
					
					cout << "** Collision between Crawler and Projectile ***" << endl;
					}
				else if (((*it)->GetType() == CEntity3D::TYPE::PROJECTILE) &&((*it_other)->GetType2() == CEntity3D::ENEMYTYPE::CRAWLER))
				{

					(*it)->SetToDelete(true);
					if (static_cast<CEnemy3D*>(*it)->GetEnemyHealth() > 0)
					{
						(*it_other)->RollbackPosition();
						static_cast<CEnemy3D*>(*it)->SetEnemyHealth(static_cast<CEnemy3D*>(*it)->GetEnemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
					
					}
					else
					{
						(*it_other)->SetToDelete(true);
						static_cast<CExperienceBar*>(cExpBar)->SetiExp(static_cast<CExperienceBar*>(cExpBar)->GetiExp() + static_cast<CEnemy3D*>(*it)->GetEnemyExp());
						LootDrop((*it)->GetPosition());
						++enemy_deathCount;
						iResult = 6;
					}

					cout << "** Collision between Crawler and Projectile ***" << endl;
				}
				else if (((*it)->GetType2() == CEntity3D::ENEMYTYPE::BASIC) && ((*it_other)->GetType() == CEntity3D::TYPE::PROJECTILE))
				{
					
					(*it_other)->SetToDelete(true);
					if (static_cast<CEnemy3D2*>(*it)->GetEnemyHealth() > 0)
					{
						(*it)->RollbackPosition();
						static_cast<CEnemy3D2*>(*it)->SetEnemyHealth(static_cast<CEnemy3D2*>(*it)->GetEnemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
					}
					else
					{
						(*it)->SetToDelete(true);
						static_cast<CExperienceBar*>(cExpBar)->SetiExp(static_cast<CExperienceBar*>(cExpBar)->GetiExp() + static_cast<CEnemy3D2*>(*it)->GetEnemyExp());
						LootDrop((*it)->GetPosition());
						++enemy_deathCount;
						iResult = 6;
						
					}
					
					cout << "** Collision between Basic and Projectile ***" << endl;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::PROJECTILE) &&((*it_other)->GetType2() == CEntity3D::ENEMYTYPE::BASIC))
				{

					(*it)->SetToDelete(true);
					if (static_cast<CEnemy3D2*>(*it)->GetEnemyHealth() > 0)
					{
						(*it_other)->RollbackPosition();
						static_cast<CEnemy3D2*>(*it)->SetEnemyHealth(static_cast<CEnemy3D2*>(*it)->GetEnemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
					}
					else
					{
						(*it_other)->SetToDelete(true); 
						static_cast<CExperienceBar*>(cExpBar)->SetiExp(static_cast<CExperienceBar*>(cExpBar)->GetiExp() + static_cast<CEnemy3D2*>(*it)->GetEnemyExp());
						LootDrop((*it)->GetPosition());
						++enemy_deathCount;
						iResult = 6;
					}

					cout << "** Collision between Basic and Projectile ***" << endl;
				}
				else if (((*it)->GetType2() == CEntity3D::ENEMYTYPE::SCRAKE) && ((*it_other)->GetType() == CEntity3D::TYPE::PROJECTILE))
				{
					
					(*it_other)->SetToDelete(true);
					if (static_cast<CEnemy3D3*>(*it)->GetEnemyHealth() > 0)
					{
						(*it)->RollbackPosition();
						static_cast<CEnemy3D3*>(*it)->SetEnemyHealth(static_cast<CEnemy3D3*>(*it)->GetEnemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
					}
					else
					{
						(*it)->SetToDelete(true);
						static_cast<CExperienceBar*>(cExpBar)->SetiExp(static_cast<CExperienceBar*>(cExpBar)->GetiExp() + static_cast<CEnemy3D3*>(*it)->GetEnemyExp());
						LootDrop((*it)->GetPosition());
						++enemy_deathCount;
						iResult = 6;
					}
					
					cout << "** Collision between Scrake and Projectile ***" << endl;
					}
				else if (((*it)->GetType() == CEntity3D::TYPE::PROJECTILE) &&((*it_other)->GetType2() == CEntity3D::ENEMYTYPE::SCRAKE))
				{

					(*it)->SetToDelete(true);
					if (static_cast<CEnemy3D3*>(*it)->GetEnemyHealth() > 0)
					{
						(*it_other)->RollbackPosition();
						static_cast<CEnemy3D3*>(*it)->SetEnemyHealth(static_cast<CEnemy3D3*>(*it)->GetEnemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
					}
					else
					{
						(*it_other)->SetToDelete(true);
						static_cast<CExperienceBar*>(cExpBar)->SetiExp(static_cast<CExperienceBar*>(cExpBar)->GetiExp() + static_cast<CEnemy3D3*>(*it)->GetEnemyExp());
						LootDrop((*it)->GetPosition());
						++enemy_deathCount;
						iResult = 6;
					}

					cout << "** Collision between Scrake and Projectile ***" << endl;
				}
				else if (((*it)->GetType2() == CEntity3D::ENEMYTYPE::BOSS) && ((*it_other)->GetType() == CEntity3D::TYPE::PROJECTILE))
				{
					
					(*it_other)->SetToDelete(true);
					if (static_cast<CEnemyBoss3D*>(*it)->GetEnemyHealth() > 0)
					{
						(*it)->RollbackPosition();
						static_cast<CEnemyBoss3D*>(*it)->SetEnemyHealth(static_cast<CEnemyBoss3D*>(*it)->GetEnemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
					}
					else
					{
						(*it)->SetToDelete(true);
						static_cast<CExperienceBar*>(cExpBar)->SetiExp(static_cast<CExperienceBar*>(cExpBar)->GetiExp() + static_cast<CEnemyBoss3D*>(*it)->GetEnemyExp());
						LootDrop((*it)->GetPosition());
						++enemy_deathCount;
						iResult = 6;
					}
					
					cout << "** Collision between Boss and Projectile ***" << endl;
					}
				else if (((*it)->GetType() == CEntity3D::TYPE::PROJECTILE) &&((*it_other)->GetType2() == CEntity3D::ENEMYTYPE::BOSS))
				{

					(*it)->SetToDelete(true);
					if (static_cast<CEnemyBoss3D*>(*it)->GetEnemyHealth() > 0)
					{
						(*it_other)->RollbackPosition();
						static_cast<CEnemyBoss3D*>(*it)->SetEnemyHealth(static_cast<CEnemyBoss3D*>(*it)->GetEnemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
					}
					else
					{
						(*it_other)->SetToDelete(true);
						static_cast<CExperienceBar*>(cExpBar)->SetiExp(static_cast<CExperienceBar*>(cExpBar)->GetiExp() + static_cast<CEnemyBoss3D*>(*it)->GetEnemyExp());
						LootDrop((*it)->GetPosition());
						++enemy_deathCount;
						iResult = 6;
					}

					cout << "** Collision between Boss and Projectile ***" << endl;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::PROJECTILE) &&
					((*it_other)->GetType() == CEntity3D::TYPE::PROJECTILE))
				{
					(*it)->SetToDelete(true);
					(*it_other)->SetToDelete(true);
					cout << "** Collision between 2 Projectiles ***" << endl;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::NPC) &&
					((*it_other)->GetType() == CEntity3D::TYPE::NPC))
				{
					(*it)->RollbackPosition();
					//(*it_other)->RollbackPosition();
					cout << "** Collision between 2 NPCs ***" << endl;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::NPC) &&
					((*it_other)->GetType() == CEntity3D::TYPE::STRUCTURE))
				{
					(*it)->RollbackPosition();
					//(*it_other)->RollbackPosition();
					cout << "** Collision between NPC and STRUCTURE ***" << endl;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::STRUCTURE) &&
					((*it_other)->GetType() == CEntity3D::TYPE::NPC))
				{
					(*it_other)->RollbackPosition();
					//(*it_other)->RollbackPosition();
					cout << "** Collision between NPC and STRUCTURE ***" << endl;
				}

				// CHECK COLLISION BETWEEN NPC AND TOWER
				else if (((*it)->GetType2() == CEntity3D::ENEMYTYPE::CRAWLER) && ((*it_other)->GetType() == CEntity3D::TYPE::TOWER))
				{
					(*it)->RollbackPosition();
					cout << "** Collision between Crawler and tower ***" << endl;
					iResult = 1;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::TOWER) && ((*it_other)->GetType2() == CEntity3D::ENEMYTYPE::CRAWLER))
				{
					(*it_other)->RollbackPosition();
					cout << "** Collision between Crawler and tower ***" << endl;
					iResult = 1;
				}
				else if (((*it)->GetType2() == CEntity3D::ENEMYTYPE::BASIC) && ((*it_other)->GetType() == CEntity3D::TYPE::TOWER))
				{
					(*it)->RollbackPosition();
					cout << "** Collision between Basic and tower ***" << endl;
					iResult = 2;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::TOWER) && ((*it_other)->GetType2() == CEntity3D::ENEMYTYPE::BASIC))
				{
					(*it_other)->RollbackPosition();
					cout << "** Collision between Basic and tower ***" << endl;
					iResult = 2;
				}
				else if (((*it)->GetType2() == CEntity3D::ENEMYTYPE::SCRAKE) && ((*it_other)->GetType() == CEntity3D::TYPE::TOWER))
				{
					(*it)->RollbackPosition();
					cout << "** Collision between Scrake and tower ***" << endl;
					iResult = 3;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::TOWER) && ((*it_other)->GetType2() == CEntity3D::ENEMYTYPE::SCRAKE))
				{
					(*it_other)->RollbackPosition();
					cout << "** Collision between Scrake and tower ***" << endl;
					iResult = 3;
				}
				else if (((*it)->GetType2() == CEntity3D::ENEMYTYPE::BOSS) && ((*it_other)->GetType() == CEntity3D::TYPE::TOWER))
				{
					(*it)->RollbackPosition();
					cout << "** Collision between Boss and tower ***" << endl;
					iResult = 4;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::TOWER) && ((*it_other)->GetType2() == CEntity3D::ENEMYTYPE::BOSS))
				{
					(*it_other)->RollbackPosition();
					cout << "** Collision between Boss and tower ***" << endl;
					iResult = 4;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::TOWER) && ((*it_other)->GetType() == CEntity3D::TYPE::ANTIDOTE))
				{
					(*it_other)->SetToDelete(true);					
					iResult = 5;
					cout << "** Collision between NPC and Antidote ***" << endl;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::ANTIDOTE) && ((*it_other)->GetType() == CEntity3D::TYPE::TOWER))
				{
					(*it_other)->SetToDelete(true);
					iResult = 5;
					cout << "** Collision between NPC and Antidote ***" << endl;
				}
			}
		}
	}
	return iResult;
}

/**
 @brief CleanUp all CEntity3Ds which are marked for deletion
 */
void CEntityManager::CleanUp(void)
{
	std::list<CEntity3D*>::iterator it, end;
	it = lEntity3D.begin();
	end = lEntity3D.end();

	while (it != end)
	{
		if ((*it)->IsToDelete())
		{
			// Delete the CEntity3D
			delete *it;
			// Go to the next iteration after erasing from the list
			it = lEntity3D.erase(it);
		}
		else
		{
			// Go to the next iteration
			++it;
		}
	}
}

/**
 @brief Render this class instance
 */
void CEntityManager::Render(void)
{
	// Render all entities
	std::list<CEntity3D*>::iterator it, end;
	end = lEntity3D.end();
	for (it = lEntity3D.begin(); it != end; ++it)
	{
		(*it)->SetView(view);
		(*it)->SetProjection(projection);
		(*it)->PreRender();
		(*it)->Render();
		(*it)->PostRender();
	}
}

int CEntityManager::get_enemy_deathCount()
{
	return enemy_deathCount;
}

void CEntityManager::set_enemy_deathCount(int x)
{
	enemy_deathCount = x;
}

void CEntityManager::SetHealthBar(CHealthBar* pBar)
{
	cHealthBar = pBar;
}

void CEntityManager::SetArmorBar(CArmorBar* pBar)
{
	cArmorBar = pBar;
}

void CEntityManager::SetExpBar(CExperienceBar* pBar)
{
	cExpBar = pBar;
}
void CEntityManager::SetInfectionBar(CInfectionBar* pBar)
{
	cInfectBar = pBar;
}

bool CEntityManager::get_moveTo()
{
	return moveTo_Tower;
}

void CEntityManager::set_moveTo(bool b)
{
	moveTo_Tower = b;
}

bool CEntityManager::GetInvincibility()
{
	return bInvincibility;
}

void CEntityManager::SetInvincibility(bool bInvincibility)
{
	this->bInvincibility = bInvincibility;
}

bool CEntityManager::GetFreezeMovement()
{
	return bFreezeMovement;
}

void CEntityManager::SetFreezeMovement(bool bFreezeMovement)
{
	this->bFreezeMovement = bFreezeMovement;
}


void CEntityManager::LootDrop(glm::vec3 pos)
{
	int chance = RandIntMinMax(1, 100);
	if (chance >= 1 && chance <= 10)
	{
		CHealthPickup* cHealthPickup = new CHealthPickup;
		AddHealthPickUp(cHealthPickup, pos, glm::vec3(1.f,1.f,1.f));
	}
	else if (chance >= 11 && chance <= 20)
	{
		CArmorPickup* cArmorPickup = new CArmorPickup;
		AddArmorPickUp(cArmorPickup, pos, glm::vec3(1.f, 1.f, 1.f));
	}
	else if (chance >= 21 && chance <= 30)
	{
		CAmmoPickup* cAmmoPickup = new CAmmoPickup;
		AddAmmoPickUp(cAmmoPickup, pos, glm::vec3(1.f, 1.f, 1.f));
	}
	else if (chance >= 31 && chance <= 37)
	{
		CSMGPickup* cSMGPickup = new CSMGPickup;
		AddSMGPickup(cSMGPickup, pos, glm::vec3(1.f, 1.f, 1.f));
	}
	else if (chance >= 38 && chance <= 40)
	{
		CMinigunPickup* cMinigunPickup = new CMinigunPickup;
		AddMinigunPickup(cMinigunPickup, pos, glm::vec3(1.f, 1.f, 1.f));
	}
	else if (chance >= 41 && chance <= 45)
	{
		CRiflePickup* cRiflePickup = new CRiflePickup;
		AddRiflePickup(cRiflePickup, pos, glm::vec3(1.f, 1.f, 1.f));
	}
	else if (chance >= 46 && chance <= 53)
	{
		CBarrelAttachment* cBarrelPickup = new CBarrelAttachment;
		AddBarrelPickup(cBarrelPickup, pos, glm::vec3(1.f, 1.f, 1.f));
	}
	else if (chance >= 54 && chance <= 61)
	{
		CMagazineAttachment* cMagazinePickup = new CMagazineAttachment;
		AddMagazinePickup(cMagazinePickup, pos, glm::vec3(1.f, 1.f, 1.f));
	}
	else if (chance >= 62 && chance <= 67)
	{
		CInvincibility* cInvincibility = new CInvincibility;
		AddInvincibility(cInvincibility, pos, glm::vec3(1.f, 1.f, 1.f));
	}
	else if (chance >= 68 && chance <= 73)
	{
		CFreezeMovement* cFreezemovement = new CFreezeMovement;
		AddFreezeMovement(cFreezeMovement, pos, glm::vec3(1.f, 1.f, 1.f));
	}
	else
	{

	}
}


void CEntityManager::AddArmorPickUp(CArmorPickup* cArmorPickup, glm::vec3 pos, glm::vec3 scale)
{
	cArmorPickup = new CArmorPickup(pos);
	cArmorPickup->SetShader(cShader);
	cArmorPickup->Init();
	cArmorPickup->SetScale(scale);
	cArmorPickup->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cArmorPickup);

}

void CEntityManager::AddHealthPickUp(CHealthPickup* cHealthPickup, glm::vec3 pos, glm::vec3 scale)
{
	cHealthPickup = new CHealthPickup(pos);
	cHealthPickup->SetShader(cShader);
	cHealthPickup->Init();
	cHealthPickup->SetScale(scale);
	cHealthPickup->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cHealthPickup);
}

void CEntityManager::AddAmmoPickUp(CAmmoPickup* cAmmoPickup, glm::vec3 pos, glm::vec3 scale)
{
	cAmmoPickup = new CAmmoPickup(pos);
	cAmmoPickup->SetShader(cShader);
	cAmmoPickup->Init();
	cAmmoPickup->SetScale(scale);
	cAmmoPickup->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cAmmoPickup);
}

void CEntityManager::AddInvincibility(CInvincibility* cInvincibility, glm::vec3 pos, glm::vec3 scale)
{
	cInvincibility = new CInvincibility(pos);
	cInvincibility->SetShader(cShader);
	cInvincibility->Init();
	cInvincibility->SetScale(scale);
	cInvincibility->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cInvincibility);
}

void CEntityManager::AddFreezeMovement(CFreezeMovement* cFreezeMovement, glm::vec3 pos, glm::vec3 scale)
{
	cFreezeMovement = new CFreezeMovement(pos);
	cFreezeMovement->SetShader(cShader);
	cFreezeMovement->Init();
	cFreezeMovement->SetScale(scale);
	cFreezeMovement->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cFreezeMovement);
}

void CEntityManager::AddBarrelPickup(CBarrelAttachment* cBarrelAttachment, glm::vec3 pos, glm::vec3 scale)
{
	cBarrelAttachment = new CBarrelAttachment(pos);
	cBarrelAttachment->SetShader(cShader);
	cBarrelAttachment->Init();
	cBarrelAttachment->SetScale(scale);
	cBarrelAttachment->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cBarrelAttachment);
}

void CEntityManager::AddMagazinePickup(CMagazineAttachment* cMagazineAttachment, glm::vec3 pos, glm::vec3 scale)
{
	cMagazineAttachment = new CMagazineAttachment(pos);
	cMagazineAttachment->SetShader(cShader);
	cMagazineAttachment->Init();
	cMagazineAttachment->SetScale(scale);
	cMagazineAttachment->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cMagazineAttachment);

}

void CEntityManager::AddRiflePickup(CRiflePickup* cRiflePickup, glm::vec3 pos, glm::vec3 scale)
{
	cRiflePickup = new CRiflePickup(pos);
	cRiflePickup->SetShader(cShader);
	cRiflePickup->Init();
	cRiflePickup->SetScale(scale);
	cRiflePickup->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cRiflePickup);
}

void CEntityManager::AddMinigunPickup(CMinigunPickup* cMinigunPickup, glm::vec3 pos, glm::vec3 scale)
{
	cMinigunPickup = new CMinigunPickup(pos);
	cMinigunPickup->SetShader(cShader);
	cMinigunPickup->Init();
	cMinigunPickup->SetScale(scale);
	cMinigunPickup->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cMinigunPickup);
}

void CEntityManager::AddSMGPickup(CSMGPickup* cSMGPickup, glm::vec3 pos, glm::vec3 scale)
{
	cSMGPickup = new CSMGPickup(pos);
	cSMGPickup->SetShader(cShader);
	cSMGPickup->Init();
	cSMGPickup->SetScale(scale);
	cSMGPickup->ActivateCollider(cSimpleShader);
	cEntityManager->Add(cSMGPickup);
}
