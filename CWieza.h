#ifndef CWIEZA_H
#define CWIEZA_H
#include "CFigura.h"

/**
 * @brief The CWieza class
 *Klasa figury Wieża
 */
class CWieza : public CFigura
{
public:
    /**
     * @brief CWieza
     *Konstruktor klasy
     * @param kolor Kolor danej Wieży
     */
    CWieza(char kolor);
    ~CWieza();
private:

    /**
     * @brief figureSign
     *Funkcja przypisująca znak dla Wieży
     * @return Znak 'W'
     */
    virtual char figureSign();

    /**
     * @brief move
     * Funkcja wprowadzająca algorytm ruchu dla Wieży
     * @param poczRow   Współrzędna wierszu figury
     * @param poczCol    Współrzędna kolumny figury
     * @param docRow    Współrzędna wierszu celu
     * @param docCol     Współrzędna kolumny celu
     * @param szachownica   Szachownica na której odbywa się rzeczywista gra
     * @return Wartość logiczna czy dany ruch jest możliwy
     */
    bool move(int poczRow, int poczCol, int docRow, int docCol, CFigura * szachownica[8][8], int tour);
    bool getDoubleFieldMove();
    void setDoubleFieldMove(bool a);

};

#endif // CWIEZA_H
