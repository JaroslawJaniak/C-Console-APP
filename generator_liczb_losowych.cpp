#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>

//JAROSLAW JANIAK
//WFiIS_2019

using namespace std;

//---------------------------------------------------------------------------------------------------------
int LCG_okres(int a, int c, int m, int x0){
        int x = x0;
		int i = 0;
    do
    {
       x = (a* x + c) % m;
       //x = rand();
       i++;
       if(x == x0) {
       break;
       }
       }
    while(1);
           return i;
    }
    
int LCG_histogram(int a, int c, int m, int x0, int H[], double xd, double xg, int nk, int np){
        int x = x0;
        double y = 0.;
		
    double h = (xg-xd)/double(nk);
    cout<<"xd: "<<xd<<", xg: "<<xg<<endl<<endl;
	cout<<"liczba klas: "<<nk<<endl<<endl;
	cout<<"liczba powtorzen: "<<np<<endl<<endl;
	cout<<"szerokosc klasy: "<<(xg-xd)/double(nk)<<endl<<endl;
	
    x = x0;
    for(int i = 0; i < np; i++){
            x = (a* x + c) % m;
            y = double (x/(m-1.));
            //cout<<"y: "<< y << " " ; 
    int k = int ((y/h));
    H[k]++;
            }
    }
    
int LCG_histogram_x2(int a, int c, int m, int x0, int *X[], double xd, double xg, int nk, int np){
        
		int x = x0;
        double y1 = 0., y2 = 0.;
		
    double h = (xg-xd)/double(nk);
    cout<<"xd: "<<xd<<", xg: "<<xg<<endl<<endl;
	cout<<"liczba klas (nk x nk): "<<nk<<"x"<<nk<<endl<<endl;
	cout<<"liczba powtorzen: "<<np<<endl<<endl;
	//cout<<"szerokosc klasy: "<<(xg-xd)/double(nk)<<endl<<endl;
	
    x = x0;
    for(int i = 0; i < np; i++){
            x = (a* x + c) % m;
            y1 = double (x/(m-1.));
            
            x = (a* x + c) % m;
            y2 = double (x/(m-1.));
            
    		int k1 = int ((y1/h));
    		int k2 = int ((y2/h));
    X[k1][k2]++;
            }
    }
    
int LCG_test_Chi_2(int a, int c, int m, int x0, int N[], double xd, double xg, int nk, int np){
    double chi = 0.;
    double nt = double(np/nk);
    
    cout<<"nt_: "<< nt <<endl;
    
    for(int i = 0; i<nk; i++) {
		//cout<<"(N - nt)/nt: "<< (N[i] - nt)/nt<<",  (N - nt)^2/nt: "<< ((N[i] - nt)/nt)*(N[i] - nt) <<endl;
    	chi = chi + (((N[i] - nt)*(N[i] - nt))/nt);
    	
    }
    
    cout<<"\n   chi^2: "<< chi <<endl;
    }
    
    int LCG_test_Chi_2_x2(int a, int c, int m, int x0, int *N[], double xd, double xg, int nk, int np){
    double chi = 0.;
    double nt = double(np/(nk*nk));
    
    cout<<"\nnt_: "<< nt <<endl;
    
    for(int k = 0;k<nk;k++){
    	for(int l = 0;l<nk;l++){
			chi = chi + (((N[k][l] - nt)*(N[k][l] - nt))/nt);
			} 
	}
    
    cout<<"\n   chi^2: "<< chi <<endl;
    }
//---------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));
	
    int nk = 10, nw = 10; //liczba klas histogramu
    int np = 1000;
    
    int *N = new int[nk];
    for(int k=0; k<nk; k++) N[k]=0;
    
    int **M=new int *[nw];
    for(int i = 0;i<nw;i++) M[i]=new int [nk];
    
    for(int k = 0;k<nw;k++){
    for(int l = 0;l<nk;l++)M[k][l] = 0;}
	
	//------------------------------------------------------------------------------------------------------
	int a = 43, c = 64, m = 5011 , x = 0, x0 = 4;
	int i = 0;
	
	double xd = 0., xg = 1.;
	double y = 0.;

    //cout<<np<<" powtorzen"<<endl<<endl;
    //cout<<"LICZNOSC KLAS:"<<endl<<endl;
    
    //--ZAWARTOSC HISTOGRAMU--//
    
    
    cout<<"---------------------------------------------------------\n";
    cout<<"LCG_okres: "<< LCG_okres(a, c, m, x0) <<endl;
    
    for(int k=0; k<nk; k++) N[k]=0;
    cout<<"---------------------------------------------------------\n";
    LCG_histogram(a, c, m, x0, N, xd, xg, nk, np);
    	for(int k=0; k<nk; k++) cout<<N[k]<<" "; 
    	cout<<endl<<endl;
    LCG_test_Chi_2( a, c, m, x0, N, xd, xg, nk, np);
    
    cout<<"---------------------------------------------------------\n";
    for(int k=0; k<nk; k++) N[k]=0;
    	np = 2000;
    LCG_histogram(a, c, m, x0, N, xd, xg, nk, np);
    	for(int k=0; k<nk; k++) cout<<N[k]<<" "; 
    	cout<<endl<<endl;
    LCG_test_Chi_2( a, c, m, x0, N, xd, xg, nk, np);

    //--RYSUJEMY HISTOGRAM--//
    //------------------------------------------------------------------------------------------------------
    cout<<"\n-- HISTOGRAM (wykres) - np = 2000 --"<<endl;
    int K=N[0];
	int jk=0;
	while(jk<nk) {
		if(K<N[jk]) K=N[jk];
		jk++;
	}
	
    if(K>120) {
		
		cout<<"\njedna kreska to: "<<int (7+floor(K/80))<<" zliczen"<<endl;
		for(int i=0; i<nk; i++) {
			if(i == 0) cout<<"---------------------------------------------------------\n";
			
			for(int j=0; j<N[i]; j++) {
				if(j%int (7+floor(K/120))==0) cout<<"_";
			}
			
			if(i == nk - 1) cout<<"\n\n---------------------------------------------------------";
			cout<<endl;
		}
	} 
    else {
    for(int i=0; i<nk; i++) {
    	if(i == 0) cout<<"---------------------------------------------------------\n";
			for(int j=0; j<N[i]; j++) {
				cout<<"_";
			}
		if(i == nk - 1) cout<<"\n\n---------------------------------------------------------\n";
			cout<<endl;
		}
}
    //------------------------------------------------------------------------------------------------------
    //--KONIEC RYSOWANIA--//
    
    
	//--HISTOGRAM 10x10--//
	cout<<"\n-- HISTOGRAM 10x10 --"<<endl;
	cout<<"\n-- test chi^2 (dwa wymiary) --\n"<<endl;
	np = 1000;
    LCG_histogram_x2(a, c, m, x0, M, xd, xg, nk, np);
    for(int k = 0;k<nw;k++){
    for(int l = 0;l<nk;l++) {cout<<M[k][l]<<" ";} cout<<endl;}	
    
    LCG_test_Chi_2_x2( a, c, m, x0, M, xd, xg, nk, np);

	cout<<endl<<endl;

	cout<<endl<<endl;
		
	system("PAUSE");
	return EXIT_SUCCESS;
}
