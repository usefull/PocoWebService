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
};