
#include <XGL/XGL.h>

struct MetalRendererPlugin : public XGL::IPlugin
{
    //! @brief Returns the Plugin Name.
    const char* name() const { return "MetalRendererPlugin"; }

    //! @brief Inscribes the Plugin.
    void inscribe(XGL::Main& main) {}

    //! @brief Unscribe the Plugin.
    void unscribe(XGL::Main& main) {}
};

extern "C" MetalRendererPlugin* PluginMain(void) 
{
    static MetalRendererPlugin instance;
    return &instance;
}
