#ifndef CGRA_H
#define CGRA_H
#include "CFigura.h"

class CSzachownica;
class CGlowneOkno;
class CFigura;

class CGra
{

public:
    CGra();
    ~CGra();

    /**
     * @brief checkMate
     *Funkcja sprawdzająca czy jest SzachMat
     * @param gra Orginalna szachownica która jest badana
     * @return  Zwraca prawde gdy jest Szach Mat
     */
    bool checkMate(CSzachownica *gra);

    /**
     * @brief nowaGra
     *Funkcja która rozstawia figury na logicznej planszy, tak że po rozstawieniu wszystkie figury są na swoich pozycjach startowych
     * @param gra Orginalna szachownica na której rozstawiane są figury
     */
    void nowaGra(CSzachownica *gra);


    /**
     * @brief wyczyscZaznaczenia
     *Funkcja która po zakończonym ruchu wyczyszcza zaznaczone pola, na które może być wykonany ruch
     * @param gra Orginalna szachownica na której dokonywane są zmiany
     */
    void wyczyscZaznaczenia(CSzachownica *gra);

    /**
     * @brief wyznaczMozliweRuchy
     *Funkcja wyznaczająca pola na które może być wykonany ruch
     * @param gra  Orginalna szachownica na której dokonywane są zmiany
     */
    void wyznaczMozliweRuchy(CSzachownica *gra);

    /**
     * @brief zmienGracza
     *Funkcja zmieniająca kolejność gracza
     */
    void zmienGracza();

    /**
     * @brief check
     *Funkcja sprawdzająca czy przy ruchu danego gracza, jego król jest w sytuacji Szach
     * @param gra Orginalna szachownica
     * @return  Funkcja zwraca prawdę -  jest szach
     */
    bool check(CSzachownica *gra) ;


    /**
     * @brief mozliwaUcieczka
     *Funkcja która sprawdza czy możliwa jest ucieczka przy sytuacji szach oraz zapamietuje te figury i ich możliwości ruchu, które ratują od tej sytuacji
     * @param gra Orginalna szachownica
     * @return  Zwraca prawde gdy jest możliwa ucieczka
     */
    bool mozliwaUcieczka(CSzachownica *gra);


    /**
     * @brief przesunFigure
     *Funkcja która w rzeczywistości przesuwa figurę na pole docelowe
     * @param pocz Wspólrzędne początkowe figury
     * @param doc  Wpółrzędne docelowe ruchu figury
     * @param gra  Orginalna szachownica na której dokonywane są zmiany
     */
    void przesunFigure(QPoint pocz, QPoint doc , CSzachownica *gra, int whichRook);

    /**
     * @brief getAktualnyGracz
     *Funkcja zwracająca kolej aktualnyego gracza
     * @return Kolej gracza
     */
    char getAktualnyGracz();

    /**
     * @brief setTheEnd
     *Funkcja ustawiająca wartość prywatnego pola logicznego odpowiadającego za koniec rozgrywki
     * @param koniec
     */
    void setTheEnd(bool koniec);

    /**
     * @brief getTheEnd
     *Funkcja pobierająca wartość prywatnego pola logicznego odpowiadającego za koniec rozgrywki
     * @return  true - koniec gry, false - gramy dalej
     */
    bool getTheEnd();

    int getTour();
    void incermentTour();
    void setTour(int tour);


private:

    /**
     * @brief aktualnyGracz
     *Atrybut określający aktualną kolej zawodnika.
     */
    char aktualnyGracz = 'B';

    /**
     * @brief lista_pocz
     *Lista współrzędnych figur które umożliwiają ucieczkę od sytuacji Szach
     */
    QList <QPoint> lista_pocz;

    /**
     * @brief lista_doc
     *Lista współrzędnych docelowych ruchu figur które umożliwiają ucieczkę od sytuacji Szach
     */
    QList <QPoint> lista_doc;

    /**
     * @brief theEnd
     *Zmienna logiczna odpowiadająca za koniec rozgrywki
     */
    bool theEnd = false;

    int tour = 1;


};


#endif // CGRA_H
