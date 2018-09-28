#include "stdafx.h"
#include "ErrorModule.h"
using namespace System;

Compilador::CErrorModule::CErrorModule()
{
	m_numErrors = 0;
	m_errorsArray = gcnew cli::array<String ^>(MAXERROR);
	for (int i = 0; i < MAXERROR; ++i)
	{
		m_errorsArray[i] = gcnew String("");
	}
}

Compilador::CErrorModule::~CErrorModule()
{
	
}

void Compilador::CErrorModule::reset()
{
	m_numErrors = 0;
}

bool Compilador::CErrorModule::addErrorLex(int lineNum, const char * desc, const char * line)
{
	String ^ strDesc = gcnew String(desc);
	String ^ strLine = gcnew String(line);
	return addError(Compilador::ERROR_PHASE::LEX_ANALYZER, lineNum, strDesc, strLine);
}

bool Compilador::CErrorModule::addError(ERROR_PHASE errorPhase, int lineNumber, String ^ errorDesc, String ^ errorLine)
{
	if (m_numErrors < MAXERROR)
	{
		String ^ errLine = gcnew String("");
		if (errorLine->Length > 20)
		{
			errLine = errorLine->Substring(0, 20);
		}
		else
		{
			errLine = errorLine;
		}
		m_errorsArray->SetValue(String::Format("<{0}>: \t{1} \t\t{2} \t\t{3}", errorPhase.ToString(), lineNumber, errorDesc, errLine), m_numErrors);
		++m_numErrors;
		return true;
	}
	return false;
}


