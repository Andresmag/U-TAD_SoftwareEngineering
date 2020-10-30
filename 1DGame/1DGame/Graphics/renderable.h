//
// Clasa Renderable Element
//
// This class specify the data that are necessary in order to print
// an entity in the world window (terminal), as well it has the render
// method that the graphic engine will call to print the element
//

#pragma once

class CRenderableElement
{
private:
	unsigned int m_uPos;
	char m_cSymbol;

public:
	CRenderableElement(unsigned int _uPos, const char _cValue);

	void SetPos(unsigned int _uPos);
	void SetSymbol(char _cSymbol);
	unsigned int GetPos() const;
	char GetSymbol() const;

	// Render method.
	void Render();
};