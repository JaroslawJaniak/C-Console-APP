#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
//Jaroslaw Janiak
//2018_ASD2

void zamien(int X[], int i, int k);

int main(int argc, char *argv[])
{

    
int k=0;
cin>>k; 
    
while(k>=1){
	
int m=0; 
cin>>m; 
int *X=new int [m];
X[0] = m;

for(int i =1;i<=X[0];i++){
cin>>X[i];}


while(X[0]>=2){

	for (int i = 2; i <= X[0]; i = i+2) {
		int q = floor(i / 2);

		if (X[i] > X[q]) {
			zamien(X, i, q);
			i = 0;
		}

		
		else if (X[i + 1] > X[q] && i + 1 <= X[0]) {
				zamien(X, i + 1, q);
				i = 0;
			}
		

	
	}
	
for(int i =1;i<=X[0];i++){
cout<<X[i];}
cout<<endl;

zamien(X, 1, X[0]);
X[0]=X[0]-1;
}

for(int i =1;i<=m;i++){
cout<<X[i];}
cout<<endl<<endl;

k--;
}

return 0;
}

void zamien(int X[], int i, int k){
	int w=X[i];
    X[i]=X[k];
    X[k]=w;
}
