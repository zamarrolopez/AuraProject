#pragma once

#include <framework/global.h>
#include <framework/graphics/declarations.h>
#include "applicationcontext.h"

//@bindsingleton g_app
class Application
{
public:
    virtual ~Application() = default;

    virtual void init(std::vector<std::string>& args, ApplicationContext* context) {}
    virtual void deinit() {}
    virtual void terminate() {}
    virtual void run() { m_running = true; while (!m_stopping) poll(); }
    virtual void poll() {}
    virtual void exit() { m_stopping = true; }
    virtual void close() { exit(); }
    virtual void restart() {}

    void setName(const std::string_view name) {
        m_appName = name;
#ifndef NDEBUG
        m_appName += " (DEBUG MODE)";
#endif
    }
    void setCompactName(const std::string_view name) { m_appCompactName = name; }
    void setOrganizationName(const std::string_view name) { m_organizationName = name; }

    bool isRunning() const { return m_running; }
    bool isStopping() const { return m_stopping; }
    bool isTerminated() const { return m_terminated; }
    const std::string& getName() const { return m_appName; }
    const std::string& getCompactName() const { return m_appCompactName; }
    const std::string& getOrganizationName() const { return m_organizationName; }
    std::string getVersion() const;

    std::string getCharset() const { return m_charset; }
    std::string getBuildCompiler() const { return BUILD_COMPILER; }
    std::string getBuildDate() const { return std::string{ __DATE__ }; }
    std::string getBuildType() const { return BUILD_TYPE; }
    std::string getBuildArch() const { return BUILD_ARCH; }
    std::string getBuildRevision() const;
    std::string getBuildCommit() const;
    std::string getOs() const;
    std::string getStartupOptions() const { return m_startupOptions; }

protected:
    void registerLuaFunctions();

    std::string m_charset{ "cp1252" };
    std::string m_organizationName{ "otbr" };
    std::string m_appName{ "OTClient - Redemption" };
    std::string m_appCompactName{ "otcr" };
    std::string m_startupOptions;

    std::vector<std::string> m_startupArgs;

    bool m_running{ false };
    bool m_terminated{ false };
    bool m_stopping{ false };

    std::unique_ptr<ApplicationContext> m_context;
};
