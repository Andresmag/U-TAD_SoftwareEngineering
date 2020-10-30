#include "render_comp.h"
#include "../../Managers/graphics.h"
#include "../Messages/newpos_msg.h"

CCompRender::CCompRender(unsigned int _uPos, const char _cValue)
	: m_pPosition(_uPos, _cValue)
{
	CGraphics::GetInstance().InsertRenderElement(m_pPosition);
}

CCompRender::~CCompRender()
{
	CGraphics::GetInstance().DeleteRenderElement(m_pPosition);
}

void CCompRender::SetPos(unsigned int _uPos)
{
	m_pPosition.SetPos(_uPos);
}

unsigned int CCompRender::GetPos() const
{
	return m_pPosition.GetPos();
}

char CCompRender::GetSymbol() const
{
	return m_pPosition.GetSymbol();
}

void CCompRender::ReceiveMsg(const CMessage& message)
{
	// Checks for messages informing on a change in the logic position of the entity
	const CNewPosMsg* pMsg = dynamic_cast<const CNewPosMsg*>(&message);
	if (pMsg != nullptr) {
		m_pPosition.SetPos(pMsg->GetPos());
		return;
	}
}
