#pragma once

#include <string>
#include <optional>
#include <unordered_map>

using namespace std;

#define SYMBOL_UNDEFINED "UNDEFINED"

class Symbol
{

public:

	// Static functions that interface with "g_Symbols"

	static optional<Symbol> Get(string Name);
	static bool Exists(string Name);
	static bool Add(Symbol NewSymbol);

public:

	// Member functions

	Symbol();
	~Symbol();

	Symbol(string Name);
	Symbol(string Name, bool Value);
	Symbol(string Name, bool* pValue);

	string GetName();
	bool SetName(string Name);

	bool GetValue();
	void SetValue(bool Value);

	bool* GetValueAdress();
	bool SetParent(bool* pValue);

private:

	string m_SymbolName;
	bool m_Value;
	bool* m_pValue;
};


extern unordered_map<string, Symbol> g_Symbols;
