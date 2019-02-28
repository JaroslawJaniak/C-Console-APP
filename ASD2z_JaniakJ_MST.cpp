ASD2z_JaniakJ_MST.cpp

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//--version Visual_Studio--//
///.......................................................................        
class TEdge {
	int id_1;
	int id_2;


public:
	TEdge();
	void read();
	void view();
	int w;

	friend class Graph;
	friend class Vertex;
};

TEdge::TEdge() {
	id_1 = 0;
	id_2 = 0;
	w = 0;
}

void TEdge::read() {
	cin >> id_1 >> id_2 >> w;
}

void TEdge::view() {
	cout << id_1 << id_2 << w << endl;
}

///.......................................................................        
class TVertex {
	int id;
	string name;

public:
	TVertex();
	void read();
	void view();

	vector <TEdge> vEdg;
	void sort(vector <TVertex> &vVrt);

	friend class Graph;
	friend class TEdge;
};


TVertex::TVertex() {
	id = 0;
	name = "NULL";
}

void TVertex::read() {
	cin >> id >> name;
}

void TVertex::view() {
	cout << id << name << endl;
}

void TVertex::sort(vector <TVertex> &vVrt) {
	//SORTOWANIE (w malejacym porzadku) KRAWEDZI W WIERZCHOLKU ZE WZGLEDU NA WAGI
	///.......................................................................        
	int j = 1; int k = 0; TVertex tmp, tmp1;
	int n = 0; n = vVrt.size();

	while (j) {

		for (int i = 0; i<n - 1; i++)
		{
			if (vVrt[i].id<vVrt[i + 1].id) {
				tmp = vVrt[i];
				vVrt[i] = vVrt[i + 1];
				vVrt[i + 1] = tmp;
				k = 1;
			}
		}

		if (k == 1) { k = 0; }
		else { break; }
	}
}


///.......................................................................        
class Graph {
	vector <TVertex> vVrt;
	vector <TEdge> vEdg;

	//pojemnik na Edges MST
	vector <TEdge> vEdgMST_tmp;
	vector <TEdge> vEdgMST;
	//pojemnik na Vertex MST
	vector <TVertex> vVrtMST;

	int n_g;
	int n_v;
	int n_edg;

public:
	Graph();
	void read();
	void MST_Prim();
	void write();

	void inv_sort(vector <TEdge> &vEdg);
	void sort(vector <TEdge> &vEdgv);
};

Graph::Graph() {
	n_g = 0;
	n_v = 0;
	n_edg = 0;
}

void Graph::inv_sort(vector <TEdge> &vEdg) {
	//SORTOWANIE (w malejacym porzadku) ELEMENTOW WEKTORA 'vEdg' ZE WZGLEDU NA WAGI
	///.......................................................................        
	int j = 1; int k = 0; TEdge tmp, tmp1;
	int n = 0; n = vEdg.size();

	while (j) {

		for (int i = 0; i<n - 1; i++)
		{
			if (vEdg[i].w<vEdg[i + 1].w) {
				tmp = vEdg[i];
				vEdg[i] = vEdg[i + 1];
				vEdg[i + 1] = tmp;
				k = 1;

			}
			if (vEdg[(n - 1) - i].w>vEdg[(n - 1) - i - 1].w) {
				tmp1 = vEdg[n - 1 - i - 1];
				vEdg[n - 1 - i - 1] = vEdg[n - 1 - i];
				vEdg[n - 1 - i] = tmp1;
				k = 1;
			}
		}
		if (k == 1) { k = 0; }
		else { break; }
	}
}

void Graph::sort(vector <TEdge> &vEdgv) {
	//SORTOWANIE (w rosnacym porzadku) ELEMENTOW WEKTORA 'vEdg' ZE WZGLEDU NA WAGI
	///.......................................................................        
	int j = 1; int k = 0; TEdge tmp, tmp1;
	int n = 0; n = vEdgv.size();

	while (j) {

		for (int i = 0; i<n - 1; i++)
		{
			if (vEdgv[i].w>vEdgv[i + 1].w) {
				tmp = vEdgv[i];
				vEdgv[i] = vEdgv[i + 1];
				vEdgv[i + 1] = tmp;
				k = 1;

			}
			if (vEdgv[(n - 1) - i].w<vEdgv[(n - 1) - i - 1].w) {
				tmp1 = vEdgv[n - 1 - i - 1];
				vEdgv[n - 1 - i - 1] = vEdgv[n - 1 - i];
				vEdgv[n - 1 - i] = tmp1;
				k = 1;
			}
		}
		if (k == 1) { k = 0; }
		else { break; }
	}
}

void Graph::read() {
	cin >> n_v;
	vVrt.resize(n_v);

	for (int i = 0; i < n_v; i++) vVrt[i].read();
	cin >> n_edg;
	vEdg.resize(n_edg);
	for (int i = 0; i < n_edg; i++) vEdg[i].read();

	for (int i = 0; i < n_edg; i++) {
		vVrt[vEdg[i].id_1 - 1].vEdg.push_back(vEdg[i]);
		vVrt[vEdg[i].id_2 - 1].vEdg.push_back(vEdg[i]);
	}

	//SORTOWANIE (w malejacym porzadku) KRAWEDZI DANEGO WIERZCHOLKA ZE WZGLEDU NA WAGI
	///.......................................................................        
	int j = 1; int k = 0; TEdge tmp, tmp1;
	int n = 0;

	for (int iv = 0; iv < n_v; iv++) {
		n = vVrt[iv].vEdg.size();

		while (j) {

			for (int i = 0; i<n - 1; i++)
			{
				if (vVrt[iv].vEdg[i].w<vVrt[iv].vEdg[i + 1].w) {
					tmp = vVrt[iv].vEdg[i];
					vVrt[iv].vEdg[i] = vVrt[iv].vEdg[i + 1];
					vVrt[iv].vEdg[i + 1] = tmp;
					k = 1;

				}
				if (vVrt[iv].vEdg[(n - 1) - i].w>vVrt[iv].vEdg[(n - 1) - i - 1].w) {
					tmp1 = vVrt[iv].vEdg[n - 1 - i - 1];
					vVrt[iv].vEdg[n - 1 - i - 1] = vVrt[iv].vEdg[n - 1 - i];
					vVrt[iv].vEdg[n - 1 - i] = tmp1;
					k = 1;
				}
			}

			if (k == 1) { k = 0; }
			else { break; }
		}
	}
	//for (int i = 0; i < vVrt.size(); i++) vVrt[i].view();
	///.......................................................................
	///.......................................................................  
}

void Graph::MST_Prim() {
	//TWORZENIE DRZEWA MST
	///.......................................................................

	TEdge edg_tmp;
	int id_tmp;

	for (int i = 0; i < vVrt.size();) {

		/*
		1- dodaj krawedzie danego wierzcholka ktorych nie ma w TMP
		2- usun kraedzie z TMP ktore sa juz w MST
		3- sortuj (malejaco) TMP
		4- dodaj ostatni element TMP (krawedz o najmniejszej wadze) do MST (jesli nie ma go w MST -> pkt 2) i jesli jednoczesnie id1 i id2 tej krawedzi != vVrtMST
		5- usun ostatni element TMP
		6- sprawdz czy krawedzie dodane do MST przebiegaja wszystkie wierzcholki:
			6a- tak -> zakoncz
			6b- nie -> przejdz do wierzcholka o id z dodanej wlasnie krawedzi i takim ze id1 lub id2 != od vVrtMST

		*/

		//--1--//
		if (vEdgMST_tmp.empty()) {
			for (int k = 0; k < vVrt[i].vEdg.size(); k++) {
				vEdgMST_tmp.push_back(vVrt[i].vEdg[k]);
			}
		}

		if (!vEdgMST_tmp.empty()) {
			int c = 1;
			for (int j = 0; j < vVrt[i].vEdg.size(); j++) {
				for (int t = 0; t < vEdgMST_tmp.size(); t++) {
					//jesli krawedz wierzcholka nalezy do TMP to ustaw c na 0 
					if ((vVrt[i].vEdg[j].id_1 == vEdgMST_tmp[t].id_1) && (vVrt[i].vEdg[j].id_2 == vEdgMST_tmp[t].id_2)) { c = 0; }
				}
				//jsli c != 0 dodaj krawedz (tzn ze nie ma jej w TMP)
				if (c) {
					vEdgMST_tmp.push_back(vVrt[i].vEdg[j]);
				}
				c = 1;
			}
		}
		//--1koniec--//

		//--2--//
		//usun kraedzie z TMP ktore sa juz w MST
		if (!vEdgMST.empty()) {
			for (int j = 0; j < vEdgMST.size(); j++) {
				for (int t = 0; t < vEdgMST_tmp.size(); t++) {
					if ((vEdgMST[j].id_1 == vEdgMST_tmp[t].id_1) && (vEdgMST[j].id_2 == vEdgMST_tmp[t].id_2)) { vEdgMST_tmp.erase(vEdgMST_tmp.begin() + (t)); }
				}
			}
		}
		//--2koniec--//

		//--3--//
		//sortowanie (malejaco )tymczasowej listy krawedzi
		inv_sort(vEdgMST_tmp);
		//--3koniec--//

		//--4--//
		//wybor krawedzi o najmniejszej wadze i takiej ze jej id 1 i id2 != od vVrtMST
		int ck1 = 1; int ck2 = 1;
		for (int t = 0; t < vVrtMST.size(); t++) {
			if ((vEdgMST_tmp.back().id_1 == vVrtMST[t].id)) { ck1 = 0; }
			if ((vEdgMST_tmp.back().id_2 == vVrtMST[t].id)) { ck2 = 0; }
		}
		//jsli c != 0 dodaj krawedz (tzn ze nie ma jej w TMP)
		if (ck1 || ck2) {
			vEdgMST.push_back(vEdgMST_tmp.back());
			edg_tmp = vEdgMST.back();
		}
		else {
			vector<TEdge>::iterator it;
			it = vEdgMST_tmp.end() - 2;
			vEdgMST.push_back(*it);
			edg_tmp = vEdgMST.back();
		}
		ck1 = 1, ck2 = 1;

		//wybor id dla przyszlego wierzcholka taki ze jednoczesnie id1 i id2 != vVrtMST i != od wierzcholka w ktorym jestesmy
		if (vVrtMST.empty()) {
			if (vVrt[i].id != edg_tmp.id_1) id_tmp = edg_tmp.id_1;
			else id_tmp = edg_tmp.id_2;
		}
		if (!vVrtMST.empty()) {
			for (int t = 0; t < vVrtMST.size(); t++) {
				if ((vEdgMST.back().id_1 != vVrtMST[t].id) && (vVrt[i].id != edg_tmp.id_1)) { id_tmp = edg_tmp.id_1; }
				if ((vEdgMST.back().id_2 != vVrtMST[t].id) && (vVrt[i].id != edg_tmp.id_2)) { id_tmp = edg_tmp.id_2; }
			}
		}
		//--4koniec--//

		//--5--//
		vEdgMST_tmp.pop_back();
		//--5koniec--//

		sort(vEdgMST);

		//--6--//
		if (vVrtMST.empty()) for (int t = 0; t < vEdgMST.size(); t++) {
			vVrtMST.push_back(vVrt[vEdgMST[t].id_1 - 1]);
			vVrtMST.push_back(vVrt[vEdgMST[t].id_2 - 1]);
		}

		//gdy vVrtMST nie jest pusty
		int c1 = 0, c2 = 0, id_tmp1 = 0, id_tmp2 = 0;
		if (!vVrtMST.empty()) {
			for (int k = 0; k < vEdgMST.size(); k++) {
				for (int j = 0; j < vVrtMST.size(); j++) {
					if (vEdgMST[k].id_1 == vVrtMST[j].id) c1 = 1;
					else id_tmp1 = vEdgMST[k].id_1;
				}
				if (c1 == 0) vVrtMST.push_back(vVrt[id_tmp1 - 1]);
				c1 = 0;
			}

			for (int k = 0; k < vEdgMST.size(); k++) {
				for (int j = 0; j < vVrtMST.size(); j++) {
					if (vEdgMST[k].id_2 == vVrtMST[j].id) c2 = 1;
					else id_tmp2 = vEdgMST[k].id_2;
				}
				if (c2 == 0) vVrtMST.push_back(vVrt[id_tmp2 - 1]);
				c2 = 0;
			}

		}



		//--6a--//
		if (vVrtMST.size() == n_v) { break; }
		//--6b--//
		else i = id_tmp - 1;
		//--6koniec--// 
	}

	sort(vEdgMST);
	//for (int r = 0; r < vEdgMST.size(); r++) vEdgMST[r].view();
	//krawedzie identyfikowane znakami
	for (int r = 0; r < vEdgMST.size(); r++) cout << vVrt[vEdgMST[r].id_1 - 1].name << vVrt[vEdgMST[r].id_2 - 1].name << vEdgMST[r].w << endl;

}


///////////////////////////////////////////////////////////////////////////////

int main()
{
	int n_g; cin >> n_g;

	for (int i = 0; i < n_g; i++) {
		Graph g;
		g.read();
		g.MST_Prim();
		cout << endl;
	}

	return 0;
}
