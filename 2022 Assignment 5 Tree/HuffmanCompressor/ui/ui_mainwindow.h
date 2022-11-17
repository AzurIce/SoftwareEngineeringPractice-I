/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <views/FileTreeView.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionCompress_to;
    QAction *actionDecompress_to;
    QAction *actionNew;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    FileTreeView *treeViewContent;
    QTextEdit *logTextEdit;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionCompress_to = new QAction(MainWindow);
        actionCompress_to->setObjectName(QString::fromUtf8("actionCompress_to"));
        actionDecompress_to = new QAction(MainWindow);
        actionDecompress_to->setObjectName(QString::fromUtf8("actionDecompress_to"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeViewContent = new FileTreeView(centralwidget);
        treeViewContent->setObjectName(QString::fromUtf8("treeViewContent"));
        treeViewContent->setStyleSheet(QString::fromUtf8("QTreeView{\n"
"	border: none;\n"
"	border-radius: 20px;\n"
"	padding: 10px;\n"
"	background-color: #ffffff;\n"
"}\n"
"\n"
"QHeaderView::section{\n"
"	background-color: #ffffff;\n"
"	border: none;\n"
"	border-bottom: 1px solid #cccccc;\n"
"}"));
        treeViewContent->setSortingEnabled(false);
        treeViewContent->setAnimated(false);

        gridLayout->addWidget(treeViewContent, 0, 0, 1, 1);

        logTextEdit = new QTextEdit(centralwidget);
        logTextEdit->setObjectName(QString::fromUtf8("logTextEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logTextEdit->sizePolicy().hasHeightForWidth());
        logTextEdit->setSizePolicy(sizePolicy);
        logTextEdit->setMaximumSize(QSize(16777215, 16777215));
        logTextEdit->setLayoutDirection(Qt::LeftToRight);
        logTextEdit->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"	border: none;\n"
"	border-radius: 20px;\n"
"	padding: 10px;\n"
"	background-color: #ffffff;\n"
"}"));
        logTextEdit->setReadOnly(true);

        gridLayout->addWidget(logTextEdit, 2, 0, 1, 1);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar{\n"
"	height:22px;\n"
"	text-align:center;\n"
"	font-size:14px;\n"
"	color:black;\n"
"	border-radius:11px;\n"
"	background:#ffffff;\n"
"}\n"
"QProgressBar::chunk{\n"
"	border-radius:11px;\n"
"	background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #99ffff,stop:1 #9900ff);\n"
"}"));
        progressBar->setValue(10);

        gridLayout->addWidget(progressBar, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionNew);
        menu->addAction(actionCompress_to);
        menu->addAction(actionDecompress_to);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        actionCompress_to->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        actionDecompress_to->setText(QCoreApplication::translate("MainWindow", "\350\247\243\345\216\213\345\210\260", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
