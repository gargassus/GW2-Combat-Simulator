#include "comminterfacejson.h"
#include "mainwindow.h"

#include <QDebug>
#include <QtNetwork/QNetworkRequest>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

// oletusrakentaja
CommInterfaceJson::CommInterfaceJson( MainWindow *mainwindow ) : QObject(), mNetworkManager( 0 ),
      mApiUrl( "https://api.guildwars2.com/v2" )
{

    mMainwindow = mainwindow;
    // luodaan manageri ja yhdistetään sen signaalit
    mNetworkManager = new QNetworkAccessManager( this );
    connect( mNetworkManager, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( dataReceived( QNetworkReply* ) ) );

    // tyhjennetään response vektori
    mReplyVector.clear();
}

// oletuspurkaja
CommInterfaceJson::~CommInterfaceJson() {}


void CommInterfaceJson::getAccount()
{
    // muodostetaan request
    const QString urlString = mApiUrl.toString() + "/account";
    QNetworkRequest request( QUrl::fromUserInput( urlString ) );
    setRequestHeaders( &request );

    // odotetaan vastausta
    ResponseData rData;
    rData.response = mNetworkManager->get(request);
    rData.function = GW_GET_ACCOUNT;
    mReplyVector.push_back( rData );
}

// callback vastaukselle
void CommInterfaceJson::dataReceived( QNetworkReply *reply ) {

    // etsitään oikea paketti
    ResponseData rData;
    for (int i = 0; i < mReplyVector.size(); ++i)
    {
        if (mReplyVector.at( i ).response == reply)
        {
            rData = mReplyVector.at(i);
            mReplyVector.erase(mReplyVector.begin() + i);
            break;
        }
    }

    // tarkistetaan paketin eheys
    if (reply->error() == QNetworkReply::NoError) {

        // vastauksen parsiminen
        QByteArray bytes = reply->readAll();
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson( bytes, &err );

        switch (rData.function)
        {
        case GW_GET_ACCOUNT:
            QString strJson(doc.toJson(QJsonDocument::Compact));
            mMainwindow->debug(strJson);
            break;
        }

    }
    // jotakin tapahtui
    else
    {
        QString e = reply->errorString();
        mMainwindow->debug(e);
    }

    // tuhotaan vastaus
    reply->deleteLater();
}

// asettaa headerit paketille
int CommInterfaceJson::setRequestHeaders( QNetworkRequest *req )
{

    req->setHeader( QNetworkRequest::ContentTypeHeader, "application/json" );
    req->setRawHeader( "Accept", "application/json" );
    req->setRawHeader( "Authorization", "Bearer 28FAF88A-22A1-4340-AA2B-C7F346C1497CFED81CBD-99E5-47D2-B4E2-F78B7FDCC084");
    req->setRawHeader( "Connection", "keep-alive");

    return 0;
}
