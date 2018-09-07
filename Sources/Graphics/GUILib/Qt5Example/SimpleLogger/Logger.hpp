#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <QtCore/QtCore>
//
static void recvMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
//
class Logger : public QObject
{
public:
	static Logger &instance()
	{
		static Logger logger;
		return logger;
	}
	//
	void setLogPath(QString path)
	{
		QMutexLocker locker(&m_logMutex);
		if (path.isEmpty())
		{
			path = "";
		}
		//
		m_logDir.setPath(path);
		//
		if (!m_logDir.exists())
		{
			m_logDir.mkpath("."); //
		}
		QString fileName = QDate::currentDate().toString("yyyy-MM-dd_log.txt");
		QString logPath = m_logDir.absoluteFilePath(fileName); //

		m_logFile.setFileName(logPath);
		m_logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
		//
		m_textStream.setDevice(&m_logFile);
		m_textStream.setCodec("UTF-8");
		//
		m_textStream << QString().fill('-', 120);
		m_textStream << "\n";
		//
		qInstallMessageHandler(recvMessage);
	}
	//
	void flushLogFile()
	{
		QMutexLocker locker(&m_logMutex);
		m_textStream.flush();
	}
	//
	void onMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
	{
		QMutexLocker locker(&m_logMutex);
		QString level = m_mapMessageType[type];
		//
		QByteArray localMsg = msg.toLocal8Bit();
		//
		QString fileName = QFileInfo(context.file).fileName();
		//
		QString dateTime = QDateTime::currentDateTime().toString("hh:mm:ss,zzz");
		QString output = QString("[%1] [%2] (%3:%4): %6\n")
			.arg(level)
			.arg(dateTime)
			.arg(fileName)
			.arg(context.line)
			.arg(msg);
		//
		m_textStream << output;
	}
	//
private:
	Logger()
	{
		m_mapMessageType =
		{
			{QtDebugMsg, "Debug"},
			{QtInfoMsg, "Info "},
			{QtWarningMsg, "Warn "},
			{QtCriticalMsg, "Error"},
			{QtFatalMsg, "Fatal"},
		};
	}

	~Logger()
	{
		m_logFile.flush();
		m_logFile.close();

		QMutexLocker locker(&m_logMutex);
		qInstallMessageHandler(0);
	}

private:
	QDir m_logDir;
	QFile m_logFile;
	QMutex m_logMutex;
	QTimer m_flushTimer;
	QTextStream m_textStream;
	//
	QMap<int, QString> m_mapMessageType;
};
//
#define LoggerInstance Logger::instance()
//
static void recvMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	LoggerInstance.onMessage(type, context, msg);
}
//
#endif // LOGGER_H