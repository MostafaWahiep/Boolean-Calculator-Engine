// Unate Recursive Complement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <deque>
#include "CubeList.h"
#include "Cube.h"

using namespace std;


int main()
{
	freopen("input.txt", "r", stdin);

	int number_of_variables;
	int number_of_cubes;
	int vars, val, i , j;

	deque<Cube> terms;

	cin >> number_of_variables >> number_of_cubes;
	
	for (i = 0; i < number_of_cubes; i++) {
		cin >> vars;
		Cube c(number_of_variables);
		for (j = 0; j < vars; j++) {
			cin >> val;
			c.setValue_at(val);
		}
		terms.push_back(c);
	}





}

