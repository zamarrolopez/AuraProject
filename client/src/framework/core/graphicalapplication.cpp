#include "graphicalapplication.h"
#include <framework/core/clock.h>
#include <framework/graphics/graphics.h>
#include <framework/platform/platformwindow.h>
#include <framework/graphics/painter.h>
#include "framework/core/applicationcontext.h"
#include "framework/core/graphicalapplicationcontext.h"


// Inicialización global de g_painter
std::unique_ptr<Painter> g_painter = std::make_unique<Painter>();
// Instancia global de GraphicalApplication
GraphicalApplication g_app;

void GraphicalApplication::init(std::vector<std::string>& args, ApplicationContext* context) {
    Application::init(args, context);

    g_graphics.init();
    g_window.init();
    //g_painter->init();

    // Validar si el contexto es GraphicalApplicationContext
    if (auto graphicalContext = dynamic_cast<GraphicalApplicationContext*>(context); graphicalContext && graphicalContext->getDrawEvents()) {
        setDrawEvents(graphicalContext->getDrawEvents());
    }
}

void GraphicalApplication::deinit() {
    //g_painter->terminate();
    g_window.terminate();
    g_graphics.terminate();

    Application::deinit();
}

void GraphicalApplication::terminate() {
    Application::terminate();
}

void GraphicalApplication::run() {
    while (!isStopping()) {
        mainPoll();
    }
}

void GraphicalApplication::poll() {
    Application::poll();

    if (m_drawEvents) {
        g_graphics.beginRender();
        g_painter->drawFilledRect(Rect(0, 0, g_window.getWidth(), g_window.getHeight()), Color::black);

        if (m_drawEvents->canDraw(DrawPoolType::FOREGROUND)) {
            m_drawEvents->draw(DrawPoolType::FOREGROUND);
        }

        g_graphics.endRender();
    }
}

void GraphicalApplication::mainPoll() {
    g_clock.update();
    g_window.poll();

    poll();

    if (m_drawEvents && m_drawEvents->isLoadingAsyncTexture()) {
        m_drawEvents->onLoadingAsyncTextureChanged(false);
    }
}

void GraphicalApplication::close() {
    Application::close();
}

void GraphicalApplication::resize(const Size& size) {
    if (m_drawEvents) {
        m_drawEvents->preLoad();
    }
}

void GraphicalApplication::inputEvent(const InputEvent& event) {
    m_onInputEvent = true;
    g_dispatcher.addEvent([this, event]() {
        // Procesar eventos de entrada
        m_onInputEvent = false;
    });
}
