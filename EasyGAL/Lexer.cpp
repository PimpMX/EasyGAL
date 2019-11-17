#include "Lexer.h"

Lexer g_Lexer;

bool Lexer::Analyze(string Path)
{
	if (LoadFile(Path) == false) 
	{
		ERROR("%s", "Lexical analysis failed, could not load file");
		return false;
	}

	return false;
}

bool Lexer::LoadFile(string Path)
{
	m_InputFile = ifstream(Path);

	if (m_InputFile.good() == false)
	{
		ERROR("%s%s%s", R"(File ")", Path.c_str(), R"(" could not be opened)");
		return false;
	}

	return true;
}

void Lexer::PreProcessing()
{
}

void Lexer::RemoveSpaces()
{
}

void Lexer::RemoveComments()
{
}
