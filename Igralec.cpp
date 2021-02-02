#include "Igralec.h"

void Igralec::setName() {
	cout << "Vpisi svoje ime, " << ime << endl;
	getline(cin, ime);
	cout << "Pozdravljen/a " << ime << "!" << endl;
}
void Igralec::setName(string s) {
	ime = s;
	cout << "Pozdravljen/a " << ime << "!" << endl;
}
string Igralec::getName() {
	return ime;
}
Igralec::Igralec() {
	ime = "bumbar";
}
Igralec::~Igralec() {
	cout << "Nasvidenje " << ime << "!" << endl;
}