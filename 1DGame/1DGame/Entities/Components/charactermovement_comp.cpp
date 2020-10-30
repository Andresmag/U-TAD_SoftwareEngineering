#include "charactermovement_comp.h"
#include "render_comp.h"
#include "../entity.h"
#include "../../Managers/world.h"
#include "../Messages/newpos_msg.h"
#include "../Messages/collision_msg.h"
#include <assert.h>

CCompCharacterMovement::CCompCharacterMovement(unsigned int _uPos)
	: m_uPos(_uPos)
{
}

unsigned int CCompCharacterMovement::GetPos()
{
	return m_uPos;
}

void CCompCharacterMovement::ReceiveMsg(const CMessage& message)
{
	// Checks for messages informing on a change in the position of the entity
	// this message will come from the input component
	const CNewPosMsg* pNewPosMsg = dynamic_cast<const CNewPosMsg*>(&message);
	if (pNewPosMsg != nullptr) {
		m_uPos = pNewPosMsg->GetPos();
		return;
	}

	// Checks for messages informing on a collision with another entity
	const CCollisionMsg* pEntityCollMsg = dynamic_cast<const CCollisionMsg*>(&message);
	if (pEntityCollMsg != nullptr)
	{
		CEntity* pEntityColl = const_cast<CEntity*>(pEntityCollMsg->GetEntityToCollision());
		assert(pEntityColl != nullptr);

		// Get the render component to check what type of entity has collided with the main character
		CCompRender* pRenderCompEntColl = pEntityColl->FindComponent<CCompRender>();
		assert(pRenderCompEntColl != nullptr);
		if (pRenderCompEntColl->GetSymbol() == '*') // It only matters if the entity is an enemy
		{
			CWorld::GetInstance().SetExit(true); // Game over
			return;
		}
		return;
	}
}
