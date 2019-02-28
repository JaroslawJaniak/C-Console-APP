#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

void warstwa_net_ (double beta, double eta, double *E[], int m, double d1, double d2, double *x, double *w[], double *o){
	
	double s0 = 0., s1 = 0.;
	double s[2] = {0.,0.};
	
	for (int k = 0; k < 2; k++){
		for (int i = 0; i < 13; i++) s[k] = s[k] + x[i] * w[k][i];
	}
	
	for (int k = 0; k < 2; k++) o[k] = (1 - exp(-beta * s[k])) / (1 + exp(-beta * s[k]));
	
	
		for (int i = 0; i < 13; i++) w[0][i] = w[0][i] + 0.5 * eta * (d1 - o[0]) * (1 - o[0]*o[0]) * x[i];
		for (int i = 0; i < 13; i++) w[1][i] = w[1][i] + 0.5 * eta * (d2 - o[1]) * (1 - o[1]*o[1]) * x[i];
	
		
		E[0][m] = 0.5*(d1 - o[0])*(d1 - o[0]);
		E[1][m] = 0.5*(d2 - o[1])*(d2 - o[1]);
}

int main() {
	
	srand((unsigned)time(NULL));

	double 
	x1[13] = { 1,1,-1,1,1,-1,1,1,-1,1,1,-1,1 }, 
	x4[13] = { -1,1,-1,-1,-1,-1,1,1,-1,1,1,-1,1 },
	x7[13] = { -1,-1,-1,1,1,-1,1,1,-1,1,1,-1,1 };
	
	double **w_=new double *[2];
    for(int i =0;i<13;i++)
    {
        w_[i]=new double [13];
            }
            
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 13; j++) w_[i][j] = (double (rand()) / RAND_MAX);
	}
	
	double d_[3][2] = {{ -1., 1.},{ -1., -1.},{ 1., 1.}};
	double o[] = {0,0};
	
	double **E=new double *[2];
    for(int i =0;i<3;i++)
    {
        E[i]=new double [3];
            }

	double beta = 0.5, eta = 0.5, E_1 = 0., E_2 = 0., E_max = 0.0001;

	int m = 0;
	
	//=====================================================================================
	do {
		//--X1--//
		warstwa_net_ ( beta, eta, E, 0, d_[0][0], d_[0][1], x1, w_, o);
		
		//--X4--//
		warstwa_net_ ( beta, eta, E, 1, d_[1][0],d_[1][1], x4, w_, o);
		
		//--X7--//
		warstwa_net_ ( beta, eta, E, 2, d_[2][0], d_[2][1], x7, w_, o);
		
		//--neuron_1--//
		E_1 = E[0][0] + E[0][1] + E[0][2];
		
		//--neuron_2--//
		E_2 = E[1][0] + E[1][1] + E[1][2];
		
		cout << "E_1: " << E_1 << ", E_2: " << E_2<< endl;
		

	} while (E_1 > E_max && E_2 > E_max);

	double s[2] = {0.,0.};
	
	cout<<"wartosci oczekiwane:"<<endl;
	cout << "X1 - d1: " << d_[0][0] << ", d2: " << d_[0][1]<< endl;
	cout << "X4 - d1: " << d_[1][0] << ", d2: " << d_[1][1]<< endl;
	cout << "X7 - d1: " << d_[2][0] << ", d2: " << d_[2][1]<< endl;
	
	//--X1--//
	//======================================================================
	s[0] = 0., s[1] = 0.;
	o[0] = 0., o[1] = 0.;
	for (int k = 0; k < 2; k++){
		for (int i = 0; i < 13; i++) s[k] = s[k] + x1[i] * w_[k][i];
	}
	
	for (int k = 0; k < 2; k++)
	o[k] = (1 - exp(-beta * s[k])) / (1 + exp(-beta * s[k]));
	
	cout << "\nX1 - o1: " << o[0] << ", o2: " << o[1]<< endl;
	
	//--X4--//
	//======================================================================
	s[0] = 0., s[1] = 0.;
	o[0] = 0., o[1] = 0.;
	for (int k = 0; k < 2; k++){
		for (int i = 0; i < 13; i++) s[k] = s[k] + x4[i] * w_[k][i];
	}
	
	for (int k = 0; k < 2; k++)
	o[k] = (1 - exp(-beta * s[k])) / (1 + exp(-beta * s[k]));
	
	cout << "X4 - o1: " << o[0] << ", o2: " << o[1]<< endl;
	
	//--X7--//
	//======================================================================
	s[0] = 0., s[1] = 0.;
	o[0] = 0., o[1] = 0.;
	for (int k = 0; k < 2; k++){
		for (int i = 0; i < 13; i++) s[k] = s[k] + x7[i] * w_[k][i];
	}
	
	for (int k = 0; k < 2; k++)
	o[k] = (1 - exp(-beta * s[k])) / (1 + exp(-beta * s[k]));
	
	cout << "X7 - o1: " << o[0] << ", o2: " << o[1]<< endl;



	system("pause");

	return 0;
}


