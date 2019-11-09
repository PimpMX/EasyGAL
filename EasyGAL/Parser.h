#pragma once

#include <fstream>

#include "Debug.h"
#include "Symbol.h"

class Parser 
{
	
public:

	Parser();
	~Parser();

	bool Parse(string Path);

private:

	bool LoadFile(string Path);
	void DumpContents();

	void PreProcessing();
	void ParseSymbols();

private:

	ifstream File; 
	vector<string> Contents;
};

extern Parser g_Parser;