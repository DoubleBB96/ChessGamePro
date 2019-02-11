#ifndef CFIGURY_H
#define CFIGURY_H
#include <QString>
#include <QPixmap>

class CGra;

/**
 * @brief The CFigura class
 *
 * Klasa główna, abstrakcyjna, po której dziedziczą wszystkie klasy figur
 */

class CFigura
{
public:
    /**
     * @brief CFigura
     * Konstruktor klasy
     * @param kolor Kolor danej figury
     * @param nazwa Nazwa figury, wykorzystywana w dopasowaniu odpowiedniego obrazka do danej figury
     */
    CFigura(char kolor, QString nazwa= QString());

    ~CFigura();

    /**
     * @brief ZnakPionka
     * Wirtualna funkcja, która przypisuje figurom ich odpowiednie znaki
     * @return  Znak figury
     */
    virtual char figureSign() = 0;

    /**
     * @brief setColor
     * Funkcja zwracająca kolor dla danej figury
     * @return Kolor figury
     */

    char setColor(); //Nadanie koloru danej figurze


    /**
     * @brief possibleMove
     * Funkcja sprawdzająca czy jest możliwy ruch lub bicie dla wybranej figury
     * @param poczRow   Współrzędna wierszu figury
     * @param poczCol    Współrzędna kolumny figury
     * @param docRow    Współrzędna wierszu celu
     * @param docCol     Współrzędna kolumny celu
     * @param szachownica   Szachownica na której odbywa się rzeczywista gra
     * @return Możliwy ruch lub bicie
     */
    bool possibleMove(int poczRow, int poczCol, int docRow, int docCol, CFigura * szachownica[8][8], int tour);

    /**
     * @brief Obrazek
     * Funkcja przyporządkowująca odpowiedni obrazek dla danej figury
     * @return  Ikona figury
     */
    QPixmap Obrazek();


    virtual bool getDoubleFieldMove() = 0;
    virtual void setDoubleFieldMove(bool a) = 0;
    void setDoubleMoveTour( int tour);
    int getDoubleMoveTour();
    bool getEnPassant();
    void setEnPassant(bool enPassant);
    int getMoveAmount();
    void setMoveAmount(int moveAmount);
    void incrementMoveAmount();

private:

    /**
     * @brief move
     * Funkcja wirtualna odpowiadająca za sprawdzenie możliwości ruchu danej figury
     * @param poczRow   Współrzędna wierszu figury
     * @param poczCol    Współrzędna kolumny figury
     * @param docRow    Współrzędna wierszu celu
     * @param docCol     Współrzędna kolumny celu
     * @param szachownica   Szachownica na której odbywa się rzeczywista gra
     * @return Możliwy ruch wybranej figury
     */
    virtual bool move(int poczRow, int poczCol, int docRow, int docCol, CFigura* szachownica[8][8], int tour) = 0; //kazdy pionek ma swoj indywidualny algorytm ruchu nadpisanie 0

    ///@param kolor  Kolor figur

    char kolor;

    ///@param obrazek  Ikona pobrana z zasobów, przyporządkowywana każdej z figur na podstawie jej nazwy
    QPixmap obrazek;

    int doubleMoveTour = 0;
    bool enPassant = 0;
    int moveAmount = 0;




};

#endif // CFIGURY_H
