#include <QCoreApplication>
#include <QtNetwork/QtNetwork>
#include <QDebug>


QByteArray WebRequest(QString url, int& status_code, QString method="get",
	QByteArray postData="", QList<QNetworkReply::RawHeaderPair>* reply_pairs=nullptr, int time_out=0)
{
	QNetworkAccessManager networkManager;
	QNetworkRequest request;
	QSslConfiguration config;

	request.setUrl(QUrl(url));

	QNetworkReply* reply;
	if (method == "get")
	{
		reply = networkManager.get(request);
	}
	else if (method == "post")
	{
		request.setHeader(QNetworkRequest::ContentTypeHeader,
			"application/x-www-form-urlencoded");
		reply = networkManager.post(request, postData);
	}
	else
	{
		qDebug() << "method not support.";
		return QByteArray("");
	}

	QTimer timer;
	timer.setSingleShot(true);

	QEventLoop loop;
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	if (time_out <= 0)
	{
		time_out = 3000;
	}
	timer.start(time_out);   // 3 secs. timeout
	loop.exec();

	if (timer.isActive())
	{
		timer.stop();
		if (reply->error() > 0)
		{
			qDebug() << "error";// handle error
			return QByteArray("");
		}
		else
		{
			status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
			if (status_code >= 200 && status_code < 300)
			{
				// Success
				if (reply_pairs)
				{
					*reply_pairs = reply->rawHeaderPairs();
				}
				return reply->readAll();
			}
		}
	}
	else
	{
		// timeout
		QObject::disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		reply->abort();
		return QByteArray("");
	}
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	QString identifier = "10016";
	QString usersig = "eJxlz0FPwjAUwPH7PkXTq0a6dWPDWxkLDpkBR4J4aWbXQWdsSymLw-jdxalxxnf9-V9e3psDAICreX5VMKaO0lLbag7BNYAIXv6i1qKkhaXYlP*Qv2phOC0qy02HbhAEHkL9RpRcWlGJnwIhd9jjQ-lMuxtf6p*XcYj-JmLbYZZs4nQ5aX2mLxJWVywanxY4jwf50zAZTdcmrPVsk0drdb-PHoOZJOmO3AnBJ-VSqXR7moaczJtdPX44VvtWxqS5KWxmLUm8we1q1DtpxQv-fsjFkY-8sK8NNwehZBd46Jx4GH0OdN6dDzo7XFY_";

	QString login = QString("https://webim.tim.qq.com/v4/openim/login?identifier=%1&usersig=%2&contenttype=json&sdkappid=1400037316").arg(identifier).arg(usersig);
	int statusCode;
	QString jsonString = WebRequest(login, statusCode);
	qDebug() << jsonString;
	QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonString.toUtf8());
	QJsonObject jsonObject = jsonResponse.object();
	//qDebug() << jsonObject.contains("A2Key");
	qDebug() << jsonObject["A2Key"];
	qDebug() << jsonObject["TinyId"];

	QString authKey = QString("https://webim.tim.qq.com/v4/openim/authkey?tinyid=%1&a2=%2&contenttype=json&sdkappid=1400037316").arg(jsonObject["TinyId"].toString()).arg(jsonObject["A2Key"].toString());
	qDebug() << authKey;
	jsonString = WebRequest(authKey, statusCode);
	qDebug() << jsonString;
	jsonResponse = QJsonDocument::fromJson(jsonString.toUtf8());
	jsonObject = jsonResponse.object();
	qDebug() << jsonObject.contains("AuthKey");
	qDebug() << jsonObject["AuthKey"];
	//
	QString fileid = "3051020100044a30480201000405313030303502037a1afd02041a16a3b402045a546fe2042531363437303036313830313838393130303233385fb3b6f685f9ad44cdc6cb8eb05a10912f0201000201000400";
	QString filename = "%E6%8D%95%E8%8E%B7.PNG";
	QString file = QString("http://180.163.22.25/asn.com/stddownload_common_file?authkey=%1&bid=10001&subbid=1400037316&fileid=%2&filetype=2107&openid=10005&ver=0&filename=%3").arg(jsonObject["AuthKey"].toString()).arg(fileid).arg(filename);
	qDebug() << file;
	QByteArray data = WebRequest(file, statusCode);
	qDebug() << data.size();
    //return a.exec();
}

