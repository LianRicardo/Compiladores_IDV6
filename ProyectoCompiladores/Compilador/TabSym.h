#pragma once

#include <map>
#include "GlobalNode.h"
#include "EnumScope.h"
using namespace std;

class CTabSym
{
public:
	CTabSym();
	~CTabSym();
private:
	std::map<std::string, CGlobalNode *> m_symbols;
	bool addSymbols(string name, E_Scope s,int dimen, string func);
	bool SymbolExists(string name, E_Scope s, string func);
	string getSymbolType(string name, E_Scope s, string func);
	string getSymbolScope(string name);
	bool updateSymbolType();
	int getSybolDimen(string name, E_Scope s, string func);
	void reset();
};

