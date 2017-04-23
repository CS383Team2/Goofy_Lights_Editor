#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
class helpdialog;
}

class helpdialog : public QDialog
{
    Q_OBJECT

public:
    explicit helpdialog(QWidget *parent = 0);
    ~helpdialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::helpdialog *ui;
};

#endif // HELPDIALOG_H
