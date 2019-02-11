#ifndef CPION_H
#define CPION_H
#include "CFigura.h"

    class CSzachwonica;


/**
 * @brief The CPion class
 *Klasa figury Pion
 */
class CPion : public CFigura
{

public:

    /**
     * @brief CPion
     *Konstruktor klasy
     * @param kolor Kolor danego Piona
     */
    CPion(char kolor);//konstruktor nadający kolor
    ~CPion();           // destruktor



private:

    /**
     * @brief figureSign
     *Funkcja przypisująca znak danemu Pionowi
     * @return Znak 'P'
     */
    virtual char figureSign(); //Znak w konsoli , w GUI będzie to grafika dla danej figury

    /**
     * @brief move
     * Funkcja wprowadzająca algorytm ruchu i bicia (rozróżnialne) dla Piona
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

#endif // CPION_H
