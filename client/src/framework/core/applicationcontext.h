#pragma once

class ApplicationContext {
public:
    ApplicationContext() = default;
    virtual ~ApplicationContext() = default;

    virtual void initialize() {}
    virtual void shutdown() {}
};