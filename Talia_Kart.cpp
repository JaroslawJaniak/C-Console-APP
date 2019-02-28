#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

class TKarta {
private:
    string kolor;
    string figura;
    int wartosc;

public:

    TKarta();
    void pokaz_karte();
    //~TKarta();

    friend class TTalia;
};

TKarta::TKarta() {
    kolor = "NULL";
    figura = "NULL";
    wartosc = 0;
}

void TKarta::pokaz_karte()
{
    cout << "(" << figura << "-" << kolor << ")" << " ";
}

class TTalia {
private:

public:
    vector <TKarta> vCard;

    TTalia();
    void tasuj();
    void pokaz_talie();

    ~TTalia() {};

};

TTalia::TTalia() {
    vCard.resize(52);
    string _kolor[4] = { "Kier", "Pik", "Trefl", "Karo" };
    string _figura[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "W", "D", "K",  "A"};
    int _wartosc[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

    for (int i = 0; i < 52; i++) {
        vCard[i].kolor = _kolor[ static_cast <int> (floor(i/13)) ];
        vCard[i].figura = _figura[i % 13];
        vCard[i].wartosc = _wartosc[i % 13];
    }
    
}

void TTalia::tasuj() {
    int i = 0;
    do {
        swap(vCard[rand()%52], vCard[rand()%52]), i++;
    } while (i < 999);
}

void TTalia::pokaz_talie() {
	cout << "\nTALIA:\n\n";
    for (int i = 0; i < vCard.size(); i++) {
        vCard[i].pokaz_karte();
        if ((i + 1) % 4 == 0) cout << endl << endl;
    }
    cout << "\n\nliczba kart w talii: "<< vCard.size() <<endl<<endl;
}

class TGracz
{
public:

    TGracz();

private:
    vector <TKarta> vHand;

    friend class TGra;
    friend class TKarta;
};

TGracz::TGracz()
{
    
}

class TGra
{
public:
    int ng;
    TGra();
    ~TGra();

    void rozdaj();

private:

    vector <TGracz> vGracz;
    TTalia gTalia;
    
};

TGra::TGra()
{
    
	cout << "\nczy tasowac? (y/n): ";
    char q = 'n';
    cin>>q;
    
    if(q == 'y' || q == 'Y') gTalia.tasuj(), q = 'n';
    
    cout << "\npkazac zawartosc talii? (y/n): ";
    cin>>q;
    
    if(q == 'y' || q == 'Y') gTalia.pokaz_talie(), q = 'n';

    ng = 0;
    cout << "\nilu graczy (jesli > 4 -> max liczba graczy = 4): ";
    cin >> ng;
    if (ng <= 1) ng = 1, cout << "\njestes jedynym graczem! (indeks: 1)\n";
    if (ng > 4) ng = 4;
    vGracz.resize(ng);
}

void TGra::rozdaj()
{
    TKarta tmp_Card;

    for (int i = 0; i < ng; i++) {
        cout << "\n\n    REKA GRACZA '" << i+1 << "': \n\n";
        for (int j = 0; j < 5; j++) {
            tmp_Card = gTalia.vCard.back();
            vGracz[i].vHand.push_back(tmp_Card);
            vGracz[i].vHand[j].pokaz_karte();

            gTalia.vCard.pop_back();
        }
        cout << endl;
    }

    cout << endl;
    
    
    cout << "\npkazac zawartosc talii? (y/n): ";
    char q = 'n';
    cin>>q;
    
    if(q == 'y' || q == 'Y') gTalia.pokaz_talie(), q = 'n';
   

}

TGra::~TGra()
{
}


int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));

    TTalia T;
    
    //T.tasuj();
    //T.pokaz_talie();
    
    //T.vK[0].pokaz_karte();


    TGra G;
    G.rozdaj();

    cout << endl << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

