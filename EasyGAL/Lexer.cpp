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

	GenerateFile(Helper::File::ExtractFileName(Path) + string(".lex"));

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

			TokenType Type;

			if (Value == "=")
				Type = TokenType::OPERATOR_EQUAL;
			else if (Value == "&")
				Type = TokenType::OPERATOR_AND;
			else if (Value == "|")
				Type = TokenType::OPERATOR_OR;
			else if (Value == "^")
				Type = TokenType::OPERATOR_XOR;
			else if (Value == "!")
				Type = TokenType::OPERATOR_NOT;
			else if (Value == "(")
				Type = TokenType::PAREN_LEFT;
			else if (Value == ")")
				Type = TokenType::PAREN_RIGHT;
			else if (Value == "[")
				Type = TokenType::BRACKET_LEFT;
			else if (Value == "]")
				Type = TokenType::BRACKET_RIGHT;
			else if (Value == "{")
				Type = TokenType::CURLY_LEFT;
			else if (Value == "}")
				Type = TokenType::CURLY_RIGHT;
			else if (Value == ";")
				Type = TokenType::SEMICOLON;
			else if (Helper::String::IsNumber(Value))
				Type = TokenType::NUMBER;
			else
				Type = TokenType::IDENTIFIER;

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


