#include "Logger.hpp"

int main(int argc,char* argv[])
{
	LoggerInstance.setLogPath("log");
	qDebug() << "hello";
	qDebug() << "world";
	LoggerInstance.flushLogFile();
	return 0;
}