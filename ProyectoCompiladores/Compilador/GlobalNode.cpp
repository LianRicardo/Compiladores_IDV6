#include "stdafx.h"
#include "GlobalNode.h"


CGlobalNode::CGlobalNode()
{
}

CGlobalNode::~CGlobalNode()
{
	m_localnode = nullptr;
	m_value = nullptr;
	delete(m_localnode);
	delete(&m_name);
	delete(&m_type);
	delete(&m_dimen);
	delete(&m_scope);
	delete(&m_value);
}
