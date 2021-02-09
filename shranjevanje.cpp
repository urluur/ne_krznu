#include "includes.h"

void GameManager::zasilnoShranjevanje() {
	ofstream datoteka;
	datoteka.open("quicksave.txt");
	if (datoteka.is_open()) {
		datoteka << igralec.getName() << "\n" << getNivo() << "\n";
		cout << "Zabelezeno da si koncal/a " << getNivo() << " nivo in se klices ";
		igralec.coutName();
		cout << endl;
		datoteka.close();
	}
	else {
		cerr << "Error: quicksave" << endl;
		cleanup();
		exit(1);
	}
}

void GameManager::branjeShranjenega() {
	cout << "Loading..." << endl;
	
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
	setNivo(tempLvl);
	igralec.setName(tempName);
	system("cls");
	cout << "Zabelezeno je, da si koncal/a " << getNivo() << " nivo in se klices ";
	igralec.coutName();
	cout << endl;
}

void GameManager::branjeLestvice() {
	cout << "Berem lestvico..." << endl;
}

void GameManager::shranjevanjeLestvice() {
	cout << "Shranjujem tvoje rezultate..." << endl;
	ofstream lestvica;
	lestvica.open("top.txt");
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
	cout << "Zbrisano." << endl;
}
