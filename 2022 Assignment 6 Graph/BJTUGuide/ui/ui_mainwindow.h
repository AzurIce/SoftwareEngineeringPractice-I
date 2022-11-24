/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QPushButton *btnCancelEnd;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QPushButton *btnCancelStart;
    QPushButton *btnSetStart;
    QPushButton *btnSetEnd;
    QPushButton *btnShowShortestPath1;
    QQuickWidget *quickWidget;
    QPushButton *btnShowShortestPath2;
    QSlider *slider;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1164, 704);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setStyleSheet(QString::fromUtf8("QGraphicsView {\n"
"	border: none;\n"
"	border-radius: 20px;\n"
"	padding: 10px;\n"
"	background-color: #ffffff;\n"
"}"));

        gridLayout->addWidget(graphicsView, 0, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        btnCancelEnd = new QPushButton(centralwidget);
        btnCancelEnd->setObjectName("btnCancelEnd");

        gridLayout_3->addWidget(btnCancelEnd, 3, 3, 1, 1);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	border: none;\n"
"	border-radius: 4px;\n"
"	padding: 2px;\n"
"	background-color: #ffffff;\n"
"}"));
        lineEdit->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit, 1, 2, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label, 3, 0, 1, 1);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        sizePolicy2.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy2);
        lineEdit_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	border: none;\n"
"	border-radius: 4px;\n"
"	padding: 2px;\n"
"	background-color: #ffffff;\n"
"}"));
        lineEdit_2->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_2, 3, 2, 1, 1);

        btnCancelStart = new QPushButton(centralwidget);
        btnCancelStart->setObjectName("btnCancelStart");

        gridLayout_3->addWidget(btnCancelStart, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        btnSetStart = new QPushButton(centralwidget);
        btnSetStart->setObjectName("btnSetStart");
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnSetStart->sizePolicy().hasHeightForWidth());
        btnSetStart->setSizePolicy(sizePolicy3);
        btnSetStart->setMinimumSize(QSize(0, 40));
        btnSetStart->setMaximumSize(QSize(300, 16777215));
        btnSetStart->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btnSetStart);

        btnSetEnd = new QPushButton(centralwidget);
        btnSetEnd->setObjectName("btnSetEnd");
        sizePolicy3.setHeightForWidth(btnSetEnd->sizePolicy().hasHeightForWidth());
        btnSetEnd->setSizePolicy(sizePolicy3);
        btnSetEnd->setMinimumSize(QSize(0, 40));
        btnSetEnd->setMaximumSize(QSize(300, 16777215));
        btnSetEnd->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btnSetEnd);

        btnShowShortestPath1 = new QPushButton(centralwidget);
        btnShowShortestPath1->setObjectName("btnShowShortestPath1");
        sizePolicy3.setHeightForWidth(btnShowShortestPath1->sizePolicy().hasHeightForWidth());
        btnShowShortestPath1->setSizePolicy(sizePolicy3);
        btnShowShortestPath1->setMinimumSize(QSize(0, 40));
        btnShowShortestPath1->setMaximumSize(QSize(300, 16777215));
        btnShowShortestPath1->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btnShowShortestPath1);

        quickWidget = new QQuickWidget(centralwidget);
        quickWidget->setObjectName("quickWidget");
        quickWidget->setStyleSheet(QString::fromUtf8(""));
        quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

        verticalLayout->addWidget(quickWidget);

        btnShowShortestPath2 = new QPushButton(centralwidget);
        btnShowShortestPath2->setObjectName("btnShowShortestPath2");
        sizePolicy3.setHeightForWidth(btnShowShortestPath2->sizePolicy().hasHeightForWidth());
        btnShowShortestPath2->setSizePolicy(sizePolicy3);
        btnShowShortestPath2->setMinimumSize(QSize(0, 40));
        btnShowShortestPath2->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btnShowShortestPath2);


        gridLayout->addLayout(verticalLayout, 0, 9, 2, 1);

        slider = new QSlider(centralwidget);
        slider->setObjectName("slider");
        slider->setMinimum(77);
        slider->setMaximum(200);
        slider->setSingleStep(5);
        slider->setPageStep(5);
        slider->setValue(100);
        slider->setOrientation(Qt::Vertical);
        slider->setInvertedAppearance(false);

        gridLayout->addWidget(slider, 0, 4, 2, 1);

        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setMaximumSize(QSize(16777215, 100));
        plainTextEdit->setStyleSheet(QString::fromUtf8("QPlainTextEdit {\n"
"	border: none;\n"
"	border-radius: 20px;\n"
"	padding: 10px;\n"
"	background-color: #ffffff;\n"
"}"));
        plainTextEdit->setReadOnly(true);

        gridLayout->addWidget(plainTextEdit, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1164, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\350\265\267\347\202\271", nullptr));
        btnCancelEnd->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\273\210\347\202\271", nullptr));
        btnCancelStart->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210", nullptr));
        btnSetStart->setText(QCoreApplication::translate("MainWindow", "\350\256\276\344\270\272\350\265\267\347\202\271", nullptr));
        btnSetEnd->setText(QCoreApplication::translate("MainWindow", "\350\256\276\344\270\272\347\273\210\347\202\271", nullptr));
        btnShowShortestPath1->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\350\265\267\347\202\271\345\210\260\347\273\210\347\202\271\347\232\204\346\234\200\347\237\255\350\267\257\345\276\204", nullptr));
        btnShowShortestPath2->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\270\270\351\201\215\351\200\211\345\256\232\346\231\257\347\202\271\347\232\204\346\234\200\347\237\255\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
