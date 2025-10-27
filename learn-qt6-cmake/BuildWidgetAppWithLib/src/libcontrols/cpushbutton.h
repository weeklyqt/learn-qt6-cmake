#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include <QPushButton>

class CPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CPushButton(QWidget *parent = nullptr);

signals:
};

#endif // CPUSHBUTTON_H
