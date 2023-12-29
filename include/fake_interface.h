#pragma once

#include "plugin.h"

class FakeInterface : public plugin::IInterface
{
public:
    FakeInterface() : m_shutdown(false), frame(0), name("FakeInterface") {}
    virtual ~FakeInterface() {}
    void incrementFrame()
    {
        frame++;
    }

    virtual void shutdown()
    {
        this->m_shutdown = true;
    }

    virtual const std::string &getName()
    {
        return name;
    }
    virtual ssize_t getFrame()
    {
        return frame;
    }
    virtual double getPositionX()
    {
        return 3.14;
    }
    virtual double getPositionY()
    {
        return 0.159;
    }
    virtual double getPositionZ()
    {
        return 0.265;
    }

    bool inShutdown()
    {
        return m_shutdown;
    }

protected:
    bool m_shutdown;
    ssize_t frame;
    std::string name;
};
