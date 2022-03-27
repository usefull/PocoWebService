#pragma once

#include "BaseRequestHandler.h"
#include "services\Jwt.h"
#include "services\UserService.h"
#include "dto\AuthResponse.h"

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

		AuthResponse message;

		sendResponse(response,
			HTTPServerResponse::HTTPStatus::HTTP_OK,
			message
				.access(JWT::createAccessToken(userId))
				.refresh(JWT::createRefreshToken(userId))
				.get()
		);
	}	
};
