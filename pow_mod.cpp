#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

unsigned long pow_mod(unsigned long a,unsigned long k, unsigned long n){

    unsigned long x = 1;

    for(int i = 0; i<k; i++){
        x = (x * a%n )%n;
    }

    cout << "pow_mod:" << x << endl;
    return x;


}

unsigned long pow_mod_fast(unsigned long a,unsigned long k, unsigned long n){

    vector <unsigned long> T;
	
	unsigned long x = 1;
    int c = 0;
    unsigned long t = k;

    for(int i = 0; pow(2,i)<=t; i++){
    	
		T.push_back(k%2);
    	k=floor(k/2);
    	if(k<=0) break;  
    }

    vector <unsigned long> q;
    
    unsigned long p = a%n;
    q.push_back(p);

    for(int i = 2; i<t; i=i*2){
    	p = (p*p)%n;
        q.push_back(p);  
    }
	
	
	for(int i = 0; i<q.size(); i++) x = int(x*pow(q[i],T[i]))%n;
	
    cout << "pow_mod_fast:" << x << endl;
}

void alg_DifHermana(){

    unsigned long p = 0;
    unsigned long g = 0;
    unsigned long a = 0;

    cout << "\npodaj 'p':"; cin>>p;
    cout << "\npodaj 'g':"; cin>>g;
    cout << "\npodaj 'a':"; cin>>a;

    unsigned long A = 0;

    A = pow_mod(g,a,p);

    cout << "\nA: "<<A<<endl;

    unsigned long B = 0;

    cout << "\npodaj 'B':"; cin>>B;

    unsigned long k = 0;

    k = pow_mod(B,a,p);

    cout << "\nk: "<<k<<endl;


}

int main()
{
    
	cout<<"pow_mod(19,1,100);"<<endl;
	pow_mod(19,1,100);
    pow_mod_fast(19,1,100);


    cout<<"\npow_mod(256,40,100);"<<endl;
	pow_mod(256,40,100);
    pow_mod_fast(256,40,100);

    cout<<"\npow_mod(4321,5678,9876);"<<endl;
	pow_mod(4321,5678,9876);
    pow_mod_fast(4321,5678,9876);

    
	cout<<"\npow_mod(3,7,10);"<<endl;
	pow_mod(3,7,10);
	pow_mod_fast(3,7,10);
    
    
    cout<<"\npow_mod(65,7,33);"<<endl;
	pow_mod(65,7,33);
    pow_mod_fast(65,7,33);
    
    cout<<"\npow_mod(32,3,33);"<<endl;
	pow_mod(32,3,33);
    pow_mod_fast(32,3,33);
    
    
    

    alg_DifHermana();

    cout << endl;
    return 0;
}
