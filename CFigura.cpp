#include "CFigura.h"
#include <QString>
#include "CGra.h"


    CFigura::CFigura(char kolor, QString nazwa)
    {
        this->kolor=kolor;
        QString sufiks;
        if (kolor == 'B')
            sufiks += 'w';
        else
            sufiks += 'b';

        obrazek = QPixmap(":/figury/images/" + nazwa + "_" + sufiks + ".png");
    }

    CFigura::~CFigura(){}

    char CFigura::setColor()
    {
        return kolor;
    }

    bool CFigura::possibleMove(int poczRow, int poczCol, int docRow, int docCol, CFigura * szachwonica[8][8] , int tour) //sprawdza czy mozliwy ruch lub bicie
    {
        CFigura* Cel = szachwonica[docRow][docCol]; // Wskaznik na cel

        if ((Cel == 0) || (kolor != Cel->setColor()))   // jeżeli cel pusty lub aktualny kolor gracza rózni sie od przeciwnika (mozliwe zbicie)
            return move(poczRow, poczCol, docRow, docCol, szachwonica,tour); // funkcja odpowiadająca za rzeczywisty ruch

        return false;
    }

    QPixmap CFigura::Obrazek()
    {
        return obrazek;
    }

    void CFigura::setDoubleMoveTour(int tour)
    {
        doubleMoveTour = tour;
    }

    int CFigura::getDoubleMoveTour()
    {
        return doubleMoveTour;
    }

    bool CFigura::getEnPassant()
    {
        return enPassant;
    }

    void CFigura::setEnPassant(bool enPassant)
    {
        this->enPassant = enPassant;
    }

    int CFigura::getMoveAmount()
    {
        return moveAmount;
    }

    void CFigura::setMoveAmount(int moveAmount)
    {
        this->moveAmount = moveAmount;
    }

    void CFigura::incrementMoveAmount()
    {
        moveAmount++;
    }

