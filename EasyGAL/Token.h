#pragma once

#include <string>
#include <fstream>

using namespace std;

class Token
{

public:

	Token(string Type, string Value);
	~Token();

	string GetType();
	string GetValue();

	bool ValidateType();
	bool ValidateValue();

	friend ostream& operator<<(ostream& Out, const Token& OutToken);
	friend istream& operator>>(istream& In, Token& InToken);

private:

	pair<string, string> m_KeyValuePair;
};
