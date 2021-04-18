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

void GameManager::branjeLestvice() {
	printf("Berem lestvico...\n");
	ifstream lestvica;
	lestvica.open("lestvica.txt");
	if (lestvica.fail()) {
		cerr << "error: branje lestvice" << endl;
	}
	else {
		for (int i = 0; i < 5; ++i) {
			lestvica >> najboljsi[i] >> najbolse[i];
			cout << i+1 << ". " << najboljsi[i] << " " << najbolse[i] << endl;
		}
		lestvica.close();
	}
}

void GameManager::shranjevanjeLestvice() { // se ko koncamo vse nivoje
	printf("Shranjujem tvoje rezultate...\n");
	printf("Stara lestvica:\n");
	branjeLestvice();
	// pisemo v lestvica.txt
	bool done = false;
	ofstream lestvica;
	lestvica.open("lestvica2.txt", ios::app);
	if (lestvica.is_open()) {
		string tempStr[5];
		int tempInt[5];
		int walk_og = 0;
		for (int walk_new = 0; walk_new < 5; ++walk_new) {
			if (skupne_tocke > najbolse[walk_og] && !done) {
				if (najbolse[walk_og] == 0 && walk_og == 0) {
					tempInt[walk_new] = skupne_tocke;
					tempStr[walk_new] = igralec.getName();
					done = true;
					lestvica << tempStr[walk_new] << " " << tempInt[walk_new] << endl;
					continue;
				}
				tempInt[walk_new] = skupne_tocke;
				tempStr[walk_new] = igralec.getName();
				done = true;
				--walk_og;
			}
			else {
				tempInt[walk_new] = najbolse[walk_og];
				tempStr[walk_new] = najboljsi[walk_og];
			}
			++walk_og;
			lestvica << tempStr[walk_new] << " " << tempInt[walk_new] << endl;
		}
		lestvica.close();
		remove("lestvica.txt");
		bool problemi = rename("lestvica2.txt", "lestvica.txt");
		if (problemi) {
			cerr << "error: rename lestvica" << endl;
		}
		printf("\nNova lestvica:\n");
		branjeLestvice();
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
		datoteka << "0 0\n0 0\n0 0\n0 0\n0 0\n"; // vse je zbrisano in zamenjano z prazno datoteko
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
	printf("Zbrisano.\n");
}