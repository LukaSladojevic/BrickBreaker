Brick Breaker - Luka & Brano (3D Edition)
Ovo je napredna verzija klasične arkadne igre Brick Breaker, razvijena u jeziku C++ uz korištenje SFML biblioteke. Igra uključuje progresivni sustav nivoa, zvučne efekte i specifičan vizualni stil.

🛠 Ovisnosti (Dependencies)
Projekt se oslanja na sljedeće tehnologije i biblioteke:

Visual Studio 2022: Razvojno okruženje korišteno za pisanje i prevođenje koda.

SFML 2.6.x: Biblioteka za multimediju (grafika, prozor, zvuk).

sfml-graphics: Za iscrtavanje loptice, palice i 3D cigli.

sfml-audio: Omogućuje reprodukciju zvučnih efekata tijekom igre.

sfml-window & sfml-system: Za upravljanje prozorom i osnovnim funkcijama sustava.

🚀 Kako pokrenuti projekt
Otvoreno rješenje: Pokrenite .sln datoteku u Visual Studiju.

NuGet Restore: Ako paketi nedostaju, kliknite desni klik na Solution i odaberite Restore NuGet Packages.

Potrebni resursi: Pobrinite se da su sljedeće datoteke u istom folderu kao i izvorni kod:

font.ttf (font za prikaz rezultata i nivoa).

paddle.wav, hit.wav, break.wav, lose.wav (zvučni efekti).

Pokretanje: Postavite konfiguraciju na x64 Debug i pritisnite F5.

🎮 Kontrole u igri
Strelice LIJEVO / DESNO: Pomicanje palice (Paddle).

SPACE (Razmaknica): Početak igre ili nastavak nakon gubitka loptice.

Tipke 1 - 5: Hidden Keys koji omogućuju trenutni skok na željeni nivo (za potrebe prezentacije).

💎 Značajke (Features)
3D efekt cigli: Cigle se sastoje od dva sloja za postizanje dubine.

Sustav otpornosti: Plave cigle zahtijevaju dva udarca, dok su bijele cigle neuništive.

Dizajn nivoa: Uključuje "Space Invader" formaciju na 4. nivou i potpuno generirani nasumični 5. nivo.

Audio povratna informacija: Specifični zvukovi za različite vrste sudara i gubitak života.

⚠️ Rješavanje problema (Troubleshooting)
Greška kod otvaranja .lib datoteke: Ako koristite Debug mod, provjerite jesu li u postavkama Linkera navedene datoteke s -d sufiksom (npr. sfml-audio-d.lib).

Nedostajuće DLL datoteke: Ako program javi da nedostaju .dll datoteke, kopirajte ih iz SFML bin foldera u folder gdje se nalazi vaš .exe.

Problem s učitavanjem resursa: Provjerite jesu li nazivi svih .wav i .ttf datoteka identični onima u kodu.

Autori: Luka & Brano