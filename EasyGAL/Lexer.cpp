#include "Lexer.h"

Lexer g_Lexer;

bool Lexer::Analyze(string Path)
{
	if (LoadFile(Path) == false) 
	{
		ERROR("%s", "Lexical analysis failed, could not load file");
		return false;
	}

	PreProcessing();

	if (GenerateTokens() == false)
	{
		ERROR("%s", "Lexical analysis failed, file is empty");
		return false;
	}

	GenerateFile("testlex.lex");
	return false;
}

bool Lexer::LoadFile(string Path)
{
	ifstream InputFile = ifstream(Path);

	if (InputFile.good() == false)
	{
		ERROR("%s%s%s", R"(File ")", Path.c_str(), R"(" could not be opened)");
		return false;
	}

	string Line;

	while (getline(InputFile, Line))
		m_Input.push_back(Line);

	return true;
}

void Lexer::PreProcessing()
{
	RemoveComments();
}

void Lexer::RemoveComments()
{
	vector<string> ProcessedInput;

	for (string Line : m_Input)
	{
		string ProcessedLine;

		for (char Character : Line)
		{
			if (Character == '$')
				break;

			ProcessedLine.push_back(Character);
		}

		ProcessedInput.push_back(ProcessedLine);
	}

	m_Input = ProcessedInput;
}

bool Lexer::GenerateTokens()
{
	for (string Line : m_Input) 
	{
		vector<string> Tokens = Helper::String::TokenizeEx(Line, DEFAULT_DELIMITERS + TOKEN_DELIMITERS);

		for (unsigned int Index = 0; Index < Tokens.size(); Index++) 
		{
			if (Tokens[Index] == "" || Tokens[Index] == " " || Tokens[Index] == "\t" || Tokens[Index] == "\v" || Tokens[Index] == "\n" || Tokens[Index] == "\r" || Tokens[Index] == "\f") 
			{
				Tokens.erase(Tokens.begin() + Index);
				Index--;
			}
		}

		for (string Value : Tokens) 
		{
			Token GeneratedToken(Value);

			string Type;

			if (Value == "=")
				Type = "operator=";
			else if (Value == "&")
				Type = "operator&";
			else if (Value == "^")
				Type = "operator^";
			else if (Value == "!")
				Type = "operator!";
			else if (Value == "(")
				Type = "par-left";
			else if (Value == ")")
				Type = "par-right";
			else if (Value == "[")
				Type = "bra-left";
			else if (Value == "]")
				Type = "bra-right";
			else if (Value == "{")
				Type = "cbr-left";
			else if (Value == "}")
				Type = "cbr-right";
			else if (Value == ";")
				Type = "semicolon";
			else
				Type = "identifier";

			GeneratedToken.SetType(Type);
			m_Tokens.push_back(GeneratedToken);
		}
	}

	if (m_Tokens.size())
		return true;

	return false;
}

void Lexer::GenerateFile(string Name)
{
	m_OutputFile = ofstream(Name);

	for (Token GeneratedToken : m_Tokens)
		m_OutputFile << GeneratedToken << endl;

	m_OutputFile.close();
}


