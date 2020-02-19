#pragma once

#include <string>
#include <fstream>
#include "Debug.h"

using namespace std;

enum class TokenType
{
	NONE,
	NUMBER,
	IDENTIFIER,
	OPERATOR_EQUAL,
	OPERATOR_AND,
	OPERATOR_OR,
	OPERATOR_XOR,
	OPERATOR_NOT,
	PAREN_LEFT,
	PAREN_RIGHT,
	BRACKET_LEFT,
	BRACKET_RIGHT,
	CURLY_LEFT,
	CURLY_RIGHT,
	SEMICOLON
};

class Token
{

public:

	Token();
	~Token();
	
	Token(TokenType Type, string Value);
	Token(string Value);

	TokenType GetType();
	string GetValue();
	
	void SetType(TokenType Type);
	void SetValue(string Value);

	friend ostream& operator<<(ostream& Out, const Token& OutToken);
	friend istream& operator>>(istream& In, Token& InToken);

private:

	pair<TokenType, string> m_KeyValuePair;
};