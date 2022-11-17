#include <QFileDialog>
#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "libs/HuffmanCompress.h"
#include "utils/Utils.h"
#include "utils/BytesReader.h"
#include <QProgressDialog>

void MainWindow::timerEvent(QTimerEvent *event) {
    if (event->timerId() == progressTimer) {
        ui->progressBar->setValue(current);
        ui->progressBar->setMaximum(total);
    }
}

void MainWindow::open(const QString &path) {
    logln("正在读取文件...");
    delete reader;
    reader = new BytesReader(path, current, total);
    auto bytes = reader->read();

    logln("正在解码...");
    delete compress;
    compress = HuffmanCompress::fromBytes(&bytes, current, total);
    QByteArray originalBytes = compress->getOriginalBytes();

    logln("正在加载...");
    FileTreeItem *item = FileTreeItem::fromBytes(&originalBytes);

    QFileInfo file(path);
    item->setFileName(file.fileName());
    model = new FileTreeItemModel(item);
    ui->treeViewContent->setModel(model);
    logln("加载完成");
}

void MainWindow::save(const QString &path) {
    logln("正在压缩...");
    current = 0;
    delete compress;
    compress = new HuffmanCompress(model->getRootItem()->toBytes(), current, total);
//        Utils::saveBytes(compress->toBytes(), filename);
    int &&originalSize = compress->getOriginalBytes().size();
    int &&compressedSize = compress->getCompressedBytes().size();
    logln("原大小：" + QString::number(originalSize) + "Bytes");
    logln("压缩后大小：" + QString::number(compressedSize) + "Bytes");
    logln("减小了：" + QString::number((1.0 - (double) compressedSize / originalSize) * 100) + "%");

    logln("正在保存文件...");
    delete saver;
    saver = new BytesSaver(compress->toBytes(), path, current, total);
    saver->save();
    logln("文件保存完成");
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->treeViewContent->setModel(model = new FileTreeItemModel());

    connect(ui->actionNew, &QAction::triggered, this, [=]() {
        current = 0;
        ui->treeViewContent->setModel(model = new FileTreeItemModel());
    });

    connect(ui->actionCompress_to, &QAction::triggered, this, [=]() {
        QString filename = QFileDialog::getSaveFileName(this, " 保存 ", "./archive.huffmanzip", "*.huffmanzip");
        if (filename == nullptr) return;
        logln(QString("正在保存到 ") + filename + "...");

        QThread *t = QThread::create(&MainWindow::save, this, filename);
        t->start();
    });

    connect(ui->actionOpen, &QAction::triggered, this, [=]() {
        QString filename = QFileDialog::getOpenFileName(this, " 打开 ", "./", "*.huffmanzip");
        if (filename == nullptr) return;
        logln(QString("正在打开 ") + filename + "...");

        QThread *t = QThread::create(&MainWindow::open, this, filename);
        t->start();
    });

    connect(ui->actionDecompress_to, &QAction::triggered, this, [=]() {
        QString dir = QFileDialog::getExistingDirectory(this, " 解压到 ", "./",
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        logln(QString("正在解压到 ") + dir + "...");

        model->getRootItem()->save(dir);
    });

    progressTimer = startTimer(50);
}

MainWindow::~MainWindow() {
    delete ui;
    delete model;
    delete compress;
}

void MainWindow::loadHuffmanZip(const QString &path) {
    QThread *t = QThread::create(&MainWindow::open, this, path);
    t->start();
}

void MainWindow::log(const QString &str) {
    ui->logTextEdit->append(str);
}

void MainWindow::logln(const QString &str) {
    log(str);
}
