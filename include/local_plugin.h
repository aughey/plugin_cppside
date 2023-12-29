#include "plugin.h"

class LocalPlugin : public plugin::IPlugin
{
    public:
    LocalPlugin();
    virtual ~LocalPlugin() {}
    virtual void initialize();
    virtual void OnFrame(plugin::IInterface *);
    virtual void OnExit();
};