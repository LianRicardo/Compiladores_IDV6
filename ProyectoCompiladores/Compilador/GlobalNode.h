#pragma once

#include "LocalNode.h"
#include <string>
#include "EnumScope.h"
using namespace std;

class CGlobalNode
{
public:
	CGlobalNode();
	~CGlobalNode();
private:

	string m_name;
	string m_type;
	E_Scope m_scope;
	int m_dimen;
	void * m_value;
	CLocalNode* m_localnode;
};

