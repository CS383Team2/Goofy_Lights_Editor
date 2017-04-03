#ifndef DOCDIALOG_H
#define DOCDIALOG_H

#include <QDialog>

namespace Ui {
class docdialog;
}

class docdialog : public QDialog
{
    Q_OBJECT

public:
    explicit docdialog(QWidget *parent = 0);
    ~docdialog();

private:
    Ui::docdialog *ui;
};

#endif // DOCDIALOG_H
