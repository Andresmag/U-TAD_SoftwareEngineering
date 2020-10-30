//
// Class World (singleton)
//
// This class is in charge of the logic of the game.
// It manages all the entities (elements) that are in the world and update them logically.
// It also controls the main loop and decide when to stop it with the 'exit' variable.
//

#pragma once

#include <vector>
class CEntity;

class CWorld
{
public:
	typedef std::vector<CEntity*> vEntities;

private:
	static const unsigned int MAX_BULLETS = 10;
	static const unsigned int MAX_ENEMIES = 10;
	static const unsigned int WORLD_LENGTH = 81;

	vEntities m_pEntities;
	unsigned int m_uEnemies;
	unsigned int m_uPoints;
	bool m_bExit;

	CWorld();

	void UpdateEntities();

public:
	// Singleton pattern
	static CWorld& GetInstance();
	CWorld(CWorld const&) = delete;
	void operator= (CWorld const&) = delete;

	inline vEntities& GetEntities() { return m_pEntities; }

	void Init();
	void Terminate();
	void Update();

	void SetExit(bool _bValue);
	bool GetExit();

	unsigned int GetWorldLength() const;

	void IncreasePoints();
	unsigned int GetPoints() const;

	// Create/Destroy bullet
	void SpawnBullet(unsigned int _uPos, int _iDirection);
	void DeleteBullet(CEntity &_pEntity);

	// Create/Destroy enemy
	void SpawnEnemy();
	void DeleteEnemy(CEntity& _pEntity);
};