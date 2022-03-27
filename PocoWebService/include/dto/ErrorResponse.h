#pragma once

#include "BaseResponse.h"

class ErrorResponse : public BaseResponse
{
public:
	ErrorResponse& message(const std::wstring& str)
	{
		_pObj->set("message", str);
		return *this;
	}

	ErrorResponse& field(const std::wstring& str)
	{
		_pObj->set("field", str);
		return *this;
	}

	ErrorResponse& details(const std::wstring& str)
	{
		_pObj->set("details", str);
		return *this;
	}
};
