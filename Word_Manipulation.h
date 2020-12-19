#pragma once
#include <string>
#include "Enums.h"
#include <iostream>

using namespace std;

class StringDictionary
{
public:
	bool isValidated;
	string firstWord;
	string restOfTheLine;
public:
	StringDictionary()
	{
		this->firstWord = "";
		this->restOfTheLine = "";
		this->isValidated = false;
	}
	StringDictionary(const StringDictionary& stringArray)
	{
		this->isValidated = stringArray.isValidated;
		this->firstWord = stringArray.firstWord;
		this->restOfTheLine = stringArray.restOfTheLine;
	}
};

class ColumnArray
{
public:
	bool isValidated;
	string name = "";
	DataTypes type = DataTypes::INVALID;
	int dimension = 0;
	int defaultIntegerValue = 0;
	float defaultFloatValue = 0;
	string defaultTextValue = "";

public:
	ColumnArray()
	{
		this->defaultIntegerValue = 0;
		this->defaultFloatValue = 0;
		this->defaultTextValue = "";
		this->dimension = 0;
		this->type = DataTypes::INVALID;
		this->name = "";
		this->isValidated = false;
	}
	ColumnArray(string name, DataTypes type, int dimension, string defaultValue, bool validated)
	{
		this->name = name;
		this->type = type;
		this->dimension = dimension;
		this->isValidated = validated;

		if (this->type == DataTypes::TEXT)
			this->defaultTextValue = defaultValue;
		else if (type == DataTypes::INTEGER)
			this->defaultIntegerValue = stoi(defaultValue);
		else if (type == DataTypes::FLOAT)
			this->defaultFloatValue = stof(defaultValue);
	}
	ColumnArray(const ColumnArray& columnArray)
	{
		this->isValidated = columnArray.isValidated;
		this->defaultIntegerValue = columnArray.defaultIntegerValue;
		this->defaultFloatValue = columnArray.defaultFloatValue;
		this->defaultTextValue = columnArray.defaultTextValue;
		this->dimension = columnArray.dimension;
		this->type = columnArray.type;
		this->name = columnArray.name;
	}
	void operator=(const ColumnArray& columnArray)
	{
		if (this == &columnArray) {
			return;
		}
		this->defaultFloatValue = columnArray.defaultFloatValue;
		this->defaultIntegerValue = columnArray.defaultIntegerValue;
		this->defaultTextValue = columnArray.defaultTextValue;
		this->dimension = columnArray.dimension;
		this->isValidated = columnArray.isValidated;
		this->name = columnArray.name;
		this->type = columnArray.type;
	}
	friend class WordManipulation;
};

class ColumnArrayAndStringDictionary
{
public:
	ColumnArray columnArray;
	string RofL;

// Constructors
public:
	ColumnArrayAndStringDictionary(ColumnArray colArray, string text)
	{
		this->columnArray = colArray;
		this->RofL = text;
	}
};

class WordManipulation
{
public:
	bool isNumber(char c)
	{
		if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
			return true;
		return false;
	}

	int seekForSpaces(string line)
	{
		int i = 0;
		while (line[i] == 32 && i < line.length())
		{
			i++;
		}
		if (i == line.length())
			return -1;
		return i;
	}

	int getNoColumns(string line)
	{
		int leftParantheses = 0;
		int rightParantheses = 0;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '(')
				leftParantheses++;
			if (line[i] == ')')
				rightParantheses++;
		}

		if (leftParantheses != rightParantheses)
			return 0;
		return leftParantheses;
	}

	ColumnArrayAndStringDictionary separateParantheses(string line)
	{
		ColumnArray column = ColumnArray();
		int lastCommaPosition = 0;
		int noCommas = 0, i = 1;

		// Verify that the first character is a '('

		// Stop at ')' and check if next character is a comma

		// Return the

		while (noCommas < 3 && i < line.length() && line[i] != ')')
		{
			if (line[i] != ',')
			{
				i++;
			}
			else
			{
				switch (noCommas)
				{
				case 0:
				{
					// Set the column name
					column.name = line.substr(1, i-1);
					break;
				}
				case 1:
				{
					// Set the column type
					column.type = ReturnType::getColumnDataType(line.substr(lastCommaPosition + 1, i - lastCommaPosition - 1));
					break;
				}
				case 2:
				{
					// Set the column dimension
					column.dimension = stoi(line.substr(lastCommaPosition + 1, i - lastCommaPosition - 1));
					break;
				}
				}
				noCommas++;
				lastCommaPosition = i;
				i++;
			}
		}
		if (noCommas == 3 && i < line.length())
		{
			while (line[i] != ')' && i < line.length())
			{
				i++;
			}
			switch (column.type)
			{
			case DataTypes::FLOAT:
			{
				column.defaultFloatValue = stof(line.substr(lastCommaPosition + 1, i - lastCommaPosition - 1));
				column.isValidated = true;
				break;
			}
			case DataTypes::INTEGER:
			{
				column.defaultIntegerValue = stoi(line.substr(lastCommaPosition + 1, i - lastCommaPosition - 1));
				column.isValidated = true;
				break;
			}
			case DataTypes::TEXT:
				column.defaultTextValue = line.substr(lastCommaPosition + 1, i - lastCommaPosition - 1);
				if (column.defaultTextValue[0] == 39 && column.defaultTextValue[column.defaultTextValue.length() - 1] == 39)
					column.isValidated = true;
				break;
			}
		}
		if (getNoColumns(line) == 1)
			return ColumnArrayAndStringDictionary(column, "");
		return ColumnArrayAndStringDictionary(column,line.substr(i + 2, line.length() - i + lastCommaPosition));
	}

	StringDictionary separateFirstWord(string line)
	{
		StringDictionary customStringArray = StringDictionary();
		int noSpaces = seekForSpaces(line);
		if (noSpaces == -1)
		{
			customStringArray.isValidated = false;
			return customStringArray;
		}

		int i = noSpaces;
		while (i < line.length() && (isalpha(line[i]) || line[i] == '(' || line[i] == ')' || isNumber(line[i])))
		{
			i++;
		}
		if (line[i] == 32)
		{
			customStringArray.isValidated = true;
			customStringArray.firstWord = line.substr(noSpaces, i - noSpaces);
			customStringArray.restOfTheLine = line.substr(i + 1, line.length() - i);
		}
		return customStringArray;
	}

	StringDictionary separateCondition(string line)
	{
		StringDictionary customStringArray = StringDictionary();
		int i = 0, spaces = 0;

		while (i < line.length() && spaces != 3)
		{
			if (line[i] == 32) spaces++;
			i++;
		}

		if (isalpha(line[i]) || line[i] == '(' || line[i] == ')')
		{
			customStringArray.isValidated = true;
			customStringArray.firstWord = line.substr(0, i - 1);
			customStringArray.restOfTheLine = line.substr(i, line.length());
		}

		return customStringArray;
	}

	StringDictionary separateLastWord(string line)
	{
		StringDictionary customStringArray = StringDictionary();
		int noSpaces = seekForSpaces(line);
		if (noSpaces == -1)
		{
			customStringArray.isValidated = false;
			return customStringArray;
		}

		int i = noSpaces;
		while (i < line.length() && (isalpha(line[i]) || line[i] == '(' || line[i] == ')' || isNumber(line[i])))
		{
			i++;
		}
		if (i == line.length())
		{
			customStringArray.isValidated = true;
			customStringArray.firstWord = line.substr(noSpaces, i - noSpaces);
			customStringArray.restOfTheLine = "";
		}
		else
		{
			cout << "Characters found after the last word";
		}
		return customStringArray;
	}

	bool isList(string line)
	{
		for (int i = 0; i <= line.length(); i++)
			if (line[i] == ',')
				return true;
		return false;
	}
};