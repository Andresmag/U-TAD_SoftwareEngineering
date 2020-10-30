//
// Class Enemy Movement Component
//
// Component that save the logic position and direction of an enemy and gives it the ability to move along the world
//

#pragma once

#include "component.h"

class CCompEnemyMovement : public CComponent
{
private:
	unsigned int m_uPos;
	int m_iDirection;

public:
	CCompEnemyMovement(unsigned int _uPos, int _iDirection);

	void SetPos(unsigned int _uPos);
	unsigned int GetPos() const;
	void SetDirection(int _iDirection);
	int GetDirection() const;

	virtual void Update() override;

	virtual void ReceiveMsg(const CMessage& message) override;
};