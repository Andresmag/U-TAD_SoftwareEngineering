#include "Components/component.h"
#include "entity.h"

CEntity::CEntity()
{
}

CEntity::~CEntity()
{
	for (CComponent* component : m_pComponents)
	{
		delete component;
	}
	m_pComponents.clear();
}

void CEntity::Activate()
{
	for (auto compIt = m_pComponents.begin(); compIt != m_pComponents.end(); ++compIt)
	{
		(*compIt)->Activate();
	}
}

void CEntity::Deactivate()
{
	for (auto compIt = m_pComponents.begin(); compIt != m_pComponents.end(); ++compIt)
	{
		(*compIt)->Deactivate();
	}
}

void CEntity::Update()
{
	for (auto compIt = m_pComponents.begin(); compIt != m_pComponents.end(); ++compIt)
	{
		if ((*compIt)->GetActivated())
			(*compIt)->Update();
	}
}

bool CEntity::IsActivated() const
{
	for (auto compIt = m_pComponents.begin(); compIt != m_pComponents.end(); ++compIt) {
		if ((*compIt)->GetActivated()) // if at least one of its component is activated then the entity is activated
			return true;
	}

	return false;
}

void CEntity::SendMsg(const CMessage& message) const
{
	for (auto compIt = m_pComponents.begin(); compIt != m_pComponents.end(); ++compIt) {
		if ((*compIt)->GetActivated())
			(*compIt)->ReceiveMsg(message);
	}
}
