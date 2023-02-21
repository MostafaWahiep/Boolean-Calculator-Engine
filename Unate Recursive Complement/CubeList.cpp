#include "CubeList.h"
#include <algorithm>

CubeList::CubeList(int number_of_variables) {
	this->number_of_cubes = 0;
	this->number_of_variables = number_of_variables;
}

CubeList::CubeList(int number_of_variables, int number_of_cubes) {
	this->number_of_cubes = number_of_cubes;
	this->number_of_variables = number_of_variables;
}

CubeList::CubeList(const CubeList& origin) {
	this->number_of_cubes = origin.number_of_cubes;
	this->number_of_variables = origin.number_of_variables;

	for (const Cube c : origin.cubes) {
		Cube new_c(c);
		cubes.push_back(new_c);
	}
}

CubeList & CubeList::operator=(const CubeList& origin) {
	if (this != &origin) {
		number_of_cubes = origin.number_of_cubes;
		number_of_variables = origin.number_of_variables;
		for (const Cube c : origin.cubes) {
			Cube new_c(c);
			cubes.push_back(new_c);
		}
	}
	return *this;
}

CubeList CubeList::positiveCofactor(int x) {
	CubeList P(this->number_of_variables);
	for (Cube c : cubes) {
		if (c.getValue(x) == 3) {
			P.addCube(c);
		}
		else if (c.getValue(x) == 1) {
			c.setDontCare(x);
			P.addCube(c);
		}
	}
	return P;
}

CubeList CubeList::negativeCofactor(int x) {
	CubeList P(this->number_of_variables);
	for (Cube c : cubes) {
		if (c.getValue(x) == 3) {
			P.addCube(c);
		}
		else if (c.getValue(x) == 2) {
			c.setDontCare(x);
			P.addCube(c);
		}
	}
	return P;
}

bool CubeList::isBinate() {
	for (int i = 0; i < number_of_variables; i++) {
		int T = 0, C = 0;
		for (Cube &c : cubes) {
			if (c.getValue(i + 1) == 1)
				T++;
			else if (c.getValue(i + 1) == 2)
				C++;
		}
		if (T > 0 && C > 0)
			return true;
	}
	return false;
}

int CubeList::MostBinate() {
	vector<pair<pair<int, int>, int>> ties;

	for (int i = 0; i < number_of_variables; i++) {
		int T = 0, C = 0, O = 0;
		for (Cube &c : cubes) {
			const int value = c.getValue(i + 1);
			if (value == 1) {
				T++;
				O++;
			}
			else if (value == 2) {
				C++;
				O++;
			}
		}

		// if binate
		if (T > 0 && C > 0) {
			ties.emplace_back(make_pair(O, abs(T - C)), i);
		}
	}

	sort(ties.begin(), ties.end(), 
		[](const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
		if (a.first.first != b.first.first) {
			return a.first.first > b.first.first;
		}
		else if (a.first.second != b.first.second) {
			return a.first.second < b.first.second;
		}
		else {
			return a.second < b.second;
		}
		});

	return ties.front().second + 1;

}

int CubeList::Mostunate() {
	vector<pair<int, int>> ties;
	for (int i = 0; i < number_of_variables; i++) {
		int O = 0;
		for (Cube &c : cubes) {
			if (c.getValue(i + 1) < 3) {
				O++;
			}
		}
		ties.emplace_back(O, i);
	}
	sort(ties.begin(), ties.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		if (a.first != b.first) {
			return a.first > b.first;
		}
		return a.second < b.second;
		});
	return ties.front().second + 1;
}

bool CubeList::isAllDontCaresCube() {
	for (Cube &c : cubes) {
		if (c.isDontCare())
			return true;
	}
	return false;
}

void CubeList::AND(int x, int T) {
	for (Cube &c : cubes) {
		c.setValue(x, T);
	}
}

void CubeList::addCube(Cube c) {
	if (c.number_of_variables != this->number_of_variables)
		exit(1);
	number_of_cubes++;
	cubes.push_back(c);
}
