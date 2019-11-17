#include "Symbol.h"
#include "Parser.h"
#include "Token.h"
#include "Lexer.h"

#include <fstream>
#include <iostream>
#include <string>


int main()
{
	g_Lexer.Analyze("Coder.txt");
}
