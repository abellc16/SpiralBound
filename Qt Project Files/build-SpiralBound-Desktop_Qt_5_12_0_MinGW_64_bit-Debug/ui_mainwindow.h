/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open;
    QAction *actionTest;
    QAction *action_save;
    QAction *action_about;
    QAction *action_aboutQt;
    QAction *action_crashCourse;
    QAction *action_print;
    QAction *action_new;
    QAction *action_openRecent;
    QAction *action_saveAs;
    QAction *action_bold;
    QAction *action_italic;
    QAction *action_underline;
    QAction *action_comment;
    QAction *action_strikethrough;
    QAction *action_indent;
    QAction *action_unindent;
    QAction *action_bulletedList;
    QAction *action_numberedList;
    QAction *action_taskList;
    QAction *action_Preferences;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTextEdit *textEdit;
    QWidget *tab_2;
    QCalendarWidget *calendarWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuFormat;
    QMenu *menuView;
    QMenu *menuSettings;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(936, 642);
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QString::fromUtf8("action_open"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QString::fromUtf8("actionTest"));
        action_save = new QAction(MainWindow);
        action_save->setObjectName(QString::fromUtf8("action_save"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QString::fromUtf8("action_about"));
        action_aboutQt = new QAction(MainWindow);
        action_aboutQt->setObjectName(QString::fromUtf8("action_aboutQt"));
        action_crashCourse = new QAction(MainWindow);
        action_crashCourse->setObjectName(QString::fromUtf8("action_crashCourse"));
        action_print = new QAction(MainWindow);
        action_print->setObjectName(QString::fromUtf8("action_print"));
        action_new = new QAction(MainWindow);
        action_new->setObjectName(QString::fromUtf8("action_new"));
        action_openRecent = new QAction(MainWindow);
        action_openRecent->setObjectName(QString::fromUtf8("action_openRecent"));
        action_saveAs = new QAction(MainWindow);
        action_saveAs->setObjectName(QString::fromUtf8("action_saveAs"));
        action_bold = new QAction(MainWindow);
        action_bold->setObjectName(QString::fromUtf8("action_bold"));
        action_italic = new QAction(MainWindow);
        action_italic->setObjectName(QString::fromUtf8("action_italic"));
        action_underline = new QAction(MainWindow);
        action_underline->setObjectName(QString::fromUtf8("action_underline"));
        action_comment = new QAction(MainWindow);
        action_comment->setObjectName(QString::fromUtf8("action_comment"));
        action_strikethrough = new QAction(MainWindow);
        action_strikethrough->setObjectName(QString::fromUtf8("action_strikethrough"));
        action_indent = new QAction(MainWindow);
        action_indent->setObjectName(QString::fromUtf8("action_indent"));
        action_unindent = new QAction(MainWindow);
        action_unindent->setObjectName(QString::fromUtf8("action_unindent"));
        action_bulletedList = new QAction(MainWindow);
        action_bulletedList->setObjectName(QString::fromUtf8("action_bulletedList"));
        action_numberedList = new QAction(MainWindow);
        action_numberedList->setObjectName(QString::fromUtf8("action_numberedList"));
        action_taskList = new QAction(MainWindow);
        action_taskList->setObjectName(QString::fromUtf8("action_taskList"));
        action_Preferences = new QAction(MainWindow);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 10, 831, 521));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 10, 831, 501));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        calendarWidget = new QCalendarWidget(tab_2);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(0, 0, 641, 331));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 936, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuFormat = new QMenu(menuBar);
        menuFormat->setObjectName(QString::fromUtf8("menuFormat"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuFormat->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(action_new);
        menuFile->addAction(action_open);
        menuFile->addAction(action_openRecent);
        menuFile->addSeparator();
        menuFile->addAction(action_save);
        menuFile->addAction(action_saveAs);
        menuFile->addSeparator();
        menuFile->addAction(action_print);
        menuEdit->addAction(actionTest);
        menuFormat->addAction(action_bold);
        menuFormat->addAction(action_italic);
        menuFormat->addAction(action_underline);
        menuFormat->addAction(action_strikethrough);
        menuFormat->addAction(action_comment);
        menuFormat->addSeparator();
        menuFormat->addAction(action_indent);
        menuFormat->addAction(action_unindent);
        menuFormat->addSeparator();
        menuFormat->addAction(action_bulletedList);
        menuFormat->addAction(action_numberedList);
        menuFormat->addAction(action_taskList);
        menuSettings->addAction(action_Preferences);
        menuHelp->addAction(action_crashCourse);
        menuHelp->addAction(action_about);
        menuHelp->addAction(action_aboutQt);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SprialBound", nullptr));
        action_open->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionTest->setText(QApplication::translate("MainWindow", "Test", nullptr));
        action_save->setText(QApplication::translate("MainWindow", "Save", nullptr));
        action_about->setText(QApplication::translate("MainWindow", "About", nullptr));
        action_aboutQt->setText(QApplication::translate("MainWindow", "About Qt", nullptr));
        action_crashCourse->setText(QApplication::translate("MainWindow", "Crash Course", nullptr));
        action_print->setText(QApplication::translate("MainWindow", "Print", nullptr));
        action_new->setText(QApplication::translate("MainWindow", "New", nullptr));
        action_openRecent->setText(QApplication::translate("MainWindow", "Open Recent", nullptr));
        action_saveAs->setText(QApplication::translate("MainWindow", "Save As", nullptr));
        action_bold->setText(QApplication::translate("MainWindow", "Bold", nullptr));
        action_italic->setText(QApplication::translate("MainWindow", "Italic", nullptr));
        action_underline->setText(QApplication::translate("MainWindow", "Underline", nullptr));
        action_comment->setText(QApplication::translate("MainWindow", "Comment", nullptr));
        action_strikethrough->setText(QApplication::translate("MainWindow", "Strikethrough", nullptr));
        action_indent->setText(QApplication::translate("MainWindow", "Indent", nullptr));
        action_unindent->setText(QApplication::translate("MainWindow", "Unindent", nullptr));
        action_bulletedList->setText(QApplication::translate("MainWindow", "Bulleted List", nullptr));
        action_numberedList->setText(QApplication::translate("MainWindow", "Numbered List", nullptr));
        action_taskList->setText(QApplication::translate("MainWindow", "Task List", nullptr));
        action_Preferences->setText(QApplication::translate("MainWindow", "Preferences", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "TextEditor", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Calendar", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        menuFormat->setTitle(QApplication::translate("MainWindow", "Format", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View", nullptr));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
