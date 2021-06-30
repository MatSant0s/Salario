#include "principal.h"
#include "calculosalario.h"
#include <QApplication>

#include <QObject>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Principal w;
    w.show();

    //Calcular salario

    CalculoSalario prueba("Mateo", 12, 'V');
    prueba.calcular();
    CalculoSalario prueba2("edison", 51, 'M');
    prueba2.calcular();
    CalculoSalario prueba3("Diego", 54, 'N');
    prueba3.calcular();



    return a.exec();
}
