#include "consoleapplication.h"
#include <framework/core/clock.h>
#include <framework/luaengine/luainterface.h>
#include <framework/core/eventdispatcher.h>
#include <framework/core/asyncdispatcher.h>
#include <framework/stdext/time.h>
#include <iostream>

#ifdef FW_NET
#include <framework/net/connection.h>
#endif

ConsoleApplication g_app;

void ConsoleApplication::run() {
    g_lua.callGlobalField("g_app", "onRun");

    // Hilo secundario para ejecutar polling adicional
    std::thread backgroundPolling([this]() {
        while (!m_stopping) {
            poll();
            stdext::millisleep(1);
        }
    });

    m_running = true;

    // Bucle principal
    while (!m_stopping) {
        mainPoll();
    }

    // Esperar a que el hilo termine
    if (backgroundPolling.joinable()) {
        backgroundPolling.join();
    }

    m_stopping = false;
    m_running = false;
}

void ConsoleApplication::mainPoll() {
    g_clock.update();

    // Procesar eventos principales
    g_mainDispatcher.poll();
}
