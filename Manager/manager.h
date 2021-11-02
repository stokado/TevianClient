#pragma once

#include <qobject.h>

#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qhttpmultipart.h>
#include <qurl.h>
#include <qurlquery.h>

#include <qjsonobject.h>
#include <qjsondocument.h>
#include <qjsonarray.h>

#include <qfile.h>
#include <qbuffer.h>

#include <qvector.h>
#include <qdebug.h>

#include "myrect.h"

class Manager : public QObject
{
	Q_OBJECT
public:
	Manager(QObject* parent = nullptr);
	~Manager();

signals:
	void onReady(QVector<MyRect>);

public slots:
	void postImage(QString fileName);
	void onResult(QNetworkReply* reply);

private:
	void initAuthorise();

private:
	QNetworkAccessManager* manager;
	const QUrl host = QString("https://backend.facecloud.tevian.ru");
	const QString email = "gm.nazarov.work@gmail.com";
	const QString password = "pass123test";
	QString token;
};