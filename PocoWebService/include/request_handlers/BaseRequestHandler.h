#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>

#include "services/Jwt.h"
#include "dto/ErrorResponse.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::JSON::Parser;
using Poco::JSON::Object;

#define JSON_BODY(o, req, resp) const Object* tmp_##o; \
	try { \
		tmp_##o = getJsonBody(req); \
	} catch (...) { \
		ErrorResponse err; \
		sendResponse(resp, HTTPServerResponse::HTTPStatus::HTTP_BAD_REQUEST, err.message(L"Request body is not a valid JSON object").get()); \
		return; \
	} \
	const Object &o = *tmp_##o

#define GET_VALUE(obj, name, type, resp) try { \
		obj.getValue<type>(#name); \
	} catch (...) { \
		ErrorResponse err; \
		sendResponse(resp, HTTPServerResponse::HTTPStatus::HTTP_BAD_REQUEST, err.message(L"Required field not found").field(L#name).get()); \
		return; \
	} \
	type name = obj.getValue<type>(#name)

#define AUTHORIZE(userId, req, resp) int userId = authorize(req, resp); \
if (userId == 0) return

class BaseRequestHandler : public HTTPRequestHandler
{
protected:
	void sendResponse(HTTPServerResponse& response, HTTPServerResponse::HTTPStatus status, Object::Ptr pMessage = 0)
	{
		response.setContentType("application/json");
		response.setStatus(status);
		if (pMessage.isNull())
			response.send();
		else
			pMessage->stringify(response.send());
	}

	inline const Object* getJsonBody(HTTPServerRequest& request)
	{
		if (_pBody == 0)
			_pBody = _jsonParser.parse(request.stream()).extract<Object::Ptr>().get();

		return _pBody;
	}

	int authorize(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		int userId = 0;
		if (!request.has("Authorization"))
		{
			ErrorResponse err;
			sendResponse(response, HTTPServerResponse::HTTPStatus::HTTP_FORBIDDEN, err.message(L"Authorization header required").get());
			return userId;
		}
		if (!Poco::startsWith<std::string>(request["Authorization"], "Bearer "))
		{
			ErrorResponse err;
			sendResponse(response, HTTPServerResponse::HTTPStatus::HTTP_FORBIDDEN, err.message(L"Bearer token is required in the Authorization header").get());
			return userId;
		}

		std::string jwt = request["Authorization"].substr(7);
		userId = JWT::validateAccessToken(jwt);
		if (userId == 0)
		{
			ErrorResponse err;
			sendResponse(response, HTTPServerResponse::HTTPStatus::HTTP_FORBIDDEN, err.message(L"Expired access token").get());
		}
		return userId;
	}

protected:
	Parser _jsonParser;
	const Object* _pBody = 0;
};