// Unate Recursive Complement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <deque>
#include "CubeList.h"
#include "Cube.h"

using namespace std;

bool isAllDontCaresCube(deque<Cube>& F) {
	for (Cube c : F) {
		if (!c.isDontCare())
			return false;
	}
	return true;
}

void complementOneCubed(deque<Cube>& F, int& number_of_variables) {
	for (int i = 0; i < number_of_variables; i++) {
		Cube c(number_of_variables);

		switch (F.front().getValue(i + 1)) {
		case 1:
			c.setValue_at(i + 1);
			break;
		case 2:
			c.setValue_at(-1 * i - 1);
			break;
		}
		F.push_back(c);
	}
	F.pop_front();
}

void Complement(deque<Cube>& F, int& number_of_variables) {
	// Empty cube list
	if (F.size() == 0) {
		Cube c(number_of_variables);
		F.push_back(c);
	}
	// Cube list contains All Don’t Cares Cube
	else if (isAllDontCaresCube(F)) {
		F.clear();
	}
	// Cube list contains just one cube
	else if(F.size() == 1){
		complementOneCubed(F, number_of_variables);
	}
}

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

