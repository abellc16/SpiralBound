#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "document.h"
#include "markdowneditor.h"
#include "book.h"

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidgetItem>
#include <QTreeWidgetItem>

#include <editcalendarevent.h>
#include <addcalendarevent.h>
#include <deletecalendarevent.h>
#include <addcard.h>
#include <importflashcards.h>
#include <deletecard.h>
#include <editsection.h>
#include <addbook.h>
#include "adddeck.h"
#include "deletedeck.h"
#include <studycard.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // =========================
    // Menu Bar Buttons
    // =========================
    void on_action_open_triggered();
    void on_action_save_triggered();
    void on_action_about_triggered();
    void on_action_aboutQt_triggered();
    void on_action_crashCourse_triggered();
    void on_action_print_triggered();
    void on_action_new_triggered();
    void on_action_openRecent_triggered();
    void on_action_taskList_triggered();
    void on_action_preferences_triggered();
    void on_action_printPreview_triggered();
    void on_action_export_triggered();
    void on_action_quit_triggered();

    // Menu for formatting
    void on_action_bold_triggered();
    void on_action_italic_triggered();
    void on_action_underline_triggered();
    void on_action_comment_triggered();
    void on_action_strikethrough_triggered();
    void on_action_indent_triggered();
    void on_action_unindent_triggered();
    void on_action_bulletedList_triggered();
    void on_action_numberedList_triggered();

    //==================
    // Calendar Buttons
    //==================
    void on_pushButton_addEvent_clicked();
    void on_pushButton_deleteEvent_clicked();
    void on_pushButton_editEvent_clicked();
    void on_tableWidget_eventList_cellChanged(int row, int column);

    // Connections
    void receiveAddData(QString, QString);  // Receive addcalendarevent data to mainwindow
    void receiveEditData(QString, QString); // Receive editcalendarevent data to mainwindow
    void receiveDeleteData(bool);           // Receive deletecalendarevent data to mainwindow

    //=========================
    // Flash Card Tool Buttons
    //=========================
    void on_pushButton_addCard_clicked();
    void on_pushButton_addDeck_clicked();
    void on_pushButton_deleteDeck_clicked();
    void on_pushButton_deleteCard_clicked();
    void on_pushButton_studyCard_clicked();
    void on_pushButton_import_clicked();
    void on_listWidget_decks_currentItemChanged(QListWidgetItem *current);
    void on_listWidget_decks_itemDoubleClicked(QListWidgetItem *item);
    void on_tableWidget_cardsTable_itemDoubleClicked(QTableWidgetItem *item);

    // Receive addCard data to mainwindow
    void receiveCardData(QString, QString, QString);
    void receiveCardDeleteData(bool);
    void receiveDeckData(QString);
    void receiveDeckDeleteData(bool);

    // =========================
    // Notebook
    // =========================
    void on_pushButton_addPage_clicked();
    void on_pushButton_addSection_clicked();
    void on_pushButton_removePage_clicked();
    void on_treeWidget_sections_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_sections_itemClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_sections_currentItemChanged(QTreeWidgetItem *cur, QTreeWidgetItem* prev);
    void on_plainTextEdit_textChanged();
    void on_action_renameNotebook_triggered();
    void on_actionAdd_Page_triggered();
    void on_actionNew_Section_triggered();

    // Shortcut bar for Markdown
    void on_pushButton_bold_clicked();
    void on_pushButton_bulleted_clicked();
    void on_pushButton_italics_clicked();
    void on_pushButton_numbered_clicked();
    void on_pushButton_strike_clicked();
    void on_pushButton_underline_clicked();
    void on_pushButton_indent_clicked();
    void on_pushButton_undent_clicked();

    // Asynchronous
    void receiveSectionData(QString, QColor, int);
    void receiveBookData(QString, QString, QString);

signals:
    void sendEditData(QString, QString, QString);  // Send mainwindown data to editcalendarevent
    void sendSectionInfo(QString, QColor, int);

    // Loading signals
    void loadCard(QString, QString, QString);
    void loadEvent(QString, QString);

private:    
    Ui::MainWindow *ui;

    deletecalendarevent *deleteWindow;
    addcalendarevent *addWindow;
    editcalendarevent *editWindow;

    adddeck *addDeckWindow;
    addcard *addCardWindow;
    importflashcards *importCardWindow;
    deletecard *deleteCardWindow;
    deletedeck *deleteDeckWindow;
    list<Deck*> deckList;
    studycard *studyCardWindow;

    editsection* editSectionWindow;
    Book* book;
    QString file_path;
    bool isModified;

    MarkdownEditor* me;
    QString m_filePath;
    Document m_content;
    addbook *newBook;

};

#endif // MAINWINDOW_H
