#pragma once

#include <vector>
#include <deque>
#include "Cube.h"

using namespace std;

class CubeList {

public:

	int number_of_variables;
	int number_of_cubes;

	deque<Cube> cubes;

	CubeList(int number_of_variables, int number_of_cubes);

	CubeList(const CubeList &origin);

	CubeList positiveCofactor();

	CubeList negativeCofactor();

	bool isBinate();

	int MostBinate();

	int Mostunnate();

	bool isAllDontCaresCube();

	void AND(int x, int T);

	void addCube(Cube c);

	void removeCube(int index);




	
};

