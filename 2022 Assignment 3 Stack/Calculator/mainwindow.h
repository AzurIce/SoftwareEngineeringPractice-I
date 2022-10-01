#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "expression.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_leInput_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Expression expr;

    void handleInput(char c);
    void handleInput(Expression::Func f);
    void refreshInputDisp();
    void refreshResultDisp();
    void updateHistoryDisp();
    void refreshMidResultDisp();
    void refreshDebugDisp();
};
#endif // MAINWINDOW_H
