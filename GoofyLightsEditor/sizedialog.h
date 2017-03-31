#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>

namespace Ui {
class SizeDialog;
}

class SizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SizeDialog(QWidget *parent = 0);
    ~SizeDialog();

private slots:
    void on_spinBox_editingFinished();

    void on_spinBox_2_editingFinished();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SizeDialog *ui;
};

#endif // SIZEDIALOG_H
