#pragma once

#include "BaseResponse.h"

class AuthResponse : public BaseResponse
{
public:
	AuthResponse& access(const std::string& jwt)
	{
		_pObj->set("access", jwt);
		return *this;
	}

	AuthResponse& refresh(const std::string& jwt)
	{
		_pObj->set("refresh", jwt);
		return *this;
	}
};