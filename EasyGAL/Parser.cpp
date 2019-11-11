#include "Parser.h"

Parser g_Parser;

Parser::Parser()
{
}

Parser::~Parser()
{
}

bool Parser::Parse(string Path)
{
	if (LoadFile(Path) == false)
		return false;

	PreProcessing();

	return true;
}

bool Parser::LoadFile(string Path)
{
	File = ifstream(Path);

	if (File.good() == false)
	{
		ERROR("%s%s%s", R"(File ")", Path.c_str(), R"(" could not be opened)");
		return false;
	}

	string Buffer;

	while (getline(File, Buffer))
		Contents.push_back(Buffer);

	if (Contents.size() == 0)
	{
		ERROR("%s%s%s", R"(")", Path.c_str(), R"(" was empty)");
		return false;
	}

	return true;
}

void Parser::DumpContents()
{
	for (int i = 0; i < Contents.size(); i++) 
		printf("%s%i%s%s%s", "L", i + 1, ": ", Contents[i].c_str(), "\n");
}

void Parser::PreProcessing()
{
	RemoveComments();

	// Continue here
}

void Parser::ParseSymbols()
{

}

void Parser::RemoveSpaces()
{
	vector<string> Processed;

	for (string Line : Contents) 
	{
		string ProcessedLine;

		for (char Character : Line)
			if (Character != ' ')
				ProcessedLine.push_back(Character);

		if (ProcessedLine.size())
			Processed.push_back(ProcessedLine);
	}

	Contents = Processed;
}

void Parser::RemoveComments()
{
	vector<string> Processed;

	for (string Line : Contents)
	{
		string ProcessedLine;

		for (char Character : Line) 
		{
			if (Character == '$')
				break;
			else if (Character != ' ')
				ProcessedLine.push_back(Character);
		}

		if (ProcessedLine.size())
			Processed.push_back(ProcessedLine);
	}

	Contents = Processed;
}
