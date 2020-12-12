#include <iostream>
#include <string.h>
#include "Classes.h"

using namespace std;


int main()
{
	SQLDb Db = SQLDb();

	// Variables
	string line;

	cout << "Please input the full SQL command..." << '\n';
	getline(cin, line);

	WordManipulation WordManipulationService;
	WordManipulationService.ManagementCommands(Db, line);
}