//
// Class Component
//
// Components are the small parts that forms an entity.
// Every component implements a new behavior for the entities.
// A component only works when it is activated
//

#pragma once

class CEntity;
class CMessage;

class CComponent
{
private:
	CEntity* m_pOwner;
	bool m_bActivated;

public:
	CComponent();

	void SetOwner(CEntity& _cEntity);
	CEntity* GetOwner() const;
	bool GetActivated() const;

	void Activate();
	void Deactivate();
	virtual void Update() = 0;

	// Receive from another component.
	virtual void ReceiveMsg(const CMessage& message)
	{};
};