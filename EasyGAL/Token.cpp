#include "Token.h"

Token::Token(string Type, string Value) 
{
	m_KeyValuePair.first = Type;
	m_KeyValuePair.second = Value;
}

Token::Token(string Value)
{
	// Type is set to Value of Token, temporarily.

	m_KeyValuePair.first = Value;
	m_KeyValuePair.second = Value;
}

Token::Token()
{
}

Token::~Token()
{
}

string Token::GetType()
{
	return m_KeyValuePair.first;
}

void Token::SetType(string Type)
{
	m_KeyValuePair.first = Type;
}

string Token::GetValue()
{
	return m_KeyValuePair.second;
}

void Token::SetValue(string Value)
{
	m_KeyValuePair.second = Value;
}

ostream& operator<<(ostream& Out, const Token& OutToken)
{
	Out << "[" << OutToken.m_KeyValuePair.first << R"(: ")" << OutToken.m_KeyValuePair.second << R"("])";
	return Out;
}

istream& operator>>(istream& In, Token& InToken)
{
	return In;
}


