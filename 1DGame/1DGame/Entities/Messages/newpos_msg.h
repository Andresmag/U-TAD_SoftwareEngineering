//
// Class New Position Message
//
// Message that inform other components of a change in the position. 
// The message contains the new position.
//

#pragma once

#include "message.h"

class CNewPosMsg : public CMessage
{
private:
	unsigned int m_uPos;

public:
	CNewPosMsg(unsigned int _uPos) : m_uPos(_uPos) {}

	inline unsigned int GetPos() const { return m_uPos; }
};