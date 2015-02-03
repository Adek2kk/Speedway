			 _____ ______  _____  _____ ______  _    _   ___  __   __
			/  ___|| ___ \|  ___||  ___||  _  \| |  | | / _ \ \ \ / /
			\ `--. | |_/ /| |__  | |__  | | | || |  | |/ /_\ \ \ V / 
			 `--. \|  __/ |  __| |  __| | | | || |/\| ||  _  |  \ /  
			/\__/ /| |    | |___ | |___ | |/ / \  /\  /| | | |  | |  
			\____/ \_|    \____/ \____/ |___/   \/  \/ \_| |_/  \_/  
                                                         

Projekt wykonali: 

	Adam Chojan 109723 adam.chojan@student.put.poznan.pl
	Roman Kaczorowski 109729 roman.kaczorowski@student.put.poznan.pl
                                                         
1. Ogólny opis 
	
	Temat nr 15. Gra sieciowa Żużel dla 2 osób.

2. Opis protokołu komunikacji.

	W grze bierze udział dwóch graczy: gracz HOST i CLIENT. Gracze są odpowiednio 
	powiązani z portami 6668 i 6667.

	Gracz HOST rozpoczyna grę i zaczyna nasłuchiwać pakietów na swoim porcie.

	Gracz CLIENT dołącza się do gry rozpoczynając wysyłanie na port HOSTA pakietu 
	zawierającego informację o swojej pozycji.

	Po otrzymaniu pierwszej pozycji gracza CLIENT gracz HOST również rozpozpoczyna 
	wysyłanie swojej pozycji na port CLIENTA. Od tego momentu rozpoczyna się rozgrywka.

	Jednocześnie obaj gracze rozpoczynają nasłuchiwanie pakietów TCP na swoich 
	portach. Gdy dany gracz dojedzie na metę zaprzestaje nadawać komunikat o swojej 
	pozycji, a następnie przesyła na port przeciwnika pakiet z informacją o uzyskanym 
	wyniku. 

	Po otrzymaniu przez obu graczy informacji o wyniku przeciwnika można zamknąć
	aplikację.


3. Opis plików źródłowych i ogólnie przyjętego modelu implementacji

	Aplikacja została napisana w języku C++ z wykorzystaniem biblioteki SDL1.2 do 
   	stworzenia interfejsu graficznego. 

	W głównym folderze znajdują się:
	- plik Makefile 
	- plik README
	- main - zawiera główny program z funkcjami server() i client(); znajduje się w nim główna pętla gry.
	- move - zawiera dwie funkcje: lap_count oraz change_angle
	- circle_functions - zawiera dwie wersje rysowania koła. Jedna wersja zawiera sprawdzenie czy wystąpiła kolizja i jest wykorzystywana do rysowania pierwszego koła.
	Druga nie zawiera wykrywania kolizji i służy do rysowania "ogona" gracza.

4. Informacje o kompilacji i użytkowaniu.

	UWAGA! Do poprawnego działania aplikacji konieczne jest zainstalowanie biblioteki SDL1.2.

	Aplikacja korzysta z systemu budowania make. W tym celu stworzony został plik Makefile 
   	zawierający wszystkie niezbędne polecenia służące kompilacji kodu źródłowego.

	Aby skompilować program należy wpisać następujące komendy:

	 $ make

	Najpierw należy uruchomić gracza "Hosta". Host uruchamiany jest z parametrem 1
	 
	 $ ./speedway 1.

	Po uruchomieniu host czeka na dołączeniu drugiego gracza. Drugi gracz łączy się z hostem po przez wpisanie ip hosta jako drugi argument

	 $ ./speedway 2 ip (np. 127.0.0.1)

	Po uzyskaniu połączenia między graczami po około trzech sekundach rozpocznie się rozgrywka,
	co zostanie zakomunikowane zielonym światłem i ruszeniem graczy. Każdy z graczy porusza się 
	zielonym punktem. 

	Rozgrywka trwa 4 okrążenia. Po zakończeniu rozgrywki przez obu graczy aplikację można zamknąć.
