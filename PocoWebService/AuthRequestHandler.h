#pragma once

#include "BaseRequestHandler.h"
#include "Poco/UnicodeConverter.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"

class AuthRequestHandler : public BaseRequestHandler
{
public:
	AuthRequestHandler()
	{
	}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		if (request.getMethod() == "POST")
			handlePost(request, response);
		else
			handleMethodNotAllowed(response);
	}

	void handlePost(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		auto gg = request["Content-Type"];

		//std::istream& i = request.stream();
		Poco::JSON::Parser parser;
		auto json = parser.parse(request.stream());
		auto pObject = json.extract<Poco::JSON::Object::Ptr>();
		std::string name = pObject->getValue<std::string>("login");
		std::string pass = pObject->getValue<std::string>("pass");

		//int len = request.getContentLength();
		//char* buffer = new char[len + 1];
		//i.read(buffer, len);
		//buffer[len] = 0;

		//std::wstring ws(&buffer[0], &buffer[len]);

		//std::string utf8line;

		//Poco::UnicodeConverter::toUTF16(ws, utf8line);

		

		//Poco::Dynamic::Struct
		std::ostream& ostr = response.send();
		ostr << "This is auth";
	}
};
