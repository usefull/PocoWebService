#pragma once

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

#include "HomeRequestHanler.h"
#include "NotFoundHandler.h"

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
		auto uri = request.getURI();

		if (request.getURI() == "/")
			return new HomeRequestHanler();
		else
			return new NotFoundHandler();
	}
};