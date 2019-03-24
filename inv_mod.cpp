#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <string.h>
#include <cmath>
#include <ctime>
#include <sstream>

using namespace std;

long long int inv_mod(long long int a, long long int n){
	
	long long int s0 = 0, s1 = 0, s = 0;
	long long int r0 = 0, r1 = 0, r = 0;
	long long int q = 0;
	
	
	if(a < n){
		r0 = n;
		r1 = a;
		
		s0 = 0;
		s1 = 1;
	}
	else{
		r0 = a;
		r1 = n;
		
		s0 = 1;
		s1 = 0;
	}
	
	//cout << r0 <<" - "<< s0 << endl;
	//cout << r1 <<" - "<< s1 << endl;
	
	while(r != 1){
	
		q = ceil(r0/r1);
		r = r0%r1;
		s = s0 - q * s1;
		
		r0 = r1, r1 = r;
		s0 = s1, s1 = s;
		
		//cout <<"q: "<< q <<" r: "<< r <<" s: "<< s << endl;
		
		if(r == 0) break;	
	}
	
	if(r == 1) {
	return s;
	}
	else{
		return 0;
	}	
}

unsigned long pow_mod(unsigned long a,unsigned long k, unsigned long n){

    unsigned long x = 1;

    for(int i = 0; i<k; i++){
        x = (x * a%n )%n;
    }

    
    return x;
}


int main()
{
	long long int a = 11, n = 220;
	
	cout<<"inv: "<<inv_mod( a, n)<<endl;

	string tekst_str = "zloty lisc";
	string str;
	
	cout << "\nsize():" << tekst_str.size() << endl;
	cout << "lenght():" << tekst_str.length() << endl;
		
	cout<<"\ntekst:\n";
	cout<<tekst_str;
	
	cout<<"\n\ntekst (liczbowo):\n";
	for (int s = 0; s < tekst_str.size(); s++) cout<<tekst_str[s]*1<<" ";
	
	long long int p = 23, q = 11; n = p*q;
	long long int f_n = (p-1)*(q-1);
	
	long long int e = 17, d = 0;
	
	long long int m0, c0;
	
	d = inv_mod(e, f_n);
	
	long long int* m = new long long int[tekst_str.size()];
	long long int* c = new long long int[tekst_str.size()];
	
	cout <<"\n\nszyfracja: "<<endl;
	for (int s = 0; s < tekst_str.size(); s++) {
		
		c[s] = pow_mod(tekst_str[s], e, n);
		cout << c[s] <<" ";
	}
	
	cout<<endl;
	
	
	char x;
	cout <<"\n\ndeszyfracja: "<<endl;
	for (int s = 0; s < tekst_str.size(); s++) {
		
		m[s] = pow_mod(c[s], d, n);
		x = m[s];
		
		cout << x;	
	}
	
	cout <<"\n\ndeszyfracja (liczbowo): "<<endl;
	for (int s = 0; s < tekst_str.size(); s++) {
		
		m[s] = pow_mod(c[s], d, n);
		
		cout << m[s]<<" ";	
	}
	
	cout<<endl<<endl;
	
	cout <<"---------------------------------------";
	cout <<"\np: "<< p <<" q: "<< q <<endl;
	cout <<"\nn: "<< n <<" f_n: "<< f_n <<endl;
	cout <<"\ne: "<< e <<" d: "<< d <<endl;
	cout <<"---------------------------------------";
	cout<<endl<<endl;
	
	/*
	m0 = 1;
	for (int s = 0; s < 100; s++) {
		cout <<"\nszyfracja (dla m = "<<m0<<"): "<<endl;
		c0 = pow_mod(m0, e, n);
		cout<<"  c: "<< c0 <<endl;
		
		cout <<"\ndeszyfracja (dla c = "<<c0<<"): "<<endl;
		m0 = pow_mod(c0, d, n);
		cout <<"  m: "<< m0 <<endl;
		
		m0++;
		
	}
	*/
	
	

	system("PAUSE");
	return 0;
}

