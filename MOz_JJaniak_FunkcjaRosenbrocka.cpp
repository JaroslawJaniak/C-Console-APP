#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double f(double x, double y) {
	return pow(1-x,2)+100*pow(y-pow(x,2),2);
}

// pochodne czastkowe 1-go rzedu
double df_dx(double x, double y) {
	return -2*(1-x)-400*x*(y-pow(x,2));
}

double df_dy(double x, double y) {
	return 200*(y-pow(x,2));
}

//pochodne czastkowe 2-go rzedu
double d2f_dxdx(double x, double y) {
	return 2+800*pow(x,2)-400*(y-pow(x,2));
}

double d2f_dxdy(double x, double y) {
	return -400*x;
}

double d2f_dydx(double x, double y) {
	return -400*x;
}

double d2f_dydy(double x, double y) {
	return 200;
}

double detH(double x, double y){
	return (2+800*pow(x,2)-400*(y-pow(x,2)))*200 - (-400*x)*(-400*x);
}

void mo_newton_(double(*df_dx)(double,double), 
			 double(*df_dy)(double,double),
			 double(*d2f_dxdx)(double,double),
			 double(*d2f_dxdy)(double,double),
			 double(*d2f_dydx)(double,double),
			 double(*d2f_dydy)(double,double),
			 double x_0, double y_0, double eps) {
	
    int c = 0;
    double df = sqrt(pow(df_dx(x_0, y_0),2) + pow(df_dy(x_0, y_0),2));
   
	while(df>eps)	{
		
	cout<<"\ndetH = "<<detH(x_0,y_0)<<endl<<endl;
    cout<<"\ndf_dx(x_0, y_0) = "<<df_dx(x_0, y_0)<<endl;
    cout<<"\ndf_dy(x_0, y_0) = "<<df_dy(x_0, y_0)<<endl;
    cout<<"\nd2f_dxdx(x_0, y_0) = "<<d2f_dxdx(x_0, y_0)<<endl;
    cout<<"\nd2f_dxdy(x_0, y_0) = "<<d2f_dxdy(x_0, y_0)<<endl;
    cout<<"\nd2f_dydx(x_0, y_0) = "<<d2f_dydx(x_0, y_0)<<endl;
    cout<<"\nd2f_dydy(x_0, y_0) = "<<d2f_dydy(x_0, y_0)<<endl;
		
		//---GRADIENT---
		double d0 = df_dx(x_0, y_0);
		double d1 = df_dy(x_0, y_0);
		
		//wartosc bezwgledna gradientu funkcji f(x1,x2)
		df = sqrt(pow(df_dx(x_0, y_0),2) + pow(df_dy(x_0, y_0),2));
		
		//---odwrotnosc HESJANU---
		double h0 = (1/detH(x_0,y_0))*d2f_dydy(x_0, y_0);
		double h1 = -(1/detH(x_0,y_0))*d2f_dydx(x_0, y_0);
		double h2 = -(1/detH(x_0,y_0))*d2f_dxdy(x_0, y_0);
		double h3 = (1/detH(x_0,y_0))*d2f_dxdx(x_0, y_0);
		
			x_0 = x_0 - (h0*d0+h1*d1);
			y_0 = y_0 - (h2*d0+h3*d1);
			c++;
	
		cout<<c<<". x_0 = "<<x_0<<" y_0 = "<<y_0<<" f(x,y) = "<<f(x_0,y_0)<<endl;		
	}
	
	cout << "\n_____________________________________________________\n";
	cout<<"\nWYNIK:\n";
	cout<<"   x_0 = "<<x_0<<", y_0 = "<<y_0<<" f(x,y) = "<<f(x_0,y_0)<<endl;
	cout<<"   liczba iteracji: "<<c<<endl;
	
}

int main()
{
	double x_0 = 5., y_0 = 5., eps = 0.001;
	
	cout<<"DANE WEJSCIOWE:\n";
	cout<<"   x0 = "<<x_0<<", y0 = "<<y_0<<", eps = "<<eps;
	cout << "\n_____________________________________________________\n\n";
	mo_newton_(df_dx, df_dy, d2f_dxdx, d2f_dxdy, d2f_dydx, d2f_dydy, x_0, y_0, eps);
	
	cout << endl;

	system("PAUSE");
	return 0;
}



