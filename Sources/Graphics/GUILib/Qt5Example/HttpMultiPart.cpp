#include <QCoreApplication>
#include <QtNetwork/QtNetwork>
#include <QDebug>


QByteArray WebRequest(QString url, int& status_code, QString method = "get",
	QByteArray postData = "", QHttpMultiPart* HttpMultiPart = nullptr, QList<QNetworkReply::RawHeaderPair>* reply_pairs = nullptr, int time_out = 0)
{
	QNetworkAccessManager networkManager;
	QNetworkRequest request;
	QSslConfiguration config;

	request.setRawHeader("Cookie", "JSESSIONID=BAA9CEC316F39B3EE13AEB985670C669");
	request.setUrl(QUrl(url));

	QNetworkReply* reply;
	if (method == "get")
	{
		reply = networkManager.get(request);
	}
	else if (method == "post")
	{
		if (HttpMultiPart)
		{
			reply = networkManager.post(request, HttpMultiPart);
			HttpMultiPart->setParent(reply);
		}
		else
		{
			request.setHeader(QNetworkRequest::ContentTypeHeader,
				"application/x-www-form-urlencoded");
			reply = networkManager.post(request, postData);
		}
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


/*
--boundary_.oOo._MTIzODY=MzI2NzI=MjgxMDk=
Content-Type: application/octet-stream
Content-Disposition: form-data; name=srt;filename=Zootopia.2016.1080p.BluRay.x264-SPARKS.srt
......内容省略......
--boundary_.oOo._MTIzODY=MzI2NzI=MjgxMDk=
Content-Disposition: form-data; name="taskId"

143
--boundary_.oOo._MTIzODY=MzI2NzI=MjgxMDk=--
*/

//curl -F "srt=@Zootopia.2016.1080p.BluRay.x264-SPARKS.srt" -F "taskId=143" "http://website/upload/uploadSrt4Detail" -H "Cookie: JSESSIONID=BAA9CEC316F39B3EE13AEB985670C669" 

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QPointer<QHttpMultiPart> multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

	QHttpPart filePart;
	filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
	filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=srt;filename=\"Zootopia.2016.1080p.BluRay.x264-SPARKS.srt\""));
	QPointer<QFile> file= new QFile("Zootopia.2016.1080p.BluRay.x264-SPARKS.srt");
	file->open(QIODevice::ReadOnly);
	filePart.setBodyDevice(file);
	file->setParent(multiPart.data()); // we cannot delete the file now, so delete it with the multiPart

	QHttpPart textPart;
	textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"taskId\""));
	textPart.setBody("143");

	multiPart->append(filePart);
	multiPart->append(textPart);

	QString url = "http://website/upload/uploadSrt4Detail";
	int status_code;
	qDebug() << WebRequest(url, status_code, "post", "", multiPart.data());
	//return a.exec();
}

