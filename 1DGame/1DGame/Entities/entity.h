//
// Class Entity
//
// Entities are the elements in the game. The main character, enemies, and bullets are entities.
// The components that forms an entity shape its behavior, so differents components will result in a different entity.
// This way we can create endless different elements just creating new components and assigning them to entities.
//

#pragma once

#include <vector>

class CComponent;
class CMessage;

class CEntity
{
private:
	std::vector<CComponent*> m_pComponents;

public:
	CEntity();
	~CEntity();

	void Activate();
	void Deactivate();
	void Update();

	bool IsActivated() const;

	// Sends a message to its components.
	void SendMsg(const CMessage& message) const;

	// Add a component.
	template <class T>
	void AddComponent(T& _cComponent)
	{
		m_pComponents.push_back(&_cComponent);
		_cComponent.SetOwner(*this);
	}

	// Find a component.
	template <class T>
	T* FindComponent() const
	{
		for (auto compIt = m_pComponents.begin(); compIt != m_pComponents.end(); ++compIt) {
			T* pComp = dynamic_cast<T*>(*compIt);
			if (pComp != nullptr) {
				return pComp;
			}
		}
		return nullptr;
	}
};