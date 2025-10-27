#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionChinese, &QAction::triggered, this, [this](){
        if (translator.load("BuildWidgetAppWithTranslations_zh_CN.qm")) {
            qDebug() << "Change language to Chinese.";
            QCoreApplication::removeTranslator(&translator);
            QCoreApplication::installTranslator(&translator);
        }
    });

    connect(ui->actionEnglish, &QAction::triggered, this, [this](){
        if (translator.load("BuildWidgetAppWithTranslations_en.qm")) {
            qDebug() << "Change language to English.";
            QCoreApplication::removeTranslator(&translator);
            QCoreApplication::installTranslator(&translator);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        qDebug() << "QEvent::LanguageChange.";
    } else
        QWidget::changeEvent(event);
}
