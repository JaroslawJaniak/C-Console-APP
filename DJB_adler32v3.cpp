#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

unsigned int DJB(string s) {

	unsigned int h = 5381;

	string str = s;
	//cout<<"str:"<<str;

	for (int i = 0; i < str.length(); i++) h = h * 32 + h + str[i];

	return h;

}

unsigned int Adler32(string s) {

	unsigned int p = 65521;
	unsigned int A = 1;
	unsigned int B = 0;

	int x = 0;
	int y = 0;

	string str = s;

	for (int i = 0; i < str.size(); i++) {

		A = (A + str[i]) % p;
		B = (B + A) % p;

	}

	//cout<<"\nA: "<<A;
	//cout<<"\nB: "<<B;

	return B * 65536 + A;

}

string generator_slow(int m) {
	const unsigned char T[62] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
								  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
								  '0','1','2','3','4','5','6','7','8','9'
								};
	
	string str;
	str.resize(m);
	for (int i = 0; i < m; i++) {
		//str[i] = T[rand() % 62];
		str[i] = rand() % 256;
	}

	return str;	}


//n-cia¹gów m-znakowych
void colision_test(unsigned int n, unsigned int m) {
	
	srand((unsigned)time(NULL));

	vector <string> str_cont;
	str_cont.resize(n);
	string slowo;
	slowo.resize(m);
	
	vector <unsigned int> key_container;
	key_container.resize(n);
	
	int c = 0;

	for(unsigned int i = 0; i<n; i++) key_container[i] = Adler32(generator_slow(m));
	
	for(int i = 0; i<key_container.size(); i++){
		for(int j = i+1; j<key_container.size(); j++){
			if(key_container[i]==key_container[j] && i!=j) {
				c++;
			}
		}
	}
	
	
	cout<<"\n\nliczba ciagow: "<<n;
	cout<<"\nliczba znakow w ciagu: "<<m;
	cout<<"\nlicznik kolizji sum kontrolnych: "<<c;
}

int main()
{

	string str = "test";

	cout << "\n\nDJB: " << DJB(str);
	cout << "\n\nAdler32: " << Adler32(str);
	std::cout << '\n';
	
	colision_test(10000, 12);
	colision_test(260, 1000);
	
	
	std::cout << '\n';
	std::cout << '\n';

	//=====================================================
	std::cout << '\n';
	std::cout << "=====================================================\n";

	// set some values (from 1 to 10)
	string myvector = "AABCDAEFFBGHAAAF";

	std::cout << "myvector contains: ";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	
	std::cout << '\n';
	std::cout << '\n';
	
	std::cout << '\n' <<"myvector.size(): "<< myvector.size()<<endl<<endl;
	
	//char s1 = 1;
	//char s2 = 254;
	
	//std::cout << '\n' <<"s1: "<< s1<<endl<<endl;
	//std::cout << '\n' <<"s2: "<< s2<<endl<<endl;

	int c = 0;

	for (int i = 0; i < myvector.size(); i++) {
		for (int j = i+1; j < myvector.size(); j++) {
			
			if (myvector[i] == myvector[j]) {
				c++;
				std::cout << " " << myvector[j];
				myvector.erase(myvector.begin() + j);
				j = j -1;
			}
		}
		//myvector.erase(myvector.begin());
	}

	std::cout << '\n';
	std::cout << "\nlicznik kolizji:" << c<<endl<<endl;

	//=====================================================
	



	system("PAUSE");
	return 0;
}

