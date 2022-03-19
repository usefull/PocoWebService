#pragma once

#include <atomic>

class UIDGenerator
{
public:
	static unsigned long long getNew()
	{
		static std::atomic<unsigned long long> uid{ 0 };
		return ++uid;
	}
};