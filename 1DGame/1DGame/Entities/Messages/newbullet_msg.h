//
// Class New Bullet Message
//
// Message that inform other components that a new bullet has to be created.
// The message contains the position to spawn the bullet and its direction.
//

#pragma once

#include "message.h"

class CNewBulletMsg : public CMessage
{
private:
	unsigned int m_uPos;
	int m_iDirection;

public:
	CNewBulletMsg(unsigned int _uPos, int _iDirection) : m_uPos(_uPos), m_iDirection(_iDirection) {}

	inline unsigned int GetPos() const { return m_uPos; }
	inline int GetDirection() const { return m_iDirection; }
};