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

void Igralec::setName(GameManager& igra) { // se klice, ko zelimo da uporabnik SAM vpise svoje ime
	printf("Vpisi svoje ime, ");
	coutName();
	printf("\n");
	bool isRunning = true;
	SDL_Event ev;

	SDL_StartTextInput();
	string text;
	Text pisava_ime(igra.okno.ren, "common/pisave/8-bit-operator/8bitOperatorPlus8-Regular.ttf", igra.okno.scaleCal(50), "Luka Ursic", { 0, 0, 0, SDL_ALPHA_OPAQUE });
	do {
		text = "";
		while (isRunning) {
			igra.okno.stejFrame();
			SDL_RenderClear(igra.okno.ren);
			while (SDL_PollEvent(&ev) != 0) {
				if (ev.type == SDL_QUIT || (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)) {
					SDL_StopTextInput();
					igra.cleanup();
					exit(0);
				}
				else if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN) {
					if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
						text = text.substr(0, text.length() - 1);
					if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN && text.length() != 0) {
						isRunning = false;
						while (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN) {
							igra.okno.stejFrame();
							SDL_PollEvent(&ev);
							igra.okno.omejiFrame();
						}
					}
					else if (ev.type == SDL_TEXTINPUT) {
						char utipk = *ev.text.text;
						if ((utipk >= 'A' && utipk <= 'z') || utipk == ' ') {
							text += ev.text.text;
						}
					}
				}
			}
			if (text == "") {
				pisava_ime.update(igra.okno.ren, "Vpisi svoje ime...", { 255, 255, 255, SDL_ALPHA_OPAQUE });
			}
			else {
				pisava_ime.update(igra.okno.ren, text, { 255, 255, 255, SDL_ALPHA_OPAQUE });
			}
			pisava_ime.display(igra.okno.scaleCal(500), igra.okno.scaleCal(350), igra.okno.ren);
			SDL_RenderPresent(igra.okno.ren);
			igra.okno.omejiFrame();
		}
	} while (text == "");
	ime = text;
	SDL_StopTextInput();

	/*
	do {
		getline(cin, ime); // uporabnik lahko upise svoje ime tudi s presledkom
	} while (ime == "");
	*/
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