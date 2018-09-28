#include "stdafx.h"
#include "Lexico.h"

Compilador::CLexico::CLexico(CErrorModule ^ errorsModule)
{
	m_errors = errorsModule;
	createTokenReference();
}

Compilador::CLexico::~CLexico()
{
	delete(&m_Tokens);
	delete(m_errors);
	reset();
}

void Compilador::CLexico::reset()
{
	m_Keywords.clear();
	m_Tokens.clear();
	m_errors->reset();
}

bool Compilador::CLexico::parseSourceCode(const char * sourceCode)
{
	int lineNumber = 1;
	bool finish = false;
	const char *currcharacter = sourceCode;
	const char *nexttoke = sourceCode;
	string buffer;
	string linebuffer;
	m_state = State::START;
	while (*currcharacter != '\0')
	{
		switch (m_state)
		{
		case Compilador::State::START:
			if (isalpha(*currcharacter) || *currcharacter == '_')
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::ID;
			}
			else if (isdigit(*currcharacter))
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::INT;
			}
			else if (*currcharacter == '+' || *currcharacter == '-' || *currcharacter == '/' || *currcharacter == '*' || *currcharacter == '%' || *currcharacter == '^')
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::OPARITME;
			}
			else if (*currcharacter == ':' || *currcharacter == ';' || *currcharacter == '.' || *currcharacter == ',')
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::DEL;
			}
			else if (*currcharacter == '"')
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::STRING;
			}
			else if (*currcharacter == '=' || *currcharacter == '<' || *currcharacter == '>')
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::OPRELAT;
			}
			else if (*currcharacter == '!')
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::OPLOGUNIT;
			}
			else if (*currcharacter == '&' || *currcharacter == '|')
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::OPLOGICO;
			}
			else if (*currcharacter == '{' || *currcharacter == '}' || *currcharacter == '(' || *currcharacter == ')')
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::AGRUPACION;
			}
			else if (*currcharacter == '[' || *currcharacter == ']')
			{
				buffer.clear();
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::OPDIMENCIONAL;
			}
			else if (*currcharacter == '\t' || *currcharacter == ' ')
			{
				currcharacter++;
			}
			else if (*currcharacter == '\n' || *currcharacter == '\r')
			{
				lineNumber++;
				currcharacter++;
				m_state = State::START;
			}
			else
			{
				linebuffer.append(currcharacter, 1);
				m_errors->addErrorLex(lineNumber, LEX_ERROR_INVALID_CHARACTER, linebuffer.c_str());
				linebuffer.clear();
				currcharacter++;
				break;
			}
			break;
		case Compilador::State::ID:
			if (isalpha(*currcharacter) || *currcharacter == '_' || isdigit(*currcharacter))
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				if (*currcharacter == '\0')
				{
					finish = true;
				}
			}
			else
			{
				finish = true;
			}
			if (finish)
			{
				if (m_Keywords.find(buffer) != m_Keywords.end())
				{
					addTokens(buffer.c_str(), Compilador::TOKEN_TYPE::KEYWORD, lineNumber);
				}
				else
				{
					addTokens(buffer.c_str(), Compilador::TOKEN_TYPE::ID, lineNumber);
				}
				finish = false;
				m_state = State::START;
			}
			break;
		case Compilador::State::INT:
			if (isdigit(*currcharacter))
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
			}
			else if (*currcharacter == '.')
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::FLOAT;
			}
			else
			{
				if (isalpha(*currcharacter))
				{
					linebuffer.append(currcharacter, 1);
					m_errors->addErrorLex(lineNumber, LEX_ERROR_INVALID_INT, linebuffer.c_str());
					linebuffer.clear();
					currcharacter++;
				}
				else
				{
					addTokens(buffer.c_str(), Compilador::TOKEN_TYPE::INT, lineNumber);
				}
				m_state = State::START;
			}
			break;
		case Compilador::State::FLOAT:
			if (isdigit(*currcharacter))
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
			}
			else
			{
				if (isalpha(*currcharacter))
				{
					linebuffer.append(currcharacter, 1);
					m_errors->addErrorLex(lineNumber, LEX_ERROR_INVALID_FLOAT, linebuffer.c_str());
					linebuffer.clear();
					currcharacter++;
				}
				else
				{
					addTokens(buffer.c_str(), Compilador::TOKEN_TYPE::FLOAT, lineNumber);
				}
				m_state = State::START;
			}
			break;
		case Compilador::State::COMENTARIO:
			nexttoke = currcharacter++;
			if (*currcharacter == '*' && *nexttoke =='/')
			{
				currcharacter++;
				m_state = State::START;
			}
			else
			{
				linebuffer.append(currcharacter, 1);
				m_errors->addErrorLex(lineNumber, LEX_ERROR_COMMENT_NOT_CLOSED, linebuffer.c_str());
				linebuffer.clear();
				currcharacter++;
				m_state = State::START;
			}
			break;
		case Compilador::State::OPARITME:
			if (*currcharacter == '*' && buffer.back() == '/')
			{
				linebuffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::COMENTARIO;
			}
			else if (isdigit(*currcharacter) && buffer.back() == '-')
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::INT;
			}
			else if (*currcharacter == '.' && buffer.back() == '-')
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::FLOAT;
			}
			else if(buffer.back() == '+'|| buffer.back() == '-' || buffer.back() == '*' || buffer.back() == '/' || buffer.back() == '%' || buffer.back() == '^')
			{
				addTokens(buffer, Compilador::TOKEN_TYPE::OPARIT, lineNumber);
				m_state = State::START;
			}
			break;
		case Compilador::State::DEL:
			if (isdigit(*currcharacter) && buffer.back() == '.')
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				m_state = State::FLOAT;
			}
			else
			{
				addTokens(buffer, Compilador::TOKEN_TYPE::DEL, lineNumber);
				m_state = State::START;
			}
			break;
		case Compilador::State::STRING:
			if (*currcharacter != '"')
			{
				linebuffer.append(currcharacter, 1);
				m_errors->addErrorLex(lineNumber, LEX_ERROR_STRING_NOT_CLOSED, linebuffer.c_str());
				linebuffer.clear();
				currcharacter++;
				m_state = State::START;
			}
			else
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				addTokens(buffer, Compilador::TOKEN_TYPE::STRING, lineNumber);
				m_state = State::START;
			}
			break;
		case Compilador::State::AGRUPACION:
			addTokens(buffer, Compilador::TOKEN_TYPE::ASSIGN, lineNumber);
			m_state = State::START;
			break;
		case Compilador::State::OPDIMENCIONAL:
			addTokens(buffer, Compilador::TOKEN_TYPE::OPDIMEN, lineNumber);
			m_state = State::START;
			break;
		case Compilador::State::OPLOGICO:
			if (*currcharacter != buffer.back())
			{
				if (buffer.back() == '|')
				{
					linebuffer.append(currcharacter, 1);
					m_errors->addErrorLex(lineNumber, LEX_ERROR_INVALID_LOGICAL_OP_OR, linebuffer.c_str());
					linebuffer.clear();
					currcharacter++;
					m_state = State::START;
				}
				else
				{
					linebuffer.append(currcharacter, 1);
					m_errors->addErrorLex(lineNumber, LEX_ERROR_INVALID_LOGICAL_OP_AND, linebuffer.c_str());
					linebuffer.clear();
					currcharacter++;
					m_state = State::START;
				}
				currcharacter++;
				m_state = State::START;
			}
			else
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				addTokens(buffer, Compilador::TOKEN_TYPE::OPLOG, lineNumber);
				m_state = State::START;
			}
			break;
		case Compilador::State::OPLOGUNIT:
			if (*currcharacter == '!')
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				addTokens(buffer, Compilador::TOKEN_TYPE::OPNUNARY, lineNumber);
				m_state = State::START;
			}
			else
			{
				linebuffer.append(currcharacter, 1);
				m_errors->addErrorLex(lineNumber, "invalid Unary operator", linebuffer.c_str());
				linebuffer.clear();
				currcharacter++;
				m_state = State::START;
			}
			break;
		case Compilador::State::OPRELAT:
			if (*currcharacter == '=')
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				addTokens(buffer, Compilador::TOKEN_TYPE::OPREL, lineNumber);
				m_state = State::START;
			}
			else if (*currcharacter == '<')
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				addTokens(buffer, Compilador::TOKEN_TYPE::OPREL, lineNumber);
				m_state = State::START;
			}
			else if (*currcharacter == '>')
			{
				buffer.append(currcharacter, 1);
				currcharacter++;
				addTokens(buffer, Compilador::TOKEN_TYPE::OPREL, lineNumber);
				m_state = State::START;
			}
			else
			{
				linebuffer.append(currcharacter, 1);
				m_errors->addErrorLex(lineNumber, "invalid relational operator", linebuffer.c_str());
				linebuffer.clear();
				currcharacter++;
				m_state = State::START;
			}
			break;
		default:
			linebuffer.append(currcharacter, 1);
			m_errors->addErrorLex(lineNumber, LEX_ERROR_INVALID_STATE, linebuffer.c_str());
			linebuffer.clear();
			currcharacter++;
			m_state = State::START;
			break;
		}
	}
	return true;
}

void Compilador::CLexico::getTokens(std::vector<CToken*>* tokensVec) const
{
	*tokensVec = m_Tokens;
}

void Compilador::CLexico::addTokens(string lex, TOKEN_TYPE type, int lineNum)
{
	CToken *t = new CToken(lex, type, lineNum);
	m_Tokens.push_back(t);
	lex.clear();
}

void Compilador::CLexico::createTokenReference()
{
	m_Keywords.insert(std::make_pair("var", ""));
	m_Keywords.insert(std::make_pair("int", ""));
	m_Keywords.insert(std::make_pair("float", ""));
	m_Keywords.insert(std::make_pair("string", ""));
	m_Keywords.insert(std::make_pair("bool", ""));
	m_Keywords.insert(std::make_pair("void", ""));
	m_Keywords.insert(std::make_pair("function", ""));
	m_Keywords.insert(std::make_pair("main", ""));
	m_Keywords.insert(std::make_pair("if", ""));
	m_Keywords.insert(std::make_pair("else", ""));
	m_Keywords.insert(std::make_pair("while", ""));
	m_Keywords.insert(std::make_pair("for", ""));
	m_Keywords.insert(std::make_pair("inc", ""));
	m_Keywords.insert(std::make_pair("dec", ""));
	m_Keywords.insert(std::make_pair("switch", ""));
	m_Keywords.insert(std::make_pair("case", ""));
	m_Keywords.insert(std::make_pair("default", ""));
	m_Keywords.insert(std::make_pair("print", ""));
	m_Keywords.insert(std::make_pair("read", ""));
	m_Keywords.insert(std::make_pair("return", ""));
	m_Keywords.insert(std::make_pair("true", ""));
	m_Keywords.insert(std::make_pair("false", ""));
}
