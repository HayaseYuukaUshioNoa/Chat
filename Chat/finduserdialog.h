#ifndef FINDUSERDIALOG_H
#define FINDUSERDIALOG_H

#include <QDialog>
#include <global.h>

namespace Ui {
class FindUserDialog;
}

class FindUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindUserDialog(QWidget *parent = nullptr);
    ~FindUserDialog();
    ServerInfo info;
signals:
    void sig_show_adduser_dialog(const QString& username, const QString& email);
private slots:
    void on_pushButton_clicked();
    void slot_show_adduser_dialog(const QString& username, const QString& email);
private:
    Ui::FindUserDialog *ui;
};

#endif // FINDUSERDIALOG_H
