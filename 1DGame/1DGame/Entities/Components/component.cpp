#include "component.h"

CComponent::CComponent()
	: m_pOwner(nullptr)
	, m_bActivated(false)
{
}

void CComponent::SetOwner(CEntity& _cEntity)
{
	m_pOwner = &_cEntity;
}

CEntity* CComponent::GetOwner() const
{
	return m_pOwner;
}

bool CComponent::GetActivated() const
{
	return m_bActivated;
}

void CComponent::Activate()
{
	m_bActivated = true;
}

void CComponent::Deactivate()
{
	m_bActivated = false;
}
