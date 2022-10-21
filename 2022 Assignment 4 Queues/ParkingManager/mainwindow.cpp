#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <thread>
#include <QFileDialog>
#include <QFile>

#define FRAME_RATE 60

void MainWindow::updateTime() {
    //    while (1) {
    time_t now = time(nullptr);
    ui->lineEditTimeNow->setText(ctime(&now));
    //        std::this_thread::sleep_for(std::chrono::seconds(1));
    //    }
}

void MainWindow::updateView() {
    //    while (1) {
    ui->labelInQueueCnt->setText(QString::number(inQueue.size()) + "/" + QString::number(m));
    if (inQueue.size() == m) {
        ui->labelInQueueCnt->setStyleSheet("color:red");
    } else {
        ui->labelInQueueCnt->setStyleSheet("color:black");
    }
    ui->lineEditInQueue->setText(inQueue.toString());

    ui->labelOutQueueCnt->setText(QString::number(outQueue.size()));
    ui->lineEditOutQueue->setText(outQueue.toString());

    //        if (outQueue.size() == m) {
    //            ui->labelOutQueueCnt->setStyleSheet("color:red");
    //        } else {
    //            ui->labelOutQueueCnt->setStyleSheet("color:black");
    //        }
    ui->lineEditEmptySlotsCnt->setText(QString::number(ui->graphicsViewCarPark->getEmptySlotsCnt()));
    //        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //    }
}

void MainWindow::out() {
    //    while (1) {
    //        qDebug() << "???";
    if (outQueue.size()) {
        //            qDebug() << "???";
        auto car = outQueue.pop();
        car->updateOutTime();
        //            qDebug() << "???";
        time_t timeIn = car->getTimeIn();
        time_t timeOut = car->getTimeOut();
        QString timeInStr = car->getCTimeIn();
        QString timeOutStr = car->getCTimeOut();
        //            qDebug() << timeIn << timeOut;
        //            qDebug() << timeInStr << timeOutStr;
        //            qDebug() << "???";
        ui->textEdit->setText(
                    ui->textEdit->toPlainText().prepend(
                        QString("Car ") + car->getLicense() + " out: \n" +
                        "\t" + "timeIn: "  + car->getCTimeIn() +
                        "\t" + "timeOut: " + car->getCTimeOut() +
                        "\t" + "total: " + QString::number(timeOut - timeIn) + "seconds" + "\n" +
                        "\t" + "cost: " + QString::number(car->cauculateCost()) + " Yuan" + "\n"
                        )
                    );
        //            qDebug() << "???";
        mark.erase(car->getLicense());
        delete car;
        //            qDebug() << "???";
    }
    if (inQueue.size() && ui->graphicsViewCarPark->getEmptySlotsCnt()) {
        auto car = inQueue.front();
        qDebug() << car -> getIndex();
        if (!ui->checkBoxAutoIndex->checkState() && !ui->graphicsViewCarPark->getSlot(car->getIndex())->isEmpty()) return;
        //            emit addCar(car);
        inQueue.pop();
        if (ui->checkBoxAutoIndex->checkState()) {
            ui->graphicsViewCarPark->addCar(car);
        } else {
            ui->graphicsViewCarPark->addCar(car, car->getIndex());
        }
        mark.insert(car->getLicense());
    }
    //        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    //    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    //    qDebug() << "???";
    if(event->timerId() == timer) {
        ui->graphicsViewCarPark->scene()->advance();
    } else if(event->timerId() == timerTime) {
        updateTime();
    } else if(event->timerId() == timerView) {
        updateView();
    } else if(event->timerId() == timerOut) {
        out();
    }
}

void MainWindow::removeCar(GraphicsItemCar* car) {
    outQueue.push(car);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), n(10), m(4)
{
    ui->setupUi(this);
    connect(ui->actionExport, &QAction::triggered, this, [=]() {
        QString filename = QFileDialog::getSaveFileName(this, " 导出 ", "./historyRecord.txt", "*.txt");

        QFile file(filename);//创建文件对象
        bool tag = file.open(QIODevice::WriteOnly);//写内容到文件中

        if(!tag) return;

        QString text = ui->textEdit->toPlainText();//文本框中的内容
        file.write(text.toUtf8());//将text内容转化为字节数组

        file.close();
    });
    connect(ui->spinBoxTotalSize, &QSpinBox::valueChanged, this, [=](int x) {
        n = x; ui->graphicsViewCarPark->init(n, m);
        inQueue.clear();
        outQueue.clear();
        ui->textEdit->clear();
    });
    connect(ui->spinBoxQueueSize, &QSpinBox::valueChanged, this, [=](int x) {
        m = x; ui->graphicsViewCarPark->init(n, m);
        inQueue.clear();
        outQueue.clear();
        ui->textEdit->clear();
    });
    connect(ui->pushButtonAdd, &QPushButton::pressed, this, [=](){
        if (!ui->checkBoxAutoIndex->checkState() && (ui->lineEditIndex->text().toInt() > n || ui->lineEditIndex->text().toInt() < 1)) return;

        if (inQueue.size() == m) return;
        QString license = ui->checkBoxRandom->checkState() ?
                    QString::number(rand()) : ui->lineEditLicense->text().length() ? ui->lineEditLicense->text() : "EMPTY";
        ui->lineEditLicense->setText(license);
        if (mark.count(license)) {
            ui->textEdit->setText(
                        ui->textEdit->toPlainText().prepend("ERROR:License existed!\n")
                        );
            return;
        }

        auto car = new GraphicsItemCar(license, ui->lineEditIndex->text().length() ? ui->lineEditIndex->text().toInt() : 1);

        if (!ui->graphicsViewCarPark->getEmptySlotsCnt() ||
                !ui->checkBoxAutoIndex->checkState() && !ui->graphicsViewCarPark->getSlot(car->getIndex())->isEmpty()) {
            inQueue.push(car);
            mark.insert(car->getLicense());
        } else {
            if (ui->checkBoxAutoIndex->checkState())
                ui->graphicsViewCarPark->addCar(car);
            else {
                ui->graphicsViewCarPark->addCar(car, ui->lineEditIndex->text().toInt());
            }
            mark.insert(car->getLicense());
        }
    });
    connect(ui->graphicsViewCarPark, &GraphicsViewCarPark::outCar, this, [=](GraphicsItemCar* car) {
        outQueue.push(car);
    });
    connect(ui->checkBoxRandom, &QCheckBox::stateChanged, this, [=](int x) {
        if (x) {
            ui->lineEditLicense->setEnabled(false);
        } else {
            ui->lineEditLicense->setEnabled(true);
        }
    });
    connect(ui->checkBoxAutoIndex, &QCheckBox::stateChanged, this, [=](int x) {
        if (x) {
            ui->lineEditIndex->setEnabled(false);
        } else {
            ui->lineEditIndex->setEnabled(true);
        }
    });

    timer = startTimer(1000 / FRAME_RATE);
    timerTime = startTimer(1000);
    timerView = startTimer(500);
    timerOut = startTimer(1000);


    //    QTimer* timer = new QTimer();
    //    QObject::connect(timer, &QTimer::timeout, ui->graphicsViewCarPark->scene(), &QGraphicsScene::advance);
    //    timer->start(1000 / FRAME_RATE);

    //    QTimer* timeUpdater = new QTimer();
    //    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    //    timer->start(1000);

    //    QTimer* timeOut = new QTimer();
    //    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::out);
    //    timer->start(1000);
    //    QThread* threadTime = QThread::create(&MainWindow::updateTime, this);
    //    threadTime->start();
    //    QThread* threadView = QThread::create(&MainWindow::updateView, this);
    //    threadView->start();
    //    QThread* threadOutQueue = QThread::create(&MainWindow::out, this);
    //    threadOutQueue->start();
    //    std::thread threadTime(&MainWindow::updateTime, this);
    //    threadTime.detach();
    //    std::thread threadView(&MainWindow::updateView, this);
    //    threadView.detach();
    //    std::thread threadOutQueue(&MainWindow::out, this);
    //    threadOutQueue.detach();
}

MainWindow::~MainWindow()
{
    delete ui;
}
