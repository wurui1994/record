#include <QFile>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QCryptographicHash>

QByteArray getFileMd5(QString filePath)
{
	QFile localFile(filePath);

	if (!localFile.open(QFile::ReadOnly))
	{
		qDebug() << "file open error.";
		return 0;
	}

	QCryptographicHash ch(QCryptographicHash::Md5);

	quint64 totalBytes = 0;
	quint64 bytesWritten = 0;
	quint64 bytesToWrite = 0;
	quint64 loadSize = 1024 * 4;
	QByteArray buf;

	totalBytes = localFile.size();
	bytesToWrite = totalBytes;

	while (1)
	{
		if (bytesToWrite > 0)
		{
			buf = localFile.read(qMin(bytesToWrite, loadSize));
			ch.addData(buf);
			bytesWritten += buf.length();
			bytesToWrite -= buf.length();
			buf.resize(0);
		}
		else
		{
			break;
		}

		if (bytesWritten == totalBytes)
		{
			break;
		}
	}

	localFile.close();
	QByteArray md5 = ch.result();
	return md5;
}

QString getPrettySize(qint64 size)
{
	qint64 gb = (1 << 30), mb = (1 << 20), kb = (1 << 10);
	float fsize = 0.0;
	QString pretty_size;
	if (size >= gb)
	{
		fsize = 1.0*size / gb;
		pretty_size = pretty_size.setNum(fsize, 'f', 2) + "GB";
	}
	else if (size < gb && size >= mb)
	{
		fsize = 1.0*size / mb;
		pretty_size = pretty_size.setNum(fsize, 'f', 2) + "MB";
	}
	else if (size < mb && size >= kb)
	{
		fsize = 1.0*size / kb;
		pretty_size = pretty_size.setNum(fsize, 'f', 2) + "KB";
	}
	else
	{
		pretty_size = pretty_size.setNum(size) + "B";
	}
	return pretty_size;
}