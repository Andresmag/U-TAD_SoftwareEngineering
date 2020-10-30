//
// Class Shoot Component
//
// This component gives to an entity the ability to shoot bullets
//

#pragma once

#include "component.h"

class CCompShoot : public CComponent
{
private:
	unsigned int m_uRightAvailableBullets;
	unsigned int m_uLeftAvailableBullets;

public:
	CCompShoot(unsigned int _uRight, unsigned int _uLeft);

	unsigned int GetRightAvailableBullets();
	unsigned int GetLeftAvailableBullets();

	virtual void Update() override {};

	virtual void ReceiveMsg(const CMessage& message) override;
};