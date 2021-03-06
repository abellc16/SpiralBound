#ifndef EDITCALENDAREVENT_H
#define EDITCALENDAREVENT_H

#include <QDialog>
#include <QTableWidget>


namespace Ui {
class editcalendarevent;
}

class editcalendarevent : public QDialog
{
    Q_OBJECT

public:
    explicit editcalendarevent(QWidget *parent = nullptr);
    ~editcalendarevent();

private slots:
    void on_buttonBox_accepted();
    void receiveEditData(QString, QString, QString);   // Send editcalendarevent data to mainwindow

signals:
    void sendEditData(QTableWidgetItem *);
    void sendEditData(QString, QString);

private:
    Ui::editcalendarevent *ui;
};

#endif // EDITCALENDAREVENT_H
