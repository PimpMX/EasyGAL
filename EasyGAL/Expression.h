#pragma once

#include "Symbol.h"
#include "Token.h"
#include "Node.h"
#include "Lexer.h"

class Expression 
{

public:

	Expression(string Expression);
	Expression(vector<Token> Expression);
	~Expression();

	bool Evaluate();

private:


private:

	Node m_Root;
	vector<Token> m_Expression;
};

