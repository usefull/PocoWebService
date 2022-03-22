#pragma once

#include "Poco/Timestamp.h"

class AuthRecord
{
public:
	AuthRecord(int userId, int accessTokenId, int refreshTokenId, int accessLifetimeInMinutes, int refreshLifetimeInMinutes)
	{
		this->userId = userId;
		this->accessTokenId = accessTokenId;
		this->refreshTokenId = refreshTokenId;
		setAccessLifetime(accessLifetimeInMinutes);
		setRefreshLifetime(refreshLifetimeInMinutes);
	};

	// Check access token expired.
	bool isAccessExpired()
	{
		return Poco::Timestamp().epochMicroseconds() > accessTokenExpiration;
	}

	// Check refresh token expired.
	bool isRefreshExpired()
	{
		return Poco::Timestamp().epochMicroseconds() > refreshTokenExpiration;
	}

	// Set the access token lifetime in minutes, starting from the current moment.
	void setAccessLifetime(int minutes)
	{
		accessTokenExpiration = Poco::Timestamp().epochMicroseconds() + (minutes * 60 * 1000);
	}

	// Set the refresh token lifetime in minutes, starting from the current moment.
	void setRefreshLifetime(int minutes)
	{
		refreshTokenExpiration = Poco::Timestamp().epochMicroseconds() + (minutes * 60 * 1000);
	}

	// User ID.
	int userId;

	// Access token ID.
	int accessTokenId;

	// Refresh token ID.
	int refreshTokenId;

	// Number of milliseconds since the Epoch when access token expired.
	Poco::Timestamp::TimeVal accessTokenExpiration;

	// Number of milliseconds since the Epoch when refresh token expired.
	Poco::Timestamp::TimeVal refreshTokenExpiration;
};