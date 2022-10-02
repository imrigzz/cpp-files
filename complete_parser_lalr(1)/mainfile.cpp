/*

	To Compile:
		flex file.l
		bison -d file.y -o file.cc
		cc -c lex.yy.c -o lex.yy.o
		g++ lex.yy.o mainfile.cpp -o exe_file
		./exe_file

*/

#include <iostream>
#include <string>
#include "driver.h"
#include "struct.h"

using namespace std;

int main()
{
	cout << "Enter Input: ";
	char filename[100];
	cin >> filename;
	parseTree tm = parserd(filename);

	return 0;
}
