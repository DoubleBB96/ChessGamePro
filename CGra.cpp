#include "CGra.h"
#include "CKrol.h"
#include "CKrolowa.h"
#include "CSkoczek.h"
#include "CKon.h"
#include "CWieza.h"
#include "CPion.h"
#include "CFigura.h"
#include<time.h>
#include<stdlib.h>
#include "CPoleSzachownicy.h"
#include "CSzachownica.h"

#include <QDebug>

#include<iostream>
using namespace std ;



    CGra::CGra() {}
    CGra::~CGra() {} 

void CGra::zmienGracza()
{
    aktualnyGracz = (aktualnyGracz == 'B') ? 'C' : 'B';
    lista_pocz.clear();
    lista_doc.clear();
}

void CGra::wyczyscZaznaczenia(CSzachownica *gra)
{
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            CPoleSzachownicy *pole = gra->getPolaSzachownicy(i,j);
            pole->ustawWybrane(false);
            pole->ustawMozliwyRuch(false);
        }
    }
}

void CGra::wyznaczMozliweRuchy(CSzachownica *gra)
{
    if(check(gra)) //je?eli jest Szach
    {
        int x = gra->getZaznaczonyWiersz();
        int y = gra->getZaznaczonyKolumna();



        QPoint jest;
        jest.setX(x);
        jest.setY(y);

        if(lista_pocz.contains(jest))   // je?eli dana figura nale?y do listy w której znajduj? sie figury ratuj?ce od szach matu
        {

            QList <int> pom; // lista pomocnicza ktora przechowuje indeksy z listy figur ktore ratuja sytuacje szach mat

            for(int i = 0;i<lista_pocz.length();i++)
            {
                if(lista_pocz.at(i) == jest)
                {
                    pom.append(i);             //dodanie do listy indeksu figur ktora ratuje szach
                                                      // jest tak zrobione poniewa? czasami jedna figura dwoma ruchami moze uratowac sytuacje szach mat
                }
            }

            for(int i = 0; i<pom.length();i++) // przejscie prze tyle figur ile jest figur ratujacych
            {
                int W = lista_doc.at(pom.at(i)).x();     // zapamietany cel na liscie docelowej
                int K = lista_doc.at(pom.at(i)).y();
                CPoleSzachownicy *pole = gra->getPolaSzachownicy(W,K);
                           if(gra->getPossibleMovePlansza(jest.x(),jest.y(),W,K))

                           {
                               pole->ustawMozliwyRuch(true);
                           }
            }

            pom.clear();
         }
    }else
    {
       for (int i=0; i<8; i++)
       {
           for (int j=0; j<8; j++)
           {
               CPoleSzachownicy *pole = gra->getPolaSzachownicy(i,j);

                   if(gra->getPossibleMoveForSigned(pole->pobierzWiersz(), pole->pobierzKolumne()))
                   {

                        pole->ustawMozliwyRuch(true);

                   }
           }
       }

    }
}

void CGra::przesunFigure(QPoint pocz, QPoint doc, CSzachownica *gra, int whichRook)  // rzyczwiste przesuni?cie figury
{

       if (gra->getPlanszaField(doc.y(),doc.x()))                      // je?eli cel nie jest pusty (stoi na nim przeciwnik) DOKONANIE BICIA
            gra->setNullPlanszaField(doc.y(),doc.x());                // usuni?cie figury
       else if(gra->getPawnEnPassant(pocz.y(),pocz.x()))
       {
           //qDebug()<<"En Passant !";
           gra->setNullPlanszaField(pocz.y(),doc.x());
       }else if(gra->getPlanszaField(pocz.y(),pocz.x())->figureSign() == 'K' && gra->getPlanszaField(pocz.y(),pocz.x())->getDoubleFieldMove())
       {
           gra->setNullPlanszaField(doc.y(),doc.x() + whichRook);
       }


                                             // przesuni?cie figury (przypisanie do celu, figury ktï¿½r? wybrali?my)
       gra->setAnonymousMove(pocz.y(),pocz.x(),doc.y(),doc.x());
                                           // wyczyszczenie pozycji pocz?tkowej
       gra->setNullPlanszaField(pocz.y(),pocz.x());
}


bool CGra::check(CSzachownica *gra)
{
    int row_king;
    int col_king;

    //Szukam wspó?rz?dnych Króla aktualnegoGracza
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(gra->getPlanszaField(i,j))
            {
                if(gra->getColorFigureOnField(i,j) == aktualnyGracz && gra->getFigureSign(i,j) == 'K')
                {
                        row_king = i;        //wspó?rz?dne króla aktualnego gracz
                        col_king = j;
                }
            }
        }
    }

    //Sprawdzam czy pion przeciwnika mo?e dokona? na nim bicia
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(gra->getPlanszaField(i,j))
            {
                if(gra->getColorFigureOnField(i,j) != aktualnyGracz &&
                           gra->getPossibleMovePlansza(i, j, row_king, col_king))

                    return true;
            }
        }
    }

    return false;

}

bool CGra::mozliwaUcieczka(CSzachownica *gra)
{
    /**
     * @brief ile
     *Okre?la czy s? pola które ratuj? od sytuacji SzachMat
     */
    int ile = 0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(gra->getPlanszaField(i,j))
            {
                if(gra->getColorFigureOnField(i,j) == aktualnyGracz )
                {
                    for( int i_doc=0; i_doc<8;i_doc++)                      //przejscie przez wszystkie figury i mozliwosci ich ruchu
                    {
                        for( int j_doc=0; j_doc<8;j_doc++)
                        {              
                            if(gra->getPossibleMovePlansza(i,j,i_doc,j_doc))
                            {
                                CFigura *tmp = gra->getPlanszaField(i_doc,j_doc);
                                gra->setAnonymousMove(i,j,i_doc,j_doc);             //"tajne" przesuniecia tych figur na ich mozliwe pola docelowe
                                gra->setNullPlanszaField(i,j);

                                bool mozeUciec = !check(gra);

                                if(mozeUciec)
                                {
                                    QPoint fig;
                                    fig.setX(i_doc);
                                    fig.setY(j_doc);
                                    lista_doc.append(fig);
                                }

                                gra->setAnonymousMove(i_doc,j_doc,i,j);                    //Powrót tajnego ruchu
                                //gra->plansza[i_doc][j_doc] = tmp;
                                gra->setObjectPlanszaField(i_doc,j_doc,tmp);

                                if(mozeUciec)  //je?eli mo?liwa ucieczka
                                {
                                    ile++;
                                    QPoint fig;
                                    fig.setX(i);
                                    fig.setY(j);
                                    lista_pocz.append(fig);
                                }

                            }
                        }
                    }
                }
            }

        }
    }

    if(ile > 0){

        return true;

    }

    return false;

}

bool CGra::checkMate(CSzachownica *gra)
{
// Funkcja szach mat dzieli sie na dwa przypadki
    //1. Gdy na planszy dosz?o do sytuacji j szach i gracz nie ma mozliwosci ucieczki od tej sytuacji
    //2. Gdy niezagro?ony gracz szachem wykona? ruch umo?liwiaj?cy dokonanie bicia króla

    if(check(gra)) // realizacja pierwszego przypadku
    {
        qDebug()<<"Szach !";

        if(mozliwaUcieczka(gra))
        {
            qDebug()<<"Mozliwa ucieczka !";
            return false;
        }
        else
        {

            qDebug()<<"SzachMat!";
            return true;

        }
    }else  //reazlizacja drugiego przypadku
    {
        for(int i=0;i<8;i++)
        {
            for(int j =0 ;j<8;j++)
            {
                //if(gra->polaSzachownicy[i][j]->jestMozliwyRuch())
               if(gra->getPossibleMovePoleSzachwonica(i,j))
               {

                    if( gra->getPlanszaField(i,j))
                    {
                        if(gra->getFigureSign(i,j) == 'K')

                        {
                                   qDebug()<<"SzachMat";
                                   return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

void CGra::nowaGra(CSzachownica *gra)
{

    aktualnyGracz = 'B';

    for (int W = 0; W < 8; W++)
    {
            for (int K = 0; K < 8; K++)
            {
                gra->setNullPlanszaField(W,K);
            }
        }
        // Rozstawiamy biale
        for (int K = 0; K < 8; K++) { 
           gra->putNewFigure(6,K, "Pion" , 'B');
        }
        gra->putNewFigure(7,0, "Wieza" , 'B');
        gra->putNewFigure(7,1, "Kon" , 'B');
        gra->putNewFigure(7,2, "Skoczek" , 'B');
        gra->putNewFigure(7,3, "Krolowa" , 'B');
        gra->putNewFigure(7,4, "Krol" , 'B');
        gra->putNewFigure(7,5, "Skoczek" , 'B');
        gra->putNewFigure(7,6, "Kon" , 'B');
        gra->putNewFigure(7,7, "Wieza" , 'B');

        // Rozstawiamy czarne
        for (int K = 0; K < 8; K++) {
            gra->putNewFigure(1,K, "Pion" , 'C');
        }
        gra->putNewFigure(0,0, "Wieza" , 'C');
        gra->putNewFigure(0,1, "Kon" , 'C');
        gra->putNewFigure(0,2, "Skoczek" , 'C');
        gra->putNewFigure(0,3, "Krolowa" , 'C');
        gra->putNewFigure(0,4, "Krol" , 'C');
        gra->putNewFigure(0,5, "Skoczek" , 'C');
        gra->putNewFigure(0,6, "Kon" , 'C');
        gra->putNewFigure(0,7, "Wieza" , 'C');

}

char CGra::getAktualnyGracz()
{
    return aktualnyGracz;
}


void CGra:: setTheEnd(bool koniec)
{
    theEnd = koniec;
}

bool CGra::getTheEnd()
{
    return theEnd;
}

int CGra::getTour()
{
    return tour;
}

void CGra::setTour(int tour)
{
    this->tour = tour;
}

void CGra::incermentTour()
{
    this->tour ++;
}

