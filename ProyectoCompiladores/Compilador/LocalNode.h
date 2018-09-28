#pragma once

#include <string>
#include "EnumScope.h"
using namespace std;

class CLocalNode
{
public:
	CLocalNode();
	~CLocalNode();
private:
	string m_type;
	E_Scope m_scope;
	int m_dimen;
	void * m_value;
	CLocalNode* m_localnode;
};

