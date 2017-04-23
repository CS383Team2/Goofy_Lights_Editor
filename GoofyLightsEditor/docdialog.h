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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::docdialog *ui;
};

#endif // DOCDIALOG_H
