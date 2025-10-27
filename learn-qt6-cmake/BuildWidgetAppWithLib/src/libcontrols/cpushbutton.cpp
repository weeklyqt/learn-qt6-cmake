#include "cpushbutton.h"

CPushButton::CPushButton(QWidget *parent)
    : QPushButton{parent}
{
    this->setStyleSheet(R"(
        QPushButton {
            background-color: #1b60e7;
            border-radius: 6px;
            color: white;
            padding: 6px;
            font-size: 14px;
            border-style: solid;
            border-width: 2px;
            border-color: #0541b2;
        }
        QPushButton:hover {
            background-color: #366ef4;
        }
        QPushButton:pressed {
            background-color: #0541b2;
        }
    )");
}
