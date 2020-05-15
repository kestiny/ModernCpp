#pragma once
#include <qtgui/QDoubleValidator>

class DoubleValidator : public QDoubleValidator
{
    Q_OBJECT
public:
    DoubleValidator(QObject *parent = nullptr);
    DoubleValidator(double bottom, double top, int decimals, QObject *parent = nullptr);
    ~DoubleValidator();

protected:
    virtual QValidator::State validate(QString &input, int &pos) const;
};
