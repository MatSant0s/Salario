#ifndef CALCULOSALARIO_H
#define CALCULOSALARIO_H

#include <QObject>
#include <QtDebug>

class CalculoSalario : public QObject
{
    //EL MOC EJECUTA BIEN LAS ACCIONES

    Q_OBJECT
    Q_PROPERTY(float salarioBruto READ salarioBruto)
    Q_PROPERTY(float descuento READ descuento)
    Q_PROPERTY(float salarioNeto READ salarioNeto)

private:

    //constantes

    float const VALOR_HORA_MATUTINO   = 5.15;
    float const VALOR_HORA_VESPERTINO = 8.50;
    float const VALOR_HORA_NOCTURNO   = 12.65;
    float const PORCENTAJE_DESCUENTO  = 9.5;

    //VARIABLES DE MIEBROS

    int m_horas;        //numero horas
    QString m_nombre;   // nombre del trabajador
    char m_jornada;     // jornada [M=matutina, V=vespertina, N=nocturna]

    float m_salarioBruto; //Salario sin descuento
    float m_descuento;    //Valor del descuento
    float m_salarioNeto;   //Valro de salario a recibir

    //variable

    QString getJornada();

public:

    //METODOS SE QUEDAN

    explicit CalculoSalario(QObject *parent = nullptr); //defecto

    CalculoSalario(QString nombre, int horas, char jornada); //constructor de recibir valores

    void calcular();

    QString resultado ();

    float salarioBruto() const;

    float descuento() const;

    float salarioNeto() const;

signals:

};
#endif // CALCULOSALARIO_H
