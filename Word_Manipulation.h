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

class ColumnDictionary
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
	ColumnDictionary()
	{
		this->defaultIntegerValue = 0;
		this->defaultFloatValue = 0;
		this->defaultTextValue = "";
		this->dimension = 0;
		this->type = DataTypes::INVALID;
		this->name = "";
		this->isValidated = false;
	}
	ColumnDictionary(string name, DataTypes type, int dimension, string defaultValue, bool validated)
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
	ColumnDictionary(const ColumnDictionary& columnArray)
	{
		this->isValidated = columnArray.isValidated;
		this->defaultIntegerValue = columnArray.defaultIntegerValue;
		this->defaultFloatValue = columnArray.defaultFloatValue;
		this->defaultTextValue = columnArray.defaultTextValue;
		this->dimension = columnArray.dimension;
		this->type = columnArray.type;
		this->name = columnArray.name;
	}
	void operator=(const ColumnDictionary& columnArray)
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

class WordManipulation
{
public:
	ColumnDictionary* customColumnArrays; // (column_1,integer,20,0),(column_2,text,40,'')

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

	void separateParantheses(string line)
	{
		int curColumn = 0;
		int noColumns = getNoColumns(line);
		int i = 0, m = 0;
		/*if (customColumnArrays != nullptr)
			delete[] customColumnArrays;*/
		while (i < line.length())
		{
			if (line[i] != ',' && i > 0)
			{
				return;
			}
			else
			{
				if (line[i] == ',') i++;
				if (i != line.length())
				{
					if (line[i] != 32)
					{
						if (line[i] == '(')
						{
							string name;
							DataTypes type;
							string typeString;
							string dimensionString;
							int dimension;

							int noCommas = 0;
							i++;
							int j = i;
							while (line[j] != ')' && j <= line.length())
							{
								if (line[j] == ',')
								{
									if (noCommas == 0)
									{
										name = line.substr(i, j - i);
									}
									else if (noCommas == 1)
									{
										typeString = line.substr(i, j - i);
										type = ReturnType::getColumnDataType(line.substr(i, j - i));
									}
									else if (noCommas == 2)
									{
										dimensionString = line.substr(i, j - i);
										dimension = stoi(line.substr(i, j - i));
									}
									i = j + 1;
									j = i;
									noCommas++;
								}
								else
								{
									j++;
								}

							}
							if (line[j] == ')' && noCommas == 3)
							{
								if (type != DataTypes::INVALID)
								{

									/*customColumnArrays = new CustomColumnArray(name, type, dimension, line.substr(i, j - i), true);
									customColumnArrays++;*/
									cout << "Column: " + name << '\n';
									cout << "Type: " + typeString << '\n';
									cout << "Dimension: " + dimensionString << '\n';
									cout << "Default value: " + line.substr(i, j - i) + '\n';
									cout << '\n';
								}

								else return;
							}
							curColumn++;
							i = j;
						}
					}
					else
					{
						return;
					}
					i++;
				}
			}
		}
		customColumnArrays -= noColumns;
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
};