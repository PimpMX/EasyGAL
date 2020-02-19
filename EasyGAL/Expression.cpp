#include "Expression.h"

Expression::Expression(string Expression)
{
	if (g_Lexer.AnalyzeLine(Expression, &m_Expression) == false)
	{
		ERROR("%s", "Lexical analysis for expression failed");
	}
}

Expression::Expression(vector<Token> Expression)
{
}

Expression::~Expression()
{
}

bool Expression::Evaluate()
{
	return false;
}

bool Expression::BuildTree()
{
	return false;
}
