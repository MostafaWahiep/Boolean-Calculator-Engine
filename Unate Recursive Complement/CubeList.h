#pragma once

#include <vector>

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

			/*
			* 1-> true
			* 2-> complement
			* 3-> don't care
			*/
			short getValue(int variable) {
				variable--;
				return (terms[variable].first<<1) + terms[variable].second;
			}

			/*
			* +ve-> true
			* -ve-> complement
			*/
			void setValue_at(int value) {
				if (value > 0) {
					terms[value - 1].first = 0;
					terms[value - 1].second = 1;
				}
				else {
					value *= -1;
					terms[value - 1].first = 1;
					terms[value - 1].second = 0;
				}
			}

			void setDontCare(int variable) {
				terms[variable - 1].first = 1;
				terms[variable - 1].second = 1;
			}


	};
};

