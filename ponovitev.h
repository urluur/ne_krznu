#pragma once
#include "igra.h"

class koordinati
{
private:
	short x, y;
public:
	koordinati();
	friend class ponovitev;
	friend class zapisek;
};

class zapisek {
private:
	short nivo, st_tock, st_polje, st_farma;
	class koordinati snap_igralec;
	vector <class koordinati> snap_nasprotniki, snap_aktivisti, snap_tjulni;
public:
	zapisek();
	friend class ponovitev;
};

class ponovitev
{
private:
	vector <class zapisek> buffer;
	short lastSnapTime, snapInterval;
	GameManager* igra;
public:
	ponovitev(GameManager&);
	friend class GameManager;
	void checkSnap();
	void snapShot();
	void predvajaj();
	void cleanup();
	void cleanLastLevel();
};
