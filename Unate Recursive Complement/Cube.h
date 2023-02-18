#pragma once

#include <vector>

using namespace std;

class Cube {
public:

	int number_of_variables;
	vector<pair<bool, bool>> terms;

	Cube(int number_of_variables);

		/*
		* 1-> true
		* 2-> complement
		* 3-> don't care
		*/
		short getValue(int variable);

		/*
		* +ve-> true
		* -ve-> complement
		*/
		void setValue_at(int value);

		void setDontCare(int variable);


};

