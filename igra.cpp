#include "igra.h"

void funFact();

void GameManager::pripraviVse() { // funkcija se klice na zacetku usakega od petih nivojev
	SDL_PollEvent(&event);
	cmdLevels();

	// vse spremenljivke glede nivoja so resetirane
	konecLevela = false; adios = false;
	semNaIzhodniLokaciji = false;
	staminadown = false; fillingStamina = false;
	w = false; a = false; s = false; d = false;
	stTjulnFarma = 0; trenutne_tocke = 0;
	jaz = new Image;
	srcki = new Image;
	boss_hp = 100;

	// nastavimo timer primeren nivoju
	short casovnik_na_nivo[5] = { 100, 80, 60, 50, 60 };
	cajt.set(casovnik_na_nivo[trenutniNivo - 1]);

	// pozicija na na kateri se igralec pokaze
	short spawnPos[2][5] = {
		// 1.  2.   3.   4.   5. nivo
		{200, 70,  30, 320, 150},   // x
		{ 20,  5, 530, 650, 600} }; // y

		// igralca postavimo na zacetno mesto
	igralec.setX(spawnPos[0][trenutniNivo - 1]);
	igralec.setY(spawnPos[1][trenutniNivo - 1]);
	jaz->init(*this, "common/img/player.png", spawnPos[0][trenutniNivo - 1], spawnPos[1][trenutniNivo - 1], igralec.w, igralec.h);

	// inicializiramo toliko srckov kolikor jih imamo
	updateSrcki();

	// stevilo aktivistov, nasprotnikov in tjulnov, ki jih bomo videli v nivoju
	//           1.              2.              3.              4.              5. nivo
	stAktiv[0] = 2; stAktiv[1] = 2; stAktiv[2] = 1; stAktiv[3] = 1; stAktiv[4] = 0;
	stNaspr[0] = 2; stNaspr[1] = 3; stNaspr[2] = 4; stNaspr[3] = 5; stNaspr[4] = 1;
	stTjuln[0] = 4; stTjuln[1] = 6; stTjuln[2] = 8; stTjuln[3] = 6; stTjuln[4] = 0;

	// te stevilke malo spremenimo za nightmare mode
	if (rageMode) {
		stAktiv[0] = 0; stAktiv[1] = 0; stAktiv[2] = 0; stAktiv[3] = 0;
		stNaspr[0] = 5; stNaspr[1] = 6; stNaspr[2] = 7; stNaspr[3] = 8;
		stTjuln[0] = 10; stTjuln[1] = 15; stTjuln[2] = 20; stTjuln[3] = 25;
	}

	// ustvarimo toliko nasprotnikov, kolikor jih v nivoju potrebujemo
	for (int i = 0; i < stNaspr[trenutniNivo - 1]; ++i) {
		enemy.push_back(new komoucar);
		if (trenutniNivo < 5) { // v vseh nivojih so nasprotniki rumeni, razen v 5. nivoju je rdec (boss.png)
			enemy.at(i)->initImg(*this, "common/img/nasprotnik.png", farmPos[0][trenutniNivo - 1] - i * 10, farmPos[1][trenutniNivo - 1] - i * 10);
		}
		else {
			enemy.at(i)->initImg(*this, "common/img/boss.png", farmPos[0][trenutniNivo - 1] - i * 10, farmPos[1][trenutniNivo - 1] - i * 10);
		}
		enemy.at(i)->zrcuniRandomDestinacijo(); // nasprotnik si izbere nakljucno lokacijo na katero se bo premaknil
	}

	// ustvarimo toliko tjulnov, kolikor jih v nivoju potrebujemo
	for (int i = 0; i < stTjuln[trenutniNivo - 1]; ++i) {
		tjulni.push_back(new Tjuln);
		tjulni.at(i)->initImg(*this, "common/img/tjuln.png");
	}

	// ustvarimo toliko ativistov, kolikor jih v nivoju potrebujemo
	for (int i = 0; i < stAktiv[trenutniNivo - 1]; ++i) {
		aktivisti.push_back(new komoucar);
		aktivisti.at(i)->initImg(*this, "common/img/aktivist.png", spawnPos[0][trenutniNivo - 1] - i * 10, spawnPos[1][trenutniNivo - 1] - i * 10);
		aktivisti.at(i)->zrcuniRandomDestinacijo();
	}
}

void GameManager::updateMap() { // funkcija se klice na koncu zanke nivoja
	// vse slike se bodo prikazale
	for (unsigned int i = 0; i < aktivisti.size(); ++i) {
		aktivisti.at(i)->display(*this);
	}
	for (unsigned int i = 0; i < enemy.size(); ++i) {
		enemy.at(i)->display(*this);
	}
	for (unsigned int i = 0; i < tjulni.size(); ++i) {
		tjulni.at(i)->display(*this);
	}
	for (unsigned int i = 0; i < kepe.size(); ++i) {
		kepe.at(i)->display(*this);
	}
	if (a) {
		jaz->flip();
	}
	else {
		jaz->unFlip();
	}
	jaz->display(okno.ren);
	srcki->display(okno.ren);
	SDL_RenderPresent(okno.ren); // na oknu se prikaze spremenjeno stanje
	okno.omejiFrame(); // omejimo hitrost prikaza
}

GameManager::GameManager() { // konstruktor je klican le enkrat, zgolj ko se program zazene
	// inicializiramo vse spremenljivke
	stTjulnFarma = 0;
	//joystick = nullptr; //(testiram)
	jaz = nullptr;
	boss_red_hp = nullptr;
	srcki = nullptr;
	stamina_wheel = new Image;
	konecLevela = false;
	adios = false;
	completed = false;
	semNaIzhodniLokaciji = false;
	fillingStamina = false;
	staminadown = false;
	for (int i = 0; i < 5; ++i) {
		najboljsi[i] = "";
		najbolse[i] = 0;
	}
	stamina = 100;
	hitrost = 2;
	trenutniNivo = 0;
	stAktiv[0] = 2; stAktiv[1] = 2; stAktiv[2] = 1; stAktiv[3] = 1; stAktiv[4] = 0;
	stNaspr[0] = 2; stNaspr[1] = 3; stNaspr[2] = 4; stNaspr[3] = 5; stNaspr[4] = 1;
	stTjuln[0] = 4; stTjuln[1] = 6; stTjuln[2] = 8; stTjuln[3] = 6; stTjuln[4] = 0;
	zivljenja = 3;
	skupne_tocke = 0;
	trenutne_tocke = 0;
	boss_hp = 100;
	perfect_run = true;
	SDL_PollEvent(&event);
}

int GameManager::init() { // funkcija se klice le enkrat, ko se zazene SDL okno
	 // SDL inicializacija
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cerr << "SDL Init, Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	// ustvarimo SDL okno
	okno.window = SDL_CreateWindow("NE krznu -urlu", // naslov okna
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // pozicija okna
		// velikost okna pomnozena z nasimi zeljenimi dimentijami
		okno.scaleCal(okno.returnWindowWidth()), okno.scaleCal(okno.returnWindowHeight()),
		SDL_WINDOW_SHOWN); // okno je vidno
	if (okno.window == NULL) {
		cerr << "SDL Create Window, Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	// ustvarimo renderer (SDL struktura, ki prikaze piksle v okno na zaslonu)
	// (-1) uporabimo prvi kompatibilni grficni gonilnik, uporabljamo graficno kartico, ce je mogoce
	okno.ren = SDL_CreateRenderer(okno.window, -1, SDL_RENDERER_ACCELERATED);
	if (okno.ren == nullptr) {
		cerr << "Could not create ren! SDL error" << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	if (TTF_Init()) { // inicializacija pisav (TrueTypeFont)
		cerr << "TTF_Init Error: " << TTF_GetError() << endl;
		return EXIT_FAILURE;
	}
	okno.surface = SDL_GetWindowSurface(okno.window); // inicializacija za prikazovanje slik
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
		printf("IMG_Init Error: %s\n", IMG_GetError());
		return EXIT_FAILURE;
	}

	// nastavimo ikono v opravilni vrstici in oknu
	Image ikona(okno.ren, "common/img/ikona.png", 0, 0, 29, 29);
	SDL_Surface icon = ikona.returnSurface();
	SDL_SetWindowIcon(okno.window, &icon);

	/* lenartov nacin za kontroler (zelo zelo alfa testiram)
	int numJoystick = SDL_NumJoysticks();
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks());
	printf("The names of the joysticks are:\n");
	for (int i = 0; i < SDL_NumJoysticks(); ++i)
		std::cout << "	" << SDL_JoystickNameForIndex(i) << std::endl;
	if (numJoystick > 0) {
		SDL_JoystickEventState(SDL_ENABLE);
		joystick = SDL_JoystickOpen(0);
	}
	*/

	srand(time(NULL)); // poskrbi da generiramo nakljucna stevila
	return EXIT_SUCCESS;
}

void GameManager::haltEnter(short nivo) { // se klice, ko cakamo da igralec pritisne tipko enter
	// prikazemo sliko "pritisni enter"
	Image img_enter;
	img_enter.ini(*this, "common/img/pressreturn.png");
	img_enter.display(okno.ren);
	SDL_RenderPresent(okno.ren);

	// dokler igralec ne pritisne na enter, previrjamo ce bo pritisnil na esc za prisilni izhod
	SDL_PollEvent(&event);
	while (!keys[SDL_SCANCODE_RETURN]) {
		okno.stejFrame();
		preveriEsc(nivo);
		okno.omejiFrame(); // omejimo osvezevanje zaslona, da racunalnik ne dela kolikor hitro zmore
	}
}

void GameManager::setCompleted(bool resnica) { // se klice, ko koncamo vseh 5 nivojev
	completed = resnica; // ta spremenljivka bo nastavila drugacen zacetni zaslon (vesel konec)
	setNivo(0);
	trenutne_tocke = 0;
	skupne_tocke = 0;
	zivljenja = 3;

	// glede na to da smo igro koncali se podatki resetirajo, da ob izhodu drug igralec lahko upise svoje ime
	ofstream quicksave;
	quicksave.open("quicksave.txt");
	if (quicksave.is_open())
		quicksave << "bumbar\n0\n3\n0\n";
	else {
		cerr << "Error: setting complete" << endl;
		cleanup();
		exit(1);
	}
	quicksave.close();
}

void GameManager::cleanupVectors() { // se klice, ko hocemo izbrisati dinamicni pomnilnik (po vsakem nivoju in na koncu igre)
	if (jaz != nullptr) {
		delete jaz; // izbrisemo sliko igralca
		jaz = nullptr;
	}
	if (srcki != nullptr) {
		delete srcki; // izbrisemo sliko srckov
		srcki = nullptr;
	}
	if (!enemy.empty()) { // brisemo
		for (unsigned int i = 0; i < enemy.size(); ++i) {
			delete enemy.at(i); // izbrisemo vse nasprotnike
		}
		enemy.clear(); // izbrisemo vse kazalce na izbrisane nasprotnike
	}
	enemy.shrink_to_fit(); // vektorjevo kapaciteto zmanjsamo, ce je mogoce
	if (!tjulni.empty()) {
		for (unsigned int i = 0; i < tjulni.size(); ++i) {
			delete tjulni.at(i); // izbrisemo vse tjulne
		}
		tjulni.clear();  // izbrisemo vse kazalce na izbrisane tjulne
	}
	tjulni.shrink_to_fit(); // vektorjevo kapaciteto zmanjsamo, ce je mogoce
	if (!aktivisti.empty()) {
		for (unsigned int i = 0; i < aktivisti.size(); ++i) {
			delete aktivisti.at(i); // izbrisemo vse aktiviste
		}
		aktivisti.clear();  // izbrisemo vse kazalce na izbrisane aktiviste
	}
	aktivisti.shrink_to_fit(); // vektorjevo kapaciteto zmanjsamo, ce je mogoce
	if (!kepe.empty()) {
		for (unsigned int i = 0; i < kepe.size(); ++i) {
			delete kepe.at(i); // izbrisemo vse kepe
		}
		kepe.clear();  // izbrisemo vse kazalce na izbrisane kepe
	}
	kepe.shrink_to_fit(); // vektorjevo kapaciteto zmanjsamo, ce je mogoce

}

void GameManager::cleanup() { // se klice ko zelimo popolnoma zapreti igro
	boss_red_hp = nullptr;
	if (stamina_wheel != nullptr) {
		delete stamina_wheel; // sliko igralcene uzdrzljivosti brisemo le enkrat, saj jo dinamicno dolocimo le enkrat
		stamina_wheel = nullptr;
	}
	cleanupVectors(); // preverimo in izbrisemo dinamicni pomnilnik
	jaz = nullptr;
	SDL_DestroyWindow(okno.window); // zapremo okno
	/* to samo testiram za kontroler
	if (joystick != nullptr) SDL_JoystickClose(joystick);
	*/
	sound.toggle(false);
	funFact();
	SDL_Quit(); // izhod iz SDL
}

void GameManager::updateSrcki() {
	string pathFragment = "common/img/srcki/srcki";
	pathFragment += to_string(zivljenja);
	pathFragment += ".png";
	char* path = new char[pathFragment.size() + 1];
	std::copy(pathFragment.begin(), pathFragment.end(), path);
	path[pathFragment.size()] = '\0';
	srcki->init(*this, path, 1080, 670, 200, 50);
	delete[] path;
}

void GameManager::cmdLevels() {
	system("cls");
	cout << "### Tjulenlandija ###" << endl;
	for (int i = 0; i <= 5; ++i) {
		if (trenutniNivo == i) {
			cout << "->";
		}
		else {
			cout << "  ";
		}
		switch (i) {
		case 1:
			cout << "1. nivo" << endl; // neki cudno se to obnasa nevemzakaj.. zdi se mi zato k mam nekje -1 samo nevem kje
			break;
		case 2:
			cout << "  2. nivo" << endl;
			break;
		case 3:
			cout << "  3. nivo" << endl;
			break;
		case 4:
			cout << "  4. nivo" << endl;
			break;
		case 5:
			cout << "  5. nivo (glavni bebec)" << endl;
			break;
		case 6:
			cout << "Tjulenlandija resena!" << endl;
			break;
		}
	}
}

void funFact() {
	short a = 0, b;
	system("cls");
	cout << endl << "Ali ste vedeli: ";
	vector <string> facts;

	facts.push_back("To igro je delal en clovek 4 mesece.\nCyberpunk je naredilo vec kot 400 ljudi v 4ih letih.\nNe krznu je boljsi od Cyberpunk.\nCD Projekt zaposlite me.");
	facts.push_back("Ko pritisnemo pavzo lahko opazimo nekaj zanimivega...");
	facts.push_back("Ce ne izgubimo niti enega zivljenja in se nasprotnik ne dotakne niti enega tjulna\nste opravili perfektni poizkus. Le kaj se zgodi za tem?");
	facts.push_back("Najboljsa strategija za premagovanje zadnjega nasprotnika je, da ga udarimo,\nnato pa vrzemo tri kepe, ko se nam obnavlja uzdrzljivost.");
	facts.push_back("Vsa koda in njena zgodovina je javno dostopna,\nkar pomeni da si jo lahko ogledate, spremenite\nin te spremembe predlagate za naslednjo razlicico.");
	facts.push_back("Ce imate ustvarjalno zilico lahko po svojih zeljah\nslike v /common/img mapi spremenite ali zamenjate.\nEnako lahko naredite s /common/sounds/soundtrack.wav");
	facts.push_back("Vse kar se izpise v terminalu je bilo natipkano rocno (razen animacija 6)");
	facts.push_back("Vse slike so bile narisane v odlicnem slikarskem programu GIMP\n(razen animacija 6 je bila v Photoshopu)");
	facts.push_back("Datum za izdajo koncne verzije je bil ze dvakrat zamaknjen.");
	facts.push_back("Ce igro shranimo in zapremo ko delamo perfekten poizkus, ta ne bo stel/deloval.");
	facts.push_back("Ta igra ni originalna ideja, profesorica je poslala tocna navodila\no cem naj se igra gre. Navodila najdete na githubu v mapi common/naloge");
	facts.push_back("Ena od funkcij te igre je bila lokalni vecigralski nacin\nkjer bi lahko dodatni igralci z kontrolerji upravljali aktiviste\na je bila ta funkcija preklicana zaradi tezav z uporabo kontrolerja.");
	facts.push_back("Ko sem sosolca uprasal kaj naj dodam v igro mi je rekel naj dodam\n'kill computer button'. Najdi ga :)");
	facts.push_back("Ime 'NE krznu' izvira iz dolge tradicije poimenovanj iger,\nki jih Vegovci programirajo v tretjem letniku.\nImena iger iz prejsnjih let so:\n- Johnny Englishhh (2016/17)\n- Sea shepherd rules (2017/18)\n- Dol s plastiko (2018/19)\n- Resi amazonski pragozd (2019/20)\n- NE krznu (2020/21)\nKdo ve kaksna imena se bodo profesorji se spomnili... ;)");
	facts.push_back("Ce se zelite po polju hitreje premikati, tecite posevno.");
	facts.push_back("Ce se vam zdi da razvijalec te igre obvlada programiranje\nvas bo to sokiralo: v drugem letniku je imel zakljuceno 2,\nv tretjem pa povprecje kaze na 3 (2,75)");
	facts.push_back("Lukov zgled za razvijanje iger je definitivno Nintendo.\nIgre imajo vec globine, kot se nam zdi na prvi pogled,\nin zelo pomembno je, da ko jo nekdo igra uziva in se ima fajn.");
	facts.push_back("Od razvijanja te igre sem odnesel nekaj pametnih nasvetov za programerje:\n1. Uporabljajte aplikacijo Workrave, ki lahko izboljsa vase zdravje.\n2. Ko ne veste kako se necesa lotiti zaprite IDE in pisite po tabli (lahko virtualni, npr MS Whiteboard)\n3. Za vse projekte uporabljajte Git. Veliko bolje od ostalih online drive-ov.");
	facts.push_back("Ce naletite na napako, jo prijavite na vec -> izvorna koda -> issues -> new issue");
	facts.push_back("Resolucija zaslona 360p je ustvarjena izklucno za to\nker zelim igro narediti primirno za igranje na telefonu.");
	facts.push_back("Windows in Linux sta trenutno edini platformi, kjer lahko igro namestimo.\nMoja zelja je ustvariti se verzijo za Android in Nintendo Switch.");
	facts.push_back("Veliko motivacije in zagona sem dobil od github.com/therok1 in github.com/LenartSvetek\nHvala! :)");
	facts.push_back("Tjulni pobrani iz farm vam prinesejo zelo malo tock.");
	facts.push_back("Vec srckov kot imamo, vec tock bomo dobili.");
	facts.push_back("Tjulni ki so bili pobrani hitreje, prinesejo vec tock.");
	facts.push_back("Ideja za krog uzdrzljivosti izvira iz igre The Legend of Zelda: Breath of the Wild");
	facts.push_back("Ideja za kazalec v menujih izvira iz igre Final Fantasy VII");
	facts.push_back("Ideja za izgled otoka izvira iz igre Super Mario World");
	facts.push_back("Ideja za boj z glavnim nasprotnikom izvira iz igre Xenoblade Chronicles in mnogih drugih iger.");
	facts.push_back("Ce pritisnemo tipko esc se igra shrani in zapre.");
	facts.push_back("Problemi, na katere sem naletel ob programiranju: (od najmanjsega do najvecjega)\n- implementiranje novega znanja v projekt\n- prilagajanje velikosti zaslona\n- optimiziranje programa\n- izjeme (pri vektorjih)\nmoji mozgani so bili pretegnjeni po dolgem in pocez da sem naredil\nobnasanje nasprotnikov, aktivistov in tjulnov z vektorji");
	facts.push_back("Odkar je bila ta igra v razvoju je bilo vec hrane pojedene v sobi kot v jedilnici.");
	facts.push_back("Programerji obozujejo kavo. Med programiranjem te igre ni bila popita niti ena skodelica kave.");


	if (facts.size() >= 0) {
		b = (short)facts.size();
		unsigned short nakljucni_fact = rand() % (b - a) + a;
		cout << endl << facts.at(nakljucni_fact) << endl << endl;
	}

	facts.clear();
	printf("Pritisni katerokoli tipko za izhod.\n");
	char ni_vazno = _getch();
}