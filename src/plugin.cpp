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

void loadConfig()
{
    if (!std::filesystem::exists(PluginDir))
        std::filesystem::create_directories(PluginDir);
    // tr
    if (std::filesystem::exists(JsonFile))
    {
        try
        {
            settings::loadConfigFromJson(JsonFile);
        }
        catch (std::exception &e)
        {
            logger.warn("Config File isInvalid, Err {}", e.what());
            exit(1);
        }
        catch (...)
        {
            logger.warn("Config File isInvalid");
            exit(1);
        }
    }
    else
    {
        logger.info("Config with default values created");
        settings::writeDefaultConfig(JsonFile);
    }
}

void loadDatabase()
{
    try
    {
        db = std::make_unique<SQLite::Database>(PluginDatabase, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
    }
    catch (std::exception const &e)
    {
        db = std::make_unique<SQLite::Database>(PluginDatabase, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
    }
    db->exec("PRAGMA journal_mode = MEMORY");
    db->exec("PRAGMA synchronous = NORMAL");
    db->exec("CREATE TABLE IF NOT EXISTS Players ( \
			XUID  TEXT PRIMARY KEY \
			UNIQUE \
			NOT NULL\
		) \
			WITHOUT ROWID; ");
}
void RegCommand() { 
    using ParamType = DynamicCommand::ParameterType;
    auto command = DynamicCommand::createCommand("zgdd", "Enhances the original difficulty", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0x80 }, { (CommandFlagValue)1 });
    command->addOverload();
    command->setCallback([](DynamicCommand const& command, CommandOrigin const& origin, CommandOutput& output, std::unordered_map<std::string, DynamicCommand::Result>& results) {
        return output.success();
         });
     DynamicCommand::setup(std::move(command));
}
void PluginInit()
{
    loadConfig();
    loadDatabase();
    logger.info("Plugin initialized!");
    Event::ServerStartedEvent::subscribe([](const Event::ServerStartedEvent) {
        RegCommand();
        return true;
        });
}
