#pragma once

#include <string>
#include <unordered_map>

#define SYMBOL_UNDEFINED "UNDEFINED"

using namespace std;

class Symbol
{

public:

	Symbol();
	~Symbol();

	Symbol(string Name);
	Symbol(string Name, bool Value);

	string GetName();
	bool SetName(string Name);

	bool GetValue();
	void SetValue(bool Value);

private:

	bool m_Value;
	string m_SymbolName;
};


extern unordered_map<string, Symbol> g_Symbols;
