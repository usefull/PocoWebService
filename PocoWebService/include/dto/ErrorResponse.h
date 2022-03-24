#pragma once

#include <Poco/JSON/Object.h>

using Poco::JSON::Object;

class ErrorResponse
{
public:
	ErrorResponse()
	{
		_pObj.assign(new Object());
	}

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

	Object::Ptr& get()
	{
		return _pObj;
	}

private:
	Object::Ptr _pObj;
};
