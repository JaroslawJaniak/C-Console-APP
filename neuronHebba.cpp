// zad1_perceptron1.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//


#include <iostream>
#include <math.h>

using namespace std;


int main() {

	double l1[13] = { 1,1,-1,1,1,-1,1,1,-1,1,1,-1,1 }, l2[13] = { -1,1,-1,-1,-1,-1,1,1,-1,1,1,-1,1 };

	double d[2] = { 1.,-1.};
	double E[2] = { 0., 0.};

	double w[13];
	for (int j = 0; j < 13; j++) w[j] = 0;

	double y;
	 y = 0.;

	double s = 0.;

	double yq = 0.;
	double beta = 0.5, eta = 0.5, E_ = 0., dE = 0.0000001;

	do {


		for (int i = 0; i < 13; i++) {

			s = s + l1[i] * w[i];

		}
		//cout << "s: " << s << endl;

		y = (1 - exp(-beta * s)) / (1 + exp(-beta * s));
		//cout << "y: " <<y<< endl;

		for (int j = 0; j < 13; j++) w[j] = w[j] + eta * d[0] * l1[j];

		E[0] = 0.5*(y - d[0])*(y - d[0]);
		//cout << "E[0]: " << E[0] << endl;


		
		s = 0.;

		for (int i = 0; i < 13; i++) {

			s = s + l2[i] * w[i];

		}
		//cout << "s: " << s << endl;

		y = (1 - exp(-beta * s)) / (1 + exp(-beta * s));
		//cout << "y: " <<y<< endl;

		for (int j = 0; j < 13; j++) w[j] = w[j] + eta * d[1] * l2[j];

		E[1] = 0.5*(y - d[1])*(y - d[1]);
		//cout << "E[1]: " << E[1] << endl;
		
		s = 0.;

		E_ = E[0] + E[1];

		cout << "E_: " << E_ << endl;

	} while (E_>dE);

	s = 0.;


	for (int i = 0; i < 13; i++) s = s + l1[i] * w[i];
	cout << "s1: " << s << endl;
	y = (1 - exp(-beta * s)) / (1 + exp(-beta * s));
	cout << "y1: " << y << endl;

	s = 0.;

	for (int i = 0; i < 13; i++) s = s + l2[i] * w[i];
	cout << "s2: " << s << endl;
	y = (1 - exp(-beta * s)) / (1 + exp(-beta * s));
	cout << "y2: " << y << endl;

	//for (int i = 0; i < 13; i++) cout << "w[" << i << "] = " << w[i] <<endl;

	system("pause");

	return 0;
}


