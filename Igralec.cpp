#include "Igralec.h"
#include <iostream>
using namespace std;

void Igralec::setName() {
	cout << "Vpisi svoje ime, bumbar!" << endl;
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

Igralec::~Igralec() {
	cout << "Nasvidenje " << ime << "!" << endl;
}