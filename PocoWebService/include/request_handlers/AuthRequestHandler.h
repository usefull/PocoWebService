#pragma once

#include "BaseRequestHandler.h"
#include "services\Jwt.h"
#include "services\UserService.h"

class AuthRequestHandler : public BaseRequestHandler
{
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		if (request.getMethod() == "POST")
			handlePost(request, response);
		else
			sendResponse(response, HTTPServerResponse::HTTPStatus::HTTP_METHOD_NOT_ALLOWED);
	}

	void handlePost(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		JSON_BODY(body, request, response);
		GET_VALUE(body, login, std::wstring, response);
		GET_VALUE(body, pass, std::wstring, response);

		int userId = UserService::authonticate(login, pass);
		if (userId == 0)
		{
			sendResponse(response, HTTPServerResponse::HTTPStatus::HTTP_UNAUTHORIZED);
			return;
		}

		Object::Ptr pMessage;
		pMessage.assign(new Object());
		pMessage->set("access", JWT::createAccessToken(userId));
		pMessage->set("refresh", JWT::createRefreshToken(userId));

		sendResponse(response, HTTPServerResponse::HTTPStatus::HTTP_OK, pMessage);
	}
};
