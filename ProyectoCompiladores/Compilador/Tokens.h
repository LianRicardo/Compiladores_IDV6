#pragma once
#include <string>
using namespace std;

namespace Compilador
{
	enum TOKEN_TYPE
	{
		UNDEFINED = 0,
		ID,
		INT,
		FLOAT,
		STRING,
		KEYWORD,
		OPLOG,
		OPNUNARY,
		OPARIT,
		OPREL,
		ASSIGN,
		DEL,
		OPAGROUP,
		OPDIMEN
	};

	class CToken
	{
	private:
		string m_Lex;
		TOKEN_TYPE m_Type;
		int m_LineNumber;
	public:
		CToken(string lex, TOKEN_TYPE type, int lineNum);
		~CToken();
        string getLex() const { return m_Lex; }
		string getTypeStr();
		TOKEN_TYPE getType() const { return m_Type; }
		int getLineNumber() const { return m_LineNumber; }
	};
}
