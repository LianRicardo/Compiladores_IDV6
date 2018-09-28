#include "stdafx.h"
#include "TabSym.h"


CTabSym::CTabSym()
{

}

CTabSym::~CTabSym()
{
	for each (auto var in m_symbols)
	{
		//delete m_symbols;
	}
	m_symbols.clear();
}
