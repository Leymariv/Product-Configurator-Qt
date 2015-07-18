#ifndef SAISICODE_H
#define SAISICODE_H

#include <QWidget>

namespace Ui {
class SaisiCode;
}

class SaisiCode : public QWidget
{
    Q_OBJECT

public:
    explicit SaisiCode(QWidget *parent = 0);
    ~SaisiCode();

private:
    Ui::SaisiCode *ui;
};

#endif // SAISICODE_H
