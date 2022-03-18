#include "UserJWTokens.h"

std::once_flag UserJWTokens::initializeFlag;

UserJWTokens* UserJWTokens::p_instance = 0;
UserJWTokensDestroyer UserJWTokens::destroyer;

UserJWTokensDestroyer::~UserJWTokensDestroyer()
{
	std::cout << "User JWT storage destroyed" << std::endl;
	delete p_instance;
}

void UserJWTokensDestroyer::initialize(UserJWTokens* p)
{
	p_instance = p;
}

UserJWTokens::UserJWTokens()
{

}

void UserJWTokens::initialize()
{
	std::call_once(initializeFlag, []()
		{
			std::cout << "User JWT storage initialized" << std::endl;
			p_instance = new UserJWTokens();
			destroyer.initialize(p_instance);
		}
	);
}

UserJWTokens* UserJWTokens::instance()
{
	if (p_instance == 0)
		throw std::runtime_error("ERROR: Attempt to use the UserJWTokens component before initialization");

	return p_instance;
}