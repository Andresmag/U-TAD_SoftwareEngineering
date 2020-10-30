//
// Class Character Movement Component
//
// Component that save the logic position of the player and provides it with the ability to move along the world
//

 #pragma once

#include "component.h"

class CCompCharacterMovement : public CComponent
{
private:
	unsigned int m_uPos;

public:
	CCompCharacterMovement(unsigned int _uPos);

	unsigned int GetPos();

	virtual void Update() override {};

	virtual void ReceiveMsg(const CMessage& message) override;
};