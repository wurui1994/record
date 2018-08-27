//clang++ -std=c++14
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QtConcurrent/QtConcurrent>

QByteArray getFileMd5(QString filePath)
{
	QFile localFile(filePath);
	if (!localFile.open(QFile::ReadOnly))
	{
		qDebug() << "file open error.";
		return 0;
	}
	quint64 totalBytes = localFile.size();
	quint64 bytesWritten = 0;
	quint64 bytesToWrite = totalBytes;
	quint64 loadSize = 1024 * 4;

	using Hash = QCryptographicHash;
	Hash md5Hash(Hash::Md5);
	QByteArray buffer;
	while (true)
	{
		if (bytesToWrite > 0)
		{
			buffer = localFile.read(qMin(bytesToWrite, loadSize));
			md5Hash.addData(buffer);
			bytesWritten += buffer.length();
			bytesToWrite -= buffer.length();
			buffer.resize(0);
		}
		else break;

		if (bytesWritten == totalBytes) break;
	}
	localFile.close();
	return md5Hash.result();
}

template<
	typename U,
	typename X,
	typename... Args
>
void AsyncCall(U func, X callback, Args... args)
{
	auto future = QtConcurrent::run(func, args...);
	using Watcher = QFutureWatcher<decltype(future.result())>;
	QSharedPointer<Watcher> watcher(new Watcher());
	QObject::connect(watcher.data(), &Watcher::finished, [=]()
	{
		callback(watcher->result());
	});
	watcher->setFuture(future);
}

auto AsyncCallL = [](auto  func, auto callback, auto... args)
{
	auto future = QtConcurrent::run(func, args...);
	using Watcher = QFutureWatcher<decltype(future.result())>;
	QSharedPointer<Watcher> watcher(new Watcher());
	QObject::connect(watcher.data(), &Watcher::finished, [=]()
	{
		callback(watcher->result());
	});
	watcher->setFuture(future);
};

bool asyncGetFileMd5(QString const& file, std::function<void(QByteArray const& md5)> callback)
{
	if (!QFile::exists(file)) return false;
	using Watcher = QFutureWatcher<QByteArray>;
	QSharedPointer<Watcher> watcher(new Watcher());
	QObject::connect(watcher.data(), &Watcher::finished, [=]()
	{
		callback(watcher->result());
	});
	watcher->setFuture(QtConcurrent::run(getFileMd5, file));
	return true;
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

    //Async:"Normal" maybe not output.
	qDebug() << asyncGetFileMd5(argv[0], [&](QByteArray const& md5)
	{
		qDebug() << md5.toHex() << "Normal";
		//app.quit();
	});

	//Template
	AsyncCall(getFileMd5,[&](auto md5)
	{
		qDebug() << md5.toHex() << "Template";
		//app.quit();
	}, argv[0]);

	//Lambda
	AsyncCallL(getFileMd5, [&](auto md5)
	{
		qDebug() << md5.toHex() << "Lambda";
		app.quit();
	}, argv[0]);

	app.exec();
}