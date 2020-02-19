#include "Token.h"

Token::Token()
{
	m_KeyValuePair.first = TokenType::NONE;
	m_KeyValuePair.second = "";
}

Token::~Token()
{

}

Token::Token(TokenType Type, string Value)
{
	m_KeyValuePair.first = Type;
	m_KeyValuePair.second = Value;
}

Token::Token(string Value)
{
	m_KeyValuePair.first = TokenType::NONE;
	m_KeyValuePair.second = Value;
}

TokenType Token::GetType()
{
	return m_KeyValuePair.first;
}

string Token::GetValue()
{
	return m_KeyValuePair.second;
}

void Token::SetType(TokenType Type)
{
	m_KeyValuePair.first = Type;
}

void Token::SetValue(string Value)
{
	m_KeyValuePair.second = Value;
}

ostream& operator<<(ostream& Out, const Token& OutToken)
{
	Out << "[" << (int)(OutToken.m_KeyValuePair.first) << R"(: ")" << OutToken.m_KeyValuePair.second << R"("])";
	return Out;
}

istream& operator>>(istream& In, Token& InToken)
{
	return In;
}


