#include "input_comp.h"
#include "shoot_comp.h"
#include "../Messages/newbullet_msg.h"
#include "../Messages/bulletdeleted_msg.h"
#include "../../Managers/world.h"

CCompShoot::CCompShoot(unsigned int _uRight, unsigned int _uLeft)
	: m_uRightAvailableBullets(_uRight)
	, m_uLeftAvailableBullets(_uLeft)
{
}

unsigned int CCompShoot::GetRightAvailableBullets()
{
	return m_uRightAvailableBullets;
}

unsigned int CCompShoot::GetLeftAvailableBullets()
{
	return m_uLeftAvailableBullets;
}

void CCompShoot::ReceiveMsg(const CMessage& message)
{
	// Checks for messages informing on the creation of a new bullet and in what direction
	const CNewBulletMsg* pNewBulletMsg = dynamic_cast<const CNewBulletMsg*>(&message);
	if (pNewBulletMsg != nullptr) {
		if (pNewBulletMsg->GetDirection() > 0)
			m_uRightAvailableBullets--;
		else
			m_uLeftAvailableBullets--;

		// Inform to the logic that a new bullet has to be made
		CWorld::GetInstance().SpawnBullet(pNewBulletMsg->GetPos(), pNewBulletMsg->GetDirection());
		return;
	}

	// Checks for messages informing on the destruction of a bullet and what was its direction
	const CBulletDeletedMsg* pBulletDeletedMsg = dynamic_cast<const CBulletDeletedMsg*>(&message);
	if (pBulletDeletedMsg != nullptr) {
		if (pBulletDeletedMsg->GetDirection() > 0)
			m_uRightAvailableBullets++;
		else
			m_uLeftAvailableBullets++;

		return;
	}
}
