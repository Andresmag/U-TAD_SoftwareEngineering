//
// Class Bullet Movement Component
//
// Component that save the logic position and direction of a bullet and gives it the ability to move along the world
//

#pragma once

#include "component.h"

class CCompBulletMovement : public CComponent
{
private:
	unsigned int m_uPos;
	int m_iDirection;

public:
	CCompBulletMovement(unsigned int _uPos, int _iDirection);

	void SetPos(unsigned int _uPos);

	unsigned int GetPos() const;
	int GetDirection() const;

	virtual void Update() override;

	virtual void ReceiveMsg(const CMessage& message) override;
};