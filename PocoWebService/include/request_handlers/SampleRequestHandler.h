#pragma once

#include <string>

#include "BaseRequestHandler.h"
#include "services/Jwt.h"
#include "dto/SampleResponse.h"

class SampleRequestHandler : public BaseRequestHandler
{
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		if (request.getMethod() == "GET")
			handleGet(request, response);
		else
			sendResponse(response, HTTPServerResponse::HTTPStatus::HTTP_METHOD_NOT_ALLOWED);
	}

	void handleGet(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		AUTHORIZE(userId, request, response);

		SampleResponse message;		
		sendResponse(response, HTTPServerResponse::HTTPStatus::HTTP_OK, message.userId(userId).get());
	}
};