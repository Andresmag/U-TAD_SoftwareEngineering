//
// Class Input Component
//
// This component gives to an entity the ability to read the inputs in the keyboard
// It is restricted to the main character entity
//

#pragma once

#include "component.h"

class CCompInput : public CComponent
{
public:
	CCompInput() {}

	virtual void Update() override;
};