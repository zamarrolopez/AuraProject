/*
 * Copyright (c) 2010-2022 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include "declarations.h"
#include "hardwarebuffer.h"

class VertexArray
{
public:
    static constexpr int CACHE_MIN_VERTICES_COUNT = 42;

    VertexArray(const size_t size = 64) { m_buffer.reserve(size); }

    ~VertexArray()
    {
        if (m_hardwareBuffer)
            delete m_hardwareBuffer;
    }

    void addTriangle(const Point& a, const Point& b, const Point& c)
    {
        int arr[] = {
            a.x, a.y,
            b.x, b.y,
            c.x, c.y
        };

        const size_t size = sizeof(arr) / sizeof(int);
        m_buffer.insert(m_buffer.end(), &arr[0], &arr[size]);
    }

    void addRect(const Rect& rect)
    {
        const float top = rect.top();
        const float right = rect.right() + 1;
        const float bottom = rect.bottom() + 1;
        const float left = rect.left();

        float arr[] = {
            left, top,
            right, top,
            left, bottom,
            left, bottom,
            right, top,
            right, bottom
        };

        const size_t size = sizeof(arr) / sizeof(float);
        m_buffer.insert(m_buffer.end(), &arr[0], &arr[size]);
    }

    void addRect(const RectF& rect)
    {
        const float top = rect.top();
        const float right = rect.right() + 1.f;
        const float bottom = rect.bottom() + 1.f;
        const float left = rect.left();

        float arr[] = {
            left, top,
            right, top,
            left, bottom,
            left, bottom,
            right, top,
            right, bottom
        };

        const size_t size = sizeof(arr) / sizeof(float);
        m_buffer.insert(m_buffer.end(), &arr[0], &arr[size]);
    }

    void addQuad(const Rect& rect)
    {
        const float top = rect.top();
        const float right = rect.right() + 1;
        const float bottom = rect.bottom() + 1;
        const float left = rect.left();

        float arr[] = {
            left, top,
            right, top,
            left, bottom,
            left, bottom,
            right, top,
            right, bottom
        };

        const size_t size = sizeof(arr) / sizeof(float);
        m_buffer.insert(m_buffer.end(), &arr[0], &arr[size]);
    }

    void addUpsideDownQuad(const Rect& rect)
    {
        const float top = rect.top();
        const float right = rect.right() + 1;
        const float bottom = rect.bottom() + 1;
        const float left = rect.left();

        float arr[] = {
            left, bottom,
            right, bottom,
            left, top,
            right, top,
        };

        const size_t size = sizeof(arr) / sizeof(float);
        m_buffer.insert(m_buffer.end(), &arr[0], &arr[size]);
    }

    void addUpsideDownRect(const Rect& rect)
    {
        const float top = rect.top();
        const float right = rect.right() + 1;
        const float bottom = rect.bottom() + 1;
        const float left = rect.left();

        float arr[] = {
            left, bottom,
            right, bottom,
            left, bottom,
            left, top,
            right, bottom,
            right, top
        };

        const size_t size = sizeof(arr) / sizeof(float);
        m_buffer.insert(m_buffer.end(), &arr[0], &arr[size]);
    }

    void append(const VertexArray* buffer)
    {
        m_buffer.insert(m_buffer.end(), buffer->m_buffer.begin(), buffer->m_buffer.end());
    }

    void clear()
    {
        m_buffer.clear();
        m_cached = false;
    }

    const float* vertices() const { return m_buffer.data(); }
    int vertexCount() const { return m_buffer.size() / 2; }
    int size() const { return m_buffer.size(); }

    // cache
    void cache()
    {
        if (m_cached || m_buffer.size() < CACHE_MIN_VERTICES_COUNT) return;

        if (!m_hardwareBuffer)
            m_hardwareBuffer = new HardwareBuffer(HardwareBuffer::Type::VERTEX_BUFFER);

        m_hardwareBuffer->bind();
        m_hardwareBuffer->write(m_buffer.data(), m_buffer.size() * sizeof(float), HardwareBuffer::UsagePattern::DYNAMIC_DRAW);

        m_cached = true;
    }

    bool isCached() const { return m_cached; }
    HardwareBuffer* getHardwareCache() const { return m_hardwareBuffer; }

private:
    bool m_cached{ false };
    std::vector<float> m_buffer;
    HardwareBuffer* m_hardwareBuffer = nullptr;
};