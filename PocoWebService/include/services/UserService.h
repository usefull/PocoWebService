#pragma once

#include <string>

class UserService
{
public:
	static int authonticate(std::wstring& login, std::wstring& pass)
	{
		if (login == L"mike" && pass == L"123")
		{
			return 14;
		}
		else if (login == L"admin" && pass == L"654321")
		{
			return 33;
		}

		return 0;
	}
};