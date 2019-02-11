#ifndef CKROLOWA_H
#define CKROLOWA_H
#include "CFigura.h"

/**
 * @brief The CKrolowa class
 *Klasa figury Królowa
 */
class CKrolowa : public CFigura
{
public:
    /**
     * @brief CKrolowa
     *Konstruktor klasy
     * @param kolor Kolor danej Królowej
     */
    CKrolowa(char kolor);
    ~CKrolowa();
private:

    /**
     * @brief figureSign
     *Funkcja przypisująca znak dla Królowej
     * @return Znak 'Q'
     */
    virtual char figureSign();

    /**
     * @brief move
     * Funkcja wprowadzająca algorytm ruchu dla Królowej
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

#endif // CKROLOWA_H
