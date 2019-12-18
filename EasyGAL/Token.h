#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

#include "Debug.h"
#include "Helper.h"

using namespace std;

class Token
{

public:

	Token(string Type, string Value);
	Token(string Value);

	Token();
	~Token();

	string GetType();
	string GetValue();
	
	void SetType(string Type);
	void SetValue(string Value);

	friend ostream& operator<<(ostream& Out, const Token& OutToken);
	friend istream& operator>>(istream& In, Token& InToken);

private:

	pair<string, string> m_KeyValuePair;
};