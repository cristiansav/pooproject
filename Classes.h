#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class Commands
{
	CREATE,
	DROP,
	DISPLAY,
	INVALID
};

enum class Identifiers
{
	TABLE,
	INDEX,
	INVALID
};

enum class DataTypes
{
	TEXT,
	INTEGER,
	FLOAT,
	INVALID
};

enum class Conditions
{
	IFNOTEXISTS,
	WHERE,
	INVALID
};

class Row
{
public:
	int Id;
	string Name;
private:
	int NoColumns = 0;

public:


	// Methods
public:
	void setNoColumns(int noColumns)
	{
		this->NoColumns = noColumns;
	}
};

class Column
{
public:
	int Id;
	string Name;
	string DefaultValue;
	DataTypes Type;
public:
	void setDataType(DataTypes dataType)
	{
		this->Type = dataType;
	}
};

class Table
{
public:
	static int noTables;
public:
	int Id;
	string Name;
	int noColumns = 0;
	int noRows = 0;
	Column* Columns;
	Row* Rows;

public:
	Table()
		: Id(Table::noTables)
	{
		Columns = new Column();
		Rows = new Row();
	}
};

class Index
{
public:
	static int noIndexes;
public:
	int Id;
	string Name;
	/*int noColumns = 0;
	int noRows = 0;
	Column* Columns;
	Row* Rows;*/

public:
	Index()
		: Id(Index::noIndexes)
	{
		/*Columns = new Column();
		Rows = new Row();*/
	}
};

class CustomStringArray
{
public:
	bool isValidated;
	string firstWord;
	string restOfTheLine;
public:
	CustomStringArray()
	{
		this->firstWord = "";
		this->restOfTheLine = "";
		this->isValidated = false;
	}
	CustomStringArray(const CustomStringArray& customStringArray)
	{
		this->isValidated = customStringArray.isValidated;
		this->firstWord = customStringArray.firstWord;
		this->restOfTheLine = customStringArray.restOfTheLine;
	}
};

class CustomColumnArray
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
	CustomColumnArray()
	{
		this->defaultIntegerValue = 0;
		this->defaultFloatValue = 0;
		this->defaultTextValue = "";
		this->dimension = 0;
		this->type = DataTypes::INVALID;
		this->name = "";
		this->isValidated = false;
	}
	CustomColumnArray(string name, DataTypes type, int dimension, string defaultValue, bool validated)
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
	CustomColumnArray(const CustomColumnArray& customColumnArray)
	{
		this->isValidated = customColumnArray.isValidated;
		this->defaultIntegerValue = customColumnArray.defaultIntegerValue;
		this->defaultFloatValue = customColumnArray.defaultFloatValue;
		this->defaultTextValue = customColumnArray.defaultTextValue;
		this->dimension = customColumnArray.dimension;
		this->type = customColumnArray.type;
		this->name = customColumnArray.name;
	}
	void operator=(const CustomColumnArray& customColumnArray)
	{
		if (this == &customColumnArray) {
			return;
		}
		this->defaultFloatValue = customColumnArray.defaultFloatValue;
		this->defaultIntegerValue = customColumnArray.defaultIntegerValue;
		this->defaultTextValue = customColumnArray.defaultTextValue;
		this->dimension = customColumnArray.dimension;
		this->isValidated = customColumnArray.isValidated;
		this->name = customColumnArray.name;
		this->type = customColumnArray.type;
	}
	friend class WordManipulation;
};

class ReturnType
{
public:
	static Conditions getConditionType(string condition)
	{
		if (condition == "IF NOT EXISTS")
		{
			return Conditions::IFNOTEXISTS;
		}
		else if (condition == "WHERE")
		{
			return Conditions::WHERE;
		}
		return Conditions::INVALID;
	}

	static DataTypes getColumnDataType(string type)
	{
		if (type == "float")
		{
			return DataTypes::FLOAT;
		}
		else if (type == "integer")
		{
			return DataTypes::INTEGER;
		}
		else if (type == "text")
		{
			return DataTypes::TEXT;
		}
		return DataTypes::INVALID;
	}

	static Commands getCommandType(string command)
	{
		if (command == "CREATE")
		{
			return Commands::CREATE;
		}
		else if (command == "DROP")
		{
			return Commands::DROP;
		}
		else if (command == "DISPLAY")
		{
			return Commands::DISPLAY;
		}
		return Commands::INVALID;
	}

	static Identifiers getCommandIdentifier(string identifier)
	{
		if (identifier == "TABLE")
		{
			return Identifiers::TABLE;
		}
		else if (identifier == "INDEX")
		{
			return Identifiers::INDEX;
		}
		return Identifiers::INVALID;
	}
};

class SQLDb
{

public:
	Table* Tables;
	Index* Indexes;
public:
	SQLDb()
	{
		this->Tables = new Table();
		this->Indexes = new Index();
	}

	bool TableExists(string table)
	{
		for (int i = 0; i < Table::noTables; i++)
		{
			if (Tables[i].Name == table)
				return true;
		}
		return false;
	}

	bool IndexExists(string index)
	{
		for (int i = 0; i < Table::noTables; i++)
		{
			if (Indexes[i].Name == index)
				return true;
		}
		return false;
	}

	void CreateTable(string tableName, CustomColumnArray* customColumnArrays)
	{
		cout << "Table " + tableName + " was successfully created!";
		cout << customColumnArrays[0].name;
	}

	void CreateIndex(string indexName, string tableName, string columnName)
	{
		cout << "Index " + indexName + " was successfully created!";
	}

	void DropTable(string tableName)
	{
		cout << "Table " + tableName + " was successfully dropped!";
	}

	void DropIndex(string indexName)
	{
		cout << "Index " + indexName + " was successfully dropped!";
	}

	void DisplayTable(string tableName)
	{
		cout << tableName + " will be displayed sometime...";
	}

	void DisplayIndex(string indexName)
	{
		cout << indexName + " will be displayed sometime...";
	}
};

class WordManipulation
{
public:
	CustomColumnArray* customColumnArrays; // (column_1,integer,20,0),(column_2,text,40,'')

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

	CustomStringArray separateFirstWord(string line)
	{
		CustomStringArray customStringArray = CustomStringArray();
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

	CustomStringArray separateCondition(string line)
	{
		CustomStringArray customStringArray = CustomStringArray();
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

	CustomStringArray separateLastWord(string line)
	{
		CustomStringArray customStringArray = CustomStringArray();
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

	void ManagementCommands(SQLDb Db, string line)
	{
		WordManipulation WordManipulationService;

		CustomStringArray commandStringArray = WordManipulationService.separateFirstWord(line);

		if (commandStringArray.isValidated == true)
		{
			Commands Command = ReturnType::getCommandType(commandStringArray.firstWord);

			if (Command != Commands::INVALID) // Verificam daca Command este un tip de comanda valid (CREATE/DROP/DISPLAY)
			{
				CustomStringArray identifierStringArray = WordManipulationService.separateFirstWord(commandStringArray.restOfTheLine);
				Identifiers Identifier = ReturnType::getCommandIdentifier(identifierStringArray.firstWord);
				if (Identifier != Identifiers::INVALID) // Verificam daca Identifier este un tip de identifier valid (TABLE, INDEX)
				{
					if (Command == Commands::CREATE)
					{
						if (identifierStringArray.restOfTheLine.substr(0, 2) == "IF")
						{
							CustomStringArray conditionStringArray = WordManipulationService.separateCondition(identifierStringArray.restOfTheLine);
							if (conditionStringArray.isValidated)
							{
								Conditions Condition = ReturnType::getConditionType(conditionStringArray.firstWord);
								CustomStringArray indexOrTableNameStringArray = WordManipulationService.separateFirstWord(conditionStringArray.restOfTheLine);
								if (indexOrTableNameStringArray.isValidated && Condition == Conditions::IFNOTEXISTS)
								{
									if (Identifier == Identifiers::TABLE && !Db.TableExists(indexOrTableNameStringArray.firstWord) && indexOrTableNameStringArray.isValidated)
									{
										if (indexOrTableNameStringArray.restOfTheLine.substr(0, 2) == "((" && indexOrTableNameStringArray.restOfTheLine.substr(indexOrTableNameStringArray.restOfTheLine.length() - 2, 2) == "))")
										{

											WordManipulationService.separateParantheses(indexOrTableNameStringArray.restOfTheLine.substr(1, indexOrTableNameStringArray.restOfTheLine.length() - 2));
											//Db.CreateTable(indexOrTableNameStringArray.firstWord, WordManipulationService.customColumnArrays);
										}
										else if (indexOrTableNameStringArray.restOfTheLine.substr(0, 2) == "(" && indexOrTableNameStringArray.restOfTheLine.substr(indexOrTableNameStringArray.restOfTheLine.length() - 2, 2) == ")")
										{
											WordManipulationService.separateParantheses(indexOrTableNameStringArray.restOfTheLine);
											//Db.CreateTable(indexOrTableNameStringArray.firstWord, WordManipulationService.customColumnArrays);
										}
										else
											cout << "Column synthax error!";
									}
									else if (Identifier == Identifiers::INDEX)
									{
										CustomStringArray separatorStringArray = WordManipulationService.separateFirstWord(indexOrTableNameStringArray.restOfTheLine);
										if (separatorStringArray.firstWord == "ON")
										{
											CustomStringArray tableNameStringArray = WordManipulationService.separateFirstWord(separatorStringArray.restOfTheLine);
											if (!Db.IndexExists(indexOrTableNameStringArray.firstWord) && tableNameStringArray.isValidated)
											{
												CustomStringArray ColumnStringArray = WordManipulationService.separateLastWord(tableNameStringArray.restOfTheLine);
												if (ColumnStringArray.isValidated && ColumnStringArray.firstWord[0] == '(' && ColumnStringArray.firstWord[ColumnStringArray.firstWord.length() - 1] == ')')
													/*Db.CreateIndex(indexOrTableNameStringArray.firstWord, tableNameStringArray.firstWord, ColumnStringArray.firstWord.substr(1, ColumnStringArray.firstWord.length() - 2));*/
													cout << "Created index " + indexOrTableNameStringArray.firstWord + " for table " + tableNameStringArray.firstWord + " on column " + ColumnStringArray.firstWord.substr(1, ColumnStringArray.firstWord.length() - 2);
												else
												{
													cout << "Column is invalid!";
												}
											}
											else
											{
												if (Db.IndexExists(indexOrTableNameStringArray.firstWord))
													cout << "Index already exists!" << '\n';
												if (!tableNameStringArray.isValidated)
													cout << "Table name is invalid!" << '\n';
											}
										}
										else
											cout << "ON separator expected!" << '\n';
									}
									else
										cout << "Identifier not valid!" << '\n';
								}
								else
								{
									if (indexOrTableNameStringArray.isValidated)
									{
										if (Identifier == Identifiers::TABLE)
											if (Command == Commands::DROP)
											{
												Db.DropTable(indexOrTableNameStringArray.firstWord);
											}
											else if (Identifier == Identifiers::INDEX)
												if (Command == Commands::DROP)
												{
													Db.DropIndex(indexOrTableNameStringArray.firstWord);
												}
									}
									else
										cout << "Index/Table name is invalid!" << '\n';
									if (Condition != Conditions::IFNOTEXISTS)
										cout << "Condition not valid!" << '\n';

								}
							}
							else
								cout << "Condition is invalid!" << '\n';
						}
						else
						{
							CustomStringArray indexOrTableNameStringArray = WordManipulationService.separateFirstWord(identifierStringArray.restOfTheLine);
							if (indexOrTableNameStringArray.isValidated)
							{
								if (indexOrTableNameStringArray.restOfTheLine.substr(0, 2) == "IF")
								{
									CustomStringArray conditionStringArray = WordManipulationService.separateCondition(indexOrTableNameStringArray.restOfTheLine);
									if (conditionStringArray.isValidated)
									{
										Conditions Condition = ReturnType::getConditionType(conditionStringArray.firstWord);

										if (Condition == Conditions::IFNOTEXISTS)
										{
											if (Identifier == Identifiers::TABLE && !Db.TableExists(indexOrTableNameStringArray.firstWord))
											{
												if (conditionStringArray.restOfTheLine.substr(0, 2) == "((" && conditionStringArray.restOfTheLine.substr(conditionStringArray.restOfTheLine.length() - 2, 2) == "))")
												{
													WordManipulationService.separateParantheses(conditionStringArray.restOfTheLine.substr(1, conditionStringArray.restOfTheLine.length() - 2));
													//Db.CreateTable(indexOrTableNameStringArray.firstWord, customColumnArrays);
												}
												else if (conditionStringArray.restOfTheLine.substr(0, 2) == "(" && conditionStringArray.restOfTheLine.substr(conditionStringArray.restOfTheLine.length() - 2, 2) == ")")
												{
													WordManipulationService.separateParantheses(conditionStringArray.restOfTheLine.substr(1, conditionStringArray.restOfTheLine.length() - 2));
													//Db.CreateTable(indexOrTableNameStringArray.firstWord, customColumnArrays);

												}
												else
													cout << "Column synthax error! ";
											}
											else if (Identifier == Identifiers::INDEX && !Db.IndexExists(indexOrTableNameStringArray.firstWord))
											{
												CustomStringArray separatorStringArray = WordManipulationService.separateFirstWord(indexOrTableNameStringArray.restOfTheLine);
												if (separatorStringArray.firstWord == "ON")
												{
													CustomStringArray tableNameStringArray = WordManipulationService.separateFirstWord(separatorStringArray.restOfTheLine);
													if (!Db.IndexExists(indexOrTableNameStringArray.firstWord) && tableNameStringArray.isValidated)
													{
														CustomStringArray ColumnStringArray = WordManipulationService.separateLastWord(tableNameStringArray.restOfTheLine);
														if (ColumnStringArray.isValidated && ColumnStringArray.firstWord[0] == '(' && ColumnStringArray.firstWord[ColumnStringArray.firstWord.length() - 1] == ')')
															/*Db.CreateIndex(indexOrTableNameStringArray.firstWord, tableNameStringArray.firstWord, ColumnStringArray.firstWord.substr(1, ColumnStringArray.firstWord.length() - 2));*/
															cout << "Created index " + indexOrTableNameStringArray.firstWord + " for table " + tableNameStringArray.firstWord + " on column " + ColumnStringArray.firstWord.substr(1, ColumnStringArray.firstWord.length() - 2);
														else
														{
															cout << "Column is invalid!";
														}
													}
													else
													{
														if (Db.IndexExists(indexOrTableNameStringArray.firstWord))
															cout << "Index already exists!" << '\n';
														if (!tableNameStringArray.isValidated)
															cout << "Table name is invalid!" << '\n';
													}
												}
												else
													cout << "ON separator expected!" << '\n';
											}
											else
												cout << "Identifier not valid!!!!!!!!!" << '\n';
										}
										else
										{
											if (indexOrTableNameStringArray.isValidated)
											{
												if (Identifier == Identifiers::TABLE)
													if (Command == Commands::DROP)
													{
														Db.DropTable(indexOrTableNameStringArray.firstWord);
													}
													else if (Identifier == Identifiers::INDEX)
														if (Command == Commands::DROP)
														{
															Db.DropIndex(indexOrTableNameStringArray.firstWord);
														}
											}
											else
												cout << "Index/Table name is invalid!" << '\n';
											if (Condition != Conditions::IFNOTEXISTS)
												cout << "Condition not valid!" << '\n';

										}
									}
									else
										cout << "Condition is invalid!" << '\n';
								}
								else
								{
									WordManipulationService.separateParantheses(indexOrTableNameStringArray.restOfTheLine.substr(1, indexOrTableNameStringArray.restOfTheLine.length() - 2));
								}
							}
							else
							{
								cout << "Index/Table not valid!" << '\n';
							}

						}
					}
					else
					{
						CustomStringArray indexOrTableStringArray = WordManipulationService.separateLastWord(identifierStringArray.restOfTheLine);
						if (indexOrTableStringArray.isValidated)
						{
							if (Command == Commands::DISPLAY)
							{
								if (Identifier == Identifiers::INDEX)
									Db.DisplayIndex(indexOrTableStringArray.firstWord);
								if (Identifier == Identifiers::TABLE)
									Db.DisplayTable(indexOrTableStringArray.firstWord);
							}
							else
							{
								if (Identifier == Identifiers::INDEX)
									Db.DropIndex(indexOrTableStringArray.firstWord);
								if (Identifier == Identifiers::TABLE)
									Db.DropTable(indexOrTableStringArray.firstWord);
							}
						}

					}
				}
				else
				{
					cout << "Command identifier is incorrectly formatted!";
				}
			}
			else
			{
				cout << "Command type is incorrectly formatted!";
			}
		}
		else if (commandStringArray.isValidated == false)
			cout << "Space expected after command type!";
	}

};

int Table::noTables = 0;
int Index::noIndexes = 0;