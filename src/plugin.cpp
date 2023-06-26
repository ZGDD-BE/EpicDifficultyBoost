/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */
#include "global.h"
#include "version.h"

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *        
 */

void loadConfig(){
    settings::writeDefaultConfig(JsonFile);
    if (!std::filesystem::exists(PluginDir))
        std::filesystem::create_directories(PluginDir);
    //tr	
    if (std::filesystem::exists(JsonFile)) {
        try {
            settings::loadConfigFromJson(JsonFile);
        }
        catch (std::exception& e) {
            logger.warn("Config File isInvalid, Err {}", e.what());
            exit(1);
        }
        catch (...) {
            logger.warn("Config File isInvalid");
            exit(1);
        }
    }
    else {
        logger.info("Config with default values created");
        settings::writeDefaultConfig(JsonFile);
    }
}

void PluginInit()
{
    loadConfig();
    logger.info("Plugin initialized!");
}
