#pragma once

#include <string>
#include <fstream>

using namespace std;

class Token
{

public:

	Token(string Type, string Value);
	Token(string Value);

	Token();
	~Token();

	string GetType();
	void SetType(string Type);

	string GetValue();
	void SetValue(string Value);

	friend ostream& operator<<(ostream& Out, const Token& OutToken);
	friend istream& operator>>(istream& In, Token& InToken);

private:

	pair<string, string> m_KeyValuePair;
};
