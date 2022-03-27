#pragma once

#include <Poco/JSON/Object.h>

using Poco::JSON::Object;

class SampleResponse
{
public:
	SampleResponse()
	{
		_pObj.assign(new Object());
	}

	SampleResponse& userId(int userId)
	{
		_pObj->set("userId", userId);
		return *this;
	}

	Object::Ptr& get()
	{
		return _pObj;
	}

private:
	Object::Ptr _pObj;
};