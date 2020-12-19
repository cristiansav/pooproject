#include <iostream>
#include <string.h>
#include "Enums.h"
#include "DB.h"

using namespace std;


int main()	
{
	SQLDb Db = SQLDb();

	string line;

	// cout << "Please input the full SQL command..." << '\n';
	// getline(cin, line);
	
	// Db.ManagementCommands(Db, line);
	Db.ManagementCommands(Db, "CREATE TABLE IF NOT EXISTS ELEVI ((nume,text,20,'Popescu'),(varsta,integer,3,0),(medie,float,20,9.092),(dioptrie,float,4,0.50),(geaca,text,20,'Alba'),(arma,text,20,'9mm'))");
}