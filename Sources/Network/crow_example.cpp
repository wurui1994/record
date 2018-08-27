// g++ crow_example.cpp -lboost_system -lpthread -o crow_example
// https://github.com/ipkn/crow

#ifdef _WIN32
#define _SCL_SECURE_NO_WARNINGS
#endif

#include <crow.h>

int main()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([]() {
		return "Hello world\n";
	});

	app.port(80).multithreaded().run();
	// `curl localhost` or `curl localhost:80`
}