#include <QFileDialog>
#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "libs/HuffmanCompress.h"
#include "utils/Utils.h"
#include <QProgressDialog>

void MainWindow::timerEvent(QTimerEvent *event) {
    if(event->timerId() == timer) {
        if (compress != nullptr) {
            if (compress->state == HuffmanCompress::COMPRESSING) {
//                progress->setLabelText("正在保存");
//                progress->setValue(compress->getCurrent());
//                progress->setMaximum(compress->getTotal());
                ui->actionCompress_to->setDisabled(true);
                ui->actionDecompress_to->setDisabled(false);
            } else if (compress->state == HuffmanCompress::DECOMPRESSING) {
//                progress->setLabelText("正在打开");
//                progress->setValue(compress->getCurrent());
//                progress->setMaximum(compress->getTotal());
                ui->actionCompress_to->setDisabled(false);
                ui->actionDecompress_to->setDisabled(true);
            } else {
//                progress->setValue(progress->maximum());
                ui->actionCompress_to->setDisabled(false);
                ui->actionDecompress_to->setDisabled(false);
            }
            ui->progressBar->setMaximum(compress->getTotal());
            ui->progressBar->setValue(compress->getCurrent());
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), compress(nullptr) {
    ui->setupUi(this);
    model = new FileTreeItemModel();
//    progress = new QProgressDialog(this);
//    progress->setWindowModality(Qt::WindowModal);
//    progress->close();

    ui->treeViewContent->setModel(model);

    connect(ui->actionNew, &QAction::triggered, this, [=]() {
        delete compress;
        compress = nullptr;
        model = new FileTreeItemModel();
        ui->treeViewContent->setModel(model);
    });

    connect(ui->actionCompress_to, &QAction::triggered, this, [=]() {
        QString filename = QFileDialog::getSaveFileName(this, " 保存 ", "./archive.huffmanzip", "*.huffmanzip");
        if (filename == nullptr) return;

//        progress->setLabelText("正在打开");
//        progress->setWindowModality(Qt::WindowModal);
//        progress->setValue(0);
//        progress.show();
        delete compress;
        compress = new HuffmanCompress(model->getRootItem()->toBytes());
        ui->progressBar->setMaximum(compress->getOriginalSize());
        Utils::saveBytes(compress->toBytes(), filename);
    });

    connect(ui->actionOpen, &QAction::triggered, this, [=]() {
        QString filename = QFileDialog::getOpenFileName(this, " 打开 ", "./", "*.huffmanzip");
        if (filename == nullptr) return;

        QByteArray bytes = Utils::readBytes(filename);

//        progress->setLabelText("正在打开");
//        progress->setWindowModality(Qt::WindowModal);
//        progress->setValue(0);
//        progress.show();
        delete compress;
        compress = HuffmanCompress::fromBytes(&bytes);
        ui->progressBar->setMaximum(compress->getOriginalSize());
        qDebug() << "decoded";

        QByteArray originalBytes = compress->getOriginalBytes();
        FileTreeItem *item = FileTreeItem::fromBytes(&originalBytes);

        QFileInfo file(filename);
        item->setFileName(file.fileName());
        model = new FileTreeItemModel(item);
        ui->treeViewContent->setModel(model);
    });

    connect(ui->actionDecompress_to, &QAction::triggered, this, [=]() {
        QString dir = QFileDialog::getExistingDirectory(this, " 解压到 ", "./",
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        FileTreeItem *item = model->getRootItem();

        item->save(dir);
    });

    timer = startTimer(200);

}

MainWindow::~MainWindow() {
    delete ui;
    delete model;
    delete compress;
}

