#pragma once

#include <Windows.h>
#include <vcclr.h>
using namespace System;
#include <map>
#include <vector>
#include <stack>
#include "ErrorModule.h"
#include "Tokens.h"

namespace Compilador
{
	enum class State
	{
		START = 0,
		ID,
		INT,
		FLOAT,
		STRING,
		OPLOGICO,
		OPARITME,
		OPRELAT,
		DEL,
		AGRUPACION,
		COMENTARIO,
		OPDIMENCIONAL,
		OPLOGUNIT
	};

#define LEX_ERROR_INVALID_CHARACTER         "Invalid character"
#define LEX_ERROR_STRING_NOT_CLOSED         "String constant not closed"
#define LEX_ERROR_COMMENT_NOT_CLOSED        "Comment not closed"
#define LEX_ERROR_INVALID_FLOAT             "Invalid floating point number. Digit expected"
#define LEX_ERROR_INVALID_LOGICAL_OP_AND    "Invalid logical 'AND' operator. "
#define LEX_ERROR_INVALID_LOGICAL_OP_OR     "Invalid logical 'OR' operator."
#define LEX_ERROR_INVALID_STATE             "Internal error. Invalid state."
#define LEX_ERROR_INVALID_INT               "Invalid int number. Digit expected"

	class CLexico
	{
	private:
		msclr::gcroot<CErrorModule ^> m_errors;
		std::map<std::string, std::string> m_Keywords;
		std::vector<CToken *> m_Tokens;
	public:
		State m_state;
		CLexico(CErrorModule ^errorsModule);
		~CLexico();
		bool parseSourceCode(const char *sourceCode);
		void reset();
		void getTokens(vector<CToken *> *tokensVec) const;
		void addTokens(string lex, TOKEN_TYPE type, int lineNum);
		void createTokenReference();
		bool isalpha(const char c)
		{
			return(c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h' || c == 'i' || c == 'j' || c == 'k' ||
				c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' ||
				c == 'w' || c == 'x' || c == 'y' || c == 'z' || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G' || c == 'H' || c == 'I' || c == 'J' || c == 'K' ||
				c == 'L' || c == 'M' || c == 'N' || c == 'O' || c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' || c == 'U' || c == 'V' ||
				c == 'W' || c == 'X' || c == 'Y' || c == 'Z');
		}
		bool isdigit(const char c)
		{
			return(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
				c == '6' || c == '7' || c == '8' || c == '9');
		}

	};
}

