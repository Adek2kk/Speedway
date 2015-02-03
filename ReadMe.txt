Projekt wykonali:
Adam Chojan 109723 adam.chojan@student.put.poznan.pl
Roman Kaczorowski 109729 

Temat:
15. Sieciowa gra zuzel dla 2 osob.

Kompilacja:
Program działa w środowisku Linux. Kompilacja wymaga zainstalowania w systemie dodatkowej biblioteli SDL w wersji 1.2
Kompilacja odpywa się za pomoca pliku makefile.

Pliki źródłowe:
main- zawiera główny program z funkcjami server() i client(); znajduje sie w nim glowna petla gry.
move- zawiera dwie funkcje: lap_count oraz change_angle
circle_functions- zawiera dwie wersje rysowania koła. Jedna wersja zawiera sprawdzenie czy wystąpiła kolizja i jest wykorzystywana do rysowania pierwszego koła.D
Druga nie zawiera wykrywania kolizji i służy do rysowania "ogona" gracza.

Uruchomienie:
Najpierw należy uruchomić gracza "Hosta". Host uruchamiany jest z parametrem 1
./speedway 1.
Po uruchomieniu host czeka na dołaczeniu drugiego gracza. Drugi gracz łączy się z hostem po przez wpisanie ip hosta jako pierwszy argument
./speedway ip (np. 127.0.0.1)


