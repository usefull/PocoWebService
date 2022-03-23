#pragma once

#include "BaseRequestHandler.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"

class AuthRequestHandler : public BaseRequestHandler
{
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		if (request.getMethod() == "POST")
			handlePost(request, response);
		else
			sendStatus(response, HTTPServerResponse::HTTPStatus::HTTP_METHOD_NOT_ALLOWED);
	}

	void handlePost(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		JSON_BODY(body, request, response);
		GET_VALUE(body, login, std::wstring, response);
		GET_VALUE(body, pass, std::wstring, response);

		std::ostream& ostr = response.send();
		ostr << "This is auth";
	}
};
