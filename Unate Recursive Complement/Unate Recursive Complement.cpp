// Unate Recursive Complement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <algorithm>
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

bool isBinate(deque<Cube>& F, int& number_of_variables) {
	int num = 0;
	for (int i = 0; i < number_of_variables; i++) {
		int T = 0, C = 0;
		for (int j = 0; j < F.size(); j++) {
			if (F[j].getValue(i + 1) == 1)
				T++;
			else if (F[j].getValue(i + 1) == 2)
				C++;
		}
		if (T > 0 && C > 0)
			num++;
	}
	return num > 0;
}

int MostBinate(deque<Cube>& F, int& number_of_variables) {

	vector < pair<pair<int, int>, int>> ties;

	for (int i = 0; i < number_of_variables; i++) {
		int T = 0, C = 0, O = 0;
		for (int j = 0; j < F.size(); j++) {
			if (F[j].getValue(i + 1) == 1)
				T++, O++;
			else if (F[j].getValue(i + 1) == 2)
				C++, O++;
		}

		// if binate
		if (T > 0 && C > 0)
			ties.push_back(make_pair(make_pair(O, abs(T - C)), i));
	}

	sort(ties.begin(), ties.end(), [](pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b) {
		if (a.first.first != b.first.first)
			return a.first.first > b.first.first;
		if (a.first.second != b.first.second)
			return a.first.second < b.first.second;
		return a.second < b.second;
		});

	return ties.front().second;
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
	else {

		if (isBinate(F,number_of_variables)) {

		}

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

