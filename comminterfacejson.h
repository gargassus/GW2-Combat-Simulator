#ifndef COMMINTERFACEJSON_H
#define COMMINTERFACEJSON_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QVector>
#include <QObject>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "mainwindow.h"

// eri komennot enumissa
enum ApiFunction {
    GW_GET_ACCOUNT
};

class CommInterfaceJson : public QObject {
    Q_OBJECT
public:
    // oletusrakentaja
    CommInterfaceJson(MainWindow *mainwindow);
    // oletuspurkaja
    ~CommInterfaceJson();

    void getAccount();

public slots:
    // callback vastaukselle
    void dataReceived(QNetworkReply *reply);

private:
    int setRequestHeaders(QNetworkRequest *req );

    // verkkomanageri
    QNetworkAccessManager *mNetworkManager;

    // odottavat responset
    struct ResponseData {
        QNetworkReply *response;
        ApiFunction function;
    };
    QVector< ResponseData > mReplyVector;

    MainWindow *mMainwindow;
    // end-point urlit
    QUrl mApiUrl;
};

#endif // COMMINTERFACEJSON_H
