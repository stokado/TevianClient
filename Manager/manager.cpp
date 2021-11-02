#include "manager.h"

Manager::Manager(QObject* parent) : QObject(parent)
{
	manager = new QNetworkAccessManager(this);
	initAuthorise();
}

Manager::~Manager()
{
	delete manager;
}

void Manager::postImage(QString fileName)
{

	QUrl route = host;
	const QString detectPath = "/api/v1/detect";
	route.setPath(detectPath);

	QUrlQuery query;
	query.addQueryItem("fd_min_size", "0");
	query.addQueryItem("fd_max_size", "0");
	query.addQueryItem("fd_threshold", "0.8");
	query.addQueryItem("demographics", "true");
	route.setQuery(query);
	
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "image/jpeg");
	request.setRawHeader(QByteArray("Authorization"), token.toUtf8());
	request.setUrl(route);

	QByteArray body;
	QFile test (fileName);
	test.open(QIODevice::ReadOnly);
	body = test.readAll();

	manager->post(request, body);
}

void Manager::onResult(QNetworkReply* reply)
{
	if (reply->error()) 
	{
		qDebug() << "ERROR";
		qDebug() << reply->errorString();
	}
	else 
	{
		QByteArray body { reply->readAll() };
		std::string str { body.toStdString() };
		QJsonDocument doc = QJsonDocument::fromJson(body);

		
		QJsonArray arr = doc["data"].toArray();
		QVector<MyRect> faces;

		foreach(auto temp, arr)
		{
			QJsonObject jObj = temp.toObject();

			MyRect rect;

			QJsonObject bbox = jObj["bbox"].toObject();
			rect.x = bbox["x"].toInt();
			rect.y = bbox["y"].toInt();
			rect.height = bbox["height"].toInt();
			rect.width = bbox["width"].toInt();

			QJsonObject demographics = jObj["demographics"].toObject();
			rect.age = demographics["age"].toObject()["mean"].toDouble();
			rect.gender = demographics["gender"].toString();

			faces.push_back(rect);
		}

		emit onReady(faces);
		
		qDebug() << "*** Answer Begin ***";
		qDebug() << str.c_str();
		qDebug() << "*** Answer End ***";
	}
}

void Manager::initAuthorise()
{
	QUrl route = host;
	const QString authPath = "/api/v1/login";
	route.setPath(authPath);

	QNetworkRequest request(route);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	
	QJsonObject obj;
	obj["email"] = email;
	obj["password"] = password;

	QJsonDocument doc(obj);
	QByteArray body = doc.toJson();

	QNetworkReply* reply = manager->post(request, body);
	connect(reply, &QNetworkReply::finished, [=]()
		{
			if (reply->error())
			{
				qDebug() << "ERROR";
				qDebug() << reply->errorString();
			}
			else
			{
				QByteArray body{ reply->readAll() };
				QJsonDocument replyDoc = QJsonDocument::fromJson(body);
				QJsonObject replyObj = replyDoc["data"].toObject();
				token = "Bearer " + replyObj["access_token"].toString();
			}
			connect(manager, &QNetworkAccessManager::finished, this, &Manager::onResult);
		});

}