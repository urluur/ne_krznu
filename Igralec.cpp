#include "Igralec.h"

void space2underscore(std::string& text) {
	for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
		if (*it == ' ') {
			*it = '_';
		}
	}
}
void Igralec::setName() {
	cout << "Vpisi svoje ime, ";
	coutName();
	cout << endl;
	getline(cin, ime);
	space2underscore(ime);
	cout << "Pozdravljen/a ";
	coutName();
	cout << "!" << endl;
}
void Igralec::setName(string s) {
	space2underscore(s);
	ime = s;
	cout << "Pozdravljen/a ";
	coutName();
	cout << "!" << endl;
}
string Igralec::getName() {
	return ime;
}
void Igralec::coutName() {
	string ispis_imena = ime;
	for (std::string::iterator it = ispis_imena.begin(); it != ispis_imena.end(); ++it) {
		if (*it == '_') {
			*it = ' ';
		}
	}
	cout << ispis_imena;
}
Igralec::Igralec() {
	ime = "bumbar";
}
Igralec::~Igralec() {
	cout << "Nasvidenje ";
	coutName();
	cout << "!" << endl;
}