#ifndef HTTPMGR_H
#define HTTPMGR_H

#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

// CRTP
class HttpMgr : public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT

public:
    // 析构公有，因为父类析构会析构智能指针进而析构这个所以需要公有
    ~HttpMgr();
    // 现在的qt使用异步，所以我们需要req_id和mod来知道回调的时候是哪个模块。
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private:
    // 父类需要能够new构造
    friend class Singleton<HttpMgr>;
    // 构造子类时会调用父类的构造，所以单例类构造设置为保护。
    HttpMgr();
    QNetworkAccessManager _manager;

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
