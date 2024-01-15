# Ne krznu

Moja prva SDL2/C++ igra

## O projektu 

Predmet: RPA, prof. Nataša Makarovič, Vegova Ljubljana

Luka Uršič R 3. A, jan. - apr. 2021


# Namestitev

Igro lahko prenesete [tukaj](https://github.com/urluur/ne_krznu/releases).

- Če prenesete installer za Windows se bo po namestitvi bližnjica pokazala na namizju.

- Če pa ste prenesli portable verzijo;
  - razširite .zip datoteko
  - kliknite na `ne_krznu.exe`

![overworld](https://github.com/urluur/ne_krznu/blob/master/common/screenshoots/overworld.png?raw=true)

# Navodila

## Pred igro

- Začnete tako, da vnesete svoje ime in kliknete `Enter`
- Velikost zaslona lahko spremenite v `Nastavitve -> Dimenzije`

  ![main menu](https://github.com/urluur/ne_krznu/blob/master/common/screenshoots/mainmenu.png?raw=true)

## Igranje

### Tjulni

- Na polju so tjulni, katere rešujemo.
- Ko se ga dotaknemo je tjulen rešen in število tjulnov na polju se zmanjša. (npr. `polje: 2`)

### Farme

- Tjulni so lahko tudi v farmah, ko jih nasprotniki odnesejo do tja.
- Ko se dotaknemo farme, rešimo tjulne v njej.
- Vemo, da je en tjulen v farmi zaradi napisa: `farma: 1`

  ![gameplay](https://github.com/urluur/ne_krznu/blob/master/common/screenshoots/gameplay.png?raw=true)

### Nasprotniki

- Rdeče oblečeni nasprotniki lovijo tjulne na polju.
- Tjulna poberejo in ga nesejo na farmo.
- Če pa pridemo dovolj blizu njih, bodo spustili tjulna in začeli preganjati nas.

### Aktivisti

Aktivisti se sprehajajo po polju in poizkušajo najti tjulna. Če mu pridejo dovolj blizu, ga poberejo in nam ga prinesejo.

### Cilj igre

Da končamo nivo, moramo rešiti vse tjulne na polju in farmi, ter se premakniti na označen izhod iz nivoja.

## Dodatno

- Lestvica
  - Najboljših 5 igralcev z največ točkami je zapisanih na lestvici
- Ogled premikov
  - Po končani igri si lahko ogledamo svoje premike skozi vse nivoje

    ![replay](https://github.com/urluur/ne_krznu/blob/master/common/screenshoots/replay.png?raw=true)

- Zgodba
  - sm prou narisu slike in se zmislu zgodbo kr cene bi blo preuc boring
  - se celo ascii art sm narisu za vecino stvari
  - to je biu korona cajt folk, ofc da nism meu lajfa
  
    ![animation](https://github.com/urluur/ne_krznu/blob/master/common/screenshoots/animation.png?raw=true)