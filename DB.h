#pragma once
#include <iostream>
#include <string>
#include "Enums.h"
#include "Word_Manipulation.h"
#include <fstream>

using namespace std;

ifstream Read("database.txt");
ofstream Write("database.txt");

ofstream NiceOutput("Nice_Output.txt");

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

	void CreateTable(string tableName, ColumnDictionary* customColumnArrays)
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

	void ManagementCommands(SQLDb Db, string line)
	{
		WordManipulation WordManipulationService;

		StringDictionary commandDictionary = WordManipulationService.separateFirstWord(line);
		if (commandDictionary.isValidated)
		{
			switch (ReturnType::getCommandType(commandDictionary.firstWord))
			{
			case Commands::CREATE:
			{
				// 1. Separate identifier
				StringDictionary identifierDictionary = WordManipulationService.separateFirstWord(commandDictionary.restOfTheLine);
				// 2. Validate identifier
				if (identifierDictionary.isValidated)
				{
					if (identifierDictionary.restOfTheLine.substr(0, 2) == "IF")
					{
						// 3. Separate condition
						StringDictionary conditionDictionary = WordManipulationService.separateCondition(identifierDictionary.restOfTheLine);
						// 4. Validate condition
						if (conditionDictionary.isValidated && ReturnType::getConditionType(conditionDictionary.firstWord) == Conditions::IFNOTEXISTS)
						{
							if (ReturnType::getCommandIdentifier(identifierDictionary.firstWord) == Identifiers::INDEX)
							{
								// 5. Separate index name
								StringDictionary indexDictionary = WordManipulationService.separateFirstWord(conditionDictionary.restOfTheLine);
								// 6. Validate index and check for existing index with the same name
								if (indexDictionary.isValidated && !IndexExists(indexDictionary.firstWord))
								{
									// 7. Check if "ON" separator exists
									if (indexDictionary.restOfTheLine.substr(0, 2) == "ON")
									{
										// 8. Separate "ON"
										StringDictionary onDictionary = WordManipulationService.separateFirstWord(indexDictionary.restOfTheLine);
										// 9. Validate "ON"
										if (onDictionary.isValidated)
										{
											// 10. Separate table name
											StringDictionary tableDictionary = WordManipulationService.separateFirstWord(onDictionary.restOfTheLine);
											// 11. Validate table name
											if (tableDictionary.isValidated && TableExists(tableDictionary.firstWord))
											{
												// 12. Get table's number of columns if the table exists

												// 13. Check if index has one or more columns
												if (WordManipulationService.isList(tableDictionary.restOfTheLine))
												{
													// 14. Check if every column exists

													// 15. Create index on the specified columns

												}
												else
												{
													// 14. Check if the column exists

													// 15. Create index on the specified column

												}
											}
											else
											{
												// Table does not exist / Table name is invalid!
											}
										}
										else
										{
											// "ON" separator is invalid!
										}
									}
									else
									{
										// "ON" expected after index name!
									}
								}
								else
								{
									// Index already exists / Index name is invalid
								}
							}
							else if (ReturnType::getCommandIdentifier(identifierDictionary.firstWord) == Identifiers::TABLE)
							{
								// 5. Separate table name
								StringDictionary tableDictionary = WordManipulationService.separateFirstWord(conditionDictionary.restOfTheLine);
								// 6. Validate table
								if (tableDictionary.isValidated && !TableExists(tableDictionary.firstWord))
								{
									// 7. Check if there are one or more columns
									int noColumns = WordManipulationService.getNoColumns(tableDictionary.restOfTheLine);
									if (noColumns > 1)
									{
										// At least 2 columns
										// 8. Create ("Table_" + tableDictionary.firstWord + ".txt") file
										fstream tableWrite("Table_" + tableDictionary.firstWord + ".txt", ios::app);
										tableWrite.seekg(0, ios::end);
										tableWrite << tableDictionary.firstWord << '\n';
										// 9. Append every column that is valid to the .txt file that was previously generated

									}
									else if (noColumns == 1)
									{
										// 1 column

									}
									else
									{
										// Invalid columns synthax!
									}
								}
							}
							else
							{
								// Identifier is invalid
							}
						}
						else
						{
							// Identifier synthax is invalid
						}
					}
					else
					{
						// Condition is invalid
					}
				}
				else
				{
					// 1. Get identifier

					// 2. Separate condition if it exists

				}
				break;
			}
			case Commands::DISPLAY:
				//
				break;
			case Commands::DROP:
				//
				break;
			default:
				cout << "Invalid command!";
				break;
			}
		}

	}
};










//
//	if (commandStringArray.isValidated == true)
//	{
//		Commands Command = ReturnType::getCommandType(commandStringArray.firstWord);

//		if (Command != Commands::INVALID) // Verificam daca Command este un tip de comanda valid (CREATE/DROP/DISPLAY)
//		{
//			StringDictionary identifierStringArray = WordManipulationService.separateFirstWord(commandStringArray.restOfTheLine);
//			Identifiers Identifier = ReturnType::getCommandIdentifier(identifierStringArray.firstWord);
//			if (Identifier != Identifiers::INVALID) // Verificam daca Identifier este un tip de identifier valid (TABLE, INDEX)
//			{
//				if (Command == Commands::CREATE)
//				{
//					if (identifierStringArray.restOfTheLine.substr(0, 2) == "IF")
//					{
//						StringDictionary conditionStringArray = WordManipulationService.separateCondition(identifierStringArray.restOfTheLine);
//						if (conditionStringArray.isValidated)
//						{
//							Conditions Condition = ReturnType::getConditionType(conditionStringArray.firstWord);
//							StringDictionary indexOrTableNameStringArray = WordManipulationService.separateFirstWord(conditionStringArray.restOfTheLine);
//							if (indexOrTableNameStringArray.isValidated && Condition == Conditions::IFNOTEXISTS)
//							{
//								if (Identifier == Identifiers::TABLE && !Db.TableExists(indexOrTableNameStringArray.firstWord) && indexOrTableNameStringArray.isValidated)
//								{
//									if (indexOrTableNameStringArray.restOfTheLine.substr(0, 2) == "((" && indexOrTableNameStringArray.restOfTheLine.substr(indexOrTableNameStringArray.restOfTheLine.length() - 2, 2) == "))")
//									{

//										WordManipulationService.separateParantheses(indexOrTableNameStringArray.restOfTheLine.substr(1, indexOrTableNameStringArray.restOfTheLine.length() - 2));
//										//Db.CreateTable(indexOrTableNameStringArray.firstWord, WordManipulationService.customColumnArrays);
//									}
//									else if (indexOrTableNameStringArray.restOfTheLine.substr(0, 2) == "(" && indexOrTableNameStringArray.restOfTheLine.substr(indexOrTableNameStringArray.restOfTheLine.length() - 2, 2) == ")")
//									{
//										WordManipulationService.separateParantheses(indexOrTableNameStringArray.restOfTheLine);
//										//Db.CreateTable(indexOrTableNameStringArray.firstWord, WordManipulationService.customColumnArrays);
//									}
//									else
//										cout << "Column synthax error!";
//								}
//								else if (Identifier == Identifiers::INDEX)
//								{
//									StringDictionary separatorStringArray = WordManipulationService.separateFirstWord(indexOrTableNameStringArray.restOfTheLine);
//									if (separatorStringArray.firstWord == "ON")
//									{
//										StringDictionary tableNameStringArray = WordManipulationService.separateFirstWord(separatorStringArray.restOfTheLine);
//										if (!Db.IndexExists(indexOrTableNameStringArray.firstWord) && tableNameStringArray.isValidated)
//										{
//											StringDictionary ColumnStringArray = WordManipulationService.separateLastWord(tableNameStringArray.restOfTheLine);
//											if (ColumnStringArray.isValidated && ColumnStringArray.firstWord[0] == '(' && ColumnStringArray.firstWord[ColumnStringArray.firstWord.length() - 1] == ')')
//												/*Db.CreateIndex(indexOrTableNameStringArray.firstWord, tableNameStringArray.firstWord, ColumnStringArray.firstWord.substr(1, ColumnStringArray.firstWord.length() - 2));*/
//												cout << "Created index " + indexOrTableNameStringArray.firstWord + " for table " + tableNameStringArray.firstWord + " on column " + ColumnStringArray.firstWord.substr(1, ColumnStringArray.firstWord.length() - 2);
//											else
//											{
//												cout << "Column is invalid!";
//											}
//										}
//										else
//										{
//											if (Db.IndexExists(indexOrTableNameStringArray.firstWord))
//												cout << "Index already exists!" << '\n';
//											if (!tableNameStringArray.isValidated)
//												cout << "Table name is invalid!" << '\n';
//										}
//									}
//									else
//										cout << "ON separator expected!" << '\n';
//								}
//								else
//									cout << "Identifier not valid!" << '\n';
//							}
//							else
//							{
//								if (indexOrTableNameStringArray.isValidated)
//								{
//									if (Identifier == Identifiers::TABLE)
//										if (Command == Commands::DROP)
//										{
//											Db.DropTable(indexOrTableNameStringArray.firstWord);
//										}
//										else if (Identifier == Identifiers::INDEX)
//											if (Command == Commands::DROP)
//											{
//												Db.DropIndex(indexOrTableNameStringArray.firstWord);
//											}
//								}
//								else
//									cout << "Index/Table name is invalid!" << '\n';
//								if (Condition != Conditions::IFNOTEXISTS)
//									cout << "Condition not valid!" << '\n';

//							}
//						}
//						else
//							cout << "Condition is invalid!" << '\n';
//					}
//					else
//					{
//						StringDictionary indexOrTableNameStringArray = WordManipulationService.separateFirstWord(identifierStringArray.restOfTheLine);
//						if (indexOrTableNameStringArray.isValidated)
//						{
//							if (indexOrTableNameStringArray.restOfTheLine.substr(0, 2) == "IF")
//							{
//								StringDictionary conditionStringArray = WordManipulationService.separateCondition(indexOrTableNameStringArray.restOfTheLine);
//								if (conditionStringArray.isValidated)
//								{
//									Conditions Condition = ReturnType::getConditionType(conditionStringArray.firstWord);

//									if (Condition == Conditions::IFNOTEXISTS)
//									{
//										if (Identifier == Identifiers::TABLE && !Db.TableExists(indexOrTableNameStringArray.firstWord))
//										{
//											if (conditionStringArray.restOfTheLine.substr(0, 2) == "((" && conditionStringArray.restOfTheLine.substr(conditionStringArray.restOfTheLine.length() - 2, 2) == "))")
//											{
//												WordManipulationService.separateParantheses(conditionStringArray.restOfTheLine.substr(1, conditionStringArray.restOfTheLine.length() - 2));
//												//Db.CreateTable(indexOrTableNameStringArray.firstWord, customColumnArrays);
//											}
//											else if (conditionStringArray.restOfTheLine.substr(0, 2) == "(" && conditionStringArray.restOfTheLine.substr(conditionStringArray.restOfTheLine.length() - 2, 2) == ")")
//											{
//												WordManipulationService.separateParantheses(conditionStringArray.restOfTheLine.substr(1, conditionStringArray.restOfTheLine.length() - 2));
//												//Db.CreateTable(indexOrTableNameStringArray.firstWord, customColumnArrays);

//											}
//											else
//												cout << "Column synthax error! ";
//										}
//										else if (Identifier == Identifiers::INDEX && !Db.IndexExists(indexOrTableNameStringArray.firstWord))
//										{
//											StringDictionary separatorStringArray = WordManipulationService.separateFirstWord(indexOrTableNameStringArray.restOfTheLine);
//											if (separatorStringArray.firstWord == "ON")
//											{
//												StringDictionary tableNameStringArray = WordManipulationService.separateFirstWord(separatorStringArray.restOfTheLine);
//												if (!Db.IndexExists(indexOrTableNameStringArray.firstWord) && tableNameStringArray.isValidated)
//												{
//													StringDictionary ColumnStringArray = WordManipulationService.separateLastWord(tableNameStringArray.restOfTheLine);
//													if (ColumnStringArray.isValidated && ColumnStringArray.firstWord[0] == '(' && ColumnStringArray.firstWord[ColumnStringArray.firstWord.length() - 1] == ')')
//														/*Db.CreateIndex(indexOrTableNameStringArray.firstWord, tableNameStringArray.firstWord, ColumnStringArray.firstWord.substr(1, ColumnStringArray.firstWord.length() - 2));*/
//														cout << "Created index " + indexOrTableNameStringArray.firstWord + " for table " + tableNameStringArray.firstWord + " on column " + ColumnStringArray.firstWord.substr(1, ColumnStringArray.firstWord.length() - 2);
//													else
//													{
//														cout << "Column is invalid!";
//													}
//												}
//												else
//												{
//													if (Db.IndexExists(indexOrTableNameStringArray.firstWord))
//														cout << "Index already exists!" << '\n';
//													if (!tableNameStringArray.isValidated)
//														cout << "Table name is invalid!" << '\n';
//												}
//											}
//											else
//												cout << "ON separator expected!" << '\n';
//										}
//										else
//											cout << "Identifier not valid!!!!!!!!!" << '\n';
//									}
//									else
//									{
//										if (indexOrTableNameStringArray.isValidated)
//										{
//											if (Identifier == Identifiers::TABLE)
//												if (Command == Commands::DROP)
//												{
//													Db.DropTable(indexOrTableNameStringArray.firstWord);
//												}
//												else if (Identifier == Identifiers::INDEX)
//													if (Command == Commands::DROP)
//													{
//														Db.DropIndex(indexOrTableNameStringArray.firstWord);
//													}
//										}
//										else
//											cout << "Index/Table name is invalid!" << '\n';
//										if (Condition != Conditions::IFNOTEXISTS)
//											cout << "Condition not valid!" << '\n';

//									}
//								}
//								else
//									cout << "Condition is invalid!" << '\n';
//							}
//							else
//							{
//								WordManipulationService.separateParantheses(indexOrTableNameStringArray.restOfTheLine.substr(1, indexOrTableNameStringArray.restOfTheLine.length() - 2));
//							}
//						}
//						else
//						{
//							cout << "Index/Table not valid!" << '\n';
//						}

//					}
//				}
//				else
//				{
//					StringDictionary indexOrTableStringArray = WordManipulationService.separateLastWord(identifierStringArray.restOfTheLine);
//					if (indexOrTableStringArray.isValidated)
//					{
//						if (Command == Commands::DISPLAY)
//						{
//							if (Identifier == Identifiers::INDEX)
//								Db.DisplayIndex(indexOrTableStringArray.firstWord);
//							if (Identifier == Identifiers::TABLE)
//								Db.DisplayTable(indexOrTableStringArray.firstWord);
//						}
//						else
//						{
//							if (Identifier == Identifiers::INDEX)
//								Db.DropIndex(indexOrTableStringArray.firstWord);
//							if (Identifier == Identifiers::TABLE)
//								Db.DropTable(indexOrTableStringArray.firstWord);
//						}
//					}

//				}
//			}
//			else
//			{
//				cout << "Command identifier is incorrectly formatted!";
//			}
//		}
//		else
//		{
//			cout << "Command type is incorrectly formatted!";
//		}
//	}
//	else if (commandStringArray.isValidated == false)
//		cout << "Space expected after command type!";
//}


int Table::noTables = 0;
int Index::noIndexes = 0;