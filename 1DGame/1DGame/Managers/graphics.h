//
// Class CGraphics (singleton)
//
// This class is the graphics engine which is in charge of rendering all
// the entities (elements) in the world that has a render component.
//

#pragma once

#include <vector>

class CRenderableElement;

class CGraphics
{
private:
	std::vector<CRenderableElement*> m_pRenderableElements;

	CGraphics() {};

public:
	// Singleton pattern
	static CGraphics& GetInstance();
	CGraphics(CGraphics const&) = delete;
	void operator= (CGraphics const&) = delete;

	void Init();
	void Update();
	void Terminate();

	void InsertRenderElement(CRenderableElement& _cRenderObj);
	void DeleteRenderElement(CRenderableElement& _cRenderObj);
};