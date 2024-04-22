#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_lineEditNombreDeUsuario_editingFinished();

    void on_lineEditCorreo_editingFinished();

    void on_lineEditDia_editingFinished();

    void on_lineEditYear_editingFinished();

    void on_lineEditNombreDeUsuario_textChanged(const QString &arg1);

    void on_lineEditCorreo_textChanged(const QString &arg1);

    void on_lineEditDia_textChanged(const QString &arg1);

    void on_lineEditYear_textEdited(const QString &arg1);

    void on_comboBoxCorreo_currentIndexChanged(int index);

    void on_pushButtonRegistrarse_clicked();

private:
    Ui::Dialog *ui;

    void inicio();

    bool revisarUsuario();
    bool revisarCorreo();
    bool revisarDia();
    bool revisarYear();

    void esValidoElRegistro();

    bool usuario = false, correo = false, dia = false, year = false;
};
#endif // DIALOG_H
