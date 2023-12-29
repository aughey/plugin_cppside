#pragma once
#include <string>

namespace plugin
{
    class IInterface {
    public:
        virtual ~IInterface() = default;
        virtual std::string getName() = 0;
        virtual ssize_t getFrame() = 0;
        virtual double getPositionX() = 0;
        virtual double getPositionY() = 0;
        virtual double getPositionZ() = 0;
    };

    class IPlugin {
    public:
        virtual ~IPlugin() = default;
        virtual void initialize() = 0;
        virtual void OnFrame(IInterface *) = 0;
        virtual void OnExit() = 0;
    };
}