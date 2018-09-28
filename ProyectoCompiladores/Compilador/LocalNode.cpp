#include "stdafx.h"
#include "LocalNode.h"


CLocalNode::CLocalNode()
{
}

CLocalNode::~CLocalNode()
{
	m_localnode = nullptr;
	m_value = nullptr;
	delete(m_localnode);
	delete(&m_type);
	delete(&m_dimen);
	delete(&m_scope);
	delete(&m_value);
}
