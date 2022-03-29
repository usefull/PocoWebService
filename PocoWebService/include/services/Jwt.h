#pragma once

#include <string>

#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include <Poco/Timestamp.h>

#include "Configuration.h"

using Poco::JWT::Token;
using Poco::JWT::Signer;
using Poco::Timestamp;

class JWT
{
public:
	static std::string createAccessToken(int userId)
	{
		Timestamp now;
		Timestamp rrr = now + (Configuration::Instance().accessTokenLifetime() * 60 * 1000000);
		
		Token token;
		token.setType("JWT");
		token.setId(std::to_string(userId));
		token.setExpiration(now + (Configuration::Instance().accessTokenLifetime() * 60 * 1000000));

		Signer signer(Configuration::Instance().accessTokenSecret());
		return signer.sign(token, Signer::ALGO_HS256);
	}

	static std::string createRefreshToken(int userId)
	{
		Timestamp now;

		Token token;
		token.setType("JWT");
		token.setId(std::to_string(userId));
		token.setExpiration(now + (Configuration::Instance().refreshTokenLifetime() * 60 * 1000000));

		Signer signer(Configuration::Instance().refreshTokenSecret());
		return signer.sign(token, Signer::ALGO_HS256);
	}

	static int validateAccessToken(std::string& jwt)
	{
		try
		{
			Signer signer(Configuration::Instance().accessTokenSecret());
			Token token = signer.verify(jwt);
			Timestamp now;
			if (now > token.getExpiration())
				return 0;
			int userId;
			if (Poco::strToInt(token.getId(), userId, 10))
				return userId;
			else
				return 0;			
		}
		catch (...)
		{
			return 0;
		}
	}

	static int validateRefreshToken(std::string& jwt)
	{
		try
		{
			Signer signer(Configuration::Instance().refreshTokenSecret());
			Token token = signer.verify(jwt);
			Timestamp now;
			if (now > token.getExpiration())
				return 0;
			int userId;
			if (Poco::strToInt(token.getId(), userId, 10))
				return userId;
			else
				return 0;			
		}
		catch (...)
		{
			return 0;
		}
	}
};