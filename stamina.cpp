#include "igra.h"

void GameManager::racuniStamino() {
	if (staminadown || stamina < 100) {
		if (stamina > 0 && staminadown && !fillingStamina) {
			hitrost = 3;
			--stamina;
			initNavadnaStamina();
		}
		else if (stamina == 0 && staminadown) {
			hitrost = 2;
			fillingStamina = true;
		}
		else if (!staminadown) {
			hitrost = 2;
			if (stamina == 99) {
				fillingStamina = false;
			}
			++stamina;
			if (fillingStamina)
				initRisingStamina();
			else
				initNavadnaStamina();
		}
	}
	stamina_wheel->display(okno.ren);
}

void GameManager::initNavadnaStamina() {
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

void GameManager::initRisingStamina() {
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