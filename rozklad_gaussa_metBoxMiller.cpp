#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>

//JAROSLAW JANIAK
//WFiIS_2019

using namespace std;

//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));
	
    int nk = 40; //liczba klas histogramu
    int np = 10000;
    
    int *N = new int[nk];
    for(int k=0; k<nk; k++) N[k]=0;
	
	//------------------------------------------------------------------------------------------------------
	double sigma = 1.;
	double mi = 0.;
	
	double xd = 0., xg = 0.;
	double q1 = 0., q2 = 0.; //kontener na zmienne losowe
	double z1 = 0., z2 = 0.; //zmienne metody Boxa-Millera

	double R = 0.0, fi = 0.;
	
	xd = -4*sigma, xg = 4*sigma;
	
	cout<<"sigma: "<<sigma<<", mi: "<<mi<<endl<<endl;
	cout<<"xd: "<<xd<<", xg: "<<xg<<endl<<endl;
	cout<<"liczba klas: "<<nk<<endl<<endl;
	cout<<"szerokosc klasy: "<<(xg-xd)/double(nk)<<endl<<endl;
	double h = (xg-xd)/double(nk);
    
    
    
    
    //--TWORZYMY HISTOGRAM--//
	for(int j = 0; j<np; j++) 
	{
		
		q1 = (double (rand()) / RAND_MAX);
		q2 = (double (rand()) / RAND_MAX);
		
		R = sqrt(-2 * log(q1));
		fi = 2 * M_PI * q2;
		
		z1 = R * cos(fi); 
		z2 = R * sin(fi);
		
		//bierzeny po uwagê tylko z1, tylko ona daje obraz rozk³adu normalnego
		int k = int (floor(((z1 * sigma + mi)-xd)/h));
		N[k]++;
	}

    cout<<"("<<nk<<" klas)"<<endl<<endl;
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
		
		cout<<"\njedna kreska to: "<<int (7+floor(K/80))<<" zliczen"<<endl;
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
