#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <fstream>
#include <cstring>
#include <math.h>

using namespace std;
//Jaroslaw_Janiak_2018_ASD2_27_09_18

unsigned char T[36] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};

void strcopy(char cel[], string zrodlo) {
	int i = 0;
	do {
		cel[i] = zrodlo[i];
	} while (cel[i++] != 0);
}


class T_tekst {
public:
	string tekst_str;
	string file_name;

	T_tekst();
	void read();
	void szyfrowanie();
	void deszyfracja();
	void view_frq();
	void view_tekst();
};

T_tekst::T_tekst() {
	tekst_str = "null";
	
}

void T_tekst::view_tekst() {
	cout<<"\ntekst:\n";
	for (int s = 0; s < tekst_str.size(); s++) cout<<tekst_str[s];
}

void T_tekst::view_frq() {
	
	
	unsigned int frq[36];
	unsigned int count = 0;
	
	//cout<<"\n\nliczba znakow: "<<tekst_str.size()-1<<endl;
	
	
	for(int i =0;i<36;i++) frq[i] = 0;
	
	for(int i=0; i<tekst_str.size();i++){
                for(int j = 0; j< 36;j++){
                    if(tekst_str[i]==T[j]) {
                            frq[j]++; 
                            count++;
							break;
							}
                }
            }
            
    cout<<"\n\nliczba znakow (count): "<<count<<endl;
    
	cout<<endl;
	for(int i =0;i<36;i++) {
		//if(frq[i]!=0) cout<<T[i] <<": "<< (double(frq[i])/(tekst_str.size()-1))*100.<<"%\n";
		if(frq[i]!=0) cout<<T[i] <<": "<< (double(frq[i])/(count))*100.<<"%\n";
}
	
	double q = 0.0;
	
	for(int i =0;i<36;i++) {
		//q = q + (double(frq[i])/(tekst_str.size()-1))*100.;
		q = q + (double(frq[i])/(count))*100.;
	}
	
	cout<<"\nsum: "<<q<<"%"<<endl;
	
	q=0.0;
	
	for(int i =0;i<36;i++) {
		q = q + (frq[i]*(frq[i]-1));
	}
	
	q = q/((tekst_str.size()-1)*(tekst_str.size()-2));
	
	cout<<"\nq: "<<q<<endl;
}

void T_tekst::read() {
	
	
	//zamiana string: 'name_file' na c-string
	char * cstr = new char[file_name.length() + 1];
	strcopy(cstr, file_name);

	//czytanie tekstu
	ifstream file_txt(cstr, std::ios::in);
	tekst_str.clear();
	if (file_txt) {
		while (!file_txt.eof())  tekst_str.push_back(file_txt.get());
	}
	file_txt.close();
	
	
	//zamiana na wilkie litery
	for(int i=0; i<tekst_str.size();i++){
		if (islower(tekst_str[i])) tekst_str[i] = toupper(tekst_str[i]);
	}
	
	//usowanie znaku nowej linii i spacji
	for(int i=0; i<tekst_str.size();i++){
		if (tekst_str[i]=='\n' || tekst_str[i]==' ') tekst_str.erase(i,1);
	}
	
	/*
	//usowanie znakow spoza alfabetu - nie dziala; modyfikuje tekst (???)	
		for(int i=0; i<tekst_str.size();i++){
		 	for(int j =0;j<36;j++){ 
				 	if(tekst_str[i]!=T[j]) tekst_str.erase(i,1); 		
			 }
		}
 	*/
	
}

void T_tekst::szyfrowanie() {

	
	int k = 0;
	cout<<"\npodaj klucz: "; cin>>k;

    char *a = new char[tekst_str.size()];

            for(int i=0; i<tekst_str.size();i++){
                for(int j = 0; j< 36;j++){
                    if(tekst_str[i]==T[j]) {
                            j=(k+j)%36;
                            a[i] = T[j]; break;
							}
							else{
							a[i] = tekst_str[i];
							}
							
                }
            }
            
    for(int i=0; i<tekst_str.size();i++)  tekst_str[i] = a[i];
	cout<<"\ntekst zaszyfrowano! (plik: s_out.txt)\n\n";
	
	ofstream file_out("s_out.txt");
	for (int s = 0; s < tekst_str.size(); s++) file_out << tekst_str[s];
	file_out.close();

}

void T_tekst::deszyfracja(){
	
	
	int k = 0;
	cout<<"\npodaj klucz: "; cin>>k;

    char *a = new char[tekst_str.size()];

            for(int i=0; i<tekst_str.size();i++){
                for(int j = 0; j< 36;j++){
                    if(tekst_str[i]==T[j]) {
                            j=(36-k+j)%36;
                            a[i] = T[j]; break;
							}
							else{
							a[i] = tekst_str[i];
							}
                }
            }
            
    for(int i=0; i<tekst_str.size();i++) tekst_str[i] = a[i]; 
	cout<<"\ntekst odszyfrowano! (plik: d_out.txt)\n\n";
    
    ofstream file_out("d_out.txt");
	for (int s = 0; s < tekst_str.size(); s++) file_out << tekst_str[s];
	file_out.close();
    
	
}

int main()
{
		T_tekst t;
		char q = 'n';
		string str;
	
	cout << "\n\nnazwa pliku: ";
	cin>>str;
		
	t.file_name = str;
	t.read();
	t.view_tekst();	
    	
		
	cout << "\n\npokaz czestosc? (y/n): ";
    cin>>q;
    if(q == 'y' || q == 'Y'){ 
	t.view_frq();
	}
		
//=========================================			
	cout << "\n\nszyfracja? (y/n): ";
    cin>>q;
    if(q == 'y' || q == 'Y') {

	t.szyfrowanie(), q = 'n';
	t.view_tekst();	
	
	cout << "\n\npokaz czestosc? (y/n): ";
    cin>>q;
    if(q == 'y' || q == 'Y'){ 
	t.view_frq();
	}
}

//=========================================		
	cout << "\n\ndeszyfracja? (y/n): ";
    cin>>q;
    if(q == 'y' || q == 'Y'){
    	
	cout << "\n\nnazwa pliku: ";
	cin>>str;
	t.file_name = str;
	t.read();
	//t.view_tekst();
		
	t.deszyfracja(), q = 'n';
	
	cout << "\n\npokaz czestosc? (y/n): ";
    cin>>q;
    if(q == 'y' || q == 'Y'){ 
	t.view_frq();
	}
	 
}
		

	cout<<endl<<endl;
	system("PAUSE");
	return 0;
}


