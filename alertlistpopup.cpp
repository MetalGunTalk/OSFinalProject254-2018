#include "alertlistpopup.h"
#include "ui_alertlistpopup.h"
#include "mainwindow.h"





AlertListPopUp::AlertListPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlertListPopUp)
{
    ui->setupUi(this);
    UpdateAlertList();
}

AlertListPopUp::~AlertListPopUp()
{
    delete ui;
}

void AlertListPopUp::on_DeleteButton_clicked()
{
    if (ui->listWidget->selectedItems().isEmpty())
        return;
    MainWindow::Alert_List.removeAt(ui->listWidget->currentIndex().row());
    UpdateAlertList();
}

void AlertListPopUp::UpdateAlertList()
{
    ui->listWidget->clear();
    for (auto a : MainWindow::Alert_List){
        ui->listWidget->addItem(a.getSummary());
    }
}

void AlertListPopUp::on_UpdateButton_clicked()
{
    if (ui->listWidget->selectedItems().isEmpty())
        return;
    MainWindow::Alert_List[(ui->listWidget->currentIndex().row())].setPost(ui->PostRX->toPlainText().toInt());
    MainWindow::Alert_List[(ui->listWidget->currentIndex().row())].setPre(ui->PreRX->toPlainText().toInt());
    UpdateAlertList();
}

void AlertListPopUp::on_pushButton_2_clicked()
{
    Alert::FileOutput = ui->FilePath->toPlainText();
    Alert::saveToTextFileICalendar();
}
