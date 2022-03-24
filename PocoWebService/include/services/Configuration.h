#pragma once

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

protected:
    Configuration()
    {
    }

    ~Configuration()
    {        
    }
};