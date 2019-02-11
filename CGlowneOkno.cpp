#include "CGlowneOkno.h"
#include "ui_cglowneokno.h"
#include "CSzachownica.h"
#include <QDebug>

CGlowneOkno::CGlowneOkno(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::CGlowneOkno),
        szachownica(new CSzachownica(this))
{
	ui->setupUi(this);

        szachownica->setSceneRect(0, 0, 800, 800);
        ui->widok->setScene(szachownica);

        ui->stackedWidget->setCurrentIndex(0);

        connect(szachownica,SIGNAL(sendCheckMate(bool)),this,SLOT(czyKoniec(bool)));



}


CGlowneOkno::~CGlowneOkno()
{
    delete ui;
}

void CGlowneOkno::on_nowa_gra_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void CGlowneOkno::on_close_clicked()
{
    qApp->exit();
}

void CGlowneOkno::czyKoniec(bool czy_koniec)
{
    if(czy_koniec)
    {
        char aktualnyGracz = gra->getAktualnyGracz();
        if(aktualnyGracz == 'B')
             ui->label_3->setText("Czarny");
        else
             ui->label_3->setText("Biały");

        qDebug()<<"Gracz Wygrany: " << aktualnyGracz;

        ui->stackedWidget->setCurrentIndex(1);
    }
}


