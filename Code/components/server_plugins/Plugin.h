// Copyright (C) 2022 TiltedPhoques SRL.
// For licensing information see LICENSE at the root of this distribution.
#pragma once

#include <string>

namespace server_plugins
{
class Plugin
{
  public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Detatch() = 0;
};

struct PluginDescriptor
{
    const char* const name;
    const char* const desc;
    const char* const fileName;

    // Create a plugin instance with memory owned by your own
    // plugin.
    Plugin* (*createPlugin)() = nullptr;
    void (*destroyPlugin)(Plugin* apPluginInstance) = nullptr;
};

struct PluginData
{
    enum class Type
    {
        kNativePlugin,
        kRuntimePlugin,
        kReserved
    };

    PluginData(const Type actype, const void* apModuleHandle, PluginDescriptor *apDesc);

    Type m_type;
    const void* m_pModuleHandle{nullptr};
    PluginDescriptor* m_pDescriptor{nullptr};
};
} // namespace server_plugins
