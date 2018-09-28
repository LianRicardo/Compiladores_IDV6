// Archivo DLL principal.

#include "stdafx.h"

#include "Compilador.h"
#include "ErrorModule.h"

Compilador::Manager::Manager()
{
	managed_errorsModule = gcnew CErrorModule();
	cpp_lexAnalyzer = new CLexico(managed_errorsModule);
}

Compilador::Manager::~Manager()
{
	if (cpp_lexAnalyzer != nullptr)
	{
		delete cpp_lexAnalyzer;
		cpp_lexAnalyzer = nullptr;
	}
}


cli::array<String ^>^ Compilador::Manager::compileProgram(String ^ sourcecode)
{
	cli::array<String ^> ^ compilationDetails;

	// Clear state if all pointers are valid
	if (managed_errorsModule && cpp_lexAnalyzer)
	{
		managed_errorsModule->reset();
		cpp_lexAnalyzer->reset();
	}
	else
	{
		// invalid pointers, return error...
	}

	lexAnalysis(sourcecode);

	compilationDetails = getCompilationDetails();

	return compilationDetails;
};

void Compilador::Manager::lexAnalysis(String ^ sourceCode)
{
	if (cpp_lexAnalyzer != nullptr)
	{
		cpp_lexAnalyzer->parseSourceCode((const char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sourceCode).ToPointer());
	}
}

cli::array<String^>^ Compilador::Manager::getCompilationDetails()
{
	//crea una variable auto que deduce el tipo de managed_errors->errors osea un array de cli
	auto errors = managed_errorsModule->Errors;
	//crea un vector de tokens dode va a ir todas las token
	vector <CToken*> tokens;
	//hace un get tokens para llenar el vector
	cpp_lexAnalyzer->getTokens(&tokens);
	//hace un int que le da el numero de errores totales
	int sizeoferror = managed_errorsModule->m_numErrors;
	//hace un arreglo de cli(que es el que va a tener toda la cadena) y lo crea con el tamaño de los tokens y errores 
	cli::array<String ^> ^ compilerdetails = gcnew cli::array<String ^>(sizeoferror + (int)tokens.size() + 1);
	//hace un for que recorra de 0 al total de errores y los va metiendo en el arreglo de cli
	for (int i = 0; i < sizeoferror; i++)
	{
		compilerdetails[i] = errors[i];
	}
	//al final le mete un arroba para separar esta cadena y la de tokens
	compilerdetails[sizeoferror] = "@";
	//lo mismo un for que recorra de 0 al token.size y le va metiendo los tokens, los tipos y el numero de linea separandolos por un tabulador
	for (int i = 0; i < tokens.size(); i++)
	{
		compilerdetails[i + sizeoferror + 1] = gcnew String((to_string(tokens[i]->getLineNumber()) + "\t" + tokens[i]->getLex() +"\t" + tokens[i]->getTypeStr()).c_str());
	}
	// regresa la cadena que va a recibir el form.
	return compilerdetails;
}
