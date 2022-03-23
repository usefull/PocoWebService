#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::JSON::Parser;
using Poco::JSON::Object;

#define JSON_BODY(o, req, resp) const Object* tmp_##o; \
	try { \
		tmp_##o = getJsonBody(req); \
	} catch (...) { \
		sendStatus(resp, HTTPServerResponse::HTTPStatus::HTTP_BAD_REQUEST); \
		return; \
	} \
	const Object &o = *tmp_##o

#define GET_VALUE(obj, name, type, resp) try { \
		obj.getValue<type>(#name); \
	} catch (...) { \
		sendStatus(resp, HTTPServerResponse::HTTPStatus::HTTP_BAD_REQUEST); \
		return; \
	} \
	type name = obj.getValue<type>(#name)

class BaseRequestHandler : public HTTPRequestHandler
{
protected:
	void sendStatus(HTTPServerResponse& response, HTTPServerResponse::HTTPStatus status)
	{
		response.setStatus(status);
		response.send();
	}

	inline const Object* getJsonBody(HTTPServerRequest& request)
	{
		if (_pBody == 0)
			_pBody = _jsonParser.parse(request.stream()).extract<Object::Ptr>().get();

		return _pBody;
	}

protected:
	Parser _jsonParser;
	const Object* _pBody = 0;
};