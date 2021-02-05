#include "function_definitions.h"

void zasilnoShranjevanje(class GameManager& igra) {
	cout << "Zasilno shranjujem..." << endl;
	ofstream quicksave;
	quicksave.open("quicksave.txt");
	if (quicksave.is_open()) {
		quicksave << to_string(igra.getNivo()) << "\n" << igra.igralec.getName() << "\n";
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
	save >> tempLvl >> tempName;
	cout << tempName << "je tempname" << endl;
	igra.setNivo(tempLvl);
	igra.igralec.setName(tempName);
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
		cout << "Error: lead save" << endl;
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
		igra.setNivo(-1);
		igra.setCompleted(false);
		quicksave << "bumbar\n-1\n";
		
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
