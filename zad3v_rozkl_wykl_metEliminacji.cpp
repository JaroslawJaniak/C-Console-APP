#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>

//JAROSLAW JANIAK
//WFiIS_2019

using namespace std;

//---------------------------------------------------------------------------------------------------------
void Hist(double xd, double xg, int n, int *H, double x) {

	double h = (xg-xd)/double(n);

	int k = int (floor((x-xd)/h));
	if(k<0)k=0;
	if(k>n+1)k=n+1;

	H[k]++;
}


//---------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));
	
    int nk = 20; //liczba klas histogramu
    int np = 1000;
    
    int *N = new int[nk];
    for(int k=0; k<nk; k++) N[k]=0;
	
	//------------------------------------------------------------------------------------------------------
	double lambda = 2.;
	double teta = 5.;
	
	double xd = 0., xg = 0.;
	double xq = 0.0, yq = 0.0;
	double x_max = 0.0; double y_max = 0.0;
	double f_ = 0.0;
	
	x_max = teta - (lambda * log(1/100.));
	y_max = 1/lambda;
	
	cout<<"x_max: "<<x_max<<endl<<endl;
	cout<<"y_max: "<<y_max<<endl<<endl;
	
	f_ = (1/lambda) * exp(-1 * ((x_max - teta)/lambda));
	
	cout<<"f(x_max): "<<f_<<endl<<endl;
	cout<<"x_max - teta: "<<x_max - teta<<endl<<endl;
	
	
	xd = teta, xg = 5 * teta;
	cout<<"xd: "<<xd<<", xg: "<<xg<<endl<<endl;
	cout<<"liczba klas: "<<nk<<endl<<endl;
	cout<<"szerokosc klasy: "<<(xg-xd)/double(nk)<<endl<<endl;
	double h = (xg-xd)/double(nk);
    
    //--TWORZYMY HISTOGRAM--//
	for(int j = 0; j<np; j++) 
	{
		xq = (double (rand()) / RAND_MAX)*(x_max - teta) + teta;
		yq = (double (rand()) / RAND_MAX)*(y_max);
		
		if(yq <= (1/lambda) * exp(-(xq - teta)*(1/lambda)))
		{
			int k = int (floor((xq-xd)/h));
			N[k]++;
		}
	}

    cout<<"("<<nk<<" klasy)"<<endl<<endl;
    cout<<np<<" powtorzen"<<endl<<endl;
    cout<<"LICZNOSC KLAS:"<<endl<<endl;
    
    //--ZAWARTOSC HISTOGRAMU--//
    for(int k=0; k<nk; k++) cout<<N[k]<<" "; 
    cout<<endl;
    
    //--RYSUJEMY HISTOGRAM--//
    //------------------------------------------------------------------------------------------------------
    int K=N[0];
	int jk=0;
	while(jk<nk) {
		if(K<N[jk]) K=N[jk];
		jk++;
	}
	
    if(K>120) {
		
		cout<<"\njedna gwaizdka to: "<<int (7+floor(K/80))<<" zliczen"<<endl;
		for(int i=0; i<nk; i++) {
			if(i == 0) cout<<"------------------------------------------------------------------\n";
			
			for(int j=0; j<N[i]; j++) {
				if(j%int (7+floor(K/120))==0) cout<<"_";
			}
			
			if(i == nk - 1) cout<<"\n\n------------------------------------------------------------------";
			cout<<endl;
		}
	} 
    else {
    for(int i=0; i<nk; i++) {
    	if(i == 0) cout<<"------------------------------------------------------------------\n";
			for(int j=0; j<N[i]; j++) {
				cout<<"_";
			}
		if(i == nk - 1) cout<<"\n\n------------------------------------------------------------------";
			cout<<endl;
		}
}
    //------------------------------------------------------------------------------------------------------
    //--KONIEC RYSOWANIA--//
    
	cout<<endl<<endl;

	cout<<endl<<endl;
	
	system("PAUSE");
	return EXIT_SUCCESS;
}
