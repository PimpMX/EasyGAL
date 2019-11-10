#include "Symbol.h"

unordered_map<string, Symbol> g_Symbols;

optional<Symbol> Symbol::Get(string Name) 
{

}

bool Symbol::Exists(string Name) 
{

}

void Symbol::Add(Symbol& NewSymbol) 
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

bool Symbol::SetParent(bool* pValue)
{
	if (pValue) 
	{
		m_pValue = pValue;
		return true;
	}

	return false;
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

std::string Symbol::GetName()
{
	return m_SymbolName;
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

/*
*	If the symbol has a parent it doesn't have its own value.
*	This means it's value can't be set.
*/

void Symbol::SetValue(bool Value)
{
	if(!m_pValue) 
		m_Value = Value;
}
