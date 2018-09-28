#include "stdafx.h"
#include "Tokens.h"

Compilador::CToken::CToken(string lex, TOKEN_TYPE type, int lineNum)
{
	m_Lex = lex;
	m_Type = type;
	m_LineNumber = lineNum;
}

Compilador::CToken::~CToken()
{

}

string Compilador::CToken::getTypeStr()
{
	switch (m_Type)
	{
	case Compilador::TOKEN_TYPE::UNDEFINED:
		return string("Sin definir");
		break;
	case Compilador::TOKEN_TYPE::ID:
		return string("ID");
		break;
	case Compilador::TOKEN_TYPE::INT:
		return string("int");
		break;
	case Compilador::TOKEN_TYPE::FLOAT:
		return string("float");
		break;
	case Compilador::TOKEN_TYPE::STRING:
		return string("string");
		break;
	case Compilador::TOKEN_TYPE::KEYWORD:
		return string("keyword");
		break;
	case Compilador::TOKEN_TYPE::OPLOG:
		return string("Operador logico");
		break;
	case Compilador::TOKEN_TYPE::OPNUNARY:
		return string("Operador logico unario");
		break;
	case Compilador::TOKEN_TYPE::OPARIT:
		return string("Operador aritmetico");
		break;
	case Compilador::TOKEN_TYPE::OPREL:
		return string("Operador relacional");
		break;
	case Compilador::TOKEN_TYPE::ASSIGN:
		return string("Operador de asignacion");
		break;
	case Compilador::TOKEN_TYPE::DEL:
		return string("Delimitador");
		break;
	case Compilador::TOKEN_TYPE::OPAGROUP:
		return string("Agrupacion");
		break;
	case Compilador::TOKEN_TYPE::OPDIMEN:
		return string("Operador de dimension");
		break;
	default:
		return string("Desconocido");
		break;
	}
}
