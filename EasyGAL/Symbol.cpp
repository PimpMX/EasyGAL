#include "Symbol.h"

unordered_map<string, Symbol> g_Symbols;

optional<Symbol> Symbol::Get(string Name) 
{
	for (auto Pair : g_Symbols)
		if (Pair.first == Name)
			return Pair.second;

	return {};
}

bool Symbol::Exists(string Name) 
{
	for (auto Pair : g_Symbols)
		if (Pair.first == Name)
			return true;
	
	return false;
}

bool Symbol::Add(Symbol NewSymbol) 
{
	if (Symbol::Exists(NewSymbol.GetName()))
		return false;

	g_Symbols[NewSymbol.GetName()] = NewSymbol;
	return true;
}

Symbol::Symbol()
{
	m_SymbolName = SYMBOL_UNDEFINED;
	m_Value = false;
	m_pValue = nullptr;
}

Symbol::~Symbol() 
{
}

Symbol::Symbol(std::string Name)
{
	m_SymbolName = Name;
	m_Value = false;
	m_pValue = nullptr;
}

Symbol::Symbol(string Name, bool Value)
{
	m_SymbolName = Name;
	m_Value = Value;
	m_pValue = nullptr;
}

Symbol::Symbol(string Name, bool* pValue)
{
	m_SymbolName = Name;
	m_Value = false;
	m_pValue = pValue;
}

std::string Symbol::GetName()
{
	return m_SymbolName;
}

/*
*	Depending on if the symbol has a parent this function will either return
*	the value of the symbol or the value of its parent.
*/

bool Symbol::GetValue()
{
	if(!m_pValue)
		return m_Value;
	return *m_pValue;
}

/*
*	Returns adress of own value.
*	Can be used to set other symbols parents.
*/

bool* Symbol::GetValueAdress()
{
	return &m_Value;
}

bool Symbol::SetName(std::string Name)
{
	if (Name != SYMBOL_UNDEFINED)
	{
		m_SymbolName = Name;
		return true;
	}

	return false;
}

/*
*	If the symbol has a parent it doesn't have its own value.
*	This means it's value can't be set.
*/

void Symbol::SetValue(bool Value)
{
	if(!m_pValue) 
		m_Value = Value;
}

bool Symbol::SetParent(bool* pValue)
{
	if (pValue) 
	{
		m_pValue = pValue;
		return true;
	}

	return false;
}