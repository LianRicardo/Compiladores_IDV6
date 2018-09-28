// Compilador.h

#pragma once
#include <Windows.h>
#include "Lexico.h"
#include "ErrorModule.h"
using namespace System;

namespace Compilador 
{
	public ref class Manager
	{
	private:
		CLexico  * cpp_lexAnalyzer;      // LEX ANALYZER INSTANCE
		CErrorModule ^ managed_errorsModule; // ERRORS MODULE
		void lexAnalysis(String ^ sourceCode);
		cli::array<String ^> ^ getCompilationDetails();
	public:
		Manager();
		~Manager();
		
		cli::array<String ^> ^ compileProgram(String ^ sourcecode);
	};
}
