#ifndef CSZACHOWNICA_H
#define CSZACHOWNICA_H

#include <QGraphicsScene>
#include "CGra.h"
#include <string>
#include<iostream>

class CFigura;
class CPoleSzachownicy;
class CGra;

class CSzachownica : public QGraphicsScene
{
	Q_OBJECT

    class CGlowneOkno;

public:

	explicit CSzachownica(QObject *parent = nullptr);

    /**
     * @brief czy_koniec
     *Zmienna logiczna która przechwuje stan gry i zwraca true gdy wystąpił Szach Mat
     */
    bool czy_koniec = false;

    /**
     * @brief getPolaSzachownicy
     *Getter konkretnego pola szachownicy określonego przez współrzędne i,j
     * @param i
     * @param j
     * @return Pole Szachwonicy
     */
    CPoleSzachownicy *getPolaSzachownicy(int i, int j);

    /**
     * @brief getZaznaczonyWiersz
     *Getter indeksu wiersza zaznaczonego pola
     * @return Indeks wiersza zaznaczonego pola
     */
    int getZaznaczonyWiersz();

    /**
     * @brief getZaznaczonyKolumna
     *Getter indeksu kolumny zaznaczonego pola
     * @return Indeks kolumny zaznaczonego pola
     */
    int getZaznaczonyKolumna();

    /**
     * @brief getPossibleMovePlansza
     *Funkcja zwracająca możliwy ruch na planszy logicznej
     * @param w_pocz Wiersz początkowy
     * @param k_pocz Kolumna początkowa
     * @param w_doc Wiersz docelowy
     * @param k_doc Kolumna docelowa
     * @return True dla możliwego ruchu, false dla zabronionego
     */
    bool getPossibleMovePlansza(int w_pocz, int k_pocz, int w_doc, int k_doc);

//    /**
//     * @brief getZaznaczonyElement
//     *Getter zaznaczonego pola szachownicy
//     * @return Zaznaczone pole szachownicy
//     */
//    CPoleSzachownicy *getZaznaczonyElement();

    /**
     * @brief getPossibleMoveForSigned
     *Funkcja zwracająca możliwy ruch dla zaznaczonego pola planszy
     * @param w_doc Wiersz docelowy
     * @param k_doc Kolumna docelowa
     * @return  True dla możliwego ruchu, false dla zabronionego
     */
    bool getPossibleMoveForSigned(int w_doc, int k_doc);

    /**
     * @brief getPlanszaField
     *Funkcja pobierająca figurę na polu o podanych współrzędnych i,j
     * @param i
     * @param j
     * @return Figura na polu szachownicy
     */
    CFigura *getPlanszaField(int i, int j);

    /**
     * @brief setNullPlanszaField
     *Setter wartości pola na planszy logicznej o podanych współrzednych na null. Funkcja wykorzystywana przy poruszaniu oraz biciu pionków
     * @param i
     * @param j
     */
    void setNullPlanszaField(int i, int j);

    /**
     * @brief getColorFigureOnField
     *Funkcja pobierająca kolor figury która znajduje sie na polu o podanych współrzędnych i,j
     * @param i
     * @param j
     * @return Kolor figury
     */
    char getColorFigureOnField(int i, int j);

    /**
     * @brief getFigureSign
     *Funkcja pobierająca znak figury która znajduje sie na polu o podanych współrzędnych i,j
     * @param i
     * @param j
     * @return  Znak figury
     */
    char getFigureSign(int i, int j);

    /**
     * @brief setAnonymousMove
     *Funkcja wpisująca w polu o wspolrzednych docelowych obiekt z pola poczatkowego planszy
     * @param w_pocz
     * @param k_pocz
     * @param w_doc
     * @param k_doc
     */
    void setAnonymousMove(int w_pocz, int k_pocz, int w_doc, int k_doc);

    /**
     * @brief setValuePlanszaField
     *Funkcja ustawiająca na polu o podanych wspolrzednych, obkiekt klasy CFigura
     * @param i
     * @param j
     * @param tmp
     */
    void setObjectPlanszaField(int i, int j, CFigura *tmp );

    /**
     * @brief getPossibleMovePoleSzachwonica
     *Funkcja zwracająca czy na podane pole szachownicy można wykonać ruch
     * @param i
     * @param j
     * @return True - można
     */
    bool getPossibleMovePoleSzachwonica(int i, int j);

    /**
     * @brief putNewFigure
     *Funkcja tworząca nowe obiekty na polu planszy o podanych wspolrzednych, danej nazwie oraz kolorze
     * @param i
     * @param j
     * @param figure
     * @param color
     */
    void putNewFigure(int i, int j, std::string figure ,char color);

    bool getPawnEnPassant(int i, int j);

    void setNullMoveAmount();

signals:

    /**
     * @brief sendCheckMate
     *Funkcja, która wysyła stan gry, czy wystąpił Szach Mat
     */
    void sendCheckMate(bool);

protected slots:
    /**
     * @brief kliknietoPole
     *Funkcja która przejmuje sygnał z klasy CSzachownica, dzięki czemu wie, że dane pole zostało kliknięte
     */
	void kliknietoPole(CPoleSzachownicy*);

protected:

    /**
     * @brief przesunFigure
     *Funkcja która ustawia figure z poczatku ruchu na miejscu docelowym i przekazuje dalej funkcji klasy CGra, która odpowiada za rzeczywisty ruch figury na planszy
     * @param pocz Współrzędne wybranej figury
     * @param doc Współrzędne docelowego miejsca ruchu
     */
    void przesunFigure(CPoleSzachownicy *pocz, CPoleSzachownicy *doc , bool enPassant);

    /**
     * @brief kontener
     *Funkcja wykorzystująca logiczną wirtualną szachownice do wypełnienia ją polami oraz figurami (GUI)
     */
    void kontener();

    /**
     * @brief plansza
     *Tablica klasy CFigura na której są rozstawiane wirtualne pionki
     */
    CFigura *plansza[8][8];

    /**
     * @brief polaSzachownicy
     *Tablica klasy CPoleSzachownicy, w której przechowywane są wszystkie pola
     */
    CPoleSzachownicy *polaSzachownicy[8][8];

    /**
     * @brief zaznaczonyElement
     *Atrybut przechowujący informacje o polu szachownicy które zostało wybrane i ma być zaznaczone (dot. wyboru konkretnej figury do poruszenia)
     */
    CPoleSzachownicy *zaznaczonyElement = nullptr;

    /**
     * @brief gra
     *Atrybut klasy CGra, który obsługuje wszystkie wydarzenia odbywające się na planszy
     */
    CGra gra;

};

#endif // CSZACHOWNICA_H
