#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutspiralbound.h"
#include "addcalendarevent.h"
#include "deletecalendarevent.h"
#include "editcalendarevent.h"
#include "book.h"
#include "section.h"
#include "page.h"
#include "util.h"
#include "previewpage.h"
#include "adddeck.h"
#include "deletedeck.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QItemSelectionModel>
#include <QTableWidget>
#include <QListWidgetItem>
#include <list>
#include <qinputdialog.h>
#include <QWebChannel>
#include <regex>

//black magic
#define UNUSED(expr) do { (void)(expr); } while (0)

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget_eventList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_cardsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Book and MarkdownEditor setup; set default book path
    book = Book::generateBook("Default", "User");
    me = new MarkdownEditor(ui->plainTextEdit);
    file_path = QString("%1/.spiralbound/books/%2").arg(QDir::homePath()).arg(book->getName());

    // Check for the saving directory on startup; create it if it doesnt exist
    QDir save = QDir(QString("%1/.spiralbound/books").arg(QDir::homePath())),
         back = QDir(QString("%1/.spiralbound/backup").arg(QDir::homePath()));

    if (!save.exists()) { save.mkdir(save.path()); } // Returns a bool - do error check?
    if (!back.exists()) { back.mkdir(save.path()); }

    // Change the view to show the default book's first page; set flag to false so no changes
    // done during this block impact the loading 'unsaved changes' prompt
    file_path = "";
    ui->plainTextEdit->setDocument(book->getSection(0)->getPage(0)->getContent());
    ui->treeWidget_sections->setItemSelected(ui->treeWidget_sections->topLevelItem(0)->child(0), true);
    ui->treeWidget_sections->topLevelItem(0)->setExpanded(true);
    ui->label_bookInfo->setText(book->getName()+" by "+book->getAuthor());
    isModified = false;

    // Setup webengine for displaying markdown notes
    PreviewPage *page = new PreviewPage(this);
    QWebChannel *channel = new QWebChannel(this);

    ui->preview->setContextMenuPolicy(Qt::NoContextMenu);
    ui->preview->setPage(page);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged,
            [this]() { m_content.setText(ui->plainTextEdit->toPlainText()); });
    channel->registerObject(QStringLiteral("content"), &m_content);
    page->setWebChannel(channel);
    ui->preview->setUrl(QUrl("qrc:/resources/index.html"));
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//-----------------------------------------------------------+
//                    Menu Bar Buttons                       |
//-----------------------------------------------------------+
// Author:       Nicholas Ellis
// Init Date:    29.01.2019
// Last Updated: 29.01.2019
void MainWindow::on_action_about_triggered()
{
    AboutSpiralBound dialogWindow;
    dialogWindow.setModal(true);
    dialogWindow.exec();
}

// Author:       Tyler Rogers
// Init Date:    29.01.2019
// Last Updated: 29.01.2019
void MainWindow::on_action_aboutQt_triggered() { QApplication::aboutQt(); }

void MainWindow::on_action_crashCourse_triggered() {}
void MainWindow::on_action_print_triggered() {}

// Author:       Ketu Patel, Matthew Morgan
// Init Date:    23.03.2019
// Last Updated: 24.04.2019
void MainWindow::receiveBookData(QString bookNm, QString authNm, QString date)
{
    QTreeWidgetItem *root = new QTreeWidgetItem(), *page = new QTreeWidgetItem();
    Book* repBook = Book::generateBook(bookNm, authNm, &date), *hold;
    root->setText(0, repBook->getSection(0)->getSecName());
    page->setText(0, repBook->getSection(0)->getPage(0)->getPageName());

    hold = book;
    book = repBook;
    delete hold;

    // Clear calendar events, card table, and sections
    // Reset the section view to have only one section and one page
    // Update interface elements (such as book info label)
    for(int i=ui->tableWidget_eventList->rowCount(); i>0; i--)
        ui->tableWidget_eventList->removeRow(0);

    for(int i=ui->tableWidget_cardsTable->rowCount(); i>0; i--)
        ui->tableWidget_cardsTable->removeRow(0);

    for(int i=ui->listWidget_decks->count(); i>0; i--)
        ui->listWidget_decks->takeItem(0);

    for(Deck* d : deckList) { delete d; }
    deckList.clear();

    ui->treeWidget_sections->clear();
    ui->treeWidget_sections->addTopLevelItem(root);
    root->addChild(page);
    ui->treeWidget_sections->setItemSelected(page, true);
    root->setExpanded(true);
    on_treeWidget_sections_itemClicked(page, 0);
    ui->label_bookInfo->setText(bookNm+" by "+authNm);

    // Update isModified and directory for saving
    isModified = false;
    file_path = QString("%1/.spiralbound/books/%2").arg(QDir::homePath()).arg(book->getName());

    qDebug() << "New Book:" << bookNm << authNm << date;
}

// Author:       Ketu Patel, Matthew Morgan
// Init Date:    23.03.2019
// Last Updated: 06.04.2019
void MainWindow::on_action_new_triggered() {
    // Prompt if there are unsaved changes
    if (isModified) {
        if (!Util::confirm("Proceed", "You have unsaved changes. Continue?"))
            return;
    }

    newBook = new addbook();
    newBook->setModal(true);
    newBook->show();

    connect(newBook, SIGNAL(sendBookData(QString, QString, QString)), this, SLOT(receiveBookData(QString, QString, QString)));
}

void MainWindow::on_action_openRecent_triggered() {}

// Author:       Matthew Morgan
// Init Date:    21.03.2019
// Last Updated: 24.04.2019
void MainWindow::on_action_open_triggered() {
    // Prompt if there are unsaved changes
    if (isModified) {
        if (!Util::confirm("Proceed", "You have unsaved changes. Continue?"))
            return;
    }

    // Get the directory of the notebook and check for the about file's existence
    QString dir = QFileDialog::getExistingDirectory(this, "Select Notebook Directory", QString("%1/.spiralbound/books").arg(QDir::homePath()));
    //QString dir = "F:/Academic/Source/SpiralBound/SampleNotebook";

    if (dir == "") { return; }

    try {
        list<Deck*> decks = list<Deck*>();
        list<Event*> events = list<Event*>();
        Book* nBook;

        // -----------------------------------------------------------------------------
        // Open the book file and read in it's information
        QString about = QString("%1/about.txt").arg(dir);
        QFile* read = new QFile(about);
        int numDeck;

        if (!QFile::exists(about))
            throw "The selected directory is not detected as a notebook!";

        if (!read->open(QFile::ReadOnly))
            throw "The notebook's 'about' file couldn't be opened!";

        QTextStream str(&*read);

        QString name = str.readLine(),
                auth = str.readLine(),
                date = str.readLine();
        numDeck = str.readLine().toInt();

        nBook = Book::fromString(QString("%1\n%2\n%3").arg(name).arg(auth).arg(date).toStdString().c_str());
        read->close();
        delete read;

        // -----------------------------------------------------------------------------
        // Read in the study decks by connecting mainwindow to itself and emitting read cards
        // for insertion into the card table.

        for(int i=1; i<=numDeck; i++) {
            // Read in a single study deck
            QFile* deck = new QFile(QString("%1/study/%2.csv").arg(dir).arg(i));

            if (!deck->open(QFile::ReadOnly))
                throw "A study deck couldn't be read; there may be corruption!";

            QTextStream deckStr(&*deck);
            Deck* dck = new Deck();
            decks.push_back(dck);
            dck->name = deckStr.readLine();

            while(!deckStr.atEnd()) {
                // Card format is <n>,<front>,<back>, where <n> specifies where to split the front/back from
                // As such, parse <n>, then remove '<n>,' from the string, then parse the front/back
                QString card = deckStr.readLine();
                int ind = card.left(card.indexOf(',')).toInt();
                card = card.right(card.length()-card.indexOf(',')-1);

                dck->front.push_back(card.left(ind));
                dck->back.push_back(card.right(card.length()-ind-1));
            }

            deck->close();
            delete deck;
        }

        // -----------------------------------------------------------------------------
        // Read in calendar events, but only if the cal.csv file exists
        read = new QFile(QString("%1/cal.txt").arg(dir));

        if (read->exists()) {
            if (!read->open(QFile::ReadOnly))
                throw "The notebook's calendar events couldn't be loaded!";

            QTextStream cal(&*read);

            while(!cal.atEnd()) {
                Event* ev = new Event();
                ev->date = cal.readLine();
                ev->name = cal.readLine();
                ev->time = cal.readLine();
                events.push_back(ev);
            }
        }

        read->close();
        delete read;

        // -----------------------------------------------------------------------------
        // Read in notebook sections
        QDir sec = QDir(QString("%1/sections").arg(dir));
        sec.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);

        // For every section, we will:
        // + Open the 'about.txt' file for that section to get the name, color, and summary
        // + Iterate through every page of the section and add them to the section
        for(QString section : sec.entryList()) {
            QFile* about = new QFile(QString("%1/%2/about.txt").arg(sec.path()).arg(section));
            QDir pgs = QDir(QString("%1/%2").arg(sec.path()).arg(section)); // Should point to <path>/sections/<sec>
            pgs.setFilter(QDir::Files);

            if (!about->open(QFile::ReadOnly))
                throw "The about file for a section couldn't be opened!";

            QTextStream abStr(*&about);

            Section* mySec = Section::fromString(abStr.readAll().toStdString().c_str());
            nBook->loadSection(mySec);

            about->close();
            delete about;

            // Read in pages
            for(QString pg : pgs.entryList()) {
                QFile* page = new QFile(QString("%1/%2").arg(pgs.path()).arg(pg));

                // Skip the 'about' file since it was already used
                if (page->fileName().split('/').last() == "about.txt") {
                    delete page;
                    continue;
                }

                if (!page->open(QFile::ReadOnly))
                    throw "A page couldn't be read for a section!";

                QTextStream pgStream(*&page);

                Page* myPg = Page::fromString(pgStream.readAll().toStdString().c_str());
                nBook->loadPage(mySec, myPg);

                delete page;
            }
        }

        // Update the notebook interface to reflect the new book
        ui->treeWidget_sections->clear();

        for(int i=nBook->numSections()-1; i>=0; i--) {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            QBrush pal = item->background(0);

            // Set the item's properties after inserting it
            pal.setColor(nBook->getSection(i)->getColor());
            pal.setStyle(Qt::BrushStyle::SolidPattern);
            item->setBackground(0, pal);
            item->setText(0, nBook->getSection(i)->getSecName());
            ui->treeWidget_sections->insertTopLevelItem(0, item);

            for(int k=nBook->getSection(i)->numPages()-1; k>=0; k--) {
                QTreeWidgetItem* pg = new QTreeWidgetItem();
                pg->setText(0, nBook->getSection(i)->getPage(k)->getPageName());
                item->insertChild(0, pg);
            }
        }

        // Select the first section's summary
        ui->treeWidget_sections->topLevelItem(0)->setExpanded(true);
        ui->treeWidget_sections->topLevelItem(0)->child(0)->setSelected(true);
        ui->plainTextEdit->setDocument(nBook->getSection(0)->getPage(0)->getContent());

        // Update the list of calendar events and decks
        for(int i=ui->tableWidget_eventList->rowCount(); i>0; i--)
            ui->tableWidget_eventList->removeRow(0);

        for(int i=ui->tableWidget_cardsTable->rowCount(); i>0; i--)
            ui->tableWidget_cardsTable->removeRow(0);

        for(int i=ui->listWidget_decks->count(); i>0; i--) {
            ui->listWidget_decks->takeItem(0);
        }

        connect(this, SIGNAL(loadCard(QString, QString, QString)), this, SLOT(receiveCardData(QString, QString, QString)));
        for(Deck* d : decks) {
            ui->listWidget_decks->addItem(d->name);
        }
        for(Deck* d : deckList) { delete d; }
        deckList = decks;
        disconnect(this, SIGNAL(loadCard(QString, QString, QString)), this, SLOT(receiveCardData(QString, QString, QString)));

        connect(this, SIGNAL(loadEvent(QString, QString)), this, SLOT(receiveAddData(QString, QString)));
        for(Event* e : events) {
            emit loadEvent(e->name, e->date+" "+e->time);
            delete e;
        }
        disconnect(this, SIGNAL(loadEvent(QString, QString)), this, SLOT(receiveAddData(QString, QString)));

        delete book;
        book = nBook;
        file_path = QString(dir);
        isModified = false;
        ui->label_bookInfo->setText(book->getName()+" by "+book->getAuthor());
        ui->listWidget_decks->setCurrentRow(0);
    }
    catch(exception& e) {
        qDebug() << "Woopsie: " << e.what();
        Util::showError("Load Error", "The notebook you selected couldn't be loaded.");
    }
    catch(...) { qDebug() << "Woopsie..."; }
}

// Author:       Matthew Morgan
// Init Date:    22.03.2019
// Last Updated: 24.04.2019
/** save(book, main, decks, <dir>) saves the current Book instance, and flash cards/calendar information, to the
  * directory selected, using the MainWindow interface - main - to perform fetching of needed data. It
  * returns the directory of the saved book. It further requires the list of decks for saving flash cards.
  *
  * The default directory for dir is <home>/.spiralbound/books/. */
QString save(Book* book, Ui::MainWindow* main, list<Deck*> decks, QString dir=QString("%1/.spiralbound/books/").arg(QDir::homePath())) {
    QString backup = QDir::homePath() + "/.spiralbound/backup/" + book->getName();
    dir = dir + book->getName();

    QDir root = QDir(dir);
    QDir back = QDir(backup);
    back.setFilter(QDir::NoDotAndDotDot|QDir::AllEntries);

    if (!root.exists()) { root.mkpath(dir); }
    else {
        // Create a backup in the backup directory and remove the old one
        if (back.exists()) { back.removeRecursively(); }
        Util::copyDirectory(dir, backup);

        if (!QDir(dir).removeRecursively()) {
            qDebug() << "ERROR: Couldn't delete old notebook (save).";
        }
        root.mkpath(dir);
    }

    try {
        // ------------------------------------------
        // Save the about file
        QFile* bkFile = new QFile(QString("%1/about.txt").arg(dir));

        if (!bkFile->open(QFile::WriteOnly))
            throw "The notebook's about file couldn't be written";

        QTextStream bk(*&bkFile);
        bk << book->toString();

        // ------------------------------------------
        // Save study cards
        QDir study = QDir(QString("%1/study").arg(dir));
        if (!study.exists()) { study.mkdir(study.path()); }

        bk << endl << decks.size() << endl;

        int i=1;
        for(Deck* deck : decks) {
            QFile* deckFile = new QFile(QString("%1/study/%2.csv").arg(dir).arg(i));

            if (!deckFile->open(QFile::WriteOnly))
                throw "A deck file couldn't be opened for writing!";

            QTextStream dStream(*&deckFile);
            dStream << deck->name << "\n";

            for(int k=deck->front.size(); k>0; k--) {
                QString card_fr = deck->front.takeFirst(), card_bk = deck->back.takeFirst();
                dStream << card_fr.length() << "," << card_fr << "," << card_bk << "\n";
                deck->front.push_back(card_fr);
                deck->back.push_back(card_bk);
            }

            deckFile->close();
            delete deckFile;
            i++;
        }

        // ************************************************************************************************************

        // ------------------------------------------
        // Save calendar events
        bkFile = new QFile(QString("%1/cal.txt").arg(dir));

        if (!bkFile->open(QFile::WriteOnly))
            throw "The notebook's calendar events couldn't be saved!";

        QTextStream cal(*&bkFile);

        for(int i=main->tableWidget_eventList->rowCount()-1; i>=0; i--) {
            cal << main->tableWidget_eventList->item(i, 0)->text() << "\n"
                << main->tableWidget_eventList->item(i, 1)->text() << "\n"
                << main->tableWidget_eventList->item(i, 2)->text() << "\n";
        }

        bkFile->close();
        delete bkFile;

        // ------------------------------------------
        // Create section directories and store section information
        for(int i=book->numSections()-1; i>=0; i--) {
            QDir section = QDir(QString("%1/sections/%2").arg(dir).arg(i));
            if (section.exists()) { section.rmdir(section.path()); }
            section.mkpath(section.path());
            bkFile = new QFile(QString("%1/about.txt").arg(section.path()));

            if (!bkFile->open(QFile::WriteOnly))
                throw "A section's about file couldn't be written!";

            QTextStream sec(*&bkFile);
            sec << book->getSection(i)->toString();

            // Save pages
            for(int k=book->getSection(i)->numPages()-1; k>=0; k--) {
                QFile* page = new QFile(QString("%1/pg-%2.txt").arg(section.path()).arg(k));

                if (!page->open(QFile::WriteOnly))
                    throw "A section's pages couldn't be saved properly";

                QTextStream pg(*&page);
                pg << book->getSection(i)->getPage(k)->toString();

                page->close();
                delete page;
            }

            bkFile->close();
            delete bkFile;
        }
    }
    catch(...) {
        // An error occured - reverse backup
        qDebug() << "Saving Woopsie";
        Util::showError("Save Error", "An error occured during saving.");
        Util::copyDirectory(backup, dir);
    }

    return dir;
}

// Author:       Matthew Morgan
// Init Date:    21.03.2019
// Last Updated: 06.04.2019
void MainWindow::on_action_save_triggered() { save(book, ui, deckList); isModified = false;}

// Author:       Matthew Morgan
// Init Date:    22.03.2019
// Last Updated: 22.03.2019
void MainWindow::on_action_export_triggered() {
    // Export the notebook to the given location of the user's choice;
    // Show a message that they'll need to create a directory if it doesn't exist
    // If they select a location that has a notebook in it, then prompt for overwrite

    Util::showMessage("Exporting", "A file dialog is about to open for you to select where to export this notebook. If the directory "
                                   "doesn't exist, then you'll need to create it before accepting.");

    QString dir = QFileDialog::getExistingDirectory(this, "Select Notebook Directory", QString("%1/.spiralbound/books").arg(QDir::homePath()));
    if (dir == "") { return; }

    if (QFile(QString("%1/%2/about.txt").arg(dir).arg(book->getName())).exists())
        if (!Util::confirm("Overwrite", "A notebook is detected in this directory. Overwrite?"))
            return;

    save(book, ui, deckList, dir);
}

void MainWindow::on_action_bold_triggered() { ui->plainTextEdit->setTextCursor(me->bold()); }
void MainWindow::on_action_italic_triggered() { ui->plainTextEdit->setTextCursor(me->italic()); }
void MainWindow::on_action_strikethrough_triggered() { ui->plainTextEdit->setTextCursor(me->strikethough()); }
void MainWindow::on_action_underline_triggered() { ui->plainTextEdit->setTextCursor(me->underline()); }
void MainWindow::on_action_indent_triggered() {}
void MainWindow::on_action_unindent_triggered() {}
void MainWindow::on_action_bulletedList_triggered() { me->insertBullet(); }
void MainWindow::on_action_numberedList_triggered() { me->insertNumeral(); }
void MainWindow::on_action_comment_triggered() {}

void MainWindow::on_action_taskList_triggered() {}
void MainWindow::on_action_preferences_triggered() {}
void MainWindow::on_action_printPreview_triggered() {}

// Author:       Tyler Rogers (cirkuitbreaker)
// Init date:    29.01.2019
// Last Updated: 29.01.2019
void MainWindow::on_action_quit_triggered() { QApplication::quit(); }

//-----------------------------------------------------------+
//                   Calendar Tab                            |
//-----------------------------------------------------------+
// Author:       Nicholas, Matthew
// Init Date:    19.02.2019
// Last Updated: 06.04.2019
void MainWindow::receiveAddData(QString eventName, QString eventDateTime)
{
    // Seperate date from time
    QStringList datetime = eventDateTime.split(" ");
    QString date = datetime[0];
    QString time = datetime[1].append(" ").append(datetime[2]);

    // Create row
    ui->tableWidget_eventList->insertRow(ui->tableWidget_eventList->rowCount() );
    // Populate row
    int row = ui->tableWidget_eventList->rowCount()-1;
    ui->tableWidget_eventList->setSortingEnabled(false);
    ui->tableWidget_eventList->setItem(row, 0, new QTableWidgetItem(date));
    ui->tableWidget_eventList->setItem(row, 1, new QTableWidgetItem(eventName));
    ui->tableWidget_eventList->setItem(row, 2, new QTableWidgetItem(time));
    ui->tableWidget_eventList->setSortingEnabled(true);
    isModified = true;
}

// Author:       Nicholas, Cam, Jamie
// Init Date:    05.02.2019
// Last Updated: 22.03.2019
void MainWindow::on_pushButton_addEvent_clicked()
{
    QDate curDate = ui->calendarWidget->selectedDate();

   // Builds addcalendarevent GUI/window
   addWindow = new addcalendarevent(curDate ,this);
   addWindow->setModal(true);
   addWindow->show();

   // Connect mainwindow to addeventwindow
   connect(addWindow, SIGNAL(sendAddData(QString, QString)), this, SLOT(receiveAddData(QString, QString)));
}

// Author:       Nicholas, Matthew
// Init Date:    19.02.2019
// Last Updated: 06.04.2019
void MainWindow::receiveEditData(QString eventName, QString eventDateTime)
{
    // Seperate date from time
    QStringList datetime = eventDateTime.split(" ");
    QString date = datetime[0];
    QString time = datetime[1].append(" ").append(datetime[2]);

    // Populate current row
    int row = ui->tableWidget_eventList->currentRow();
    ui->tableWidget_eventList->setSortingEnabled(false);
    ui->tableWidget_eventList->setItem(row, 0, new QTableWidgetItem(date));
    ui->tableWidget_eventList->setItem(row, 1, new QTableWidgetItem(eventName));
    ui->tableWidget_eventList->setItem(row, 2, new QTableWidgetItem(time));
    ui->tableWidget_eventList->setSortingEnabled(true);
    isModified = true;
}

// Author:       Nicholas
// Init Date:    09.02.2019
// Last Updated: 19.02.2019
void MainWindow::on_pushButton_editEvent_clicked()
{
    QTableWidgetItem *item = ui->tableWidget_eventList->currentItem();
    int row = ui->tableWidget_eventList->currentRow();
    ui->tableWidget_eventList->selectRow(row);

    // If user did not select an event from the event list
    if(item == nullptr)
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","Select event to edit, please try again.");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        QString date = ui->tableWidget_eventList->item(row, 0)->text();
        QString name = ui->tableWidget_eventList->item(row, 1)->text();
        QString time = ui->tableWidget_eventList->item(row, 2)->text();

        // Builds editcalendarevent GUI/window
        editWindow = new editcalendarevent(this);
        editWindow->setModal(true);
        editWindow->show();

        // Connect mainwindow to editcalendarevent window
        connect(this, SIGNAL(sendEditData(QString, QString, QString)), editWindow, SLOT(receiveEditData(QString, QString, QString)));

        // Send selected item to editcalendarevent window
        emit sendEditData(date, name, time);

        // Connect editcalendarevent to maindwindow
        connect(editWindow, SIGNAL(sendEditData(QString, QString)), this, SLOT(receiveEditData(QString, QString)));
    }
}
// Author:       Nicholas, Matthew
// Init Date:    09.02.2019
// Last Updated: 06.04.2019
void MainWindow::receiveDeleteData(bool response)
{
   if(response == true)
   {
       // Delete item from table
       ui->tableWidget_eventList->removeRow(ui->tableWidget_eventList->currentItem()->row());
       isModified = true;
   }
}

// Author:       Jamie, Nicholas
// Init Date:    07.02.2019
// Last Updated: 19.02.2019
void MainWindow::on_pushButton_deleteEvent_clicked()
{
    // Get current selected row
    QTableWidgetItem *item = ui->tableWidget_eventList->currentItem();

    if(item == nullptr)
        {
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Error","Select event to edit, please try again.");
            messageBox.setFixedSize(500,200);
        }
        else
        {
            // Builds deletecalendarevent GUI/window
            deleteWindow = new deletecalendarevent(this);
            deleteWindow->setModal(true);
            deleteWindow->show();

            // Connect mainwindow to addeventwindow
            connect(deleteWindow, SIGNAL(sendDeleteData(bool)), this, SLOT(receiveDeleteData(bool)));
        }
}

// Author:       Nicholas
// Init Date:    19.02.2019
// Last Updated: 22.03.2019
void MainWindow::on_tableWidget_eventList_cellChanged(int row, int column)
{
    UNUSED(row);
    if(column == 2)
    {
        ui->tableWidget_eventList->sortByColumn(0, Qt::AscendingOrder);
    }
}

//-----------------------------------------------------------+
//                   Notetake Tab                            |
//-----------------------------------------------------------+
// Author:       Matthew Morgan
// Init Date:    10.03.2019
// Last Updated: 06.04.2019
void MainWindow::on_pushButton_addPage_clicked()
{
    // Add a new page to the section, and activate it as the current
    int* ind = Util::getSectionPage(ui->treeWidget_sections, ui->treeWidget_sections->selectedItems().front());
    QTreeWidgetItem* pg = new QTreeWidgetItem();

    book->getSection(ind[0])->addPage("Untitled Page");
    ui->treeWidget_sections->topLevelItem(ind[0])->addChild(pg);
    ui->treeWidget_sections->clearSelection();
    pg->setText(0, "Untitled Page");
    pg->setSelected(true);
    on_treeWidget_sections_itemClicked(pg, 0);
    isModified = true;

    delete ind;
}

// Author:       Matthew Morgan
// Init Date:    10.03.2019
// Last Updated: 06.04.2019
void MainWindow::on_pushButton_addSection_clicked()
{
    // Add a new section and page, and update the tree to reflect these changes
    // Clear the page selection
    int size = book->numSections();
    QTreeWidgetItem *sec = new QTreeWidgetItem(), *pg = new QTreeWidgetItem();

    book->addSection(QString("New Section %1").arg(book->numSections()+1));
    book->getSection(size)->addPage("Untitled Page");

    ui->treeWidget_sections->addTopLevelItem(sec);
    sec->setText(0, book->getSection(size)->getSecName());
    sec->addChild(pg);
    pg->setText(0, "Untitled Page");

    ui->treeWidget_sections->setItemExpanded(sec, true);
    ui->treeWidget_sections->clearSelection();
    pg->setSelected(true);
    on_treeWidget_sections_itemClicked(pg, 0);
    isModified = true;
}

// Author:       Matthew Morgan
// Init Date:    20.03.2019
// Last Updated: 06.04.2019
void MainWindow::on_treeWidget_sections_itemDoubleClicked(QTreeWidgetItem *item, int column) {
    int* ind = Util::getSectionPage(ui->treeWidget_sections, item);

    if (ind[1] > -1) {
        // Allow renaming of a page if the new name isn't blank
        bool ok;
        QString text = QInputDialog::getText(this, "Rename Page", "New Name:", QLineEdit::Normal, item->text(column), &ok, Qt::MSWindowsFixedSizeDialogHint);


        if (ok && !text.isEmpty()) {
            Section* sec = book->getSection(ind[0]);
            sec->getPage(ind[1])->setPgName(text);
            item->setText(column, text);
            isModified = true;
        }
    }
    else {
        // Changing section information
        // Instantiate the window, then send the data and wait to receive updated data
        editSectionWindow = new editsection(this);
        editSectionWindow->setModal(true);
        editSectionWindow->show();

        Section* sec = book->getSection(ind[0]);
        connect(this, SIGNAL(sendSectionInfo(QString, QColor, int)), editSectionWindow, SLOT(receiveSectionData(QString, QColor, int)));
        emit sendSectionInfo(sec->getSecName(), sec->getColor(), ind[0]);
        connect(editSectionWindow, SIGNAL(sendSectionData(QString, QColor, int)), this, SLOT(receiveSectionData(QString, QColor, int)));
    }

    delete ind;
}

// Author:       Matthew Morgan
// Init Date:    20.03.2019
// Last Updated: 20.03.2019
void MainWindow::on_treeWidget_sections_itemClicked(QTreeWidgetItem* item, int column) {
    UNUSED(column);

    // Dynamically update the content being displayed - section info or page content
    int* ind = Util::getSectionPage(ui->treeWidget_sections, item);

    if (ind[1] == -1) {
        ui->plainTextEdit->setDocument(book->getSection(ind[0])->getDoc());
    }
    else {
        ui->plainTextEdit->setDocument(book->getSection(ind[0])->getPage(ind[1])->getContent());
    }

    delete ind;
}

// Author:       Matthew Morgan
// Init Date:    20.03.2019
// Last Updated: 06.04.2019
void MainWindow::receiveSectionData(QString nm, QColor col, int ind) {
    // Update the section's color and name
    Section* sec = book->getSection(ind);
    sec->setName(nm);
    sec->setColor(col);
    isModified = true;

    ui->treeWidget_sections->topLevelItem(ind)->setText(0, nm);
    QBrush pal = ui->treeWidget_sections->palette().background();
    pal.setColor(col);
    pal.setStyle(Qt::BrushStyle::SolidPattern);
    ui->treeWidget_sections->topLevelItem(ind)->setBackground(0, pal);
}


// Author:       Ketu Patel, Matthew Morgan
// Init Date:    13.03.2019
// Last Updated: 06.04.2019
void MainWindow::on_pushButton_removePage_clicked()
{
    int* ind = Util::getSectionPage(ui->treeWidget_sections, ui->treeWidget_sections->selectedItems().first());

    if (ind[1] == -1) {
        // Deleting a section
        if (book->numSections() > 1) {
            QMessageBox::StandardButton reply = QMessageBox::question(this,
                "Delete Section", "Are you sure you want to delete this section?");

            if (reply == QMessageBox::Yes) {
                delete ui->treeWidget_sections->topLevelItem(ind[0]);
                book->removeSection(ind[0]);

                // Move to the first page of the first section
                ui->treeWidget_sections->clearSelection();
                ui->treeWidget_sections->topLevelItem(0)->setExpanded(true);
                ui->treeWidget_sections->topLevelItem(0)->child(0)->setSelected(true);
                on_treeWidget_sections_itemClicked(ui->treeWidget_sections->topLevelItem(0)->child(0), 0);
            }
        }
        else {
            QMessageBox msg;
            msg.critical(nullptr, "Error", "Cannot delete the last section of the notebook!");
            msg.setFixedSize(500, 200);
        }
    }
    else {
        // Deleting a page
        Section* sec = book->getSection(ind[0]);

        if (sec->numPages() > 1) {
            ui->treeWidget_sections->topLevelItem(ind[0])->takeChild(ind[1]);
            sec->removePage(ind[1]);

            // Select the first page of the section from which the page was removed
            ui->treeWidget_sections->clearSelection();
            ui->treeWidget_sections->topLevelItem(ind[0])->setExpanded(true);
            ui->treeWidget_sections->topLevelItem(ind[0])->child(0)->setSelected(true);
            on_treeWidget_sections_itemClicked(ui->treeWidget_sections->topLevelItem(ind[0])->child(0), 0);
        }
        else {
            QMessageBox msg;
            msg.critical(nullptr, "Error", "Cannot delete the only page of a section!");
            msg.setFixedSize(500, 200);
        }
    }

    isModified = true;
    delete ind;
}

// Author:       Matthew Morgan
// Init Date:    21.03.2019
// Last Updated: 21.03.2019
void MainWindow::on_treeWidget_sections_currentItemChanged(QTreeWidgetItem *cur, QTreeWidgetItem *prev)
{
    UNUSED(prev);
    if (cur == nullptr) { return; }
    on_treeWidget_sections_itemClicked(cur, 0);
}

// Author:       Matthew Morgan
// Init Date:    06.04.2019
// Last Updated: 06.04.2019
void MainWindow::on_plainTextEdit_textChanged() { isModified = true; }

void MainWindow::on_pushButton_bold_clicked()
{
    ui->plainTextEdit->setTextCursor(me->bold());
    ui->plainTextEdit->setFocus();
}

void MainWindow::on_pushButton_italics_clicked()
{
    ui->plainTextEdit->setTextCursor(me->italic());
    ui->plainTextEdit->setFocus();
}

void MainWindow::on_pushButton_underline_clicked()
{
    ui->plainTextEdit->setTextCursor(me->underline());
    ui->plainTextEdit->setFocus();
}

void MainWindow::on_pushButton_strike_clicked()
{
    ui->plainTextEdit->setTextCursor(me->strikethough());
    ui->plainTextEdit->setFocus();
}

void MainWindow::on_pushButton_bulleted_clicked() { me->insertBullet(); ui->plainTextEdit->setFocus();}
void MainWindow::on_pushButton_numbered_clicked() { me->insertNumeral(); ui->plainTextEdit->setFocus();}
void MainWindow::on_pushButton_undent_clicked() {}
void MainWindow::on_pushButton_indent_clicked() { /*me->detectEnum();*/}

//-----------------------------------------------------------+
//                     Flash Card Tab                        |
//-----------------------------------------------------------+
// Author:       Nick, Cam, Matthew
// Init Date:    26.02.2019
// Last Updated: 24.04.2019
void MainWindow::receiveCardData(QString deckName, QString cardFront, QString cardBack)
{
    // If selected deck is not highlighted add only to backend
    if (ui->listWidget_decks->currentItem()->text() != deckName)
    {
        for (Deck* deck : deckList)
        {
            if (deck->name == deckName)
            {
                deck->front.append(cardFront);
                deck->back.append(cardBack);
                break;
            }
        }
    }
    else // If deck is selected add to front and backend
    {
        for (Deck* deck : deckList)
        {
            if (deck->name == deckName)
            {
                deck->front.append(cardFront);
                deck->back.append(cardBack);
                ui->tableWidget_cardsTable->insertRow(ui->tableWidget_cardsTable->rowCount() );
                ui->tableWidget_cardsTable->setItem(ui->tableWidget_cardsTable->rowCount()-1, 0, new QTableWidgetItem(cardFront));
                ui->tableWidget_cardsTable->setItem(ui->tableWidget_cardsTable->rowCount()-1, 1, new QTableWidgetItem(cardBack));
                break;
            }
        }
    }

    isModified = true;

    // Debugging
    qDebug() << "Deck contents: ";
    for (Deck* deck : deckList) {
        qDebug() << deck->front;
        qDebug() << deck->back;
    }
}

// Author:       Jamie, Nicholas, Cam, Matthew
// Init Date:    09.02.2019
// Last Updated: 24.04.2019
void MainWindow::receiveCardDeleteData(bool response)
{
   if(response == true)
   {
       int position = ui->tableWidget_cardsTable->currentItem()->row();

       // Delete card from data structure (backend)
       for (Deck* deck : deckList)
       {
           if(ui->listWidget_decks->currentItem()->text() == deck->name)
           {
               deck->back.removeAt(position);
               deck->front.removeAt(position);
               break;
           }
       }

       // Delete card from table (frontend)
       ui->tableWidget_cardsTable->removeRow(ui->tableWidget_cardsTable->currentItem()->row());
       isModified = true;
   }
}

// Author:       Cam, Nick
// Init Date:    26.03.2019
// Last Updated: 26.03.2019
void MainWindow::on_pushButton_addDeck_clicked()
{
    addDeckWindow = new adddeck(this);
    addDeckWindow->setModal(true);
    addDeckWindow->show();

    connect(addDeckWindow, SIGNAL(sendDeckData(QString)), this, SLOT(receiveDeckData(QString)));
}

// Author:       Cam, Nick, Matthew
// Init Date:    26.03.2019
// Last Updated: 24.04.2019
void MainWindow::receiveDeckData(QString deck)
{
    // Check to see if deck already exists
    for (Deck* d : deckList)
    {
        // If deck already exists, display error message.
        if (d->name.toLower().trimmed() == deck.toLower().trimmed())
        {
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Error","Deck already exists. \nCannot have duplicates.");
            messageBox.setFixedSize(500,200);
            return;
        }
    }

    // If deck does not exist already, add deck to deckList.
    ui->listWidget_decks->addItem(deck.trimmed());
    QListWidgetItem * last = ui->listWidget_decks->item(ui->listWidget_decks->count() - 1);
    Deck * newDeck = new Deck();
    newDeck->name = last->text();
    deckList.push_back(newDeck);
    ui->listWidget_decks->setCurrentRow(ui->listWidget_decks->count() - 1);
    isModified = true;

    // Debugging
    for (Deck* deck : deckList) {
        qDebug() << deck->name;
    }
}

// Author:       Cam, Nick
// Init Date:    26.03.2019
// Last Updated: 02.04.2019
void MainWindow::on_pushButton_deleteDeck_clicked()
{
    QListWidgetItem * deck = ui->listWidget_decks->currentItem();

    if (deck == nullptr)
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","Select a deck to delete, please try again.");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        // Builds deletedeck GUI/window
        deleteDeckWindow = new deletedeck(this);
        deleteDeckWindow->setModal(true);
        deleteDeckWindow->show();

        // Connect mainwindow to addeventwindow
        connect(deleteDeckWindow, SIGNAL(sendDeleteData(bool)), this, SLOT(receiveDeckDeleteData(bool)));
    }
}

// Author:       Cam, Nick
// Init Date:    26.03.2019
// Last Updated: 24.04.2019
void MainWindow::receiveDeckDeleteData(bool response)
{
    QListWidgetItem * selectedDeck = ui->listWidget_decks->currentItem();
    QString deckName = selectedDeck->text();

    if(response == true)
    {
        delete selectedDeck;
        for (Deck* deck : deckList)
        {
            if (deck->name == deckName)
            {
                deckList.remove(deck);
                break;
            }
        }
    }
    isModified = true;

    // Debugging
    qDebug() << "Deck List: ";
    for (Deck* deck : deckList) {
        qDebug() << deck->name;
    }
}

// Author:       Jamie, Nick
// Init Date:    26.02.2019
// Last Updated: 26.02.2019
void MainWindow::on_pushButton_addCard_clicked()
{
    list<Deck*> newDeckList = deckList;

    if (deckList.empty())
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","No Decks Exist.");
        messageBox.setFixedSize(500,200);
        //this->close();
    }
    else
    {
        addCardWindow = new addcard(this, newDeckList);
        addCardWindow->setModal(true);
        addCardWindow->show();

        connect(addCardWindow, SIGNAL(sendCardData(QString,QString,QString)), this, SLOT(receiveCardData(QString, QString, QString)));
    }



}

// Author:       Jamie
// Init Date:    12.03.2019
// Last Updated: 12.03.2019
void MainWindow::on_pushButton_deleteCard_clicked()
{
    // TODO: open window for deleting selected deck.
    // Get current selected row
    QTableWidgetItem *item = ui->tableWidget_cardsTable->currentItem();

    if(item == nullptr)
        {
            QMessageBox messageBox;
            messageBox.critical(nullptr,"Error","Select a card to delete, please try again.");
            messageBox.setFixedSize(500,200);
        }
        else
        {
            // Builds deletecard GUI/window
            deleteCardWindow = new deletecard(this);
            deleteCardWindow->setModal(true);
            deleteCardWindow->show();

            // Connect mainwindow to addeventwindow
            connect(deleteCardWindow, SIGNAL(sendDeleteData(bool)), this, SLOT(receiveCardDeleteData(bool)));
        }
}

// Author:
// Init Date:
// Last Updated:
void MainWindow::on_pushButton_studyCard_clicked()
{
    // TODO: open study window for selected deck.
    QListWidgetItem * deck = ui->listWidget_decks->currentItem();
    QString deckName = deck->text();

    if (deck == nullptr)
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","Select a deck to study, please try again.");
        messageBox.setFixedSize(500,200);
    }
    else
    {

        for (Deck* deck : deckList)
        {
            if (deck->name == deckName)
            {
                // Builds deletedeck GUI/window
                studyCardWindow = new studycard(this, deck);
                studyCardWindow->setModal(true);
                studyCardWindow->show();
                //studyCardWindow->set(deck);
                break;
            }
        }

    }
}

// Author:       Cam
// Init Date:    02.03.2019
// Last Updated: 07.03.2019
void MainWindow::on_pushButton_import_clicked()
{
    list<Deck*> newDeckList = deckList;

    if (deckList.empty())
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","No Decks Exist.");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        importCardWindow = new importflashcards(this, newDeckList);
        importCardWindow->setModal(true);
        importCardWindow->show();

        connect(importCardWindow, SIGNAL(sendCardData(QString,QString,QString)), this, SLOT(receiveCardData(QString, QString, QString)));
    }
}

// Author:       Ketu Patel, Matthew Morgan
// Init Date:    04.12.2019
// Last Updated: 04.24.2019
void MainWindow::on_action_renameNotebook_triggered()
{
    QString current_name = book->getName();
    bool ok;
    QString text = QInputDialog::getText(this, "Rename Notebook", "New Name:", QLineEdit::Normal ,"", &ok, Qt::MSWindowsFixedSizeDialogHint).trimmed();

    while (ok && text.isEmpty()){
        text = QInputDialog::getText(this, "Rename Notebook", "Can't assign an empty name, enter the name again:", QLineEdit::Normal,"", &ok, Qt::MSWindowsFixedSizeDialogHint).trimmed();
    }

    if (ok) {
        QRegExp rx("[a-zA-Z0-9-_ ]+");
        QRegExpValidator v(rx, nullptr);
        QString s;
        int pos = 0;

        // String validation
        if (v.validate(text, pos) == QValidator::Acceptable) {

            if (QDir(QDir::homePath() + "/.spiralbound/books/" + text).exists()) {
                Util::showMessage("Error", "Notebook with given name already exists!");
            }
            else {
                // Copy the present notebook to the backup directory
                // Save the new book
                // Destroy the old book
                QString old_name = QString(book->getName());
                file_path = QString(QDir::homePath() + "/.spiralbound/books/" + text);
                book->setName(text);

                on_action_save_triggered();
                Util::copyDirectory(file_path, QDir::homePath()+"/.spiralbound/backup/"+old_name);
                if (!QDir(QString("%1/.spiralbound/books/%2").arg(QDir::homePath()).arg(old_name)).removeRecursively()) {
                    qDebug() << "ERROR: Couldn't delete old directory";
                }

                ui->label_bookInfo->setText(book->getName() +" by "+book->getAuthor());
            }
        }
        else {
            Util::showMessage("Error", "Only alphabetic and numeric characters, hyphens, underscores, and spaces may be used in a name!");
        }
    }
}

// Author: Ketu Patel
// Init Date: 04.12.2019
// Last Updated: 04.19.2019
void MainWindow::on_actionAdd_Page_triggered()
{
    on_pushButton_addPage_clicked();
}

// Author: Ketu Patel
// Init Date: 04.12.2019
// Last Updated: 04.19.2019
void MainWindow::on_actionNew_Section_triggered()
{
    on_pushButton_addSection_clicked();
}

// Author:       Cam, Nick, Matt
// Init Date:    09.04.2019
// Last Updated: 09.04.2019
void MainWindow::on_listWidget_decks_currentItemChanged(QListWidgetItem *current)
{
    for (int rC = ui->tableWidget_cardsTable->rowCount(); rC >= 0; rC--)
    {
        ui->tableWidget_cardsTable->removeRow(rC);
    }

    if (current != nullptr)
    {
        QString deckName = current->text();

        for (Deck* deck : deckList)
        {
            if(deck->name == deckName)
            {
                for (int i = 0; i < deck->front.length(); i++)
                {
                    ui->tableWidget_cardsTable->insertRow(ui->tableWidget_cardsTable->rowCount() );
                    ui->tableWidget_cardsTable->setItem(ui->tableWidget_cardsTable->rowCount()-1, 0, new QTableWidgetItem(deck->front[i]));
                    ui->tableWidget_cardsTable->setItem(ui->tableWidget_cardsTable->rowCount()-1, 1, new QTableWidgetItem(deck->back[i]));
                }
                break;
            }
        }
    }
}

// Author:       Cam, Matthew
// Init Date:    16.04.2019
// Last Updated: 16.04.2019
void MainWindow::on_listWidget_decks_itemDoubleClicked(QListWidgetItem *item)
{
    item->setFlags (item->flags () | Qt::ItemIsEditable);
    QString oldName = item->text();
    bool ok;
    QString text = QInputDialog::getText(nullptr, "Rename Deck", "New Name:", QLineEdit::Normal, item->text(), &ok, Qt::MSWindowsFixedSizeDialogHint);


    if (ok && !text.isEmpty()) {
        // Check to see if deck already exists
        for (Deck* d : deckList)
        {
            // If deck already exists, display error message.
            if (d->name.toLower().trimmed() == item->text().toLower().trimmed())
            {
                QMessageBox messageBox;
                messageBox.critical(nullptr,"Error","Deck already exists. \nCannot have duplicates.");
                messageBox.setFixedSize(500,200);
                return;
            }

            if (d->name == oldName)
            {
                d->name = text.trimmed();
                isModified = true;
                break;
            }
        }
    }
}

// Author:       Cam, Matthew
// Init Date:    16.04.2019
// Last Updated: 16.04.2019
void MainWindow::on_tableWidget_cardsTable_itemDoubleClicked(QTableWidgetItem *item)
{
    item->setFlags (item->flags () | Qt::ItemIsEditable);
    bool ok;
    QString text = QInputDialog::getText(nullptr, "Rename Card", "New Data:", QLineEdit::Normal, item->text(), &ok, Qt::MSWindowsFixedSizeDialogHint);

    if (ok && !text.isEmpty()) {
        item->setText(text);
        for(Deck* deck : deckList)
        {
            if(ui->listWidget_decks->currentItem()->text() == deck->name)
            {
                if(ui->tableWidget_cardsTable->currentColumn() == 0)
                {
                    deck->front[ui->tableWidget_cardsTable->currentRow()] = text;
                }
                else if (ui->tableWidget_cardsTable->currentColumn() == 1)
                {
                    deck->back[ui->tableWidget_cardsTable->currentRow()] = text;
                }
            }
        }
        isModified = true;
    }
}



