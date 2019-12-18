#include "Expression.h"

Expression::Expression(string Expression)
{
	if (g_Lexer.AnalyzeLine(Expression, &m_Expression) == false)
	{
		ERROR("%s", "Lexical analysis for expression failed");
	}

	for (Token T : m_Expression) 
	{
		if (T.GetType() == "IDENTIFIER") 
		{
			if (Symbol::Get(T.GetValue())) 
			{
				printf("%i", Symbol::Get(T.GetValue()).value().GetValue());
			}
		}
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
