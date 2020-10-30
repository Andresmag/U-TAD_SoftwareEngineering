#include "collision_comp.h"
#include "../entity.h"
#include "../../Managers/world.h"
#include "../Messages/newpos_msg.h"
#include "../Messages/collision_msg.h"
#include <assert.h>

CCompCollision::CCompCollision(unsigned int _uPos)
	: m_uPos(_uPos)
{
}

void CCompCollision::SetPos(unsigned int _uPos)
{
	m_uPos = _uPos;
}

unsigned int CCompCollision::GetPos() const
{
	return m_uPos;
}

void CCompCollision::Update()
{
	CEntity* pOwnerEntity = GetOwner();
	assert(pOwnerEntity != nullptr);
	CEntity* pCollisionEntity = nullptr;
	
	// Checks every entity with each other
	for (CEntity* pEntity : CWorld::GetInstance().GetEntities())
	{
		assert(pEntity != nullptr);
		if (pEntity != pOwnerEntity)
		{
			// Collisions are only possible with other entities that has a collision component as well
			CCompCollision* pCollisionComp = pEntity->FindComponent<CCompCollision>();
			if (pCollisionComp != nullptr)
			{
				if (m_uPos == pCollisionComp->GetPos())
				{
					pCollisionEntity = pEntity;
					break;
				}
			}
		}
	}

	if (pCollisionEntity != nullptr)
	{
		CCollisionMsg msg(*pCollisionEntity);
		pOwnerEntity->SendMsg(msg);
	}
}

void CCompCollision::ReceiveMsg(const CMessage& message)
{
	// Checks for messages informing on a change in the logic position of the entity
	const CNewPosMsg* pMsg = dynamic_cast<const CNewPosMsg*>(&message);
	if (pMsg != nullptr) {
		m_uPos = pMsg->GetPos();
		return;
	}
}
