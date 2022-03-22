﻿// PocoWebService.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "Poco/Net/HTTPServer.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"

#include "HandlerFactory.h"

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
		std::cout << "Poco web-service started" << std::endl;

		HTTPServerParams* pParams = new HTTPServerParams;
		pParams->setMaxQueued(100);
		pParams->setMaxThreads(4);

		ServerSocket svs(9090);
		
		HTTPServer srv(new HandlerFactory(), svs, pParams);
		
		srv.start();
		
		waitForTerminationRequest();
		
		srv.stop();

		return Application::EXIT_OK;
	}
};

POCO_SERVER_MAIN(Application)