#ifndef IMPORTFLASHCARDS_H
#define IMPORTFLASHCARDS_H

#include <QDialog>

namespace Ui {
class importflashcards;
}

class importflashcards : public QDialog
{
    Q_OBJECT

public:
    explicit importflashcards(QWidget *parent = nullptr);
    ~importflashcards();

private slots:
    void on_pushButton_browse_clicked();
    void on_pushButton_import_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::importflashcards *ui;
};

#endif // IMPORTFLASHCARDS_H
