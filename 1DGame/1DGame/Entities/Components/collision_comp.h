//
// Class Collision Components
//
// This components provides the entity with the capacity to collide with other entities that has it too
// It saves its own position because it might be different from the logic or the render
//

#pragma once

#include "component.h"

class CCompCollision : public CComponent
{
private:
	unsigned int m_uPos;

public:
	CCompCollision(unsigned int _uPos);

	void SetPos(unsigned int _uPos);
	unsigned int GetPos() const;

	virtual void Update() override;

	virtual void ReceiveMsg(const CMessage& message) override;
};