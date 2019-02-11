#include "CKon.h"
#include "CFigura.h"


   CKon::CKon(char kolor) : CFigura(kolor, "Horse") {}
   CKon::~CKon() {}

    char CKon::figureSign()
    {
        return 'H';
    }

    bool CKon::move(int poczRow, int poczCol, int docRow, int docKol, CFigura * szachownica[8][8], int tour)
    {

        if (((poczCol == docKol + 1) || (poczCol == docKol - 1)) && ((poczRow == docRow + 2) || (poczRow == docRow - 2)))
                return true;
        else if (((poczCol == docKol + 2) || (poczCol == docKol - 2)) && ((poczRow == docRow + 1) || (poczRow == docRow - 1)))
                return true;
                                                                            //BRAK SPRAWDZERNIA CZY JEST PUSTY CEL ?!?!?!
        return false;
    }

    bool CKon::getDoubleFieldMove()
    {
        return false;
    }

    void CKon::setDoubleFieldMove(bool a)
    {
    }
