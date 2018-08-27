#include <QtCore>

class JsonTree:public QJsonObject
{
public:
	JsonTree(QJsonDocument const& doc)
	{
		object = doc.object();
	}

	JsonTree(QJsonObject const& obj)
	{
		object = obj;
	}

	JsonTree(QString const& str)
	{
		string = str;
		object = QJsonDocument::fromJson(str.toUtf8()).object();
	}

	JsonTree operator[](QString key)
	{
		if (object[key].isObject())
		{ 
			return object[key].toObject();
		}
		else
		{
			return JsonTree(object[key].toVariant().toString());
		}
	}

	QString toString()
	{
		return string;
	}

	bool isObject()
	{
		return !object.isEmpty();
	}

	void print()
	{
		if (object.isEmpty())
			qDebug() << string;
		else
			qDebug() << object;
	}
private:
	QString string;
	QJsonObject object;
};


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QByteArray json_bytes = "{\"name\": {\"test\":234},\"str\" : 34,\"enemy\" : \"Loki\"}";
	//auto json_doc = QJsonDocument::fromJson(json_bytes);
	JsonTree tree(json_bytes);
	qDebug() << tree.isObject();
	qDebug() << tree["name"]["test"].isObject();
	qDebug() << tree["name"]["test"].toString();
	tree["name"].print();
	tree["name"]["test"].print();
}

