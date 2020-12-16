#include <iostream>
#include <string.h>
#include "Enums.h"
#include "DB.h"

using namespace std;


int main()
{
	SQLDb Db = SQLDb();

	// Variables
	string line;

	cout << "Please input the full SQL command..." << '\n';
	getline(cin, line);

	Db.ManagementCommands(Db, line);
}