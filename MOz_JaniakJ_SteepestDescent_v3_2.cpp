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

//funckcja f(x1,x2)
double f(double x1, double x2) {
	increment();
	return (x1 - 1)*(x1 - 1) + (x2 - 2)*(x2 - 2) + 3;
}

//pochodna czastkowa funkcji f(x1,x2) wzgledem zmiennej x1
double df1(double x1) {
	increment();
	return 4 * (x1 - 1);
}

//pochodna czastkowa funkcji f(x1,x2) wzglêdem zmiennej x2
double df2(double x2) {
	increment();
	return 2 * (x2 - 2);
}

void steepestDescent(double(*f)(double, double), double(*df1)(double), double(*df2)(double), double x0, double y0, double eps) {

	double x1 = 0., x2 = 0, f_lambda = 0.;
	double x1_0 = 0., x2_0 = 0;
	double dx1 = 0., dx2 = 0;
	double q = 0., df = 0.;
	int i = 0;

	x1_0 = x0;
	x2_0 = y0;
	
	double tmp = 0.;

	do {
		dx1 = df1(x1_0);
		dx2 = df2(x2_0);
		f_lambda = f(x1_0,x2_0);

		for (double lambda = -0.1; lambda > -1.; lambda -= 0.1) {
			//szczególy patrz wyklad metody optymalizacji - mo_w2_h.pdf - Algorytm Gradientowy
			q = f(x1_0 + (lambda)*dx1, x2_0 + (lambda)*dx2);
			
			if (f_lambda < q) {
				x1_0 = x1_0 + (lambda + 0.1)*dx1;
				x2_0 = x2_0 + (lambda + 0.1)*dx2;
				break;
			}
			else{
				f_lambda = q;
			}	
		}
		df = sqrt(dx1*dx1 + dx2*dx2);
		i++;
	}
	//while (df > eps);
	while (fabs(q-f_lambda) > eps);
	
	cout << "   eps = " << eps << "\nf(x1,x2) = " << f_lambda << "; (x1 = " << x1_0 << ", x2 = " << x2_0 << ");" << endl;
	cout << "iteration_num = " << i << "; calls_num = " << calls_num <<endl<<endl;
	calls_num = 0;
}

int main()
{
	double x0 = 5., y0 = 5., eps = 0.01;
	
	cout<<"\nDANE WEJSCIOWE:\n";
	cout << "   x0 = " << x0 << ", y0 = " << y0 << endl;
	cout<<"   f(x1,x2) = (x1 - 1)^2 + (x2 - 2)^2 + 3\n";
	cout<<"\n   (warunkiem przerwania jest test stacjonarnosci)\n";
	cout << "\n_____________________________________________________\n\n";

	for(double eps = 0.1; eps>0.0001;eps=eps*0.1){
		steepestDescent(f, df1, df2, x0, y0, eps);
	}
	
	cout << endl;
	system("PAUSE");
	return 0;
}



