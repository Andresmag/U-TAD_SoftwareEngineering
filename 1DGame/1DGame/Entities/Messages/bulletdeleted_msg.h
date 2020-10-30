//
// Class Bullet Deleted Message
//
// Message that inform other components that a bullet has been destroyed. 
// The message contains the direction of the bullet that was destroyed.
//

#pragma once

#include "message.h"

class CBulletDeletedMsg : public CMessage
{
private:
	int m_iDirection;

public:
	CBulletDeletedMsg(int _iDirection) : m_iDirection(_iDirection) {}

	inline int GetDirection() const { return m_iDirection; }
};