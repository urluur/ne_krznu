#include "ZivoBitje.h"

Igralec::Igralec() {
	x = 0; y = 0;
	//w = 29, h = 64;
	ime = "bumbar";
}

void space2underscore(std::string& text) { // se klice, ko zelimo presledke v imenu spremeniti na podcrtaje
	for (std::string::iterator it = text.begin(); it != text.end(); ++it)
		if (*it == ' ')
			*it = '_';
}

void Igralec::setName() { // se klice, ko zelimo da uporabnik SAM vpise svoje ime
	printf("Vpisi svoje ime, ");
	coutName();
	printf("\n");
	do {
		getline(cin, ime); // uporabnik lahko upise svoje ime tudi s presledkom
	} while (ime == "");
	space2underscore(ime); // presledki bodo spremenjeni v podcrtaje
}

void Igralec::setName(string s) { // se klice, ko zelimo uporabniku nastaviti doloceno ime
	space2underscore(s); // presledke spremenimo v podcrtaje
	if (s == "") { // da se izognemo semanticnim napakam je prednastavljeno ime igralca "bumbar"
		ime = "bumbar";
	}
	else {
		ime = s;
	}
}

void Igralec::coutName() { // se klice, ko v konzolo izpisemo ime brez podcrtajev
	string ispis_imena = ime;
	for (std::string::iterator it = ispis_imena.begin(); it != ispis_imena.end(); ++it)
		if (*it == '_')
			*it = ' '; // podcrtaji se spremenijo v presledke
	cout << ispis_imena;
}