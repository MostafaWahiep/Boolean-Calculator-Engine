// Unate Recursive Complement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "CubeList.h"
#include "Cube.h"

using namespace std;

CubeList complementOneCubed(CubeList F) {
	CubeList nF(F.number_of_variables);
	for (int i = 0; i < F.number_of_variables; i++) {
		Cube c(F.number_of_variables);
		switch (F.cubes.front().getValue(i + 1)) {
		case 1:
			c.setValue(i + 1, 0);
			nF.addCube(c);
			break;
		case 2:
			c.setValue(i+1, 1);
			nF.addCube(c);
			break;
		}
	}
	return nF;
}

CubeList readInput(string file_name) {
	int number_of_variables;
	int number_of_cubes;
	int variables, value, i, j;

	ifstream input;
	input.open(file_name);

	if (!input.is_open())
		exit(EXIT_FAILURE);

	input >> number_of_variables >> number_of_cubes;

	CubeList F(number_of_variables);

	for (i = 0; i < number_of_cubes; i++) {
		input >> variables;
		Cube c(number_of_variables);
		for (j = 0; j < variables; j++) {
			input >> value;
			c.setValue_at(value);
		}
		F.addCube(c);
	}

	return F;
}

void writeOutput(CubeList F, string file_name) {
	int x, j;
	
	ofstream output;
	output.open(file_name);
	if (!output.is_open())
		exit(EXIT_FAILURE);

	output << F.number_of_variables << endl;
	output << F.number_of_cubes << endl;
	for (Cube c : F.cubes) {
		x = 0;
		for (j = 0; j < F.number_of_variables; j++)
			if (c.getValue(j + 1) < 3) x++;
		output << x << ' ';
		for (j = 0; j < F.number_of_variables; j++) {
			if (c.getValue(j + 1) == 3) continue;
			if (c.getValue(j + 1) == 1)
				output << j + 1;
			else if (c.getValue(j + 1) == 2)
				output << -1 * j - 1;
			if (j != F.number_of_variables - 1)
				output << ' ';
		}
		output << endl;
	}
	output.close();

}

CubeList OR(CubeList& R, CubeList& L) {
	CubeList D(R.number_of_variables);
	for (Cube c : R.cubes) {
		D.addCube(c);
	}
	for (Cube c : L.cubes) {
		D.addCube(c);
	}

	return D;
}

CubeList Complement(CubeList F) {
	// Empty cube list
	if (F.number_of_cubes == 0) {
		Cube c(F.number_of_variables);
		F.addCube(c);
		return F;
	}
	// Cube list contains just one cube
	else if(F.number_of_cubes == 1){
		return complementOneCubed(F);
	}
	// Cube list contains All Don’t Cares Cube
	else if (F.isAllDontCaresCube()) {
		CubeList q(F.number_of_variables);
		return q;
	}
	else {

		int x;
	
		if (F.isBinate()) {
			x = F.MostBinate();
		}
		else {
			x = F.Mostunate();
		}

		CubeList P = Complement(F.positiveCofactor(x));
		CubeList N = Complement(F.negativeCofactor(x));

		P.AND(x, 1);
		N.AND(x, 0);

		return OR(P, N);
	}
}

// works using demorgan: a.b = ~(~a+~b)
CubeList AND(CubeList& R, CubeList& L) {
	CubeList Rp(Complement(R)), Lp(Complement(L));
	CubeList O(OR(Rp, Lp));

	return Complement(O);
}

CubeList EXOR(CubeList& R, CubeList& L) {
	CubeList Rp(Complement(R)), Lp(Complement(L));
	CubeList R_Lp(AND(R, Lp));
	CubeList Rp_L(AND(Rp, L));

	return OR(R_Lp, Rp_L);
}

void BooleanCalcEngine() {
	char s;
	string a1, a2, a3;

	ifstream input;
	input.open("cmd6.txt");

	if (!input.is_open())
		exit(EXIT_FAILURE);

	unordered_map<string, CubeList> mp;
	string path;
	input >> s;
	while (input.good()) {
		switch (s)
		{
		// read
		case 'r':
			input >> a1;
			path = a1 + ".pcn";
			mp[a1] = readInput(path);
			break;
		// complement
		case '!':
			input >> a1 >> a2;
			mp[a1] = Complement(mp[a2]);
			break;
		// a1 = a2 + a3
		case '+':
			input >> a1 >> a2 >> a3;
			mp[a1] = OR(mp[a2], mp[a3]);
			break;
		// a1 = a2.a3
		case '&':
			input >> a1 >> a2 >> a3;
			mp[a1] = AND(mp[a2], mp[a3]);
			break;
		// a1 = a2.a3
		case '^':
			input >> a1 >> a2 >> a3;
			mp[a1] = EXOR(mp[a2], mp[a3]);
			break;
		// print a1
		case 'p':
			input >> a1;
			path = a1 + ".pcn";
			writeOutput(mp[a1], path);
			break;
		// quit
		case 'q':
			return;

		default:
			break;
		}
		input >> s;
	}

}

int main()
{
	//CubeList F = readInput("part5.pcn");

	//CubeList Fp = Complement(F);

	//string file_name = "outputpart5.pcn";

	//writeOutput(Fp, file_name);

	BooleanCalcEngine();

}

