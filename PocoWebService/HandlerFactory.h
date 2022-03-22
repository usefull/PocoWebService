#pragma once

#include "Poco/String.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

#include "HomeRequestHandler.h"
#include "NotFoundHandler.h"
#include "AuthRequestHandler.h"

using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;

class HandlerFactory : public HTTPRequestHandlerFactory
{
public:
	HandlerFactory()
	{
	}

	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		auto eee = request.getURI();

		if (request.getURI() == "/")
			return new HomeRequestHandler();
		else if (Poco::toLower(request.getURI()) == "/auth")
			return new AuthRequestHandler();
		else
			return new NotFoundHandler();
	}
};