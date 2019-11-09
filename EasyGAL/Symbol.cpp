#include "Symbol.h"

unordered_map<string, Symbol> g_Symbols;

Symbol::Symbol(std::string Name)
{
	m_SymbolName = Name;
	m_Value = false;
}

Symbol::Symbol(string Name, bool Value)
{
	m_SymbolName = Name;
	m_Value = Value;
}

Symbol::Symbol()
{
	m_SymbolName = SYMBOL_UNDEFINED;
	m_Value = false;
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

bool Symbol::GetValue()
{
	return m_Value;
}

void Symbol::SetValue(bool Value)
{
	m_Value = Value;
}
