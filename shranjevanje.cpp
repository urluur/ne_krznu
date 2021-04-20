#include "igra.h"

void GameManager::zasilnoShranjevanje() { // klicemo ko gremo iz igre preden jo dokoncamo
	// trenutni napredek pisemo v datoteko quicksave
	ofstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.is_open()) {
		if (getNivo() > 5) { // odpravi problem shranjevanja, ko je zadnji nivo koncan
			datoteka << igralec.getName() << "\n" << 5 << "\n" << zivljenja << "\n" << skupne_tocke << "\n";
		}
		else {
			datoteka << igralec.getName() << "\n" << getNivo() << "\n" << zivljenja << "\n" << skupne_tocke << "\n";
		}
		datoteka.close();

		// potrdimo shranjeno z izpisom
		printf("Zabelezeno da si koncal/a %d nivo in se klices ", getNivo());
		igralec.coutName();
		printf("\n");
	}
	else {
		cerr << "Error: quicksave" << endl;
		cleanup();
		exit(1);
	}
}

void GameManager::branjeShranjenega() { // se ob zagonu programa
	// beremo napredek iz quicksave datoteke
	ifstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.fail()) {
		cerr << "Error: reading quicksave" << endl;
		cleanup();
		exit(1);
	}

	// pisemo v zacasni spremenljivki
	short tempLvl;
	string tempName;
	short tempZivljenja, tempS_tocke;
	datoteka >> tempName >> tempLvl >> tempZivljenja >> tempS_tocke;

	// ce so prebrane spremenljivke drugacne od privzetih, se te napisejo v glavne spremenljivke
	if (!(tempName == "bumbar" && tempLvl == 0)) {
		// spremenimo glavne spremenljvke
		setNivo(tempLvl);
		igralec.setName(tempName);
		zivljenja = tempZivljenja;
		skupne_tocke = tempS_tocke;

		// potrdimo z izpisom
		printf("Zabelezeno je, da si koncal/a %d nivo in se klices ", getNivo());
		igralec.coutName();
		printf("\n");
	}
}

// se klice, ko beremo v dve doloceni spremenljivki in ne v glavni
void GameManager::branjeShranjenega(string& mainString, short& mainShort) {
	// beremo iz quicksave datoteke
	ifstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.fail()) {
		cerr << "Error: reading quicksave" << endl;
		cleanup();
		exit(1);
	}
	// shranjujemo v spremenljivke iz parametrov
	datoteka >> mainString >> mainShort;
}

// lestvoco beremo in shranimo v spremenljivke, pred shranjevanjem ko koncamo igro in vec->lestvica
void GameManager::branjeLestvice() {
	printf("\n");
	ifstream lestvica;
	lestvica.open("lestvica.txt");
	if (lestvica.fail()) {
		cerr << "error: branje lestvice" << endl;
	}
	else {
		for (int i = 0; i < 5; ++i) {
			lestvica >> najboljsi[i] >> najbolse[i]; // imena in tocke shranimo v spremenljivke
			cout << i+1 << ". " << najboljsi[i] << " " << najbolse[i] << endl; // izpis v konzoli
		}
		lestvica.close();
	}
}

// klice se ko koncamo vse nivoje
void GameManager::shranjevanjeLestvice() {
	// posodobimo spremenljivke z podatki iz datoteke
	branjeLestvice();

	// pisemo v lestvica.txt
	bool done = false; // uporabimo za to, da se na lestvico vpisemo le enkrat
	ofstream lestvica;
	lestvica.open("lestvica2.txt", ios::app); // odpremo novo datoteko v nacinu pripenjanja besedila
	if (lestvica.is_open()) {
		// novi zacasni tabeli spremenljivk, v katere bomo prepisovali podatke, ter vrinili nas rekord
		string tempStr[5];
		int tempInt[5];

		// indeks ki se premika po originalni tableli
		int walk_og = 0;

		// prepisemo iz starih tabel v nove tabele
		for (int walk_new = 0; walk_new < 5; ++walk_new) { // glavno nam je premikanje po novi tabeli zaradi vrinjanja
			if (skupne_tocke > najbolse[walk_og] && !done) { // ce so nase tocke vecje od opazovanih v tabeli jih vrinemo
				if (najbolse[walk_og] == 0 && walk_og == 0) { // ce je lestvica prazna se vedno vpisemo na prvo mesto
					// svoje podazke vrinemo v novo tabelo
					tempInt[walk_new] = skupne_tocke;
					tempStr[walk_new] = igralec.getName();
					
					// podatki so vpisani lahko le enkrat
					done = true;

					// novo tabelo pripnemo v novo datoteko
					lestvica << tempStr[walk_new] << " " << tempInt[walk_new] << endl;
					
					// vpisali smo se v prazno lestvico na prvem mestu, zato lahko ostala mesta v tabeli le prepisemo
					continue;
				}

				// vpisali smo se na mesto ki ni prvo
				tempInt[walk_new] = skupne_tocke;
				tempStr[walk_new] = igralec.getName();
				done = true;
				--walk_og; // ker nismo prvi in smo se vpisali, se ne premaknemo v stari tabeli, da ne izgubimo podatkov
			}
			else {
				// samo prepisujemo iz stare tabele v novo
				tempInt[walk_new] = najbolse[walk_og];
				tempStr[walk_new] = najboljsi[walk_og];
			}
			++walk_og; // premaknemo se na naslednji indeks v stari tabeli
			lestvica << tempStr[walk_new] << " " << tempInt[walk_new] << endl; // novi datoteki dodamo podatke
		}
		lestvica.close();
		remove("lestvica.txt"); // staro datoteko zbrisemo
		bool problemi = rename("lestvica2.txt", "lestvica.txt"); // novo datoteko zamenjamo na mesto stare
		if (problemi) {
			cerr << "error: rename lestvica" << endl;
		}
		printf("\nNova lestvica:\n");
		branjeLestvice(); // posodobimo spremenljivke in izpisemo kot potrditev
	}
	else {
		cerr << "Error: save file" << endl;
		cleanup();
		exit(1);
	}
}

void GameManager::deleteLeaderboard() {
	ofstream datoteka;
	// pisemo v datoteko lestvica.txt
	datoteka.open("lestvica.txt");
	if (datoteka.is_open())
		// v lestvicozapisemo privzeto vsebino
		datoteka << "[prosto] 0\n[prosto] 0\n[prosto] 0\n[prosto] 0\n[prosto] 0\n";
	else {
		cerr << "Error: delete leaderboard" << endl;
		cleanup();
		exit(1);
	}
	datoteka.close();
}

void GameManager::deleteOnlySave() {
	// pisemo v datoteko quicksave.txt
	ofstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.is_open()) {
		// resetiramo nekatere podatke
		zivljenja = 3;
		trenutne_tocke = 0;
		skupne_tocke = 0;
		igralec.setName("bumbar");
		setNivo(0);
		setCompleted(false);
		perfect_run = false;
		rageModeSet(false);
		datoteka << "bumbar\n0\n3\n0\n"; // zapisemo privzete podatke
	}
	else {
		cerr << "Error: delete save" << endl;
		cleanup();
		exit(1);
	}
	datoteka.close();
}

void GameManager::deleteSave() { // se klice v menuju "vec->izbris podatkov"
	deleteLeaderboard();
	deleteOnlySave();
}