#include "igralec.h"

void space2underscore(std::string& text) {
	for (std::string::iterator it = text.begin(); it != text.end(); ++it)
		if (*it == ' ')
			*it = '_';
}

void Igralec::setName() {
	printf("Vpisi svoje ime, ");
	coutName();
	printf("\n");
	do {
		getline(cin, ime);
	} while (ime == "");
	space2underscore(ime);
}

void Igralec::setName(string s) {
	space2underscore(s);
	if (s == "") {
		ime = "bumbar";
	}
	else {
		ime = s;
	}
}

void Igralec::coutName() {
	string ispis_imena = ime;
	for (std::string::iterator it = ispis_imena.begin(); it != ispis_imena.end(); ++it)
		if (*it == '_')
			*it = ' ';
	cout << ispis_imena;
}