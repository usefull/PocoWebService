#pragma once

#include <iostream>
#include <mutex>

class UserJWTokens;

class UserJWTokensDestroyer
{
private:
	UserJWTokens* p_instance;
public:
	~UserJWTokensDestroyer();
	void initialize(UserJWTokens* p);
};

class UserJWTokens
{
public:
	static void initialize();
	static UserJWTokens* instance();

protected:
	friend class UserJWTokensDestroyer;

private:
	UserJWTokens();
	static std::once_flag initializeFlag;
	static UserJWTokens* p_instance;
	static UserJWTokensDestroyer destroyer;
};