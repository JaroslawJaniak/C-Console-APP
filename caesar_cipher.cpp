#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <fstream>
#include <cstring>
#include <math.h>

//Jaroslaw_Janiak_2019_ochrona_danych
//szyfr cezara
//caesar cipher

using namespace std;

unsigned char T[65] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
					   '0','1','2','3','4','5','6','7','8','9',
					   '.',',',';',':','!','?','"','@','#','$','%','^','&','*','_','(',')','[',']','{','}','\\','|','/','<','>','+','-','='};

void strcopy(char destiny[], string source) {
	int i = 0;
	do {
		destiny[i] = source[i];
	} while (destiny[i++] != 0);
}

//funkcja modulo (liczy tak¿e modulo dla ujemnych w argumancie liczb zarówno 'q' jak i 'm')
//modulo function with full functionality - posytive/negative value of 'q' and 'm'
int mod(float q, float m) {
	int r = 0;
	int k = 0;

	
	if(m<0 && q>0){
		k = floor(float(fabs(q/m)));
		k = k*(-1);
	} 
	else if(m<0 && q<0){
		k = ceil(float(fabs(q/m)));
		k = k*(-1);
	}
	else if(m>0 && q<0){
		k = ceil(float(fabs(q/m)));
		k = k*(-1);
	}
	else if(m>0 && q>=0){
		k = floor(float(q/m));
	}
	
	r = q - k*m;
	return r;
 }

class T_text {
public:
	string text_str;
	string file_name;

	T_text();
	T_text(string file_name);
	void read();
	void encryption();
	void decryption();
	void view_frq();
	void view_text();
	
	
};

T_text::T_text() {
	text_str = "null";
	
}

T_text::T_text(string file_name) {
	text_str = "null";
	this->file_name = file_name;
	
}

void T_text::view_text() {
	cout<<"\n   text:\n";
	for (int s = 0; s < text_str.size(); s++) cout<<text_str[s];
}

void T_text::view_frq() {
	unsigned int frq[65];
	unsigned int count = 0;
	
	//cout<<"\n\nliczba znakow: "<<text_str.size()-1<<endl;
	
	for(int i =0;i<65;i++) frq[i] = 0;
	
	for(int i=0; i<text_str.size();i++){
                for(int j = 0; j< 65;j++){
                    if(text_str[i]==T[j]) {
                            frq[j]++; 
                            count++;
							break;
							}
                }
            }
            
    cout<<"\n\nnumber of characters (characters counter): "<<count<<endl;
    
	cout<<endl;
	for(int i =0;i<65;i++) {
		//if(frq[i]!=0) cout<<T[i] <<": "<< (double(frq[i])/(text_str.size()-1))*100.<<"%\n";
		if(frq[i]!=0) cout<<T[i] <<": "<< (double(frq[i])/(count))*100.<<"%\n";
}
	
	double q = 0.0;
	
	for(int i =0;i<65;i++) {
		//q = q + (double(frq[i])/(text_str.size()-1))*100.;
		q = q + (double(frq[i])/(count))*100.;
	}
	
	cout<<"\nsum: "<<q<<"%"<<endl;
	
	q=0.0;
	
	for(int i =0;i<65;i++) {
		q = q + (frq[i]*(frq[i]-1));
	}
	
	q = q/((text_str.size()-1)*(text_str.size()-2));
	
	cout<<"\nq: "<<q<<endl;
}

void T_text::read() {
	//zamiana string: 'name_file' na c-string
	//change 'name_file' string to c-string
	char * cstr = new char[file_name.length() + 1];
	strcopy(cstr, file_name);

	//czytanie textu
	//read text from source file
	ifstream file_text(cstr, std::ios::in);
	text_str.clear();
	if (file_text) {
		while (!file_text.eof())  text_str.push_back(file_text.get());
	}
	file_text.close();
	
	
	//zamiana na wilkie litery
	//change to upper case
	for(int i=0; i<text_str.size();i++){
		if (islower(text_str[i])) text_str[i] = toupper(text_str[i]);
	}
	
	//usowanie znaku nowej linii i spacji
	//remove new line and white space
	for(int i=0; i<text_str.size();i++){
		if (text_str[i]=='\n' || text_str[i]==' ') text_str.erase(i,1);
	}
	
	/*
	//usowanie znakow spoza alfabetu - nie dziala; modyfikuje text (???)	
		for(int i=0; i<text_str.size();i++){
		 	for(int j =0;j<65;j++){ 
				 	if(text_str[i]!=T[j]) text_str.erase(i,1); 		
			 }
		}
 	*/
	
}

void T_text::encryption() {
	int k = 0;
	cout<<"\ngive the encryption key: "; cin>>k;

    char *a = new char[text_str.size()];

            for(int i=0; i<text_str.size();i++){
                for(int j = 0; j< 65;j++){
                    if(text_str[i]==T[j]) {
                    	if(k<0){
                    		k = -1*(int(fabs(k))%(65-1));
                    		j=mod(65+k+j,65);
						} 
						else{
                            j=mod(k+j,65);
                        }
                        a[i] = T[j]; break;
					}
					else{
						a[i] = text_str[i];
					}
							
                }
            }
            
    for(int i=0; i<text_str.size();i++)  text_str[i] = a[i];
	cout<<"\n   the text has been encrypted! (plik: encrypted_text.txt)\n";
	
	ofstream file_out("encrypted_text.txt");
	for (int s = 0; s < text_str.size(); s++) file_out << text_str[s];
	file_out.close();

}

void T_text::decryption(){
	int k = 0;
	cout<<"\n\ngive the decryption key (usual same as encryption key): "; cin>>k;

    char *a = new char[text_str.size()];

            for(int i=0; i<text_str.size();i++){
                for(int j = 0; j< 65;j++){
                    if(text_str[i]==T[j]) {
                    		
                    		if(k<0){
                    			k = -1*(int(fabs(k))%(65-1));
                    			j=mod(65-k+j,65);
							} 
							else{
								j=mod(65-k+j,65);
							}
                    	         
                            a[i] = T[j]; break;
							}
							else{
							a[i] = text_str[i];
							}
                }
            }
            
    for(int i=0; i<text_str.size();i++) text_str[i] = a[i]; 
	cout<<"\n   the text has been decrypted! (file: decrypted_text.txt)\n\n";
    
    ofstream file_out("decrypted_text.txt");
	for (int s = 0; s < text_str.size(); s++) file_out << text_str[s];
	file_out.close();
    
	
}

int main()
{
		char q = 'n';
		string str = "source_text.txt";
		
	
	//T_text t;
	//t.file_name = str;
	
	T_text t("source_text.txt");
	t.read();
	t.view_text();	
    	
	t.view_frq();
			
	t.encryption(), q = 'n';
	t.view_text();	
	
	t.file_name = "encrypted_text.txt";
	t.read();
	
	t.decryption(), q = 'n';
	t.view_text();
	
	cout<<endl<<endl;
	system("PAUSE");
	return 0;
}


