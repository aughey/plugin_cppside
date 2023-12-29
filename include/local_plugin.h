#include "plugin.h"

class LocalPlugin : public plugin::IPlugin
{
    public:
    LocalPlugin();
    virtual ~LocalPlugin() = default;
    virtual void initialize() override;
    virtual void OnFrame(plugin::IInterface *) override;
    virtual void OnExit() override;
};