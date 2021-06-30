#include "principal.h"
#include "ui_principal.h"
#include "calculosalario.h"

#include <QMessageBox>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);

    //conectar los objetos

    connect(ui->actionCalcular, SIGNAL(triggered()),
            this, SLOT(on_cmdCalcular_clicked()));
}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_cmdCalcular_clicked()
{
    this->calcular();

}

void Principal::on_actionCalcular_triggered()
{
    this->on_cmdCalcular_clicked();
}

void Principal::calcular()
{
    // obtener los datos

    QString nombre = ui->inNombre->text(); //obtengo el texto
    int horas = ui->inHoras->value();  //obtenemos horas

    if(nombre.isEmpty()){

        QMessageBox ::warning(this, "Salarios", "No has proporcionado el nombre del obrero");
        return;
    }


    char jornada = '\0';

    if(ui->inMatutino->isChecked()){
        jornada = 'M';
    }else if(ui->inNocturna->isChecked()){
        jornada = 'N';
    }else if(ui->inVespertina->isChecked()){
        jornada = 'V';
    }

    CalculoSalario *s1 = new CalculoSalario(nombre, horas, jornada);
    s1->calcular();

    //Mostramos los resultadado

    ui->outResultado->appendPlainText(s1->resultado());

    //BORRAMOS LOS WIDGETS YA ANTES UTILIZADOS

    this->borrar();

}

//metodo BORRAMOS LOS WIDGETS YA ANTES UTILIZADOS

void Principal::borrar()
{
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutino->setChecked(true);
    ui->inNombre->setFocus();

}

void Principal::nuevo()
{
    ui->outResultado->clear();
}

void Principal::on_actionNuevo_triggered()
{
    this->nuevo();
}

//VERSION
void Principal::on_actionAcerca_de_triggered()
{
    Acerca *acercaDe = new Acerca(this);
    acercaDe->setVersion(VERSION);
    acercaDe->show();
}

//FICHEROS

void Principal::on_actionGuardar_triggered()
{
    //Creamos un QDir directorio apartir dle directorio dle susuario
    QDir directorio = QDir::home(); //manejar directorio
    //creamos mun path absoluto de un objeto
    QString pathArchivo = directorio.absolutePath()+ "/sin_nombre.txt"; //nombre por defecto
    QString fileName = QFileDialog::getSaveFileName(this,"Guardar archivos", //nombre de la ventan
                                                    pathArchivo,
                                                    "Archivo de texto (*.txt)");

    qDebug () <<fileName;

    //guardar datos en el archivo

    QFile f(fileName);
    //Crear el objeo
    QTextStream out (&f);
    //intentar abrir archivo, sino ventana de error
    if(!f.open(QIODevice::WriteOnly | QIODevice::Append)){
        QMessageBox ::warning(this, "Salarios", "No se ha abierto el archivo");
        return;
    }
    //GUARDA LE CONTENIDO D ELOS RESULTADOS
    out << ui->outResultado->toPlainText() <<   endl;
    //Cerramos archivo
    f.close();
    //Mostrar mensaje en la barra de estados
    ui->statusBar->showMessage("Archivo guardado en "+fileName,3000);
}

void Principal::on_actionAbrir_triggered()
{
    QDir directorio = QDir::home();
        QString pathArchivo = directorio.absolutePath();
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        "Abriendo archivo",
                                                        pathArchivo,
                                                        "Archivo de texto (*.txt)");
        QFile f(fileName);
        QTextStream in(&f);
        QString impresion;
        if(!f.open(QIODevice::ReadOnly))
            QMessageBox::warning(this,"Salarios","No se puede abrir el archivo");
        while(!in.atEnd())
        {
            impresion = impresion + in.readLine() + "\n";
        }
        f.close();
        ui->outResultado->appendPlainText(impresion);
}
