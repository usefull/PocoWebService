// PocoWebService.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"

using Poco::Util::ServerApplication;
using Poco::Util::OptionSet;

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
		std::cout << "Poco web-service started..." << std::endl;

		waitForTerminationRequest();

		return Application::EXIT_OK;
	}

};

POCO_SERVER_MAIN(Application)