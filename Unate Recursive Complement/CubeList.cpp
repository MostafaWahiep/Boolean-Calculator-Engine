#include "CubeList.h"

CubeList::CubeList(int number_of_variables)
	:number_of_variables(number_of_variables), number_of_cubes(0) {}

CubeList::CubeList(int number_of_variables, int number_of_cubes)
	:number_of_variables(number_of_variables), number_of_cubes(number_of_cubes) {}

CubeList::CubeList(const CubeList& origin)
	:number_of_variables(origin.number_of_variables), number_of_cubes(origin.number_of_cubes) {
	for (Cube c : origin.cubes) {
		Cube new_c(c);
		cubes.push_back(new_c);
	}
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
		else if (c.getValue(x) == 1) {
			c.setDontCare(x);
			P.addCube(c);
		}
	}
	return P;
}

bool CubeList::isBinate() {
	for (int i = 0; i < number_of_variables; i++) {
		int T = 0, C = 0;
		for (Cube c : cubes) {
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

int CubeList::MostBinate() {}

int CubeList::Mostunnate() {}

bool CubeList::isAllDontCaresCube() {}

void CubeList::AND(int x, int T) {}

void CubeList::addCube(Cube c) {}

void CubeList::removeCube(int index) {}
