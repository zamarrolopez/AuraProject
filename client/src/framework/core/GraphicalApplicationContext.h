#pragma once

#include <memory>
#include "applicationcontext.h"

class ApplicationDrawEvents;

using ApplicationDrawEventsPtr = std::shared_ptr<ApplicationDrawEvents>;

class GraphicalApplicationContext : public ApplicationContext {
public:
    GraphicalApplicationContext(int spriteSize, ApplicationDrawEventsPtr drawEvents)
        : m_spriteSize(spriteSize), m_drawEvents(drawEvents) {}

    int getSpriteSize() const { return m_spriteSize; }
    ApplicationDrawEventsPtr getDrawEvents() const { return m_drawEvents; }

private:
    int m_spriteSize;
    ApplicationDrawEventsPtr m_drawEvents;
};
