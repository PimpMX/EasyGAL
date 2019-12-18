#pragma once

#include <string>
#include <optional>
#include <unordered_map>

using namespace std;

class Symbol
{

public:

	// Static functions that interface with g_Symbols.

	static optional<Symbol> Get(string Name);
	static bool Exists(string Name);
	static bool Add(Symbol NewSymbol);

public:

	Symbol();
	~Symbol();

	Symbol(string Name);
	Symbol(string Name, bool Value);
	Symbol(string Name, bool* pValue);

	string GetName();
	bool GetValue();
	bool* GetValueAdress();

	bool SetName(string Name);
	void SetValue(bool Value);
	bool SetParent(bool* pValue);

private:

	string m_SymbolName;
	bool m_Value;
	bool* m_pValue;
};

extern unordered_map<string, Symbol> g_Symbols;

const string SYMBOL_UNDEFINED = "UNDEFINED";