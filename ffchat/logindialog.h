#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"

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
    // 登陆界面图标
    void initHead();
    // 初始化收到http回包操作
    void initHttpHandlers();

    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    void showTip(QString str,bool b_ok);

    bool checkUserValid();
    bool checkPwdValid();

    bool enableBtn(bool);

    Ui::LoginDialog *ui;
    QMap<TipErr, QString> _tip_errs;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;

    int _uid;
    QString _token;
signals:
    void switchRegister();
    void switchReset();
    // 收到http回包后发给tcp管理者
    void sig_connect_tcp(ServerInfo);
private slots:
    void slot_forget_pwd();
    void on_login_btn_clicked();
    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // LOGINDIALOG_H
