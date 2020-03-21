#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

//funckcja f(x1,x2)
double f(double x1, double x2) {
	return pow((x1 - 1),4)+2*pow((x2 - 2), 4);
}

void steepestDescentHJ(double(*f)(double, double), double x_0, double y_0, double s1[], double s2[], int nk, double e, double alpha) {

	double x_1, x_2;
	double f_sADD, f_sSUB, f_s0;
	bool patternMove = false;
	bool avoidedStep = false;
	
	double *x0_ = new double[nk];
	
	
	double *xADD_s1 = new double[nk];
	double *xSUB_s1 = new double[nk];
	
	double *xADD_s2 = new double[nk];
	double *xSUB_s2 = new double[nk];
	
	x0_[0] = x_0;
	x0_[1] = y_0;
	
	f_s0 = f(x0_[0],x0_[1]);
	int c = 0;
	
	while(f_s0>0.0000001){
		cout<<c+1<<"."<<endl;
		cout<<"   x0_(x0_1 = "<<x0_[0]<<", x0_2 = "<<x0_[1]<<", f() = "<<f(x0_[0],x0_[1])<<")\n\n";
			
		for(int i =0;i<nk;i++){
			xADD_s1[i] = x0_[i] + e*s1[i];
			xSUB_s1[i] = x0_[i] - e*s1[i];
		}
		
		f_sADD = f(xADD_s1[0],xADD_s1[1]);
		f_sSUB = f(xSUB_s1[0],xSUB_s1[1]);
		
		if(f_sADD<f_sSUB && f_sADD<f_s0){
			for(int i =0;i<nk;i++) x0_[i] = xADD_s1[i];
			patternMove = true;
			
		}
		else if(f_sADD>f_sSUB && f_sSUB<f_s0){
			for(int i =0;i<nk;i++) x0_[i] = xSUB_s1[i];
			patternMove = true;
		}
		else{
			avoidedStep = true;
		}
		
		
		if(avoidedStep == true) {
			cout<<"\n   *no move in s1 direction"<<endl;
			avoidedStep = false;
		}
		else{
			cout<<"   s1->["<<x0_[0]<<", "<<x0_[1]<<", "<<f(x0_[0],x0_[1])<<"]";
			avoidedStep = false;
		}
		
		
		f_s0 = f(x0_[0],x0_[1]);
		
		for(int i =0;i<nk;i++){
			xADD_s2[i] = x0_[i] + e*s2[i];
			xSUB_s2[i] = x0_[i] - e*s2[i];
		}
		
		f_sADD = f(xADD_s2[0],xADD_s2[1]);
		f_sSUB = f(xSUB_s2[0],xSUB_s2[1]);
		
		if(f_sADD<f_sSUB && f_sADD<f_s0){
			for(int i =0;i<nk;i++) x0_[i] = xADD_s2[i];
			patternMove = true;
		}
		else if(f_sADD>f_sSUB && f_sSUB<f_s0){
			for(int i =0;i<nk;i++) x0_[i] = xSUB_s2[i];
			patternMove = true;
		}
		else{
			avoidedStep = true;
		}
		
		f_s0 = f(x0_[0],x0_[1]);
		
		
		if(avoidedStep == true){
			cout<<"\n   *no move in s2 direction"<<endl;
			avoidedStep = false;
		}
		else{
			cout<<"\n   s2->["<<x0_[0]<<", "<<x0_[1]<<", "<<f(x0_[0],x0_[1])<<"]";
			avoidedStep = false;
		}
		
		if(!patternMove) {
			e = e*alpha;
			cout<<"\ne = "<<e<<endl;
			patternMove = false;
		}
		else{
			patternMove = false;
		}
		
		cout << "\n-------------------------------------\n";
		c++;
	}
}

int main()
{
	double x_0 = 7.52949, y_0 = 5.60592, e = 1., alpha = 0.5;
	int nw = 2, nk =2;
	
    double *s1 = new double[nk];
    double *s2 = new double[nk];
    
    s1[0]=1; s1[1]=0;
    s2[0]=0; s2[1]=1;
    
    cout << "\n   Metoda Hooke'a-Jeevesa\n";
	cout << "\nprzypadek testowy nr 1 zgodny z wykladem 'mo_w3_h.pdf'\n";
	cout<<"s1["<<s1[0]<<", "<<s1[1]<<"]\n";
    cout<<"s2["<<s2[0]<<", "<<s2[1]<<"]\n";
    cout<<"f(x1,x2) = (x1 - 1)^4 + 2*(x2 - 2)^4\n";
    cout << "\n_____________________________________________________\n";
    cout<<"\nDANE WEJSCIOWE:\n";
    cout<<"   (x0 = "<<x_0<<", y0 = "<<y_0<<", e = "<<e<<", alpha = "<<alpha<<")\n";
    cout<<"   s1["<<s1[0]<<", "<<s1[1]<<"]\n";
    cout<<"   s2["<<s2[0]<<", "<<s2[1]<<"]\n";
    cout << "\n_____________________________________________________\n\n";

	steepestDescentHJ(f, x_0, y_0, s1, s2, nk,e, alpha);
	
	double *s3 = new double[nk];
    double *s4 = new double[nk];
    
    s3[0]=sqrt(2)/2.; s3[1]=sqrt(2)/2.;
    s4[0]=sqrt(2)/2.; s4[1]=-sqrt(2)/2.;
    
    cout << "\n_____________________________________________________\n\n";
    cout << "\n_____________________________________________________\n\n";
	cout << "\n   Metoda Hooke'a-Jeevesa\n";
	cout << "\nprzypadek testowy nr 2 zgodny z wykladem 'mo_w3_h.pdf'\n";
	cout<<"s1["<<s3[0]<<", "<<s3[1]<<"]\n";
    cout<<"s2["<<s4[0]<<", "<<s4[1]<<"]\n";
    cout<<"f(x1,x2) = (x1 - 1)^4 + 2*(x2 - 2)^4\n";
    cout << "\n_____________________________________________________\n";
    cout<<"\nDANE WEJSCIOWE:\n";
    cout<<"   (x0 = "<<x_0<<", y0 = "<<y_0<<", e = "<<e<<", alpha = "<<alpha<<")\n";
    cout<<"   s1["<<s3[0]<<", "<<s3[1]<<"]\n";
    cout<<"   s2["<<s4[0]<<", "<<s4[1]<<"]\n";
    cout << "\n_____________________________________________________\n\n";
    
	steepestDescentHJ(f, x_0, y_0, s3, s4, nk,e, alpha);

	cout << endl;

	system("PAUSE");
	return 0;
}



