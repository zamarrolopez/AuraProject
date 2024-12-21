#pragma once

#include "framework/core/application.h"
#include "framework/core/applicationcontext.h"

// Clase heredada para aplicaciones de consola
class ConsoleApplicationContext : public ApplicationContext {
public:
    ConsoleApplicationContext() : ApplicationContext() {}
};

class ConsoleApplication : public Application {
public:
    void run() override {
        m_running = true;
        while (!m_stopping) mainPoll();
    }

    void mainPoll();

private:
    bool m_running = false;  // Inicializa a `false` por defecto
    bool m_stopping = false; // Inicializa a `false` por defecto
};
