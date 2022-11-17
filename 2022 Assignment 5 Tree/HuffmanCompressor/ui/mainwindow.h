#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "models/FileTreeItemModel.h"
#include "libs/HuffmanCompress.h"
#include "utils/BytesSaver.h"
#include "utils/BytesReader.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void loadHuffmanZip(const QString &path);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    std::atomic<int> current;
    std::atomic<int> total;

    Ui::MainWindow *ui;
    FileTreeItemModel *model;
    HuffmanCompress *compress = nullptr;
    BytesSaver *saver = nullptr;
    BytesReader *reader = nullptr;

    void log(const QString &str);

    void logln(const QString &str);

    void save(const QString &path);
    void saveAndOpen(FileTreeItem *item);

    void open(const QString &path);

//    QProgressDialog *progress;

    int progressTimer;
};

#endif // MAINWINDOW_H
