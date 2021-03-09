#include "igra.h"

void GameManager::level(short& nivo) { // glavna zanka nivo-ja, klice se iz funkcije overworld (pogleda na svet oz. nadzemlja)
	trenutniNivo = nivo + 1; // nivo je zadnji koncani nivo
	igralec.coutName();
	printf(" zacenja %d nivo.\n", trenutniNivo);

	pripraviVse(); // resetira spremenljivke, ustvari nasprotnike, tjulne...

	//pripravi odzadje
	Image odzadje;
	string pathFragment = "common/img/odzadje";
	pathFragment += to_string(trenutniNivo);
	pathFragment += ".png";
	char* path = new char[pathFragment.size() + 1];
	std::copy(pathFragment.begin(), pathFragment.end(), path);
	path[pathFragment.size()] = '\0';
	odzadje.ini(*this, path);
	odzadje.display(okno.ren);
	delete[] path;

	// povemo katero pisavo bomo uporabljani za ispis tjulnov na farmi in polju, velikost pisave (ki je odvisna od velikosti okna), dolzino izpisa in crno barvo
	Text pisava_tjulniNaFarmi(okno.ren, "common/pisave/8-bit-operator/8bitOperatorPlus8-Regular.ttf", okno.scaleCal(24), "farma: 0", { 0, 0, 0, 255 });
	Text pisava_tjulniNaPolju(okno.ren, "common/pisave/8-bit-operator/8bitOperatorPlus8-Regular.ttf", okno.scaleCal(24), "polje: 0", { 0, 0, 0, 255 });
	string polje = "polje: ", farma = "farma: ";

	// glavna zanka nivoja
	while (!keys[SDL_SCANCODE_ESCAPE] && !konecLevela && !adios) {
		okno.stejFrame(); // oznacimo zacetek zanke, da lahko na koncu zanke omejimo osvezevanje zaslona
		SDL_RenderClear(okno.ren); // ponastavimo renderer
		odzadje.display(okno.ren); // izrisemo odzadje
		handleEvents(); // preverimo pritisnjene tipke, trke z okoljem, obdelamo igralcevo uzdrljivost in premikanje

		// ce poberes vse tjulne in si na doloceni izhodni lokaciji si opravil nivo
		if (semNaIzhodniLokaciji)
			if ((stTjuln[nivo] == 0 && stTjulnFarma == 0 && trenutniNivo < 5) || (trenutniNivo == 5 && stNaspr[nivo] == 0))
				konecLevela = true; // cilj nase igre

		// igrlacevo sliko prikazemo na zaslon
		if (igralec.sepremika() && stevecNoge > 10) { // ce se igralec premika, je hoja animirana
			if (stevecNoge > 20) { // vsakih 10 slicic se igralcu spremeni slika nog
				stevecNoge = 0;
			}
			jaz->init(*this, "common/img/player_noge.png", igralec.getX(), igralec.getY(), igralec.getW(), igralec.getH());
			++stevecNoge;
		}
		else {
			jaz->init(*this, "common/img/player.png", igralec.getX(), igralec.getY(), igralec.getW(), igralec.getH());
			++stevecNoge;
		}

		// obdelamo obnasanje vseh nasprotnikov (torej trki z nami in tjulni..)
		obnasanjeNaPolju();

		//* testiram.. dokler ni petni nivo dokoncan moramo glavnega nasprotnika ubiti z presledkom
		if (keys[SDL_SCANCODE_SPACE] && trenutniNivo == 5) {
			if (stTjuln[nivo] > 0)
				--stTjuln[nivo];
			if (stNaspr[nivo] > 0) {
				--stNaspr[nivo];
				if (!enemy.empty()) {
					for (unsigned int i = 0; i < enemy.size(); ++i) {
						delete enemy.at(i);
					}
					enemy.clear();
					enemy.shrink_to_fit();
				}
			}
		}
		//*/
		// dolocimo izpisi tjulnov na farmi in na polju
		pisava_tjulniNaFarmi.update(okno.ren, farma + to_string(stTjulnFarma), { 0, 0, 0, 255 });
		pisava_tjulniNaPolju.update(okno.ren, polje + to_string(stTjuln[trenutniNivo - 1]), { 0, 0, 0, 255 });
		// prikazemo tekst na zaslonu
		pisava_tjulniNaFarmi.display(okno.scaleCal(56), okno.scaleCal(680), okno.ren);
		pisava_tjulniNaPolju.display(okno.scaleCal(56), okno.scaleCal(700), okno.ren);

		updateMap(); // slike izrisemo na zaslon, omenimo osvezevanje zaslona
	}
	cleanupVectors(); // ko gremo iz nivoja izbrisemo dinamicni pomnilnik

	// odvisno od tega ali je igralec koncal nivo, nivo zvecamo ali pa shranimo in zacnemo nivo znova
	if (konecLevela)
		printf("Koncal si %d nivo!\n", ++nivo);
	else if (adios)
		zasilnoShranjevanje();
}

void GameManager::obnasanjeNaPolju() {
	for (unsigned int i = 0; i < enemy.size(); ++i) { // zanka se ponovi za vsakega nasprotnika posebej
		if (enemy.at(i)->sprehodNaRandomDestinacijo()) { // ce je nasprotnik na svojem cilju, gre na drugo naklucno lokacijo
			enemy.at(i)->zrcuniRandomDestinacijo();
		}
		else { // nasprotnik je na poti do svoje destinacije
			// nasprotnik previri, ce je v radiju okoli njega igralec
			if (isPlayerCollidingAt(enemy.at(i)->getX() - 100, enemy.at(i)->getY() - 100, enemy.at(i)->getW() + 200, enemy.at(i)->getH() + 200)) {
				enemy.at(i)->setDest(igralec.getX(), igralec.getY()); // nasprotnikov cilj se spremeni na igralceve koordinate
				if (enemy.at(i)->nosim != -1) {
					if (enemy.at(i)->nosim <= (int)tjulni.size() && enemy.at(i)->nosim >= 0) {
						tjulni.at(enemy.at(i)->nosim)->nosilec = -1; // dovoli, da ga nosi tudi kateri drug nasprotnik
					}
					enemy.at(i)->nosim = -1; // ce nasprotnik nosi tjulna ga spusti na tla
				}
				if (rageMode) { // (ne v testingu) nasprotnik postane hitrejsi ko lovi igralca
					enemy.at(i)->rage();
				}
				// ce se nasprotnik dotakne igralca
				if (isPlayerCollidingAt(enemy.at(i)->getX(), enemy.at(i)->getY(), enemy.at(i)->getW(), enemy.at(i)->getH())) {
					printf("smrt\n");
					adios = true; // igrlec more ponoviti nivo od zacetka

					// naredi: izbrisi tocke pridobljene v tem nivoju
				}
			}
			else { // nasprotnikova prioriteta je izgnati nezazelenega igralca iz njegovega teritorija, zato preveri tjulne okoli sebe, le ce ne vidi igralca
				for (unsigned int t = 0; t < tjulni.size(); ++t) { // preveri vse tjulne okoli sebe
					// preverimo in nadaljujemo ce smo praznih rok in je tjuln na tleh, ali pa ce mi nosimo tocno tega tjulna
					if ((tjulni.at(t)->nosilec == -1 && enemy.at(i)->nosim == -1) || tjulni.at(t)->nosilec == i) {
						// preverimo ali je ta tjulen v nasem vidnem polju
						if (univerzalniTrk(enemy.at(i)->getX() - 100, enemy.at(i)->getY() - 100, enemy.at(i)->getW() + 200, enemy.at(i)->getH() + 200,
							tjulni.at(t)->getX(), tjulni.at(t)->getY(), tjulni.at(t)->getW(), tjulni.at(t)->getH())
							&& (tjulni.at(t)->nosilec == -1 || tjulni.at(t)->nosilec == i))
						{
							enemy.at(i)->setDest(tjulni.at(t)->getX(), tjulni.at(t)->getY()); // nov cilj nasprotnika je tjulen
							// ko se tjulen in nasprotnik dotakneta
							if (univerzalniTrk(enemy.at(i)->getX(), enemy.at(i)->getY(), enemy.at(i)->getW(), enemy.at(i)->getH(),
								tjulni.at(t)->getX(), tjulni.at(t)->getY(), tjulni.at(t)->getW(), tjulni.at(t)->getH())
								&& ((enemy.at(i)->nosim == -1 && tjulni.at(t)->nosilec == -1) // tjulen in nasprotnik morata biti oba prosta
								|| (enemy.at(i)->nosim == t && tjulni.at(t)->nosilec == i))) // ali pa par (en se drzita drugega)
							{
								// tjulna premaknemo na nasprotnikov hrbet
								tjulni.at(t)->setX(enemy.at(i)->getX() + t);
								tjulni.at(t)->setY(enemy.at(i)->getY() + t);
								
								// nasprotnika in njegovega tjulna dolocimo kot par
								tjulni.at(t)->nosilec = i;
								enemy.at(i)->nosim = t;

								// tjulnova pozicija se spremeni na zaslonu
								tjulni.at(t)->updateImg(*this);

								// nasprotnikov naslednji cilj je farma
								enemy.at(i)->setDest(farmPos[0][trenutniNivo - 1], farmPos[1][trenutniNivo - 1]);

								// ko se tjulen dotakne farme ga ni v polju ampak je v farmi
								if (univerzalniTrk(farmPos[0][trenutniNivo - 1], farmPos[1][trenutniNivo - 1], 20, 20,
									tjulni.at(t)->getX(), tjulni.at(t)->getY(), tjulni.at(t)->getW(), tjulni.at(t)->getH()))
								{
									printf("Joj ne, zaprt sem v farmi!!!\n");
									++stTjulnFarma;
									if (!tjulni.empty()) {
										// ko sta dva v paru in en tjulen izgine iz polja (vectotja), rabimo spremeniti pare, ki so imeli vecji indeks tjulna od zbrisanega
										for (unsigned int popravi_nasprotnike = 0; popravi_nasprotnike < enemy.size(); ++popravi_nasprotnike) {
											if (enemy.at(popravi_nasprotnike)->nosim > (int)t) {
												--enemy.at(popravi_nasprotnike)->nosim;
											}
										}

										//tjulna izbrisemo
										delete tjulni.at(t);
										tjulni.erase(tjulni.begin() + t);
									}
									--stTjuln[trenutniNivo - 1]; // na polju je en tjulen manj
									enemy.at(i)->nosim = -1; // nasprotnik ima proste roke
								}
							}
						}
						//* testiram da se nasprotnk upocasni ko ne vidi igralca
						else if (rageMode) {
							enemy.at(i)->chill();
						}
						//*/
					}
				}
			}
			enemy.at(i)->updateImg(*this); // prikazemo nasorotnike
		}
	}
}