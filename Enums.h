#pragma once
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