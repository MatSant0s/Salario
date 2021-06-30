#include "calculosalario.h"

float CalculoSalario::salarioBruto() const
{
    return m_salarioBruto;
}

float CalculoSalario::descuento() const
{
    return m_descuento;
}

float CalculoSalario::salarioNeto() const
{
    return m_salarioNeto;
}

QString CalculoSalario::getJornada()
{
    switch(m_jornada){

    case 'V':{
        return "Vespertina";
        break;
    }
    case 'M':{
        return "Matutina";
        break;
    }
    case 'N':{
       return "Nocturna";
        break;
    break;
    }
    }
    return "N/D";

}

CalculoSalario::CalculoSalario(QObject *parent) : QObject(parent)
{
    this->m_nombre = "\0";
    this->m_horas = 0;
    this->m_jornada = '\0';
}

CalculoSalario::CalculoSalario(QString nombre, int horas, char jornada)
{
    this->m_nombre  = nombre;
    this->m_horas   = horas;
    this->m_jornada = jornada;

}

void CalculoSalario::calcular()
{
    float valorHora = 0;

    switch(m_jornada){

    case 'V':{
        valorHora = VALOR_HORA_VESPERTINO;
        break;
    }
    case 'M':{
        valorHora = VALOR_HORA_MATUTINO;
        break;
    }
    case 'N':{

        valorHora = VALOR_HORA_NOCTURNO;
        break;
    break;
    }
    }

    m_salarioBruto = m_horas * valorHora;
    m_descuento = m_salarioBruto * PORCENTAJE_DESCUENTO/100;
    m_salarioNeto = m_salarioBruto - m_descuento ;

    qDebug()<<"El salario neto es :"<<m_salarioNeto;
}

QString CalculoSalario::resultado()
{
    QString str;
    str = "Obrero: "+m_nombre + "\n";
    str += "Horas: "+QString::number (m_horas) + "\n";
    str += "Jornada: "+getJornada()+"\n";
    str += "SalarioBruto: $" + QString::number(m_salarioBruto)+"\n";
    str += "Descuento: $"+QString::number(m_descuento)+"\n";
    str += "Slario Neto: $"+QString::number(m_salarioNeto)+"\n\n";
    return str;
}
