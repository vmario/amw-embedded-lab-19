---
title: "Ćwiczenie 19: Magistrala SPI na przykładzie akcelerometru"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: no
colorlinks: yes
header-right: "\\faEdit"
footer-left: "Sprawozdanie z laboratorium"
header-includes: |
  \usepackage{awesomebox}
  \usepackage{tikz}
  \usepackage{xfrac}
  \usetikzlibrary{positioning}
  \usetikzlibrary{positioning}
  \usepackage[raster]{tcolorbox}
...

\lstset{language=[11]C++}

_W trosce o Państwa wyniki proszę o czytelne wpisywanie nazwisk._

**Data**: \dotfill

**Autorzy**: \dotfill

# Część praktyczna

## Zadanie podstawowe

**Ocena prowadzącego**: \dotfill

## Zadanie rozszerzone

**Ocena prowadzącego**: \dotfill

# Część teoretyczna

## Zadanie podstawowe

Jaki jest stan spoczynkowy linii zegarowej czujnika MPU-6500? Jaki stan bitu _CPOL_ w mikrokontrolerze odpowiada temu trybowi pracy?

\awesomebox[violet]{2pt}{\faBook}{violet}{Potrzebne informacje znajdziesz na rysunku \textit{SPI Bus Timing Diagram} w nocie katalogowej czujnika.}

\vspace{1.5cm}

Na jakim zboczu następuje odczyt danych? Jaki stan bitu _CPHA_ w mikrokontrolerze odpowiada temu trybowi pracy?

\vspace{1.5cm}

Jaka jest kolejność bitów w bajcie? Jaki stan bitu _DORD_ w mikrokontrolerze odpowiada temu trybowi pracy?

\vspace{1.5cm}

Jaka jest maksymalna częstotliwość pracy magistrali SPI czujnika (przy której działają wszystkie rejestry)? Jaki stan bitów _SPR0_, _SPR1_, _SPI2X_ w mikrokontrolerze odpowiada temu trybowi pracy przy taktowaniu 16&nbsp;MHz?

\vspace{1.5cm}

Jaki jest identyfikator czujnika MPU-6500?

\awesomebox[violet]{2pt}{\faBook}{violet}{Potrzebne informacje znajdziesz w mapie rejestrów czujnika.}

\vspace{1.5cm}

## Zadanie rozszerzone

W jakim zakresie będą zmieniały się wartości w rejestrze pomiaru przyspieszenia podczas zmiany kąta nachylenia czujnika względem powierzchni Ziemi? Zakładamy pracę w domyślnym zakresie pomiarowym, tj. $\pm 2\ g$.

\vspace{1.5cm}

## \faCertificate&nbsp; Zadanie specjalne

_+1 pkt dla osoby, która jako pierwsza poda poprawną odpowiedź._

W jaki sposób akcelerometr MEMS dokonuje pomiaru przyspieszenia (jak jest zbudowany)?
