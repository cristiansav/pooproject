#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int debug()
{
	ifstream in("Tables/table1.txt");
	string text;
	getline(in, text);
	cout << text;
	cin >> text;
}