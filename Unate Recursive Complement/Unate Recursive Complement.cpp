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
		if (c.isDontCare())
			return true;
	}
	return false;
}

deque<Cube> complementOneCubed(deque<Cube> F, int number_of_variables) {
	deque<Cube> nF;
	for (int i = 0; i < number_of_variables; i++) {
		Cube c(number_of_variables);
		switch (F.front().getValue(i + 1)) {
		case 1:
			c.setValue(i + 1, 0);
			nF.push_back(c);
			break;
		case 2:
			c.setValue(i+1, 1);
			nF.push_back(c);
			break;
		}
	}
	return nF;
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
			ties.push_back(make_pair(make_pair(O, abs(T - C)), i));
	}

	sort(ties.begin(), ties.end(), [](pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b) {
		if (a.first.first != b.first.first)
			return a.first.first > b.first.first;
		else if (a.first.second != b.first.second)
			return a.first.second < b.first.second;
		else return a.second < b.second;
		});

	return ties.front().second + 1;
}

deque<Cube> positiveCofactor(deque<Cube> F, int x) {
	deque<Cube> nF;
	for (int i = 0; i < F.size(); i++) {
		if (F[i].getValue(x) == 3) {
			nF.push_back(F[i]);
		}
		else if (F[i].getValue(x) == 1) {
			F[i].setDontCare(x);
			nF.push_back(F[i]);
		}
	}
	return nF;
}

deque<Cube> negativeCofactor(deque<Cube> F, int x) {
	deque<Cube> nF;
	for (int i = 0; i < F.size(); i++) {
		if (F[i].getValue(x) == 3) {
			nF.push_back(F[i]);
		}
		else if (F[i].getValue(x) == 2) {
			F[i].setDontCare(x);
			nF.push_back(F[i]);
		}
	}
	return nF;
}

void AND(deque<Cube>& F, int x, int T) {
	for (int i = 0; i < F.size(); i++) {
		F[i].setValue(x, T);
	}
}

void removered(deque<Cube>& F, int number_of_variables) {
	for (int i = 0; i < F.size() - 1; i++) {
		for (int j = i+1; j < F.size(); j++) {
			bool t = 1;
			for (int k = 0; k < number_of_variables; k++) {
				if (F[i].getValue(k+1) != F[j].getValue(k + 1)){
					t = 0;
					break;
				}
			}
			if (t) {
				F.erase(F.begin() + j);
				j--;
			}
		}
	}
}

deque<Cube> Complement(deque<Cube> F, int number_of_variables) {
	// Empty cube list
	if (F.size() == 0) {
		Cube c(number_of_variables);
		F.push_back(c);
		return F;
	}
	// Cube list contains just one cube
	else if(F.size() == 1){
		return complementOneCubed(F, number_of_variables);
	}
	// Cube list contains All Don’t Cares Cube
	else if (isAllDontCaresCube(F)) {
		deque<Cube> q;
		return q;
	}
	else {

		int x;
	
		x = MostBinate(F, number_of_variables);

		deque<Cube> P = Complement(positiveCofactor(F, x), number_of_variables);
		deque<Cube> N = Complement(negativeCofactor(F, x), number_of_variables);

		AND(P, x, 1);
		AND(N, x, 0);

		F.clear();
		for (int i = 0; i < P.size(); i++)
			F.push_back(P[i]);
		for (int i = 0; i < N.size(); i++)
			F.push_back(N[i]);

		//removered(F, number_of_variables);

		return F;
	}
}

int main()
{
	freopen("part5.pcn", "r", stdin);
	freopen("outputpart5.pcn", "w", stdout);

	int number_of_variables;
	int number_of_cubes;
	int vars, val, i , j;

	deque<Cube> F;

	cin >> number_of_variables >> number_of_cubes;
	
	for (i = 0; i < number_of_cubes; i++) {
		cin >> vars;
		Cube c(number_of_variables);
		for (j = 0; j < vars; j++) {
			cin >> val;
			c.setValue_at(val);
		}
		F.push_back(c);
	}

	

	deque<Cube> Fp = Complement(F, number_of_variables);

	cout << number_of_variables << endl;
	cout << Fp.size() << endl;
	for (i = 0; i < Fp.size(); i++) {
		int x = 0;
		for (int j = 0; j < number_of_variables; j++)
			if (Fp[i].getValue(j + 1) < 3) x++;
		cout << x << ' ';
		for (int j = 0; j < number_of_variables; j++) {
			if (Fp[i].getValue(j + 1) == 3) continue;
			if (Fp[i].getValue(j + 1) == 1)
				cout << j + 1;
			else if(Fp[i].getValue(j + 1) == 2)
				cout << -1 * j - 1;
			if (j != number_of_variables - 1)
				cout << ' ';
		}
		if(i!= Fp.size()-1)
			cout << endl;
	}

	//cout << endl;cout << endl;cout << endl;
	//cout << number_of_variables << endl;
	//cout << F.size() << endl;
	//for (i = 0; i < F.size(); i++) {
	//	int x;
	//	for (int j = 0; j < number_of_variables; j++)
	//		cout << F[i].getValue(j + 1) << ' ';
	//	cout << endl;
	//}

}

