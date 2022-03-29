#pragma once

#include "BaseRequestHandler.h"
#include "services\Jwt.h"

class RefreshRequestHandler : public BaseRequestHandler
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
		GET_VALUE(body, token, std::string, response);

		int userId = JWT::validateRefreshToken(token);
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