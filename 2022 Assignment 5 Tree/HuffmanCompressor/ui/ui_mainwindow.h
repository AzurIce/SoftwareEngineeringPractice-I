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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
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
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddFile;
    QPushButton *btnAddDir;
    QPushButton *btnSelectAll;
    QPushButton *btnSelectNone;
    QPushButton *btnDeleteSelected;
    QPushButton *btnDeleteAll;
    QTextEdit *logTextEdit;
    FileTreeView *treeViewContent;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnSaveAs;
    QPushButton *btnExtractAllTo;
    QPushButton *btnExtractSelectedTo;
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
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar{\n"
"                                height:22px;\n"
"                                text-align:center;\n"
"                                font-size:14px;\n"
"                                color:black;\n"
"                                border-radius:11px;\n"
"                                background:#ffffff;\n"
"                                }\n"
"                                QProgressBar::chunk{\n"
"                                border-radius:11px;\n"
"                                background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #99ffff,stop:1\n"
"                                #9900ff);\n"
"                                }\n"
"                            "));
        progressBar->setValue(10);

        gridLayout->addWidget(progressBar, 8, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        btnAddFile = new QPushButton(centralwidget);
        btnAddFile->setObjectName(QString::fromUtf8("btnAddFile"));
        btnAddFile->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(btnAddFile);

        btnAddDir = new QPushButton(centralwidget);
        btnAddDir->setObjectName(QString::fromUtf8("btnAddDir"));

        horizontalLayout->addWidget(btnAddDir);

        btnSelectAll = new QPushButton(centralwidget);
        btnSelectAll->setObjectName(QString::fromUtf8("btnSelectAll"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnSelectAll->sizePolicy().hasHeightForWidth());
        btnSelectAll->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(btnSelectAll);

        btnSelectNone = new QPushButton(centralwidget);
        btnSelectNone->setObjectName(QString::fromUtf8("btnSelectNone"));

        horizontalLayout->addWidget(btnSelectNone);

        btnDeleteSelected = new QPushButton(centralwidget);
        btnDeleteSelected->setObjectName(QString::fromUtf8("btnDeleteSelected"));

        horizontalLayout->addWidget(btnDeleteSelected);

        btnDeleteAll = new QPushButton(centralwidget);
        btnDeleteAll->setObjectName(QString::fromUtf8("btnDeleteAll"));

        horizontalLayout->addWidget(btnDeleteAll);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        logTextEdit = new QTextEdit(centralwidget);
        logTextEdit->setObjectName(QString::fromUtf8("logTextEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logTextEdit->sizePolicy().hasHeightForWidth());
        logTextEdit->setSizePolicy(sizePolicy1);
        logTextEdit->setMaximumSize(QSize(16777215, 16777215));
        logTextEdit->setLayoutDirection(Qt::LeftToRight);
        logTextEdit->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"                                border: none;\n"
"                                border-radius: 20px;\n"
"                                padding: 10px;\n"
"                                background-color: #ffffff;\n"
"                                }\n"
"                            "));
        logTextEdit->setReadOnly(true);

        gridLayout->addWidget(logTextEdit, 9, 0, 1, 1);

        treeViewContent = new FileTreeView(centralwidget);
        treeViewContent->setObjectName(QString::fromUtf8("treeViewContent"));
        treeViewContent->setStyleSheet(QString::fromUtf8("QTreeView{\n"
"                                border: none;\n"
"                                border-radius: 20px;\n"
"                                padding: 10px;\n"
"                                background-color: #ffffff;\n"
"                                }\n"
"\n"
"                                QHeaderView::section{\n"
"                                background-color: #ffffff;\n"
"                                border: none;\n"
"                                border-bottom: 1px solid #cccccc;\n"
"                                }\n"
"                            "));
        treeViewContent->setSelectionMode(QAbstractItemView::MultiSelection);
        treeViewContent->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeViewContent->setSortingEnabled(false);
        treeViewContent->setAnimated(false);

        gridLayout->addWidget(treeViewContent, 7, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        btnSaveAs = new QPushButton(centralwidget);
        btnSaveAs->setObjectName(QString::fromUtf8("btnSaveAs"));

        horizontalLayout_3->addWidget(btnSaveAs);

        btnExtractAllTo = new QPushButton(centralwidget);
        btnExtractAllTo->setObjectName(QString::fromUtf8("btnExtractAllTo"));

        horizontalLayout_3->addWidget(btnExtractAllTo);

        btnExtractSelectedTo = new QPushButton(centralwidget);
        btnExtractSelectedTo->setObjectName(QString::fromUtf8("btnExtractSelectedTo"));

        horizontalLayout_3->addWidget(btnExtractSelectedTo);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

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
        actionCompress_to->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
        actionDecompress_to->setText(QCoreApplication::translate("MainWindow", "\350\247\243\345\216\213\345\210\260", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        btnAddFile->setText(QCoreApplication::translate("MainWindow", "\342\236\225\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
        btnAddDir->setText(QCoreApplication::translate("MainWindow", "\342\236\225\346\267\273\345\212\240\347\233\256\345\275\225", nullptr));
        btnSelectAll->setText(QCoreApplication::translate("MainWindow", "\342\234\205\345\205\250\351\200\211", nullptr));
        btnSelectNone->setText(QCoreApplication::translate("MainWindow", "\342\255\225\346\270\205\351\231\244\351\200\211\346\213\251", nullptr));
        btnDeleteSelected->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217\345\210\240\351\231\244\351\200\211\344\270\255\346\226\207\344\273\266", nullptr));
        btnDeleteAll->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217\345\210\240\351\231\244\346\211\200\346\234\211\346\226\207\344\273\266", nullptr));
        btnSaveAs->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276\345\217\246\345\255\230\344\270\272...", nullptr));
        btnExtractAllTo->setText(QCoreApplication::translate("MainWindow", "\360\237\223\232\350\247\243\345\216\213\346\211\200\346\234\211\346\226\207\344\273\266\345\210\260...", nullptr));
        btnExtractSelectedTo->setText(QCoreApplication::translate("MainWindow", "\360\237\223\232\350\247\243\345\216\213\351\200\211\344\270\255\346\226\207\344\273\266\345\210\260...", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
