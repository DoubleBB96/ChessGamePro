#ifndef CKROL_H
#define CKROL_H
#include "CFigura.h"

/**
 * @brief The CKrol class
 * Klasa figury Król
 */
class CKrol : public CFigura
{
public:
    /**
     * @brief CKrol
     *Konstruktor klasy
     * @param kolor Kolor danego Króla
     */
    CKrol(char kolor);
    ~CKrol();
private:

    /**
         * @brief figureSign
         * Funkcja przypisująca znak dla Króla
         * @return Znak 'K'
         */
    virtual char figureSign();

    /**
     * @brief move
     * Funkcja wprowadzająca algorytm ruchu dla Króla
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

    bool doubleFieldMove = 0;
};

#endif // CKROL_H
