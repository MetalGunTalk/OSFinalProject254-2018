#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include <QRegExp>
#include <QDebug>
#include "alertlistpopup.h"

QList<Alert> MainWindow::Alert_List = QList<Alert>(); //Instantiation
QString Alert::FileOutput = "C:\\Qt\\test.txt";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Open File Code
    QFile file(ui->FilePathText->toPlainText());
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,ui->FilePathText->toPlainText(), file.errorString());
    }
    QTextStream in(&file);

    ui->MainTestDump->setText(in.readAll());
}

void MainWindow::on_QueryButton_clicked()
{
    //Regex Query Execute Full Document

    QRegExp Big_Regex(ui->RegexInput->toPlainText());
    qDebug() << Big_Regex.pattern();
    QString Total_Text = ui->MainTestDump->toPlainText();
    QStringList List;
    //Big_Regex.setPatternSyntax(QRegExp::Wildcard);
    int pos = 0;
    this->Alert_List.clear();
    while ((pos = Big_Regex.indexIn(Total_Text, pos))!=-1) {
        List << Big_Regex.cap();
        Alert_List << Alert(Total_Text, Big_Regex.pattern(), pos);
        pos += Big_Regex.matchedLength();

    }
    if (!List.isEmpty()){
        qDebug() << "List contains: " << List;
    }
    QMessageBox::information(nullptr,"Regex Singular Result", Total_Text);
    ui->rxmatches->setText("Regex Matches: " + QString::number(List.length()));
}

void MainWindow::on_GenerateAlerts_clicked()
{
    AlertListPopUp ALPU;
    ALPU.setModal(true);
    ALPU.exec();
}
