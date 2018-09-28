#pragma once
#include "windows.h"
using namespace System;

namespace Compilador
{
#define MAXERROR 100
	public enum class ERROR_PHASE
	{
		UNDEFINED,
		LEX_ANALYZER,
		SYNTAX_ANALYZER,
		SEMANTIC_ANALYZER,
		CODE_GENERATION,
		SIZE
	};

	ref class CErrorModule
	{
	private:
		cli::array<String ^> ^ m_errorsArray;
		bool addError(ERROR_PHASE errorPhase, int lineNumber, String ^ errorDesc, String ^ errorLine);
	public:
		int m_numErrors;
		CErrorModule();
		~CErrorModule();
		void reset();
		bool addErrorLex(int lineNum, const char *desc, const char *line);
		property cli::array<String ^> ^ Errors
		{
			cli::array<String ^> ^ get()
			{
				return m_errorsArray;
			}
		}
	};
}

