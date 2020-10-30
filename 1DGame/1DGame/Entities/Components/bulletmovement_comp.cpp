#include "bulletmovement_comp.h"
#include "render_comp.h"
#include "../entity.h"
#include "../../Managers/world.h"
#include "../Messages/newpos_msg.h"
#include "../Messages/collision_msg.h"
#include <assert.h>

CCompBulletMovement::CCompBulletMovement(unsigned int _uPos, int _iDirection)
	: m_uPos(_uPos)
	, m_iDirection(_iDirection)
{
}

void CCompBulletMovement::SetPos(unsigned int _uPos)
{
	m_uPos = _uPos;
}

unsigned int CCompBulletMovement::GetPos() const
{
	return m_uPos;
}

int CCompBulletMovement::GetDirection() const
{
	return m_iDirection;
}

void CCompBulletMovement::Update()
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
	else if (m_iDirection > 0 && m_uPos == CWorld::GetInstance().GetWorldLength() - 1)
	{
		// Delete bullet because it collides with the end of the world
		CEntity* pEntity = GetOwner();
		assert(pEntity != nullptr);
		CWorld::GetInstance().DeleteBullet(*pEntity);
	}
	else if (m_iDirection < 0 && m_uPos == 0)
	{
		// Delete bullet because it collides with the beginning of the world
		CEntity* pEntity = GetOwner();
		assert(pEntity != nullptr);
		CWorld::GetInstance().DeleteBullet(*pEntity);
	}

}

void CCompBulletMovement::ReceiveMsg(const CMessage& message)
{
	// Checks for messages informing on a collision with another entity
	const CCollisionMsg* pEntityCollMsg = dynamic_cast<const CCollisionMsg*>(&message);
	if (pEntityCollMsg != nullptr)
	{
		CEntity* pEntityColl = const_cast<CEntity*>(pEntityCollMsg->GetEntityToCollision());
		assert(pEntityColl != nullptr);

		// Get the render component to check what type of entity has collided with the bullet
		CCompRender* pRenderCompEntColl = pEntityColl->FindComponent<CCompRender>();
		assert(pRenderCompEntColl != nullptr);
		if (pRenderCompEntColl->GetSymbol() == '*') // It only matters if the entity is an enemy
		{
			CEntity* pOwner = GetOwner();
			assert(pOwner != nullptr);
			CWorld::GetInstance().DeleteBullet(*pOwner);
			CWorld::GetInstance().DeleteEnemy(*pEntityColl);
			return;
		}
		return;
	}
}
