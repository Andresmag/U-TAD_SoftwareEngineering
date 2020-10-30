#include "input_comp.h"
#include "../../Managers/world.h"
#include "../Messages/newpos_msg.h"
#include "../Messages/newbullet_msg.h"
#include "../entity.h"
#include "charactermovement_comp.h"
#include "shoot_comp.h"
#include <conio.h>
#include <assert.h>

void CCompInput::Update()
{
	if (_kbhit())
	{
		char key = _getch();
		switch (key)
		{
		case 'h':
		{
			CEntity* pEntity = GetOwner();
			assert(pEntity != nullptr);
			CCompCharacterMovement* pCharacterMovementComp = pEntity->FindComponent<CCompCharacterMovement>();
			assert(pCharacterMovementComp != nullptr);
			if (pCharacterMovementComp->GetPos() > 0) {
				CNewPosMsg msg(pCharacterMovementComp->GetPos() - 1);
				pEntity->SendMsg(msg);
			}
		}
			break;
		case 'l':
		{
			CEntity * pEntity = GetOwner();
			assert(pEntity != nullptr);
			CCompCharacterMovement* pCharacterMovementComp = pEntity->FindComponent<CCompCharacterMovement>();
			assert(pCharacterMovementComp != nullptr);
			if (pCharacterMovementComp->GetPos() < CWorld::GetInstance().GetWorldLength() - 1) {
				CNewPosMsg msg(pCharacterMovementComp->GetPos() + 1);
				pEntity->SendMsg(msg);
			}
		}
			break;
		case 'k':
		{
			CEntity* pEntity = GetOwner();
			assert(pEntity != nullptr);
			CCompShoot* pShootComp = pEntity->FindComponent<CCompShoot>();
			assert(pShootComp != nullptr);
			if (pShootComp->GetRightAvailableBullets() > 0)
			{
				CCompCharacterMovement* pCharacterMovementComp = pEntity->FindComponent<CCompCharacterMovement>();
				assert(pCharacterMovementComp != nullptr);
				CNewBulletMsg msg(pCharacterMovementComp->GetPos() + 1, 1);
				pEntity->SendMsg(msg);
			}
		}
			break;
		case 'j':
		{
			CEntity* pEntity = GetOwner();
			assert(pEntity != nullptr);
			CCompShoot* pShootComp = pEntity->FindComponent<CCompShoot>();
			assert(pShootComp != nullptr);
			if (pShootComp->GetLeftAvailableBullets() > 0)
			{
				CCompCharacterMovement* pCharacterMovementComp = pEntity->FindComponent<CCompCharacterMovement>();
				assert(pCharacterMovementComp != nullptr);
				CNewBulletMsg msg(pCharacterMovementComp->GetPos() - 1, -1);
				pEntity->SendMsg(msg);
			}
		}
		break;
		case 27: // ESC key to exit the game
			CWorld::GetInstance().SetExit(true);
			break;
		}
	}
}
