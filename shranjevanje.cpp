#include "function_definitions.h"

void zasilnoShranjevanje(class GameManager& igra) {
	cout << "Zasilno shranjujem... ";
	ofstream quicksave;
	quicksave.open("quicksave.txt");
	if (quicksave.is_open()) {
		quicksave << igra.igralec.getName() << "\n" << to_string(igra.getNivo()) << "\n";
		cout << "Opazam da si koncal/a " << to_string(igra.getNivo()) << " nivo in se klices " << igra.igralec.getName() << endl;
	}
	else {
		cout << "Error: quicksave" << endl;
		igra.cleanup();
		exit(1);
	}
	quicksave.close();
}

void branjeShranjenega(class GameManager& igra) {
	cout << "Berem shranjeno..." << endl;
	
	ifstream save;
	save.open("quicksave.txt");
	if (save.fail()) {
		cerr << "Error: odpiranje quicksave" << endl;
		igra.cleanup();
		exit(1);
	}
	short tempLvl;
	string tempName;
	save >> tempName >> tempLvl;
	cout << tempName << " je tempname" << endl; //tuki neki ne dela
	igra.setNivo(tempLvl);
	igra.igralec.setName(tempName);
	cout << "Opazam da si koncal/a " << to_string(igra.getNivo()) << " nivo in se klices " << igra.igralec.getName() << endl;
}

void branjeLestvice(GameManager& igra) {
	cout << "Berem lestvico..." << endl;
}

void shranjevanjeLestvice(GameManager& igra) {
	cout << "Shranjujem tvoje rezultate..." << endl;
	ofstream lestvica;
	lestvica.open("top.txt");
	if (lestvica.is_open()) {
		//shrani sortirano
	}
	else {
		cout << "Error: load save" << endl;
		igra.cleanup();
		exit(1);
	}
	lestvica.close();
}

void deleteSave(GameManager& igra) {
	cout << "Brisem..." << endl;
	ofstream quicksave;
	quicksave.open("quicksave.txt");
	if (quicksave.is_open()) {
		igra.igralec.setName("bumbar");
		igra.setNivo(0);
		igra.setCompleted(false);
		quicksave << "bumbar\n0\n";
		//nared se za lestvico k bo
	}
	else {
		cout << "Error: delete save" << endl;
		igra.cleanup();
		exit(1);
	}
	quicksave.close();

	ofstream lestvica;
	lestvica.open("lestvica.txt");
	if (lestvica.is_open()) {
		lestvica << "\n";
	}
	else {
		cout << "Error: delete leaderboard" << endl;
		igra.cleanup();
		exit(1);
	}
	quicksave.close();
}
