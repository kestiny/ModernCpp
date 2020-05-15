#pragma once

#include "ui_QDemo.h"
#include "DialogBase.h"

class QDemo : public DialogBase
{
    Q_OBJECT
public:
    QDemo(QWidget *parent = Q_NULLPTR);

private:
    Ui::Dialog ui;
};
