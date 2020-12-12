#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Classes.h"

using namespace std;

enum class CommandTypes {
	CREATE,
	DROP,
	DISPLAY,
	INVALID
};

enum class CommandIdentifiers {
	TABLE,
	INDEX,
	INVALID
};

class CustomStringArray
{
public:
	bool isValidated = false;
	char* firstWord;
	char* restOfTheLine;
public:
	CustomStringArray()
	{
		firstWord = nullptr;
		restOfTheLine = nullptr;
	}
	CustomStringArray(const CustomStringArray& customStringArray)
	{
		this->isValidated = customStringArray.isValidated;
		if (this->firstWord != nullptr)
			delete[] this->firstWord;
		this->firstWord = new char[strlen(customStringArray.firstWord)];
		strcpy(this->firstWord, customStringArray.firstWord);

		if (this->restOfTheLine != nullptr)
			delete[] this->restOfTheLine;
		this->firstWord = new char[strlen(customStringArray.restOfTheLine)];
		strcpy(this->restOfTheLine, customStringArray.restOfTheLine);
	}
};

CustomStringArray separateFirstWord(const char* line)
{
	CustomStringArray customStringArray;
	int i = 0;
	while (i < strlen(line) && isalpha(line[i]))
	{
		i++;
	}
	if (line[i] == ' ')
	{
		customStringArray.isValidated = true;

		char* Word = new char[i]; // Word = first word
		strncpy(Word, line, i);
		strncpy(customStringArray.firstWord, line, i);
		strncpy(customStringArray.restOfTheLine, line + i + 1, strlen(line));
	}
	return customStringArray;
}

CommandTypes getCommandType(const char* command)
{
	if (command == "CREATE")
	{
		return CommandTypes::CREATE;
	}
	else if (command == "DROP")
	{
		return CommandTypes::DROP;
	}
	else if (command == "DISPLAY")
	{
		return CommandTypes::DISPLAY;
	}
	return CommandTypes::INVALID;
}

CommandIdentifiers getCommandIdentifier(string identifier)
{
	if (identifier == "TABLE")
	{
		return CommandIdentifiers::TABLE;
	}
	else if (identifier == "INDEX")
	{
		return CommandIdentifiers::INDEX;
	}
	return CommandIdentifiers::INVALID;
}

string toSQLCommand(const char* line)
{
	CustomStringArray customStringArray = separateFirstWord(line);

	if (customStringArray.isValidated == true)
	{
		CommandTypes CommandType = getCommandType(customStringArray.firstWord);

		if (CommandType != CommandTypes::INVALID) // Verificam daca CommandType este un tip de comanda corect (Create/Drop/Display)
		{
			if (CommandType == CommandTypes::CREATE) cout << "The command type is: CREATE" + '\n';
			customStringArray = separateFirstWord(customStringArray.restOfTheLine);
			CommandIdentifiers CommandIdentifier = getCommandIdentifier(customStringArray.firstWord);
			if (CommandIdentifier != CommandIdentifiers::INVALID)
			{
				if (CommandIdentifier == CommandIdentifiers::TABLE) cout << "The command identifier is: TABLE" + '\n';
				customStringArray = separateFirstWord(customStringArray.restOfTheLine);
			}
		}

		//return "The command type is " + customStringArray.firstWord + '\n';
	}
	else if (customStringArray.isValidated == false)
		return "Command is incorrectly formatted!";

}



void CreateTable(string tableName)
{

}

void CreateIndex(string tableName)
{

}

void DropTable(string tableName)
{

}

void DropIndex(string tableName)
{

}

void DisplayTable(string tableName)
{

}

int main()
{
	cout << "Please input the full SQL command..." << '\n';

	string line;
	getline(cin, line);

	toSQLCommand(line);
}