#include "Token.h"

Token::Token(string Type, string Value) 
{
	m_KeyValuePair.first = Type;
	m_KeyValuePair.second = Value;
}

Token::~Token()
{
}

string Token::GetType()
{
	return m_KeyValuePair.first;
}

string Token::GetValue()
{
	return m_KeyValuePair.second;
}

bool Token::ValidateType()
{
	return false;
}

bool Token::ValidateValue()
{
	return false;
}

ostream& operator<<(ostream& Out, const Token& OutToken)
{
	Out << OutToken.m_KeyValuePair.first << " : " << OutToken.m_KeyValuePair.second << ";";
	return Out;
}

istream& operator>>(istream& In, Token& InToken)
{
	return In;
}


