#pragma once

#include "framework/core/application.h"
#include <framework/core/adaptativeframecounter.h>
#include <framework/core/inputevent.h>
#include <framework/core/timer.h>
#include <framework/graphics/declarations.h>
#include <framework/platform/platformwindow.h>
#include "framework/graphics/painter.h"
#include "applicationcontext.h"
#include "application.h"

// Clase base para eventos de dibujo
class ApplicationDrawEvents {
protected:
    virtual void preLoad() = 0;
    virtual void draw(DrawPoolType type) = 0;

    virtual bool canDraw(DrawPoolType type) const = 0;
    virtual bool isLoadingAsyncTexture() const = 0;
    virtual bool isUsingProtobuf() const = 0;
    virtual void onLoadingAsyncTextureChanged(bool loadingAsync) = 0;
    virtual void doMapScreenshot(std::string fileName) = 0;

    friend class GraphicalApplication;
};

// Contexto de la aplicación gráfica
class GraphicalApplicationContext : public ApplicationContext {
public:
    GraphicalApplicationContext(uint8_t spriteSize, ApplicationDrawEventsPtr drawEvents)
        : ApplicationContext(), m_spriteSize(spriteSize), m_drawEvents(std::move(drawEvents)) {}

    void setSpriteSize(uint8_t size) { m_spriteSize = size; }
    uint8_t getSpriteSize() const { return m_spriteSize; }

    void setDrawEvents(ApplicationDrawEventsPtr drawEvents) { m_drawEvents = drawEvents; }
    ApplicationDrawEventsPtr getDrawEvents() const { return m_drawEvents; }

private:
    uint8_t m_spriteSize;
    ApplicationDrawEventsPtr m_drawEvents;
};

// Implementación final de la aplicación gráfica
class GraphicalApplication final : public Application {
public:
    void init(std::vector<std::string>& args, ApplicationContext* context) override;
    void deinit() override;
    void terminate() override;
    void run() override;
    void poll() override;
    void mainPoll();
    void close() override;

    void restart();
    void exit();
    std::string getOs() const;                // Sin override
    std::string getVersion() const;          // Sin override
    std::string getBuildRevision() const;    // Sin override
    std::string getBuildCommit() const;      // Sin override

    void setMaxFps(uint16_t maxFps) { m_graphicFrameCounter.setMaxFps(maxFps); }
    void setTargetFps(uint16_t targetFps) { m_graphicFrameCounter.setTargetFps(targetFps); }

    uint16_t getFps() const { return m_graphicFrameCounter.getFps(); }
    uint8_t getMaxFps() const { return m_graphicFrameCounter.getMaxFps(); }
    uint8_t getTargetFps() const { return m_graphicFrameCounter.getTargetFps(); }

    void resetTargetFps() { m_graphicFrameCounter.resetTargetFps(); }

    bool isOnInputEvent() const { return m_onInputEvent; }
    bool mustOptimize() const {
#ifdef NDEBUG
        return m_optimize && getMaxFps() >= getFps() && getFps() < 58u;
#else
        return false;
#endif
    }
    bool isForcedEffectOptimization() const { return m_forceEffectOptimization; }

    void optimize(bool optimize) { m_optimize = optimize; }
    void forceEffectOptimization(bool optimize) { m_forceEffectOptimization = optimize; }

    void setDrawTexts(bool draw) { m_drawText = draw; }
    bool isDrawingTexts() const { return m_drawText; }

    void setDrawEffectsOnTop(bool draw) { m_drawEffectOnTop = draw; }
    bool isDrawingEffectsOnTop() const { return m_drawEffectOnTop || mustOptimize(); }

    float getCreatureInformationScale() const { return m_creatureInformationScale; }
    void setCreatureInformationScale(float scale) { m_creatureInformationScale = scale; }

    float getAnimatedTextScale() const { return m_animatedTextScale; }
    void setAnimatedTextScale(float scale) { m_animatedTextScale = scale; }

    float getStaticTextScale() const { return m_staticTextScale; }
    void setStaticTextScale(float scale) { m_staticTextScale = scale; }

    bool isScaled() const { return g_window.getDisplayDensity() != 1.f; }

    bool isEncrypted() const {
#if ENABLE_ENCRYPTION == 1
        return true;
#else
        return false;
#endif
    }

    void setDrawEvents(const ApplicationDrawEventsPtr& drawEvents) { m_drawEvents = drawEvents; }
	
	ApplicationDrawEventsPtr getDrawEvents() const { return m_drawEvents; } // <--- Método agregado

	bool isLoadingAsyncTexture() const { // <-- Método agregado para verificar texturas asíncronas.
        return m_drawEvents && m_drawEvents->isLoadingAsyncTexture();
    }

protected:
    void resize(const Size& size);
    void inputEvent(const InputEvent& event);

private:
    bool m_onInputEvent{ false };
    bool m_optimize{ true };
    bool m_forceEffectOptimization{ true };
    bool m_drawEffectOnTop{ false };
    bool m_drawText{ true };

    float m_creatureInformationScale{ PlatformWindow::DEFAULT_DISPLAY_DENSITY };
    float m_animatedTextScale{ PlatformWindow::DEFAULT_DISPLAY_DENSITY };
    float m_staticTextScale{ PlatformWindow::DEFAULT_DISPLAY_DENSITY };

    AdaptativeFrameCounter m_mapProcessFrameCounter;
    AdaptativeFrameCounter m_graphicFrameCounter;

    ApplicationDrawEventsPtr m_drawEvents;
};

// Manteniendo extern para g_app como tipo GraphicalApplication
extern GraphicalApplication g_app;
extern std::unique_ptr<Painter> g_painter;
