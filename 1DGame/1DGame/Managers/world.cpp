#include "world.h"
#include "../Entities/entity.h"
#include "../Entities/Components/render_comp.h"
#include "../Entities/Components/charactermovement_comp.h"
#include "../Entities/Components/shoot_comp.h"
#include "../Entities/Components/input_comp.h"
#include "../Entities/Components/bulletmovement_comp.h"
#include "../Entities/Components/enemymovement_comp.h"
#include "../Entities/Components/collision_comp.h"
#include "../Entities/Messages/newbullet_msg.h"
#include "../Entities/Messages/bulletdeleted_msg.h"
#include <assert.h>
#include <cstdlib>

CWorld& CWorld::GetInstance()
{
	static CWorld world;
	return world;
}

CWorld::CWorld()
	: m_pEntities(MAX_BULLETS + MAX_ENEMIES + 1)
	, m_uEnemies(0)
	, m_uPoints(0)
	, m_bExit(false)
{
	m_pEntities.clear();
}

void CWorld::Init()
{
	m_uEnemies = 0;
	m_uPoints = 0;
	m_bExit = false;
	srand(1); // Initialize the random seed

	// Player entity
	CEntity* pPlayer = new CEntity();
	assert(pPlayer != nullptr);

	// Movement Component
	CCompCharacterMovement* pCharacterMovementComp = new CCompCharacterMovement(WORLD_LENGTH/2);
	assert(pCharacterMovementComp != nullptr);
	pPlayer->AddComponent<CCompCharacterMovement&>(*pCharacterMovementComp);

	// Shoot Component
	CCompShoot* pPlayerShoot = new CCompShoot(MAX_BULLETS / 2, MAX_BULLETS / 2);
	assert(pPlayerShoot != nullptr);
	pPlayer->AddComponent<CCompShoot&>(*pPlayerShoot);

	// Input Component
	CCompInput* pPlayerInputComp = new CCompInput();
	assert(pPlayerInputComp != nullptr);
	pPlayer->AddComponent<CCompInput&>(*pPlayerInputComp);

	// Collision Component
	CCompCollision* pPlayerCollisionComp = new CCompCollision(WORLD_LENGTH / 2);
	assert(pPlayerCollisionComp != nullptr);
	pPlayer->AddComponent<CCompCollision&>(*pPlayerCollisionComp);

	// Render Component
	CCompRender* pPlayerRenderComp = new CCompRender(WORLD_LENGTH / 2, 'X');
	assert(pPlayerRenderComp != nullptr);
	pPlayer->AddComponent<CCompRender&>(*pPlayerRenderComp);

	m_pEntities.push_back(pPlayer);
	pPlayer->Activate();

	// Add all bullets but not activate them
	for (unsigned int uIndex = 0; uIndex < MAX_BULLETS; ++uIndex)
	{
		// Bullet entity
		CEntity* pBullet = new CEntity();
		assert(pBullet != nullptr);

		int iDirection = 1;
		if (uIndex < MAX_BULLETS / 2)
			iDirection = -1;

		// Movement Component
		CCompBulletMovement* pBulletMovementComp = new CCompBulletMovement(WORLD_LENGTH + 1, iDirection);
		assert(pBulletMovementComp != nullptr);
		pBullet->AddComponent<CCompBulletMovement&>(*pBulletMovementComp);

		// Collision Component
		CCompCollision* pBulletCollisionComp = new CCompCollision(WORLD_LENGTH + 1);
		assert(pBulletCollisionComp != nullptr);
		pBullet->AddComponent<CCompCollision&>(*pBulletCollisionComp);

		// Render Component
		CCompRender* pBulletRenderComp;
		if (iDirection > 0)
			pBulletRenderComp = new CCompRender(WORLD_LENGTH + 1, '>');
		else
			pBulletRenderComp = new CCompRender(WORLD_LENGTH + 1, '<');
		assert(pBulletRenderComp != nullptr);
		pBullet->AddComponent<CCompRender&>(*pBulletRenderComp);

		m_pEntities.push_back(pBullet);
	}

	// Add all enemies but not activate them
	for (unsigned int uIndex = 0; uIndex < MAX_ENEMIES; ++uIndex)
	{
		// Enemy entity
		CEntity* pEnemy = new CEntity();
		assert(pEnemy != nullptr);

		// Movement Component
		CCompEnemyMovement* pEnemyMovementComp = new CCompEnemyMovement(WORLD_LENGTH + 1, 1);
		assert(pEnemyMovementComp != nullptr);
		pEnemy->AddComponent<CCompEnemyMovement&>(*pEnemyMovementComp);

		// Collision Component
		CCompCollision* pEnemyCollisionComp = new CCompCollision(WORLD_LENGTH + 1);
		assert(pEnemyCollisionComp != nullptr);
		pEnemy->AddComponent<CCompCollision&>(*pEnemyCollisionComp);

		// Render Component
		CCompRender* pEnemyRenderComp = new CCompRender(WORLD_LENGTH + 1, '*');
		assert(pEnemyRenderComp != nullptr);
		pEnemy->AddComponent<CCompRender&>(*pEnemyRenderComp);

		m_pEntities.push_back(pEnemy);
	}
}

void CWorld::Terminate()
{
	for (CEntity* pEnt : m_pEntities) {
		assert(pEnt != nullptr);
		pEnt->Deactivate();
		delete pEnt;
	}
	m_pEntities.clear();
}

void CWorld::Update()
{
	SpawnEnemy();
	UpdateEntities();
}

// Update Entities in the world
void CWorld::UpdateEntities()
{
	for (CEntity* pEnt : m_pEntities) {
		assert(pEnt != nullptr);
		pEnt->Update();
	}
}

void CWorld::SetExit(bool _bValue)
{
	m_bExit = _bValue;
}

bool CWorld::GetExit()
{
	return m_bExit;
}

unsigned int CWorld::GetWorldLength() const
{
	return WORLD_LENGTH;
}

void CWorld::IncreasePoints()
{
	m_uPoints++;
}

unsigned int CWorld::GetPoints() const
{
	return m_uPoints;
}

void CWorld::SpawnBullet(unsigned int _uPos, int _iDirection)
{
	for (auto entIt = m_pEntities.begin(); entIt != m_pEntities.end(); ++entIt)
	{
		CCompRender* pRenderComp = (*entIt)->FindComponent<CCompRender>();
		assert(pRenderComp != nullptr);
		char cSymbol = _iDirection > 0 ? '>' : '<';
		
		// Find a bullet deactivated in the correct direction
		if (pRenderComp->GetSymbol() == cSymbol && !(*entIt)->IsActivated())
		{
			// Set the position to the movement component of the bullet because it will spread it to the others that need it
			CCompBulletMovement* pBulletMovementComp = (*entIt)->FindComponent<CCompBulletMovement>();
			assert(pBulletMovementComp != nullptr);
			pBulletMovementComp->SetPos(_uPos);

			// Activate the bullet
			(*entIt)->Activate();

			// Search for activated enemies and warn them that a new bullet has been created
			for (auto entIt2 = m_pEntities.begin(); entIt2 != m_pEntities.end(); ++entIt2)
			{
				pRenderComp = (*entIt2)->FindComponent<CCompRender>();
				assert(pRenderComp != nullptr);
				if (pRenderComp->GetSymbol() == '*' && (*entIt2)->IsActivated())
				{
					(*entIt2)->SendMsg(CNewBulletMsg(_uPos, _iDirection));
				}
			}

			break;
		}
	}
}

void CWorld::DeleteBullet(CEntity &_pEntity)
{
	for (auto entIt = m_pEntities.begin(); entIt != m_pEntities.end(); ++entIt)
	{
		if (*entIt == &_pEntity)
		{
			CCompBulletMovement* pBulletMovementComp = (*entIt)->FindComponent<CCompBulletMovement>();
			// Reload a bullet in the player
			CBulletDeletedMsg msg(pBulletMovementComp->GetDirection());
			m_pEntities[0]->SendMsg(msg);

			// Deactivate the bullet entity and move the position in every component out of the world
			pBulletMovementComp->SetPos(WORLD_LENGTH + 1);
			(*entIt)->FindComponent<CCompRender>()->SetPos(WORLD_LENGTH + 1);
			(*entIt)->FindComponent<CCompCollision>()->SetPos(WORLD_LENGTH + 1);
			(*entIt)->Deactivate();
			break;
		}
	}
}

void CWorld::SpawnEnemy()
{
	if (m_uEnemies < MAX_ENEMIES && rand() % 100 < 5) // Random prob in order to create an enemy
	{
		// Calculate random direction 
		int iDirection = rand() % 100 < 50 ? -1 : 1;
		unsigned int uPos = iDirection > 0 ? 0 : WORLD_LENGTH - 1;

		for (auto entIt = m_pEntities.begin(); entIt != m_pEntities.end(); ++entIt)
		{
			CCompRender* pRenderComp = (*entIt)->FindComponent<CCompRender>();
			assert(pRenderComp != nullptr);
			char cSymbol = '*';

			// Find an enemy deactivated
			if (pRenderComp->GetSymbol() == cSymbol && !(*entIt)->IsActivated())
			{
				// Set the position and direction to the movement component of the enemy because it will spread it to the others that need it
				CCompEnemyMovement* pEnemyMovementComp = (*entIt)->FindComponent<CCompEnemyMovement>();
				assert(pEnemyMovementComp != nullptr);
				pEnemyMovementComp->SetPos(uPos);
				pEnemyMovementComp->SetDirection(iDirection);

				// Activate the bullet
				(*entIt)->Activate();
				m_uEnemies++;
				break;
			}
		}
	}
}

void CWorld::DeleteEnemy(CEntity& _pEntity)
{
	for (auto entIt = m_pEntities.begin(); entIt != m_pEntities.end(); ++entIt)
	{
		if (*entIt == &_pEntity)
		{
			// Deactivate the enemy entity and move the position in every component out of the world
			(*entIt)->FindComponent<CCompEnemyMovement>()->SetPos(WORLD_LENGTH + 1);
			(*entIt)->FindComponent<CCompRender>()->SetPos(WORLD_LENGTH + 1);
			(*entIt)->FindComponent<CCompCollision>()->SetPos(WORLD_LENGTH + 1);
			(*entIt)->Deactivate();

			// Update number of enemies activated in the world and current points
			m_uEnemies--;
			IncreasePoints();
			break;
		}
	}
}
