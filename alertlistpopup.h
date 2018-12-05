#ifndef ALERTLISTPOPUP_H
#define ALERTLISTPOPUP_H

#include <QDialog>


namespace Ui {
class AlertListPopUp;
}

class AlertListPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit AlertListPopUp(QWidget *parent = nullptr);
    ~AlertListPopUp();

private slots:
    void on_DeleteButton_clicked();

    void on_UpdateButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AlertListPopUp *ui;

    void UpdateAlertList();
};

#endif // ALERTLISTPOPUP_H
