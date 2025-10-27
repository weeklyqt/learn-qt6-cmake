#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cpushbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto button = new CPushButton(this);
    button->setText("CPushButton");
    button->setObjectName("cpushButton");

    QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(button->sizePolicy().hasHeightForWidth());
    button->setSizePolicy(sizePolicy);

    ui->verticalLayout->addWidget(button, 0, Qt::AlignmentFlag::AlignHCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}
