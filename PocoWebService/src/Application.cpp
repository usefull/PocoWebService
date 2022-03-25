// PocoWebService.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>

#include "request_handlers/HandlerFactory.h"
#include "services/Configuration.h"

using Poco::Util::ServerApplication;
using Poco::Util::OptionSet;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::Net::ServerSocket;

class Application : public ServerApplication
{
public:
	Application()
	{
	}

	~Application()
	{
	}

protected:
	void initialize(Application& self)
	{
		ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);		
	}

	int main(const ArgVec& args)
	{
		std::cout << "Poco web-service started on port " << Configuration::Instance().port() << std::endl;

		HTTPServerParams* pParams = new HTTPServerParams;
		pParams->setMaxQueued(Configuration::Instance().maxQueued());
		pParams->setMaxThreads(Configuration::Instance().maxThreads());

		ServerSocket svs(Configuration::Instance().port());		
		HTTPServer srv(new HandlerFactory(), svs, pParams);		
		srv.start();
		
		waitForTerminationRequest();
		
		srv.stop();

		return Application::EXIT_OK;
	}
};

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application app;
	return app.run(argc, argv);
}