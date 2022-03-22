#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

class BaseRequestHandler : public HTTPRequestHandler
{
protected:
	void handleMethodNotAllowed(HTTPServerResponse& response)
	{
		response.setStatus(HTTPServerResponse::HTTPStatus::HTTP_METHOD_NOT_ALLOWED);
		response.send();
	}
};