#include "CSzachownica.h"
#include "CFigura.h"
#include "CKrol.h"
#include "CKrolowa.h"
#include "CSkoczek.h"
#include "CKon.h"
#include "CWieza.h"
#include "CPion.h"
#include "CPoleSzachownicy.h"
#include "CGra.h"


#include <QDebug>



CSzachownica::CSzachownica(QObject *parent):
    QGraphicsScene(parent)
{

    gra.nowaGra(this);
    kontener();
}

void CSzachownica::kliknietoPole(CPoleSzachownicy *aktualnyElement)
{
    if (aktualnyElement->pobierzFigure()){
    qDebug() << Q_FUNC_INFO << aktualnyElement->pobierzFigure()->figureSign() << aktualnyElement->pobierzFigure()->setColor();
    //qDebug()<<"Rucha o dwa pola: "<<plansza[aktualnyElement->pobierzWiersz()][aktualnyElement->pobierzKolumne()]->getDoubleFieldMove();
              //if(plansza[aktualnyElement->pobierzWiersz()][aktualnyElement->pobierzKolumne()]->getDoubleFieldMove())
                //      qDebug()<< " W rundzie: "<<plansza[aktualnyElement->pobierzWiersz()][aktualnyElement->pobierzKolumne()]->getDoubleMoveTour();
      //qDebug()<<plansza[aktualnyElement->pobierzWiersz()][aktualnyElement->pobierzKolumne()]->getMoveAmount();
    }

	// Kliknięto w puste pole lub nie swója figure przy wyborze
    if (zaznaczonyElement == nullptr && (aktualnyElement->pobierzFigure() == nullptr || aktualnyElement->pobierzFigure()->setColor() != gra.getAktualnyGracz()))
		return;

   //Jezli kliknieto w puste pole badz pole z figura aktualnego gracza
    if (zaznaczonyElement == nullptr || (aktualnyElement->pobierzFigure() && aktualnyElement->pobierzFigure()->setColor() == gra.getAktualnyGracz()))
	{
        if (zaznaczonyElement)          // przy ruchu konkretnego gracza i zmianie wyboru figury usuwa wyznaczone mozliwe ruchy
        {

            gra.wyczyscZaznaczenia(this);

        }

		zaznaczonyElement = aktualnyElement;
		zaznaczonyElement->ustawWybrane(true);
        gra.wyznaczMozliweRuchy(this);
       // qDebug()<<"Tura GRA : "<<gra.getTour();

	}
	else
	{
        int i = zaznaczonyElement->pobierzWiersz();
        int j = zaznaczonyElement->pobierzKolumne();

        if (aktualnyElement->jestMozliwyRuch())
		{
            //if monitorujacy ruszenie piona o 2 pola z pozycji startowej i ustawiajacy zmienna odpowiadajaca za ten ruch na true
            if(zaznaczonyElement->pobierzFigure()->figureSign()=='P' && abs(aktualnyElement->pobierzWiersz() - zaznaczonyElement->pobierzWiersz()) == 2)
            {
                 //qDebug()<<"Wybrales piona i ruszyles nim o 2";

                 plansza[i][j]->setDoubleFieldMove(true);
                 plansza[i][j]->setDoubleMoveTour(gra.getTour());

                 //warunek na bicie w przelocie pion, poruszył sie po skosie obok znajduje sie pion ktory 1 ruch wczesniej wykonal przeskok o 2 pola
            }else if(zaznaczonyElement->pobierzFigure()->figureSign()=='P' && abs(aktualnyElement->pobierzWiersz() - zaznaczonyElement->pobierzWiersz()) == 1
                     && abs(aktualnyElement->pobierzKolumne() - zaznaczonyElement->pobierzKolumne()) == 1 &&
                     ((plansza[i][j+1] != 0 && plansza[i][j+1]->figureSign() == 'P' && plansza[i][j+1]->getDoubleFieldMove() == true && gra.getTour() - plansza[i][j+1]->getDoubleMoveTour() == 1)
                      || (plansza[i][j-1] != 0 && plansza[i][j-1]->figureSign() == 'P' && plansza[i][j-1]->getDoubleFieldMove() == true && gra.getTour() - plansza[i][j-1]->getDoubleMoveTour() == 1)))
                          //qDebug()<<"EnPassant!";
                                plansza[i][j]->setEnPassant(true);
            else if(zaznaczonyElement->pobierzFigure()->figureSign() == 'K' && abs(aktualnyElement->pobierzKolumne() - zaznaczonyElement->pobierzKolumne()) == 2)
            {
                plansza[i][j]->setDoubleFieldMove(true);
            }





               gra.incermentTour();                  //licznik tur
               plansza[i][j]->incrementMoveAmount(); // licznik ruchow danej figury
               przesunFigure(zaznaczonyElement, aktualnyElement,plansza[i][j]->getEnPassant());



               plansza[aktualnyElement->pobierzWiersz()][aktualnyElement->pobierzKolumne()]->setEnPassant(false);     //nastawienie enPassant na false aby po wykonaniu bicia w przelocie
                                                                                                                                                                               // pion nie miał wartosci tego pola na true do konca gry


               zaznaczonyElement = nullptr;
               gra.wyczyscZaznaczenia(this);

               gra.zmienGracza();


               if(gra.check(this))
               {
                   gra.mozliwaUcieczka(this);
               }

               if(gra.checkMate(this))
               {
                    bool theend = czy_koniec;
                    theend = true;
                    emit sendCheckMate(theend);
                    gra.setTour(0);
                    setNullMoveAmount();
                    gra.nowaGra(this);
                    kontener();
               }

        } /*else
        {
            //qDebug()<<aktualnyElement->pobierzPozycje();
        }*/
    }
}


void CSzachownica::przesunFigure(CPoleSzachownicy *pocz, CPoleSzachownicy *doc, bool enPassant)
{
    CFigura *rook;
    int whichRook = 0;

    if(enPassant)
    {
        doc->ustawFigure(pocz->zdejmijFigure());
        CFigura *pawn = getPolaSzachownicy(pocz->pobierzWiersz(),doc->pobierzKolumne())->zdejmijFigure();
        delete pawn;

    }
    else if(plansza[pocz->pobierzWiersz()][pocz->pobierzKolumne()]->figureSign() == 'K' && plansza[pocz->pobierzWiersz()][pocz->pobierzKolumne()]->getDoubleFieldMove() == true
            && plansza[pocz->pobierzWiersz()][pocz->pobierzKolumne()]->getMoveAmount() == 1)
    {
            doc->ustawFigure(pocz->zdejmijFigure());



            if(plansza[pocz->pobierzWiersz()][doc->pobierzKolumne() + 1]!=0 && plansza[pocz->pobierzWiersz()][doc->pobierzKolumne() + 1]->figureSign() == 'W'){
                rook = getPolaSzachownicy(pocz->pobierzWiersz(),doc->pobierzKolumne() + 1)->zdejmijFigure();
                whichRook = 1;
                plansza[pocz->pobierzWiersz()][doc->pobierzKolumne() - 1] = rook;
                polaSzachownicy[pocz->pobierzWiersz()][doc->pobierzKolumne() - 1]->ustawFigure(rook);

            }
           else if(plansza[pocz->pobierzWiersz()][doc->pobierzKolumne() - 2] != 0 && plansza[pocz->pobierzWiersz()][doc->pobierzKolumne() - 2]->figureSign() == 'W'){
                rook = getPolaSzachownicy(pocz->pobierzWiersz(),doc->pobierzKolumne() - 2)->zdejmijFigure();
                whichRook = -2;
                plansza[pocz->pobierzWiersz()][doc->pobierzKolumne() + 1] = rook;
               polaSzachownicy[pocz->pobierzWiersz()][doc->pobierzKolumne() + 1]->ustawFigure(rook);

            }


    }
    else
        doc->ustawFigure(pocz->zdejmijFigure());        //ustawienie obrazka wybranej figury w miejscu docelowym

    gra.przesunFigure(pocz->pobierzPozycje(), doc->pobierzPozycje(),this, whichRook); //przesuniecie figury na planszy logicznej

}

void CSzachownica::kontener()
{
    // Konstruujemy szachownicę
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            QColor kolor(Qt::darkGray);
            if ((i + j) % 2 == 0)
                kolor = Qt::white;

            polaSzachownicy[i][j] = new CPoleSzachownicy(i, j);
            polaSzachownicy[i][j]->ustawKolor(kolor);
            addItem(polaSzachownicy[i][j]);

            if (CFigura *f = plansza[i][j])
            {
                polaSzachownicy[i][j]->ustawFigure(f);
            }

            connect(polaSzachownicy[i][j], SIGNAL(kliknieto(CPoleSzachownicy*)), this, SLOT(kliknietoPole(CPoleSzachownicy*)));

        }
    }
}


CPoleSzachownicy *CSzachownica::getPolaSzachownicy(int i, int j)
{
    return polaSzachownicy[i][j];
}

int CSzachownica::getZaznaczonyWiersz()
{
    return zaznaczonyElement->pobierzWiersz();
}
int CSzachownica::getZaznaczonyKolumna()
{
    return zaznaczonyElement->pobierzKolumne();
}

bool CSzachownica::getPossibleMovePlansza(int w_pocz, int k_pocz, int w_doc, int k_doc)
{

    return plansza[w_pocz][k_pocz]->possibleMove(w_pocz,k_pocz,w_doc,k_doc,plansza,gra.getTour());
}

bool CSzachownica::getPossibleMoveForSigned(int w_doc, int k_doc)
{

    return zaznaczonyElement->pobierzFigure()->possibleMove(zaznaczonyElement->pobierzWiersz(), zaznaczonyElement->pobierzKolumne(),w_doc, k_doc, plansza, gra.getTour());
}

CFigura *CSzachownica::getPlanszaField(int i, int j)
{
    return plansza[i][j];
}

void CSzachownica::setNullPlanszaField(int i, int j)
{
    plansza[i][j] = nullptr;
}

char CSzachownica::getColorFigureOnField(int i, int j)
{
    return plansza[i][j]->setColor();
}

char CSzachownica::getFigureSign(int i, int j)
{
    return plansza[i][j]->figureSign();
}

void CSzachownica::setAnonymousMove(int w_pocz, int k_pocz, int w_doc, int k_doc)
{
    plansza[w_doc][k_doc] = plansza[w_pocz][k_pocz];
}

void CSzachownica::setObjectPlanszaField( int i, int j, CFigura *tmp )
{
    plansza[i][j] = tmp;
}

bool CSzachownica::getPossibleMovePoleSzachwonica(int i, int j)
{
    return polaSzachownicy[i][j]->jestMozliwyRuch();
}

void CSzachownica::putNewFigure(int i, int j,std::string figure,char color )
{
        if(figure == "Pion")
            plansza[i][j] = new CPion(color);
        else if (figure == "Wieza")
            plansza[i][j] = new CWieza(color);
        else if (figure == "Kon")
            plansza[i][j] = new CKon(color);
        else if (figure == "Skoczek")
            plansza[i][j] = new CSkoczek(color);
        else if (figure == "Krolowa")
            plansza[i][j] = new CKrolowa(color);
        else if (figure == "Krol")
            plansza[i][j] = new CKrol(color);


}

bool CSzachownica::getPawnEnPassant(int i, int j)
{
    return plansza[i][j]->getEnPassant();
}

void CSzachownica::setNullMoveAmount()
{
    for(int i = 0;i<8;i++)
    {
        for(int j = 0;j<8;j++)
        {
            plansza[i][j]->setMoveAmount(0);
        }
    }
}


