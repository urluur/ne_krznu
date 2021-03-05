#include "includes.h"

void GameManager::zasilnoShranjevanje() {
	ofstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.is_open()) {
		if (getNivo() > 5) {
			datoteka << igralec.getName() << "\n" << 5 << "\n";
		}
		else {
			datoteka << igralec.getName() << "\n" << getNivo() << "\n";
		}
		printf("Zabelezeno da si koncal/a %d nivo in se klices ", getNivo());
		igralec.coutName();
		printf("\n");
		datoteka.close();
	}
	else {
		cerr << "Error: quicksave" << endl;
		cleanup();
		exit(1);
	}
}

void GameManager::branjeShranjenega() {
	ifstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.fail()) {
		cerr << "Error: reading quicksave" << endl;
		cleanup();
		exit(1);
	}
	short tempLvl;
	string tempName;
	datoteka >> tempName >> tempLvl;
	if (!(tempName == "bumbar" && tempLvl == 0)) {
		setNivo(tempLvl);
		igralec.setName(tempName);
		system("cls");
		printf("Zabelezeno je, da si koncal/a %d nivo in se klices ", getNivo());
		igralec.coutName();
		printf("\n");
	}
}

void GameManager::branjeShranjenega(string& mainString, short& mainShort) {
	ifstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.fail()) {
		cerr << "Error: reading quicksave" << endl;
		cleanup();
		exit(1);
	}
	datoteka >> mainString >> mainShort;
}

void GameManager::branjeLestvice() {
	printf("Berem lestvico...\n");
}

void GameManager::shranjevanjeLestvice() {
	printf("Shranjujem tvoje rezultate...\n");
	ofstream lestvica;
	lestvica.open("lestvica.txt");
	if (lestvica.is_open()) {
		//shrani sortirano
		lestvica.close();
	}
	else {
		cerr << "Error: save file" << endl;
		cleanup();
		exit(1);
	}
}

void GameManager::deleteSave() {
	ofstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.is_open()) {
		igralec.setName("bumbar");
		setNivo(0);
		setCompleted(false);
		datoteka << "bumbar\n0\n";
		//nared se za lestvico k bo
	}
	else {
		cerr << "Error: delete save" << endl;
		cleanup();
		exit(1);
	}
	datoteka.close();

	datoteka.open("lestvica.txt");
	if (datoteka.is_open())
		datoteka << "\n";
	else {
		cerr << "Error: delete leaderboard" << endl;
		cleanup();
		exit(1);
	}
	datoteka.close();
	printf("Zbrisano.\n");
}