#include "igra.h"

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
	cout << endl << "Zanimivost: ";
	vector <string> facts;
	//*
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
	facts.push_back("Ideja za boj z glavnim nasprotnikom se mi je porodila\nko sem igral igro Xenoblade Chronicles.");
	facts.push_back("Ce pritisnemo tipko esc se igra shrani in zapre.");
	facts.push_back("Problemi, na katere sem naletel ob programiranju: (od najmanjsega do najvecjega)\n- implementiranje novega znanja v projekt\n- prilagajanje velikosti zaslona\n- optimiziranje programa\n- izjeme (pri vektorjih)\nmoji mozgani so bili pretegnjeni po dolgem in pocez da sem naredil\nobnasanje nasprotnikov, aktivistov in tjulnov z vektorji");
	facts.push_back("Programerji obozujejo kavo. Med programiranjem te igre ni bila popita niti ena skodelica kave.");
	facts.push_back("Ta igra je sprva delovala v razmerju slike 4:3 v resoluciji 800x600.\nKasneje so bile grafike veckrat prenovljene.");
	facts.push_back("Ko sem zacel delat igro je bila prva stvar glavni meni.\nNaredil sem stiri slike. Vse enake,\nle kazalec se je bil na vsaki na drugem mestu. Ko je igralec pritisnil tipko,\nse je le slika zamenjala.. Zelo neprofesionalno... :>");
	facts.push_back("Veliko dela je bilo vlozenega v izpise v terminal, saj ga malokdo spregleda.");
	facts.push_back("Nisem nekdo ki bi ponavadi prosil za donacije,\nAMPAK! Ce imate slucajno namescen Brave Browser, mi na GitHubu\nlahko donirate kaksen novcic v BAT kriptovaluti. <3");
	facts.push_back("Med ogledom svojih premikov lahko pritisnete\npresledek da ustavite ali nadaljujete predvajanje.\nZ tipkama levo in desno se lahko rocno sprehajate po svojih premikih.");
	//*/
	if (facts.size() >= 0) {
		b = (short)facts.size();
		unsigned short nakljucni_fact = rand() % (b - a) + a;
		cout << endl << facts.at(nakljucni_fact) << endl << endl;
	}

	facts.clear();
	printf("Pritisni katerokoli tipko za izhod.");
	fflush(stdin);
	char ni_vazno = _getch();
}
