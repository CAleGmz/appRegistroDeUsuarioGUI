#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    inicio();

    connect(ui->pushButtonSalir, SIGNAL(released()), this, SLOT(accept()));


}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::inicio()
{

    ui->labelErrorNombreDeUsuario->setVisible(false);

    ui->labelCorreo->setVisible(true);
    ui->labelErrorCorreo->setVisible(false);

    ui->labelErrorDia->setVisible(false);
    ui->labelErrorYear->setVisible(false);
    ui->labelErrorEdadNoValida->setVisible(false);

    ui->verticalLayoutErrorNombreUsuario->addStretch();
    ui->verticalLayoutErrorCorreo->addStretch();
    ui->verticalLayoutErrorFechaNacimiento->addStretch();

    ui->lineEditNombreDeUsuario->setStyleSheet("border: 2px solid grey");
    ui->lineEditCorreo->setStyleSheet("border: 2px solid grey");
    ui->lineEditDia->setStyleSheet("border: 2px solid grey");
    ui->lineEditYear->setStyleSheet("border: 2px solid grey");

    ui->labelCorreo->setText("El correo debe contener \n-Nombre de Usuario antes del símbolo @ (puede tener mayusculas, minusculas, \nnumeros, guines bajos y guiones, debe tener minimo un caracter[puedes usar puntos, pero no al final ni al comienzo]) \n-@ para separar el usuario del dominio \n-Dominio(puede contener mayúsculas, minúsculas y números) \n-. para separar dominos secundarios \n-Extension[es](.com,.mx,.it,etc)");

}

bool Dialog::revisarUsuario()
{
    QRegularExpression patron("^[a-zA-Z0-9_]{3,13}$");
    QRegularExpressionMatch match = patron.match(ui->lineEditNombreDeUsuario->text());

    if(match.hasMatch()){
        ui->lineEditNombreDeUsuario->setStyleSheet("border: 2px solid grey");
        ui->labelErrorNombreDeUsuario->setVisible(false);
        return true;
    }
    else{
        ui->lineEditNombreDeUsuario->setStyleSheet("border: 4px solid red");
        ui->labelErrorNombreDeUsuario->setVisible(true);
        return false;
    }
}

bool Dialog::revisarCorreo()
{
    QString expReg;
    switch (ui->comboBoxCorreo->currentIndex()) {
    case 0:
        expReg = "^[\\w-]+(\\.?[\\w-]+)@[A-Za-z0-9]+(\\.[A-Za-z0-9]+)(\\.[A-Za-z]{2,})?$";
        break;
    case 1:
        expReg = "^[\\w-]+(\\.[\\w_-]+)*@[A-Za-z0-9]+(\\.[A-Za-z0-9]+)*(\\.[A-Za-z]{2,})$";
        break;
    case 2:
        expReg = "[A-Z0-9._%+-]+@[A-Z0-9-]+.+.[A-Z]{2,4}";
        break;
    case 3:
       expReg = "^([Ss]istemas|[Aa]dministracion|[Mm]arketing|[Ff]inanzas|[Vv]entas)+.([a-zA-Z0-9ñ_])+(@jcarlos19)+.+.([a-zA-Z]{2,})$";
        break;
    }
    QRegularExpression patron(expReg);
    QRegularExpressionMatch match = patron.match(ui->lineEditCorreo->text());

    if(match.hasMatch()){
        ui->lineEditCorreo->setStyleSheet("border: 2px solid grey");
        ui->labelErrorCorreo->setVisible(false);
        return true;
    }
    else{
        ui->lineEditCorreo->setStyleSheet("border: 4px solid red");
        ui->labelErrorCorreo->setVisible(true);
        return false;
    }
}

bool Dialog::revisarDia()
{
    QString expReg;
    switch(ui->comboBoxMes->currentIndex()){
    case 0:
    case 2:
    case 4:
    case 6:
    case 7:
    case 9:
    case 11:
        expReg = "^(0?[1-9]|[12][0-9]|3[01])$";
        break;
    case 3:
    case 5:
    case 8:
    case 10:
        expReg = "^(0?[1-9]|[12][0-9]|30)$";
        break;
    case 1:
        expReg = "^(0?[1-9]|1[0-9]|2[0-8]|29)$";
        break;
    }
    QRegularExpression patron(expReg);
    QRegularExpressionMatch match = patron.match(ui->lineEditDia->text());
    if(match.hasMatch()){
        ui->lineEditDia->setStyleSheet("border: 2px solid grey");
        ui->labelErrorDia->setVisible(false);
        return true;
    }
    else{
        ui->lineEditDia->setStyleSheet("border: 4px solid red");
        ui->labelErrorDia->setVisible(true);
        return false;
    }
}

bool Dialog::revisarYear()
{
    QRegularExpression patron("^(19[0-9]{2}|20(0[0-9]|1[0-9]|2[0-4]))$");
    QRegularExpressionMatch match = patron.match(ui->lineEditYear->text());
    if(match.hasMatch()){
        ui->lineEditYear->setStyleSheet("border: 2px solid grey");
        ui->labelErrorYear->setVisible(false);
        return true;
    }
    else{
        ui->lineEditYear->setStyleSheet("border: 4px solid red");
        ui->labelErrorYear->setVisible(true);
        return false;
    }
}

void Dialog::esValidoElRegistro()
{
    if(usuario && revisarUsuario() && correo && revisarCorreo() &&
       dia && revisarDia() &&
        year && revisarYear()){
        ui->pushButtonRegistrarse->setEnabled(true);
        ui->pushButtonRegistrarse->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(125, 255, 150);");
    }
    else{
        ui->pushButtonRegistrarse->setEnabled(false);
        ui->pushButtonRegistrarse->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(56, 56, 56);");
    }
}

void Dialog::on_lineEditNombreDeUsuario_editingFinished()
{
    usuario = true;
    revisarUsuario();
    esValidoElRegistro();
}


void Dialog::on_lineEditCorreo_editingFinished()
{
    correo = true;
    revisarCorreo();
    esValidoElRegistro();
}


void Dialog::on_lineEditDia_editingFinished()
{
    dia = true;
    revisarDia();

    esValidoElRegistro();
}


void Dialog::on_lineEditYear_editingFinished()
{
    year = true;
    revisarYear();
    esValidoElRegistro();
}


void Dialog::on_lineEditNombreDeUsuario_textChanged(const QString &)
{
    if(usuario){
        revisarUsuario();
        esValidoElRegistro();
    }
}


void Dialog::on_lineEditCorreo_textChanged(const QString &)
{
    if(correo){
        revisarCorreo();
        esValidoElRegistro();
    }
}


void Dialog::on_lineEditDia_textChanged(const QString &)
{
    if(dia){
        revisarDia();
        esValidoElRegistro();
    }
}


void Dialog::on_lineEditYear_textEdited(const QString &)
{
    if(year){
        revisarYear();
        esValidoElRegistro();
    }
}


void Dialog::on_comboBoxCorreo_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->labelCorreo->setText("El correo debe contener \n-Nombre de Usuario antes del símbolo @ (puede tener mayusculas, minusculas, \nnumeros, guines bajos y guiones, debe tener minimo un caracter[puedes usar puntos, pero no al final ni al comienzo]) \n-@ para separar el usuario del dominio \n-Dominio(puede contener mayúsculas, minúsculas y números) \n-. para separar dominos secundarios \n-Extension[es](.com,.mx,.it,etc)");
        break;
    case 1:
        ui->labelCorreo->setText("El correo debe contener \n-Nombre de Usuario antes del símbolo @ (puede tener mayusculas, minusculas, \nnumeros, guines bajos y guiones, debe tener minimo un caracter[puedes usar puntos, pero no al final ni al comienzo]) \n-@ para separar el usuario del dominio \n-Dominio(puede contener mayúsculas, minúsculas y números) \n-. para separar dominos secundarios \n-Extension[es](.com,.mx,.it,etc)");
        break;
    case 2:
        ui->labelCorreo->setText("El correo debe contener SOLO mayusculas");
        break;
    case 3:
        ui->labelCorreo->setText("El correo debe contener:\n-El area de desempeño(sistemas, administracion, marketing, \nfinanzas y ventas [puede iniciar con mayuscula]) \n-Usuario[puede contener numeros, letras y guiones bajos] \n-Domino(@jcarlos19) \n-Extension[es](.com,.mx,.it,etc)");
        break;
    }
}


void Dialog::on_pushButtonRegistrarse_clicked()
{
    QMessageBox *messageBox = new QMessageBox(QMessageBox::Information,"Usuario creado con exito", "El Usuario fue creado con exito\n puede cerrar la app o crear otro",QMessageBox::Ok,this);

    messageBox->show();
}

