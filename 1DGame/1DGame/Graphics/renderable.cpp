#include "renderable.h"
#include <cstdio>

CRenderableElement::CRenderableElement(unsigned int _uPos, const char _cValue)
	: m_uPos(_uPos)
	, m_cSymbol(_cValue)
{
}

void CRenderableElement::SetPos(unsigned int _uPos)
{
	m_uPos = _uPos;
}

unsigned int CRenderableElement::GetPos() const
{
	return m_uPos;
}

char CRenderableElement::GetSymbol() const
{
	return m_cSymbol;
}

void CRenderableElement::SetSymbol(char _cSymbol)
{
	m_cSymbol = _cSymbol;
}

void CRenderableElement::Render()
{
	printf("%c", m_cSymbol);
}
