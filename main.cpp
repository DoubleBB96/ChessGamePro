#include <QApplication>
#include <CGlowneOkno.h>


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	CGlowneOkno okno;
	okno.show();
	return app.exec();
}
