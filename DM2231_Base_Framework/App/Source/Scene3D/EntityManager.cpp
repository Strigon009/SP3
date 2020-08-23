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
	, iFrames(false)
	, lastTime(0)
	, lastTime2(0)
	, bInvincibility(false)
	, bFreezeMovement(false)
	, lastTime3(0)
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
	static_cast<CHealthBar*>(cHealthBar)->SetDmgMultiplier(1.f);
	static_cast<CArmorBar*>(cArmorBar)->SetArmorDmgMultiplier(1.f);
	
	

	int bResult = 0;
		
	std::list<CEntity3D*>::iterator it, end;
	end = lEntity3D.end();
	for (it = lEntity3D.begin(); it != end; ++it)
	{
		// Check for collisions between the 2 entities
		if (cEntity3D->CheckForCollision(*it) == true)
		{
			
			if ((*it)->GetType() == CEntity3D::TYPE::NPC)
			{
				cout << "** Collision between Player and NPC ***" << endl;
			
				static_cast<CHealthBar*>(cHealthBar)->SetDmgMultiplier(1.f);
				static_cast<CArmorBar*>(cArmorBar)->SetArmorDmgMultiplier(1.f);
				if (bInvincibility || iFrames)
				{

				}
				else if(!bInvincibility || !iFrames)
				{
					if (static_cast<CArmorBar*>(cArmorBar)->GetArmorBarLength() * 100 >= 0.f)
						static_cast<CArmorBar*>(cArmorBar)->SetArmorBarState(true);
					else
						static_cast<CHealthBar*>(cHealthBar)->SetHealthBarState(true);

					// Rollback the cEntity3D's position
					//cEntity3D->RollbackPosition();
					// Rollback the NPC's position
					(*it)->RollbackPosition();
					lastTime2 = currentTime;
					iFrames = true;
				}
				bResult = 1;
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::PROJECTILE)
			{
				// Mark the projectile for deletion
				(*it)->SetToDelete(true);
				cout << "** Collision between Player and Projectile ***" << endl;
				bResult = 2;
				// Quit this loop since a collision has been found
				
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::STRUCTURE)
			{
				// Rollback the cEntity3D's position
				cEntity3D->RollbackPosition();

				cout << "** Collision between Player and Structure ***" << endl;
				bResult = 3;
				// Quit this loop since a collision has been found
				
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::HEALTH_PICKUP)
			{
				// Rollback the cEntity3D's position
				(*it)->SetToDelete(true);
				static_cast<CHealthBar*>(cHealthBar)->AddHealth(30);
				cout << "** Collision between Player and Health_PickUp ***" << endl;
				// Quit this loop since a collision has been found

				bResult = 4;
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::ARMOR_PICKUP)
			{
				(*it)->SetToDelete(true);

				static_cast<CArmorBar*>(cArmorBar)->AddArmor(30);
				cout << "** Collision between Player and Armor_PickUp ***" << endl;
				
				// Quit this loop since a collision has been found
				bResult = 5;
				break;
			}
			else if ((*it)->GetType() == CEntity3D::TYPE::INVINCIBILITY)
			{
				// Rollback the cEntity3D's position
				(*it)->SetToDelete(true);

				bInvincibility = true;
				lastTime = currentTime;
				cout << "** Collision between Player and Invincibility ***" << endl;
				bResult = 6;
				// Quit this loop since a collision has been found
				
				break;
			}
			if ((*it)->GetType2() == CEntity3D::ENEMYTYPE::SCRAKE)
			{

				cout << "** Collision between Player and NPC2 ***" << endl;

				static_cast<CHealthBar*>(cHealthBar)->SetDmgMultiplier(3.f);
				static_cast<CArmorBar*>(cArmorBar)->SetArmorDmgMultiplier(3.f);
				if (bInvincibility || iFrames)
				{

				}
				else if (!bInvincibility || !iFrames)
				{
					if (static_cast<CArmorBar*>(cArmorBar)->GetArmorBarLength() * 100 >= 0.f)
						static_cast<CArmorBar*>(cArmorBar)->SetArmorBarState(true);
					else
						static_cast<CHealthBar*>(cHealthBar)->SetHealthBarState(true);

					(*it)->RollbackPosition();
					lastTime2 = currentTime;
					iFrames = true;
				}

				bResult = 7;
				break;
			}// Quit this loop since a collision has been found
			else if ((*it)->GetType() == CEntity3D::TYPE::FREEZE_MOVEMENT)
			{
				// Rollback the cEntity3D's position
				(*it)->SetToDelete(true);

				bFreezeMovement = true;
				lastTime3 = currentTime;
				cout << "** Collision between Player and FreezeMovement ***" << endl;
				bResult = 8;
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
void CEntityManager::Update(const double dElapsedTime)
{
	static_cast<CExperienceBar*>(cExpBar)->SetExpMultiplier(1.f);
	std::list<CEntity3D*>::iterator it, end;
	std::list<CEntity3D*>::iterator it_other;
	cCurrentWeapon = CPlayer3D::GetInstance()->GetWeapon();
	currentTime = GetTickCount64() * 0.001f;


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
				if (((*it)->GetType() == CEntity3D::TYPE::NPC) &&
					((*it_other)->GetType() == CEntity3D::TYPE::PROJECTILE))
				{
					static_cast<CEnemy3D*>(*it)->set_enemyHealth(static_cast<CEnemy3D*>(*it)->get_enemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
					
					if (static_cast<CEnemy3D*>(*it)->get_enemyHealth() > 0)
					{
						cout << static_cast<CEnemy3D*>(*it)->get_enemyHealth() << endl;
						(*it)->RollbackPosition();
					}
					else
					{
						(*it)->SetToDelete(true);
						++enemy_deathCount;
						
					}
					
					(*it_other)->SetToDelete(true);
					cout << "** Collision between NPC and Projectile ***" << endl;
					
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::PROJECTILE) &&((*it_other)->GetType() == CEntity3D::TYPE::NPC))
				{
					(*it)->SetToDelete(true);

					if (static_cast<CEnemy3D*>(*it)->get_enemyHealth() > 0)
					{
						(*it_other)->RollbackPosition();
					}
					else
					{
						(*it_other)->SetToDelete(true);
						++enemy_deathCount;
					}

					cout << "** Collision between NPC and Projectile ***" << endl;
					static_cast<CEnemy3D*>(*it)->set_enemyHealth(static_cast<CEnemy3D*>(*it)->get_enemyHealth() - cPlayer3D->GetWeapon()->GetWeaponDamage());
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
				else if (((*it)->GetType() == CEntity3D::TYPE::NPC) && ((*it_other)->GetType() == CEntity3D::TYPE::TOWER))
				{
					(*it)->RollbackPosition();

					static_cast<CStructureTower*>(*it_other)->set_towerHP(static_cast<CStructureTower*>(*it_other)->get_towerHP() - static_cast<CEnemy3D*>(*it)->get_enemyDamage());
					cout << static_cast<CStructureTower*>(*it_other)->get_towerHP() << endl;

					cout << "** Collision between NPC and tower ***" << endl;
				}
				else if (((*it)->GetType() == CEntity3D::TYPE::TOWER) && ((*it_other)->GetType() == CEntity3D::TYPE::NPC))
				{
					(*it_other)->RollbackPosition();

					static_cast<CStructureTower*>(*it)->set_towerHP(static_cast<CStructureTower*>(*it_other)->get_towerHP() - static_cast<CEnemy3D*>(*it)->get_enemyDamage());
					cout << static_cast<CStructureTower*>(*it)->get_towerHP() << endl;

					cout << "** Collision between NPC and tower ***" << endl;
				}
			}
		}
	}
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
