
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int calls_num = 0;

int increment(){
	calls_num++;
	return calls_num;
}

double f(double x) {
	increment();
	return x*x*x - 9*x*x - 21*x - 15;
}

double f2(double x) {
	//minimum w przedziale(0,6)
	increment();
	return (x-6)*(x+4)*(7*x*x+10*x+24);
}

double f2_d1(double x) {
	//minimum w przedziale(0,6)
	increment();
	return (2*x-2)*(7*x*x+10*x+24) + (x-6)*(x+4)*(14*x+10);
}

//pierwsza pochodna funkcji f(x)
double f_d1(double x) {
	increment();
	return 3*x*x - 18*x - 21;
}

//druga pochodna funkcji f(x)
double f_d2(double x) {
	increment();
	return 6*x - 18;
}

void GS(double(*f)(double), double a, double b, double eps) {

	double x = a;
	double xmin = 0;
	double f_x = 0;
	double f_xe = 0;
	int n = 0;
	
	f_x = f(x);
	while (x <= b) {
		
		f_xe = f(x+eps);
	
		if(f_xe>f_x){
			//cout << "\n   GridSearch:\n";
			cout<< "eps = " << eps << " -> xmin = " << x << "; iteration_num = " << n << "; calls_num = " << calls_num <<endl;
			calls_num = 0;
			break;
		}
		
		f_x = f_xe;
		x+=eps;
		n++;	
	}
}

void GSR(double(*f)(double), double a, double b, double eps, int k, int m) {

	double x = a;
	double xmin = 0;
	double f_x = 0;
	double f_dx = 0;
	double dx = (b - a) / k;
	int n = m;
	
	f_x = f(x);

	while(1){
		f_dx = f(x+dx);
	
		if(f_dx>f_x){
			a = x - dx;
			b = x;
			x = a;
			break;
		}
		
		f_x = f_dx;
		x+=dx;
		n++;
	}
	
	if(dx>eps){
		GSR(f,a,b,eps,k,n);
	}
	else{
		cout<< "eps = " << eps << " -> xmin = " << x << "; iteration_num = " << n << "; calls_num = " << calls_num <<endl;
	calls_num = 0;
	}
}

void falsi_(double(*f)(double), double a, double b, double eps) {

	double x1 = a;
	double f1 = 0.0, fb = 0.0;
	int n = 0;

	//metoda ciêciw
	//poszukiwanie ekstremum/minimum
	//pochodna zadana jest jawnie
	
	fb = f(b);
	f1 = f(x1);
	
	while (fabs(f1) > eps) {
		f1 = f(x1);
		x1 = x1 - f1*((b - x1) / (fb - f1));
		n++;
	}

	//cout << "\n   metoda cieciw (falsi):\n";
	cout<< "eps = " << eps << " -> xmin = " << x1 << "; iteration_num = " << n << "; calls_num = " << calls_num <<endl;
	calls_num = 0;
}

void goldenRatio_v3(double(*f)(double), double a, double b, double eps) {

	double w1 = a, w2 = b, k = 0.0;
	double f1 = 0.0, f2 = 0.0;
	int n = 0;
	calls_num = 0;
	
	k = (sqrt(5.) - 1.) / 2.;
	
	w1 = a + (b - a) * k;
	w2 = b - (b - a) * k;
	f1 =f(w1);
	f2 =f(w2);

do {
		if (f1 < f2 ){
			a = w2;
			w2 = w1;
			w1 = a + (b - a) * k;
			
			f2 = f1;
			f1 =f(w1);
			
		}
		else{
			b = w1;
			w1 = w2;
			w2 = b - (b - a) * k;
			
			f1 = f2;
			f2 =f(w2);
		}
		n++;
	}
while (fabs((b-a)) > eps) ;

	//cout << "\n   metoda zlotego podzialu (Golden Ratio):\n";
	cout<< "eps = " << eps << " -> xmin = " << (b+a)/2<< "; iteration_num = " << n << "; calls_num = " << calls_num <<endl;
	calls_num = 0;
}

int main()
{
	double a = 1., b = 10., eps = 0.01;

	cout<<"\n   f(x1,x2) = x^3 - 9*x^2 - 21*x - 15\n";
	cout << "   (a = " << a << ", b = " << b << ")" <<endl;
	
	cout <<"\n--------------------------------------------------------------"<<endl;
	cout << "\n   GridSearch:\n";
	for(double eps = 0.1; eps>0.0001;eps=eps*0.1){
		GS(f, a, b, eps);
	}
	cout <<"\n--------------------------------------------------------------"<<endl;
	cout << "\n   GridSearch (Rekursja):\n";
	for(double eps = 0.1; eps>0.0001;eps=eps*0.1){
		GSR(f, a, b, eps, 7,0);
	}
	cout <<"\n--------------------------------------------------------------"<<endl;
	cout << "\n   metoda cieciw (falsi):\n";
	for(double eps = 0.1; eps>0.0001;eps=eps*0.1){
		falsi_(f_d1, a, b, eps);	
	}
	
	cout <<"\n--------------------------------------------------------------"<<endl;
	cout << "\n   metoda zlotego podzialu (Golden Ratio - v3):\n";
	for(double eps = 0.1; eps>0.0001;eps=eps*0.1){
		goldenRatio_v3(f, a, b, eps);
	}
	
	
	cout << endl;

	system("PAUSE");
	return 0;
}



