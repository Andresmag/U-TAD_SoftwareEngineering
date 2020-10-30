//
// Class Render Component
//
// This component gives to an entity the ability to be renderable by the graphic engine
//

#pragma once

#include "../../Graphics/renderable.h"
#include "component.h"

class CCompRender : public CComponent
{
private:
	CRenderableElement m_pPosition;

public:
	CCompRender(unsigned int _uPos, const char _cValue);
	~CCompRender();

	void SetPos(unsigned int _uPos);
	unsigned int GetPos() const;
	char GetSymbol() const;

	inline virtual void Update() override {}

	virtual void ReceiveMsg(const CMessage& message) override;
};
