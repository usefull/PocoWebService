#pragma once

#include "BaseRequestHandler.h"

using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

class NotFoundHandler : public BaseRequestHandler
{
public:

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		sendStatus(response, HTTPServerResponse::HTTPStatus::HTTP_NOT_FOUND);
	}
};