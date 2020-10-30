#include "enemymovement_comp.h"
#include "../entity.h"
#include "../../Managers/world.h"
#include "../Messages/newpos_msg.h"
#include "../Messages/collision_msg.h"
#include "../Messages/newbullet_msg.h"
#include "render_comp.h"
#include <assert.h>

CCompEnemyMovement::CCompEnemyMovement(unsigned int _uPos, int _iDirection)
	: m_uPos(_uPos)
	, m_iDirection(_iDirection)
{
}

void CCompEnemyMovement::SetPos(unsigned int _uPos)
{
	m_uPos = _uPos;
}

unsigned int CCompEnemyMovement::GetPos() const
{
	return m_uPos;
}

void CCompEnemyMovement::SetDirection(int _iDirection)
{
	m_iDirection = _iDirection;
}

int CCompEnemyMovement::GetDirection() const
{
	return m_iDirection;
}

void CCompEnemyMovement::Update()
{
	if (m_iDirection > 0 && m_uPos < CWorld::GetInstance().GetWorldLength() - 1)
	{
		m_uPos++;
		CEntity* pEntity = GetOwner();
		assert(pEntity != nullptr);
		CNewPosMsg msg(m_uPos);
		pEntity->SendMsg(msg);
	}
	else if (m_iDirection < 0 && m_uPos > 0)
	{
		m_uPos--;
		CEntity* pEntity = GetOwner();
		assert(pEntity != nullptr);
		CNewPosMsg msg(m_uPos);
		pEntity->SendMsg(msg);
	}
}

void CCompEnemyMovement::ReceiveMsg(const CMessage& message)
{
	// Checks for messages that informs of the creation of a new bullet
	const CNewBulletMsg* pNewBulletMsg = dynamic_cast<const CNewBulletMsg*>(&message);
	if (pNewBulletMsg != nullptr)
	{
		// Check if the bullet moves in the direction where enemy is and 
		// if that is the case make the enemy move a step back 
		if (pNewBulletMsg->GetDirection() > 0 && m_iDirection < 0)
		{
			m_uPos += 2;
			CEntity* pEntity = GetOwner();
			assert(pEntity != nullptr);
			CNewPosMsg msg(m_uPos);
			pEntity->SendMsg(msg);
		}
		else if (pNewBulletMsg->GetDirection() < 0 && m_iDirection > 0)
		{
			m_uPos -= 2;
			CEntity* pEntity = GetOwner();
			assert(pEntity != nullptr);
			CNewPosMsg msg(m_uPos);
			pEntity->SendMsg(msg);
		}
		
		return;
	}


	// Checks for messages informing on a collision with another entity
	const CCollisionMsg* pEntityCollMsg = dynamic_cast<const CCollisionMsg*>(&message);
	if (pEntityCollMsg != nullptr)
	{
		CEntity* pEntityColl = const_cast<CEntity*>(pEntityCollMsg->GetEntityToCollision());
		assert(pEntityColl != nullptr);

		// Get the render component to check what type of entity has collided with the enemy
		CCompRender* pRenderCompEntColl = pEntityColl->FindComponent<CCompRender>();
		assert(pRenderCompEntColl != nullptr);
		if (pRenderCompEntColl->GetSymbol() == '>' || pRenderCompEntColl->GetSymbol() == '<') // Bullet in any direction
		{
			CEntity* pOwner = GetOwner();
			assert(pOwner != nullptr);
			CWorld::GetInstance().DeleteEnemy(*pOwner);
			CWorld::GetInstance().DeleteBullet(*pEntityColl);
			return;
		}
		else if (pRenderCompEntColl->GetSymbol() == 'X') // Enemy has reached the player
		{
			CWorld::GetInstance().SetExit(true); // Game over
			return;
		}

		return;
	}
}
