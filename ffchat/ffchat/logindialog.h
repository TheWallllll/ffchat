/******************************************************************************
 *
 * @file       logindialog.h
 * @brief      主窗口
 *
 * @author     TheWall
 * @date       2024/09/10
 * @history
 *****************************************************************************/
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

signals:
    void switchRegister();
};

#endif // LOGINDIALOG_H
