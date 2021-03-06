#pragma once

#include <Poco/AutoPtr.h>
#include <Poco/Util/PropertyFileConfiguration.h>

using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;

class Configuration
{
public:
    static Configuration& Instance()
    {
        static Configuration myInstance;
        return myInstance;
    }

    Configuration(Configuration const&) = delete;
    Configuration(Configuration&&) = delete;
    Configuration& operator=(Configuration const&) = delete;
    Configuration& operator=(Configuration&&) = delete;

    int port()
    {
        return _pConf->getInt("port", 9000);
    }

    int maxQueued()
    {
        return _pConf->getInt("maxQueued", 50);
    }

    int maxThreads()
    {
        return _pConf->getInt("maxThreads", 3);
    }

    std::string accessTokenSecret()
    {
        return _pConf->getString("accessTokenSecret");
    }

    std::string refreshTokenSecret()
    {
        return _pConf->getString("refreshTokenSecret");
    }

    Poco::UInt64 accessTokenLifetime()
    {
        return _pConf->getUInt64("accessTokenLifetime", 10);
    }

    Poco::UInt64 refreshTokenLifetime()
    {
        return _pConf->getUInt64("refreshTokenLifetime", 60);
    }

protected:
    Configuration()
    {
        _pConf = new PropertyFileConfiguration("service.properties");
    }

    ~Configuration()
    {
    }

private:
    AutoPtr<PropertyFileConfiguration> _pConf;
};