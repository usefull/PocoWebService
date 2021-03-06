#pragma once

#include <Poco/Timestamp.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

#include "BaseRequestHandler.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Timestamp;
using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;

class HomeRequestHandler : public BaseRequestHandler
{
public:
	HomeRequestHandler()
	{			
	}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		if (request.getMethod() == "GET")
			handleGet(request, response);
		else
			sendResponse(response, HTTPServerResponse::HTTPStatus::HTTP_METHOD_NOT_ALLOWED);
	}

	void handleGet(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		Timestamp now;
		std::string dt(DateTimeFormatter::format(now, DateTimeFormat::SORTABLE_FORMAT));

		std::ostream& ostr = response.send();
		ostr	<< "Welcome to PocoWebServer API"
				<< "\n\r~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "\n\rService UTC: " << dt;
	}
};