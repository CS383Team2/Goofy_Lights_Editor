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

    void on_btnBox_OkClose_accepted();

    void on_btnBox_OkClose_rejected();

    void on_btn_Browse_clicked();

private:
    Ui::SizeDialog *ui;
};

#endif // SIZEDIALOG_H
