#include <iostream>
#include <math.h>

using namespace std;

void neuron_sigma (double beta, double eta, double E[], double d[], int k, double *x, double *w, double &y, double &dy){
	
	y = 0., dy =0.;
	double s = 0.;
	
	for (int i = 0; i < 5; i++) s = s + x[i] * w[i];
	
	y = (1 - exp(-beta * s)) / (1 + exp(-beta * s));
	dy = beta * (1 - y * y);
	
	for (int j = 0; j < 5; j++) w[j] = w[j] + eta * (d[k] - y) * dy * x[j];
	
	E[k] = 0.5*(d[k] - y)*(d[k] - y);
}

int main() {

	double 
	x1[5] = {1.,-2.,0.,-1., 1.}, 
	x2[5] = {0.,1.5,-0.5,-1., 1.},
	x3[5] = {-1.,1.,0.5,-1., 1.};
	
	double x[3][5] = {{1.,-2.,0.,-1., 1.},{0.,1.5,-0.5,-1., 1.},{-1.,1.,0.5,-1., 1.}};
	
	double d[3] = { -1,-1,1};
	double E[3] = { 0., 0., 0.};

	double w[5];
	for (int j = 0; j < 5; j++) w[j] = 0;

	double y = 0., dy =0.;

	double s = 0.;
	double beta = 0.5, eta = 0.5, E_ = 0., dE = 0.0001;

	int k = 0;
	
	cout << "y1: " << y << endl;

	s = 0., y = 0., dy = 0. ;
	do {

		neuron_sigma (beta, eta, E, d, 0, x1, w, y, dy);

		neuron_sigma (beta, eta, E, d, 1, x2, w, y, dy);

		neuron_sigma (beta, eta, E, d, 2, x3, w, y, dy);

		E_ = E[0] + E[1] + E[2];

		//cout << "E_: " << E_ << endl;

	} while (E_>dE);

	s = 0., y = 0., dy = 0. ;
	for (int i = 0; i < 5; i++) s = s + x1[i] * w[i];
	y = (1 - exp(-beta * s)) / (1 + exp(-beta * s));
	cout << "y1: " << y << endl;

	s = 0., y = 0., dy = 0. ;
	for (int i = 0; i < 5; i++) s = s + x2[i] * w[i];
	y = (1 - exp(-beta * s)) / (1 + exp(-beta * s));
	cout << "y2: " << y << endl;
	
	s = 0., y = 0., dy = 0. ;
	for (int i = 0; i < 5; i++) s = s + x3[i] * w[i];
	y = (1 - exp(-beta * s)) / (1 + exp(-beta * s));
	cout << "y3: " << y << endl;


	system("pause");

	return 0;
}


