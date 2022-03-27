#pragma once

#include <Poco/JSON/Object.h>

using Poco::JSON::Object;

class BaseResponse
{
public:
	BaseResponse()
	{
		_pObj.assign(new Object());
	}

	Object::Ptr& get()
	{
		return _pObj;
	}

protected:
	Object::Ptr _pObj;
};