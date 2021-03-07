#include "igra.h"

void GameManager::racuniStamino() { // klice se ob premikanju igralca po polju
	// uzdrzljivost racunamo le ce tiscimo tipko shift ali ce je uzdrzljivost pod 100 (zato da jo lahko polnimo)
	if (staminadown || stamina < 100) {
		// tecemo in uzdrzljivost se nam manjsa
		if (stamina > 0 && staminadown && !fillingStamina) {
			hitrost = 3;
			--stamina;
			initNavadnaStamina();
		}
		
		// utrudili smo se od teka
		else if (stamina == 0 && staminadown) {
			hitrost = 2;
			fillingStamina = true; // uzdrzljivost se nam zacne zvisevati
		}

		// ne tecemo
		else if (!staminadown) {
			hitrost = 2;
			if (stamina >= 99) { // odpocili smo se od teka
				fillingStamina = false;
			}
			else {
				++stamina;
			}

			// dolocimo barvo in sliko uzdrzljivosti glede na to ali se polni ali prazni
			if (fillingStamina) {
				initRisingStamina();
			}
			else {
				initNavadnaStamina();
			}
		}
	}

	// narisemo sliko uzdrzljivosti na zaslon
	stamina_wheel->display(okno.ren);
}

void GameManager::initNavadnaStamina() { // se klice ko se uzdrzljivot manjsa
	// inicializiramo sliko uzdrzljivosti v spodnji levi kot, odvisko od koliko jo imamo
	switch (stamina) {
	case 100:
	case 90:
		stamina_wheel->init(*this, "common/img/stamina_wheel/8.png", 5, 675, 40, 40);
		break;
	case 80:
	case 70:
		stamina_wheel->init(*this, "common/img/stamina_wheel/7.png", 5, 675, 40, 40);
		break;
	case 60:
		stamina_wheel->init(*this, "common/img/stamina_wheel/6.png", 5, 675, 40, 40);
		break;
	case 50:
		stamina_wheel->init(*this, "common/img/stamina_wheel/5.png", 5, 675, 40, 40);
		break;
	case 40:
		stamina_wheel->init(*this, "common/img/stamina_wheel/4.png", 5, 675, 40, 40);
		break;
	case 30:
		stamina_wheel->init(*this, "common/img/stamina_wheel/3.png", 5, 675, 40, 40);
		break;
	case 20:
		stamina_wheel->init(*this, "common/img/stamina_wheel/2.png", 5, 675, 40, 40);
		break;
	case 10:
		stamina_wheel->init(*this, "common/img/stamina_wheel/1.png", 5, 675, 40, 40);
		break;
	case 0:
		stamina_wheel->init(*this, "common/img/stamina_wheel/0.png", 5, 675, 40, 40);
		break;
	}
}

void GameManager::initRisingStamina() { // se klice ko se uzdrzljivost veca
	// inicializiramo sliko uzdrzljivosti v spodnji levi kot, odvisko od koliko jo imamo
	switch (stamina) {
	case 100:
		stamina_wheel->init(*this, "common/img/stamina_wheel/8.png", 5, 675, 40, 40);
	case 90:
		stamina_wheel->init(*this, "common/img/stamina_wheel/8.png", 5, 675, 40, 40);
		break;
	case 80:
	case 70:
		stamina_wheel->init(*this, "common/img/stamina_wheel/up7.png", 5, 675, 40, 40);
		break;
	case 60:
		stamina_wheel->init(*this, "common/img/stamina_wheel/up6.png", 5, 675, 40, 40);
		break;
	case 50:
		stamina_wheel->init(*this, "common/img/stamina_wheel/up5.png", 5, 675, 40, 40);
		break;
	case 40:
		stamina_wheel->init(*this, "common/img/stamina_wheel/up4.png", 5, 675, 40, 40);
		break;
	case 30:
		stamina_wheel->init(*this, "common/img/stamina_wheel/up3.png", 5, 675, 40, 40);
		break;
	case 20:
		stamina_wheel->init(*this, "common/img/stamina_wheel/up2.png", 5, 675, 40, 40);
		break;
	case 10:
		stamina_wheel->init(*this, "common/img/stamina_wheel/up1.png", 5, 675, 40, 40);
		break;
	}
}