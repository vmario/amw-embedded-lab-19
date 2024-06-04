---
title: "Ćwiczenie 19: Magistrala SPI na przykładzie akcelerometru"
subtitle: "Instrukcja laboratorium"
footer-left: "Instrukcja laboratorium"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.png"
logo-width: "70mm"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
  \usepackage{algorithm}
  \usepackage{algpseudocode}
  \usepackage{tikz}
  \usetikzlibrary{automata, positioning, arrows, shapes, patterns}
  \usepackage{tikz-timing}
  \usepackage{xfrac}
  \usepackage{ellipsis}
  \usetikzlibrary{positioning}
  \usepackage[raster]{tcolorbox}
  \usepackage{lcd}
  \LCDcolors[MidnightBlue]{MidnightBlue!10}{MidnightBlue!80}
...

\lstset{language=[11]C++}
\tikzset{
    >=stealth',
    node distance=2.8cm,
    every state/.style={thick, fill=gray!20, align=center, text width=1.1cm},
    auto,
    font=\footnotesize,
}

> I'm not a great programmer; I'm just a good programmer with great habits.
>
> — _Kent Beck_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* działaniem magistrali SPI,
* odczytem danych z akcelerometru.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _LCD Keypad Shield_ do _Arduino Uno_.
1. Podłącz akcelerometr.
1. Na wyświetlaczu wyświetlane są zerowe wartości parametrów.

\begin{center}
\LCD{2}{16}
    |       {|}{|}       |
    |00 0x0000=     0|
\captionof{figure}{Wyjściowy stan wyświetlacza}
\end{center}

Do płytki podłączony jest układ scalony MPU-6500 firmy InvenSense (obecnie wchodzącej w skład TDK), który jest czujnikiem typu MEMS (_Microelectromechanical System_), integrującym obwody elektroniczne z&nbsp;czujnikami mechanicznymi: trzyosiowym akcelerometrem i trzyosiowym żyroskopem. Umożliwiają one pomiar przyspieszenia (akcelerometry) oraz prędkości obrotowej (żyroskopy) w&nbsp;trzech ortogonalnych osiach.

![Orientacja osi w czujniku MPU-6500](axes.png){width=200px}

![Budowa wewnętrzna podobnego czujnika — MPU-6050. Obok struktur elektronicznych widoczne są elementy mechaniczne, dokonujące pomiaru](dies.jpg){width=500px}

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Akcelerometry znajdują bardzo szerokie zastosowanie: oceniają przechył telefonu komórkowego, stabilizują obraz w aparatach fotograficznych, zliczają kroki w~smartwatchu, uruchamiają poduszki powietrzne w~samochodzie czy mierzą przeciążenia mózgu graczy NHL po uderzeniu krążkiem hokejowym (do tego zastosowania firma STM musiała poszerzyć zakres pomiarowy swoich czujników).}

Dzięki zasadzie równoważności, która mówi, że jednorodone statyczne pole grawitacyjne jest dla obserwatora nieodróżnialne od ruchu z przyspieszeniem (_vide_ pojęcie przyspieszenia ziemskiego), akcelerometr nadaje się również do pomiaru siły pola grawitacyjnego. Z kolei siła grawitacji w&nbsp;określonej osi jest zależna od nachylenia tej osi do np. powierzchni Ziemi, co łatwo możemy zaobserwować przechylając stół — przy pewnym kącie nachylenia składowa siły grawitacji dociskająca przedmioty do powierzchni stołu staje się zbyt mała do ich utrzymania[^1].

[^1]: Jest to zagadnienie powszechnie wykorzystywane do dręczenia uczniów i studentów, gdyż jest praktycznym przykładem użycia trygonometrii.

Wobec powyższego akcelerometr zmienia wskazania w zakresie $\pm 1\ g$ w zależności od nachylenia danej osi do powierzchni Ziemi.

# Zadanie podstawowe

Czujnik MPU-6500 może komunikować się z mikrokontrolerem za pomocą magistrali I²C lub SPI. Ze względu na dostępne wyprowadzenia mikrokontrolera użyto interfejsu SPI.

Celem zadania podstawowego jest skonfigurowanie SPI i odczytanie z czujnika numeru identyfikacyjnego.

## Wymagania funkcjonalne

1. Na wyświetlaczu widoczny jest identyfikator czujnika.

## Modyfikacja programu

### Konfiguracja interfejsu SPI

Interfejs SPI (_Serial Peripheral Interface_) jest prostym interfejsem, w którym na jednym zboczu zegara kontroler magistrali (_master_) i układ peryferyjny (_slave_) wystawiają dane, a na przeciwnym — odczytują je. Transmisja zawsze jest możliwa w obie strony, choć nie zawsze oba urządzenia rzeczywiście wystawiają dane (jeżeli nie — odbiorca ignoruje przychodzące bity).

Transmisja z kontrolera do układu peryferyjnego zachodzi na linii _MOSI_ (_Master Out, Slave In_) zaś w&nbsp;drugą stronę — na linii MISO (_Master In, Slave Out_). Kontroler magistrali odpowiada za generowanie sygnału zegarowego. Steruje również liniami _CS_ (_Chip Select_). Każdy układ peryferyjny ma swoją linię _CS_, na której stan aktywny (logiczne 0) oznacza, że dane urządzenie zostało przez kontroler wybrane do komunikacji (pozostałe linie są współdzielone). Nawet jeżeli komunikujemy się tylko z jednym urządzeniem peryferyjnym, wskazane jest sterowanie linią _CS_, gdyż łatwo wtedy wskazać początek i&nbsp;koniec transmisji.

Mimo zasadniczej prostoty interfejs SPI ma wiele trybów pracy, różniących się:

* polaryzacją zegara (stanem zegara w stanie uśpienia),
* fazą zegara (zboczem, na którym są odczytywane dane),
* kolejnością bitów w bajcie,
* szybkością zegara.

W celu skonfigurowania interfejsu uzupełnij metodę `SPI::initialize()` o ustawienie odpowiednich bitów w rejestrze `SPCR`. Ustaw bity `SPE` (_SPI Enable_) oraz `MSTR` (_Master/Slave Select_), aby włączyć SPI w trybie _master_, a pozostałe bity ustaw zgodnie ze sprawozdaniem z ćwiczenia.

### Implementacja transferu bajtu przez SPI

Uzupełnij metodę `Spi::transfer()` o następujące kroki:

1. Wpisanie wysyłanego bajtu do rejestru `SPDR`.
1. Oczekiwanie na ustawienie flagi `SPIF`, świadczącej o zakończeniu transferu.
1. Zwrócenie odebranego bajtu z rejestru `SPDR`.

Ustawienie flagi można sprawdzać w pustej pętli:

```
while (bit_is_clear(SPSR, SPIF)) ;
```

### Implementacja odczytu rejestru

Uzupełnij metodę `Spi::readRegister()` o następujące kroki:

1. Ustawienie linii _CS_ za pomocą `gpio.chipSelect(true)`, co ustawia odpowiedni pin w stan niski (aktywny).
1. Wysłanie bajtu z adresem za pomocą wcześniej uzupełnionej metody `Spi::transfer()`. Wysyłany bajt musi mieć dodatkowo ustawiony najstarszy bit, co oznacza operację odczytu.
1. Zapamiętanie w zmiennej bajtu zwróconego przez drugie wywołanie metody `Spi::transfer()`.
1. Zwolnienie linii _CS_ za pomocą `gpio.chipSelect(false)`, co ustawia odpowiedni pin w&nbsp;stan wysoki (nieaktywny).
1. Zwrócenie odebranego bajtu.

### Odczytanie wartości rejestru _Who Am I_

W metodzie `Accelerometer::whoAmI()` wywołaj metodę `Spi::readRegister()` jako argument podając adres rejestru _Who Am I_. Na początku drugiej linii wyświetlacza powinien być widoczny identyfikator czujnika.

\awesomebox[violet]{2pt}{\faBook}{violet}{Adresy rejestrów znajdziesz w mapie rejestrów czujnika.}

# Zadanie rozszerzone

## Wymagania funkcjonalne

1. Odczytywany jest pomiar przyspieszenia w osi X.
1. Wychylenie czujnika jest wizualizowane w pierwszej linii wyświetlacza.

## Modyfikacja programu

### Odczyt podwójnego rejestru

Uzupełnij metodę `Spi::readRegisterWord()` tak, by odczytywała dwa kolejne bajty. W tym celu po wysłaniu bajtu adresu, jak w funkcji `Spi::readRegister()` należy odczytać nie jeden, ale dwa bajty, a następnie zsumować je w zmiennej 16-bitowej, używając operatora przesunięcia bitowego o 8, czyli `<< 8`.

### Odczyt pomiaru w osi X

Uzupełnij metodę `Accelerometer::measure()` tak, by z użyciem wcześniej przygotowanej funkcji `Spi::readRegisterWord()` odczytywała pomiar w osi X. Na ekranie powinien być widoczny pomiar w postaci szesnastkowej i dziesiętnej.

### Zmniejsze częstotliwości pomiaru

W celu poprawienia czytelności odczytu na wyświetlaczu zmniejsz częstotliwość pracy czujnika, ustawiając na końcu funkcji `Accelerometer::initialize()` maksymalną wartość w rejestrze _Sample Rate Divider_. Funkcja do zapisu rejestrów jest już gotowa.

### Wizualizacja pomiaru za pomocą bargrafu

W pętli głównej `mainLoop()` zwizualizuj wychylenie czujnika, rysując w pierwszej linii wyświetlacza myślniki odpowiednio po lewej lub prawej stronie znacznika \texttt{||} proporcjonalnie do wychylenia. Zakres pracy i rozdzielczość tego bargrafu dobierz wedle uznania.

\begin{center}
\LCD{2}{16}
    |     --{|}{|}       |
    |70 0xfec6=  -314|
\captionof{figure}{Przykładowy stan wyświetlacza}
\end{center}
