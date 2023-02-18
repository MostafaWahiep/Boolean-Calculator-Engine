#pragma once

#include <vector>

#define F first
#define S second

using namespace std;

class CubeList {
public:
	class Cube {
	public:
			int number_of_variables;
			vector<pair<bool, bool>> terms;

			Cube(int number_of_variables) {
				this->number_of_variables = number_of_variables;
				terms.resize(number_of_variables);

				//initialize all variables with zeros
				for (pair<bool, bool> &cube : terms) {
					cube.first = 1;
					cube.second = 1;
				}
			}


	};
};

