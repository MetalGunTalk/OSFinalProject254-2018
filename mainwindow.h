#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <string>
#include <QRandomGenerator>

class Alert;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static QList<Alert> Alert_List;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_QueryButton_clicked();

    void on_GenerateAlerts_clicked();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H


class Alert {

private:
    int Position = 1;
    int PreregLength = 0;
    QString REGEX;
    QString PREREGEX = "";
    QString POSTREGEX = "";
    QString TEXTSOURCE;
public:
    static QString FileOutput;
    static void saveToTextFileICalendar(){
        QFile file(FileOutput);
        if (file.open(QIODevice::ReadWrite)){

            QTextStream stream(&file);
            stream << "BEGIN:VCALENDAR\r\nVERSION:2.0\r\nPRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n" << endl;

            for (auto a : MainWindow::Alert_List){
                stream << "BEGIN:VEVENT\r\n"
                       <<"SUMMARY: " << a.getSummary()
                       <<"\r\nDTSTAMP:" + a.getDate()
                       <<"\r\nDTSTART:" + a.getDate()
                       <<"\r\nDTEND:" + a.getDate()
                       << "\r\nUID:" << QRandomGenerator::global()->generate() << "OSPROJECT"
                       <<"\r\nEND:VEVENT\r\n";
            }
            stream << "END:VCALENDAR\r\n";
        }

        return;
    }

    QString getRegex(){
    return PREREGEX + REGEX + POSTREGEX;
    }
    QString getSummary(){
        QRegExp RX(getRegex());
        RX.indexIn(TEXTSOURCE, Position);
        return RX.cap();
    }
    void setPost(int Characters){
        POSTREGEX = ".{" + QString::number(Characters) + "}";
    }
    void setPre(int Characters){
        if (Position - Characters < 2 || Characters == 0){
                return;
        }
        PREREGEX = ".{" + QString::number(Characters) + "}";
        Position -= Characters;
        PreregLength = Characters;
    }
    QString getDate(){
        QRegExp RX(REGEX);
        RX.indexIn(TEXTSOURCE, Position + PreregLength);
        return RX.cap();
    }
    Alert(QString Source, QString Regex, int position = 1){
        TEXTSOURCE = Source;
        REGEX = Regex;
        Position = position;
    }
};

