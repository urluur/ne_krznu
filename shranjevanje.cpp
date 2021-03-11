#include "igra.h"

void GameManager::zasilnoShranjevanje() { // klicemo ko gremo iz igre preden jo dokoncamo
	// trenutni napredek pisemo v datoteko quicksave
	ofstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.is_open()) {
		if (getNivo() > 5) { // odpravi problem shranjevanja, ko je zadnji nivo koncan
			datoteka << igralec.getName() << "\n" << 5 << "\n" << zivljenja << "\n";
		}
		else {
			datoteka << igralec.getName() << "\n" << getNivo() << "\n" << zivljenja << "\n";
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
	short tempZivljenja;
	datoteka >> tempName >> tempLvl >> tempZivljenja;

	// ce so prebrane spremenljivke drugacne od privzetih, se te napisejo v glavne spremenljivke
	if (!(tempName == "bumbar" && tempLvl == 0)) {
		// spremenimo glavne spremenljvke
		setNivo(tempLvl);
		igralec.setName(tempName);
		zivljenja = tempZivljenja;

		// potrdimo z izpisom
		system("cls");
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
	// dodaj: da prebere iz datoteke najboljsih top 5. zaenkrat se ni tockovanja, zato tudi lestvice ni
}

void GameManager::shranjevanjeLestvice() { // se klice v menuju "vec->lestvica" in ko koncamo vse nivoje
	printf("Shranjujem tvoje rezultate...\n");
	// pisemo v lestvica.txt
	ofstream lestvica;
	lestvica.open("lestvica.txt");
	if (lestvica.is_open()) {
		// naredi: shrani sortirano najboljse
		lestvica.close();
	}
	else {
		cerr << "Error: save file" << endl;
		cleanup();
		exit(1);
	}
}

void GameManager::deleteSave() { // se klice v menuju "vec->izbris podatkov"
	// pisemo v datoteko quicksave.txt
	ofstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.is_open()) {
		// resetiramo nekatere podatke
		zivljenja = 3;
		igralec.setName("bumbar");
		setNivo(0);
		setCompleted(false);
		datoteka << "bumbar\n0\n3\n"; // zapisemo privzete podatke
		// naredi: ko bodo tocke izbris tock
	}
	else {
		cerr << "Error: delete save" << endl;
		cleanup();
		exit(1);
	}
	datoteka.close();
	// pisemo v datoteko lestvica.txt
	datoteka.open("lestvica.txt");
	if (datoteka.is_open())
		datoteka << "\n"; // vse je zbrisano in zamenjano z prazno datoteko
	else {
		cerr << "Error: delete leaderboard" << endl;
		cleanup();
		exit(1);
	}
	datoteka.close();
	printf("Zbrisano.\n");
}