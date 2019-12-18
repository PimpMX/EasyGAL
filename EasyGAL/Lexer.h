#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Debug.h"
#include "Token.h"
#include "Helper.h"

using namespace std;

class Lexer
{

public:

	bool Analyze(vector<string> Input, vector<Token>* pTokensOut);
	bool AnalyzeLine(string Input, vector<Token>* pTokensOut);
	bool AnalyzeFile(string Path, vector<Token>* pTokensOut = nullptr);

private:

	bool LoadFile(string Path);

	void PreProcessing();
	void RemoveComments();

	bool GenerateTokens();
	void GenerateFile(string Name);

private:

	vector<string> m_Input;
	vector<Token> m_Tokens;
	ofstream m_OutputFile;
};

extern Lexer g_Lexer;

const string TOKEN_DELIMITERS = "=&|^!()[]{};";
const string DEFAULT_DELIMITERS = " \t\v\n\r\f";


