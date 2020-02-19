#include "Helper.h"

/*
*		String::Tokenize splits strings into tokens based on specified delimiters.
*/

vector<string> Helper::String::Tokenize(const string& InputString, string Delimiters)
{
	/*
	*	String::Tokenize() only returns one Token in case: 
	*
	*		- String only contains delimiters
	*		- String contains no delimiters
	*		- String is empty
	*/

	if (String::Find(InputString, Delimiters) == -1 || String::FindNot(InputString, Delimiters) == -1)
		return vector<string>{InputString};

	vector<string> Tokens;

	int iBegin = String::FindNot(InputString, Delimiters);

	for (unsigned int i = iBegin; i < InputString.size() + 1; i++) 
	{
		int iEnd = String::Find(InputString, Delimiters, i);

		if (iEnd == -1)
		{
			Tokens.push_back(string(InputString.begin() + iBegin, InputString.end()));
			break;
		}

		Tokens.push_back(string(InputString.begin() + iBegin, InputString.begin() + iEnd));
		iBegin = String::FindNot(InputString, Delimiters, iEnd);

		if (iBegin == -1) 
			break;

		i = iBegin;
	}

	return Tokens;
}

/*
*		String::TokenizeEx splits strings into tokens based on delimiters. This extended version of String::Tokenize 
*		also returns the delimiters which are found in the string as tokens.
*/

vector<string> Helper::String::TokenizeEx(const string& InputString, string Delimiters)
{
	if (String::Find(InputString, Delimiters) == -1 || String::FindNot(InputString, Delimiters) == -1)
		return vector<string>{InputString};

	vector<string> Tokens;

	int iBegin = 0;

	for (unsigned int i = iBegin; i < InputString.size() + 1; i++)
	{
		int iEnd = String::Find(InputString, Delimiters, i);

		if (iEnd == -1)
		{
			Tokens.push_back(string(InputString.begin() + iBegin, InputString.end()));
			break;
		}

		Tokens.push_back(string(InputString.begin() + iBegin, InputString.begin() + iEnd));
		iBegin = String::FindNot(InputString, Delimiters, iEnd);

		if (iBegin == -1)
		{
			// If no new non delimiter characters are found, the remaining characters are added as tokens.

			for (unsigned int j = i + 1; j < InputString.size(); j++) 
				Tokens.push_back(string(1, InputString[j]));
			break;
		}

		for (int i = 0; i < iBegin - iEnd; i++)
			Tokens.push_back(string(1, InputString[iEnd + i]));

		i = iBegin;
	}

	return Tokens;
}

//		String::Find() returns the index of the first occurence of an character in a specified string. 

int Helper::String::Find(const string& String, char Character, unsigned int StartIndex)
{
	for (unsigned int Index = StartIndex; Index < String.size(); Index++) 
		if (String[Index] == Character)
			return Index;

	return -1;
}

/*
*		This overload of String::Find returns the index of the first occurence of specified characters in specified string.
*		Which character was found in string is not returned.
*/

int Helper::String::Find(const string& String, const string& Characters, unsigned int StartIndex)
{
	for (unsigned int Index = StartIndex; Index < String.size(); Index++)
		for (char Character : Characters)
			if (String[Index] == Character)
				return Index;

	return -1;
}

//		String::FindNot returns the index of the first character that is not any of the specified characters.

int Helper::String::FindNot(const string& String, const string& Characters, unsigned int StartIndex)
{
	for (unsigned int Index = StartIndex; Index < String.size(); Index++) 
	{
		bool Valid = true;

		for (char Character : Characters)
			if (String[Index] == Character)
				Valid = false;

		if (Valid) 
			return Index;
	}

	// Returns -1 if every character is a non allowed character

	return -1;
}

//		Helper::String::IsNumber checks if a string is a number

bool Helper::String::IsNumber(const string& String)
{
	if (String.empty())
		return false;

	for (char Character : String) 
		if (Character < '0' || Character > '9')
			return false;
	
	return true;
}

/*
*		Helper::File::ExtractFileName extracts the name of a file from the filepath.
*		It also leaves out the file extension if it has one.
*/

string Helper::File::ExtractFileName(string Path)
{
	int iBegin = 0, iEnd = Path.size() - 1;

	for (int Index = Path.size() - 1; Index > 0; Index--) 
	{
		if (Path.at(Index) == '.')
		{
			iEnd = Index;
		}
		else if (Path.at(Index) == '\\') 
		{
			iBegin = Index;
			break;
		}
	}

	return string(Path.begin() + iBegin, Path.begin() + iEnd);
}

/*
*		Helper::Algorithms::ShuntingYard transforms a given expression from infix notation
*		to postfix notation. The function only transforms the expression and doesn't evaluate it.
*/

vector<Token> Helper::Algorithms::ShuntingYard(vector<Token> Expression)
{
	deque<Token> Right, Left, Bottom;

	//	Filter out unwanted tokens.

	for (int Index = 0; Index < Expression.size(); Index++) 
	{
		TokenType Type = Expression[Index].GetType();

		if (Type == TokenType::NUMBER) 
		{
			ERROR("%s", "Binary expression error: integers are not allowed!");
			return vector<Token>{};
		}

		switch (Type) 
		{
		case TokenType::OPERATOR_EQUAL:
		case TokenType::BRACKET_LEFT:
		case TokenType::BRACKET_RIGHT:
		case TokenType::CURLY_LEFT:
		case TokenType::CURLY_RIGHT:
		case TokenType::SEMICOLON:
			Expression.erase(Expression.begin() + Index);
		}
	}

	//	Copy filtered vector into our stack.

	Right = deque<Token>(Expression.begin(), Expression.end());		

	//	Split up operators and identifiers.

	while (Right.size()) 
	{
		if (Right.back().GetType() == TokenType::IDENTIFIER)
		{
			Left.push_back(Right.back());
			Right.pop_back();
		}
		else
		{
			Bottom.push_back(Right.back());
			Right.pop_back();
		}
	}

	//	Remove parentheses and move operators to left stack.

	while (Bottom.size()) 
	{
		if (Bottom.back().GetType() == TokenType::PAREN_LEFT || Bottom.back().GetType() == TokenType::PAREN_RIGHT) 
		{
			Right.push_back(Bottom.back());
			Bottom.pop_back();
		}
		else 
		{
			Left.push_back(Bottom.back());
			Bottom.pop_back();
		}

		int Size = Right.size() - 1;

		for (int Index = 0; Index < Size; Index++) 
		{
			if (Right[Index].GetType() == TokenType::PAREN_LEFT && Right[Index + 1].GetType() == TokenType::PAREN_RIGHT) 
			{
				Right.erase(Right.begin() + Index);
				Right.erase(Right.begin() + Index);
			}
		}
	}

	//	If the expression has unclosed parentheses, we will notice it here.

	if (Right.size())
	{
		ERROR("%s", "Binary expression error: parentheses couldn't be resolved");
		return vector<Token>{};
	}

	return vector<Token>{Left.begin(), Left.end()};
}
