#pragma once

#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "HomeRequestHandler.h"
#include "NotFoundHandler.h"
#include "AuthRequestHandler.h"
#include "SampleRequestHandler.h"

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
		if (request.getURI() == "/")
			return new HomeRequestHandler();
		else if (Poco::toLower(request.getURI()) == "/auth")
			return new AuthRequestHandler();
		else if (Poco::toLower(request.getURI()) == "/sample")
			return new SampleRequestHandler();
		else
			return new NotFoundHandler();
	}
};