#include "CPlansza.h"
#include "CKrol.h"
#include "CKrolowa.h"
#include "CSkoczek.h"
#include "CKon.h"
#include "CWieza.h"
#include "CPion.h"
#include "CFigura.h"

#include<iostream>
using namespace std;
/*

    //Konstruktor planszy
    CPlansza::CPlansza() {
        for (int W = 0; W < 8; ++W) {
            for (int K = 0; K < 8; ++K) {
                Tablica[W][K] = 0;              //wpisanie 0 w wolne miejsca, czyli brak pionka na danym polu
            }
        }
        // Rozstawiamy biale
        for (int K = 0; K < 8; ++K) {
            Tablica[6][K] = new CPion('B');
        }
        Tablica[7][0] = new CWieza('B');
        Tablica[7][1] = new CKon('B');
        Tablica[7][2] = new CSkoczek('B');
        Tablica[7][3] = new CKrol('B');
        Tablica[7][4] = new CKrolowa('B');
        Tablica[7][5] = new CSkoczek('B');
        Tablica[7][6] = new CKon('B');
        Tablica[7][7] = new CWieza('B');
        // Rozstawiamy czarne
        for (int K = 0; K < 8; ++K) {
            Tablica[1][K] = new CPion('C');
        }
        Tablica[0][0] = new CWieza('C');
        Tablica[0][1] = new CKon('C');
        Tablica[0][2] = new CSkoczek('C');
        Tablica[0][3] = new CKrol('C');
        Tablica[0][4] = new CKrolowa('C');
        Tablica[0][5] = new CSkoczek('C');
        Tablica[0][6] = new CKon('C');
        Tablica[0][7] = new CWieza('C');
    }
    //destruktor Planszy
    CPlansza::~CPlansza() {
        for (int W = 0; W < 8; ++W) {
            for (int K = 0; K < 8; ++K) {
                delete Tablica[W][K];
                Tablica[W][K] = 0;
            }
        }
    }

    bool CPlansza::Szach(char kolorek)   //funkcja przeszukująca plansze czy któryś z pionów może dokonać bicia króla

    {
        // Wyszukanie współrzędnych króla
        int WierszKrol;
        int KolumnaKrol;
        for (int Wiersz = 0; Wiersz < 8; ++Wiersz) {
            for (int Kolumna = 0; Kolumna < 8; ++Kolumna) {
                if (Tablica[Wiersz][Kolumna] != 0) {                                   //pole nie jest puste
                    if (Tablica[Wiersz][Kolumna]->NadajKolor() == kolorek) {           //jezeli jest ruch aktualnego gracza (fukncja uniemozliwia graczowi przemieszczenie sie na pole zagrozone Szachem)
                        if (Tablica[Wiersz][Kolumna]->ZnakPionka() == 'K') {           //Odnalezienie króla
                            WierszKrol = Wiersz;
                            KolumnaKrol = Kolumna;
                        }
                    }
                }
            }
        }
        // Przeszukanie planszy
        for (int Wiersz = 0; Wiersz < 8; ++Wiersz) {
            for (int Kolumna = 0; Kolumna < 8; ++Kolumna) {
                if (Tablica[Wiersz][Kolumna] != 0) {
                    if (Tablica[Wiersz][Kolumna]->NadajKolor() != kolorek) {                              // zapewnienie że to przeciwnik może zbić króla
                        if (Tablica[Wiersz][Kolumna]->MozliwyRuch(Wiersz, Kolumna, WierszKrol, KolumnaKrol, Tablica)) {      //znalezienie możliwości bicia Króla
                            return true;                               //zwraca prawde gdy król aktualnego gracza jest zagrozony Szachem 
                        }
                    }
                }
            }
        }

        return false;                                                //falsz gdy nie ma mozliwosci zbicia krola przez przeciwnika
    }
   
    bool CPlansza::MozliwoscUcieczki(char kolorek)                //metoda zwracająca mozliwosc ruchu w sytuacji Szach
    {
            for (int Wiersz = 0; Wiersz < 8; ++Wiersz)
            {
               for (int Kolumna = 0; Kolumna < 8; ++Kolumna)
               {
                   if (Tablica[Wiersz][Kolumna] != 0) //warunek na nie puste pola czyli przejscie przez wszystkie figury
                   {
                       // Jeżeli ruch aktualnego gracza
                       if (Tablica[Wiersz][Kolumna]->NadajKolor() == kolorek)
                       {
                            for (int WierszRuchu = 0; WierszRuchu < 8; ++WierszRuchu)
                            {
                               for (int KolumnaRuchu = 0; KolumnaRuchu < 8; ++KolumnaRuchu)
                               {
                                   if (Tablica[Wiersz][Kolumna]->MozliwyRuch(Wiersz, Kolumna, WierszRuchu, KolumnaRuchu, Tablica))     //przejście przez wszystkie figury i ich możliwości ruchów
                                   {

									  CFigura * Tmp = Tablica[WierszRuchu][KolumnaRuchu];
                                      Tablica[WierszRuchu][KolumnaRuchu] = Tablica[Wiersz][Kolumna]; //wirtualne przesuniecie wszystkich figur (tajne) TJ. w CGra
                                      Tablica[Wiersz][Kolumna] = 0;
                                      bool bMozliwoscRuchu = !Szach(kolorek);  //sprawdzenie czy król jest w szachu nie bedac w szachu przeciwnik ma mozliwosc ruchu
                                      //cofnięcie ruchu                         //bMozliwoscRuchu zwraca prawde gdy krol nie jest w szachu
                                      Tablica[Wiersz][Kolumna] = Tablica[WierszRuchu][KolumnaRuchu];
                                      Tablica[WierszRuchu][KolumnaRuchu] = Tmp;
                                        if (bMozliwoscRuchu)                   //nie bycie w szachu zapewnie mozliwosc ruchu
                                        {
                                        return true;
                                        }
                                   }
                               }
                           }
                       }
                   }
                }
			}
	}

	void CPlansza::PrzesunFigure(QPoint pocz, QPoint doc)
	{
		CFigura *f = Tablica[doc.y()][doc.x()];
		if (f)
			delete f;

		Tablica[doc.y()][doc.x()] = Tablica[pocz.y()][pocz.x()];
		Tablica[pocz.y()][pocz.x()] = nullptr;
	}
*/
