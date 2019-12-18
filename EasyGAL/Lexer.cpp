#include "Lexer.h"

Lexer g_Lexer;

bool Lexer::Analyze(vector<string> Input, vector<Token>* pTokensOut)
{
	/* Clear buffers from last analysis for new analysis */

	m_Input.clear();
	m_Tokens.clear();

	if (!pTokensOut) 
	{
		ERROR("%s", "pTokensOut was nullptr");
		return false;
	}

	m_Input = Input;

	PreProcessing();

	if (GenerateTokens() == false) 
	{
		ERROR("%s", "Lexical analysis failed is input empty?");
		return false;
	}

	*pTokensOut = m_Tokens;
	return true;
}

bool Lexer::AnalyzeLine(string Input, vector<Token>* pTokensOut)
{
	/* Clear buffers from last analysis for new analysis */

	m_Input.clear();
	m_Tokens.clear();

	if (!pTokensOut)
	{
		ERROR("%s", "pTokensOut was nullptr");
		return false;
	}

	m_Input.push_back(Input);
	
	PreProcessing();

	if (GenerateTokens() == false) 
	{
		ERROR("%s", "Lexical analysis failed is line empty?");
		return false;
	}

	*pTokensOut = m_Tokens;
	return true;
}

bool Lexer::AnalyzeFile(string Path, vector<Token>* pTokensOut)
{
	/* Clear buffers from last analysis for new analysis */

	m_Input.clear();
	m_Tokens.clear();

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

	GenerateFile("ANALYSIS.lex");

	if (pTokensOut) 
		*pTokensOut = m_Tokens;

	return true;
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

		/* Filters out unwanted tokens */

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
				Type = "OPERATOR=";
			else if (Value == "&")
				Type = "OPERATOR&";
			else if (Value == "^")
				Type = "OPERATOR^";
			else if (Value == "!")
				Type = "OPERATOR!";
			else if (Value == "(")
				Type = "LPAREN";
			else if (Value == ")")
				Type = "RPAREN";
			else if (Value == "[")
				Type = "LBRACKET";
			else if (Value == "]")
				Type = "RBRACKET";
			else if (Value == "{")
				Type = "LCURLY";
			else if (Value == "}")
				Type = "RCURLY";
			else if (Value == ";")
				Type = "COLON";
			else if (Helper::String::IsNumber(Value))
				Type = "NUMBER";
			else
				Type = "IDENTIFIER";
			
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


