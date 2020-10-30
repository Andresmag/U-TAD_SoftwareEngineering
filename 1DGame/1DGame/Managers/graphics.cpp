#include "graphics.h"
#include "../Graphics/renderable.h"
#include "world.h"
#include <assert.h>
#include <cstdio>
#include <stdlib.h>

CGraphics& CGraphics::GetInstance()
{
	static CGraphics graphics;
	return graphics;
}

void CGraphics::Init()
{
	m_pRenderableElements.clear();
}

void CGraphics::Update()
{
	printf("\r");

	for (unsigned int uIndex = 0; uIndex < CWorld::GetInstance().GetWorldLength(); ++uIndex)
	{
		// Search for and element that is in the uIndex position of the world and print it
		// if no element is found just print a - which is a blank space
		bool printed = false;
		for (CRenderableElement* pRenderableElement : m_pRenderableElements)
		{
			assert(pRenderableElement != nullptr);
			if (uIndex == pRenderableElement->GetPos()) {
				pRenderableElement->Render();
				printed = true;
				break;
			}
		}
		if (!printed)
			printf("-");
	}

	printf("  %u", CWorld::GetInstance().GetPoints());
}

void CGraphics::Terminate()
{
	m_pRenderableElements.clear();
	system("CLS");
	printf("GAME ENDED WITH SCORE = %u", CWorld::GetInstance().GetPoints());
}

void CGraphics::InsertRenderElement(CRenderableElement& _cRenderObj)
{
	m_pRenderableElements.push_back(&_cRenderObj);
}

void CGraphics::DeleteRenderElement(CRenderableElement& _cRenderObj)
{
	for (auto it = m_pRenderableElements.begin(); it != m_pRenderableElements.end(); ++it) {
		if (*it == &_cRenderObj) {
			m_pRenderableElements.erase(it);
			break;
		}
	}
}
