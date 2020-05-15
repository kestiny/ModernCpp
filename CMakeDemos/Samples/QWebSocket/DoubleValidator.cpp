#include "DoubleValidator.h"

DoubleValidator::DoubleValidator(QObject *parent /*= nullptr*/)
    : QDoubleValidator(parent)
{

}

DoubleValidator::DoubleValidator(double bottom, double top, int decimals, QObject *parent /*= nullptr*/)
    : QDoubleValidator(bottom, top, decimals, parent)
{

}

DoubleValidator::~DoubleValidator()
{

}

QValidator::State DoubleValidator::validate(QString &input, int &pos) const
{
    if (input.isEmpty())
    {
        return QValidator::Intermediate;
    }
    bool ok = false;
    double val = input.toDouble(&ok);

    if (!ok)
    {
        return QValidator::Invalid;
    }

    int dotPos = input.indexOf(".");
    if (dotPos > 0)
    {
        if (input.right(input.length() - dotPos - 1).length() > decimals())
        {
            return QValidator::Invalid;
        }
    }
    if (val < bottom() || val > top())
        return QValidator::Invalid;
    return QValidator::Acceptable;
}
