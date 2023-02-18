#include "Cube.h"

Cube::Cube(int number_of_variables) {
	this->number_of_variables = number_of_variables;
	terms.resize(number_of_variables);

	//initialize all variables with zeros
	for (pair<bool, bool>& cube : terms) {
		cube.first = 1;
		cube.second = 1;
	}
}

short Cube::getValue(int variable){
	variable--;
	return (terms[variable].first << 1) + terms[variable].second;
}

void Cube::setValue_at(int value) {
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

void Cube::setDontCare(int variable) {
	terms[variable - 1].first = 1;
	terms[variable - 1].second = 1;
}

bool Cube::isDontCare() const {
	for (pair<bool, bool> cube : terms) {
		if (cube.first == 0 || cube.second == 0)
			return 0;
	}
	return 1
}