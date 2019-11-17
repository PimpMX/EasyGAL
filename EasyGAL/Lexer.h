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

	bool Analyze(string Path);

private:

	bool LoadFile(string Path);

	void PreProcessing();
	void RemoveSpaces();
	void RemoveComments();

private:

	ifstream m_InputFile;
	ofstream m_OutputFile;
	vector<Token> m_Tokens;
};

extern Lexer g_Lexer;

