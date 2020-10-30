//
// Class Collision Message
//
// Message that inform other components that a collision has been detected. 
// The message contains the entity with which it has collided.
//

#pragma once

#include "message.h"

class CEntity;

class CCollisionMsg : public CMessage
{
private:
	CEntity* pEntityToCollision;

public:
	CCollisionMsg(CEntity& _cEntity) : pEntityToCollision(&_cEntity) {}
	
	inline const CEntity* GetEntityToCollision() const { return pEntityToCollision; }
};