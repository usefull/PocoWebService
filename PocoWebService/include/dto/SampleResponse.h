#pragma once

#include "BaseResponse.h"

class SampleResponse : public BaseResponse
{
public:
	SampleResponse& userId(int userId)
	{
		_pObj->set("userId", userId);
		return *this;
	}
};