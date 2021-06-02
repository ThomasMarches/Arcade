/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** FrameRate.hpp header
*/

#ifndef FRAMERATE_H_
#define FRAMERATE_H_

#include <chrono>

#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>

namespace arcade
{
    class FrameRate
    {
    public:
        FrameRate(float fps = 0)
        {
            m_fps = fps;
            m_targetTime = 1000 / m_fps;
            m_deltaTime = 0;
            reset();
        }

        ~FrameRate() {}

        void reset()
        {
            m_lastUpdate = std::chrono::steady_clock::now();
        }

        float getFPS() const { return m_fps; }
        void setFPS(float fps) { m_fps = fps; }

        float getDeltaTime()
        {
            return m_deltaTime + getElapsedTime(m_lastUpdate);
        }

        float getElapsedTime(std::chrono::steady_clock::time_point previousTime) const
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(
                       std::chrono::steady_clock::now() - previousTime)
                       .count() /
                   1000000.0f;
        }

        void synchronize()
        {
            float elapsed = getElapsedTime(m_lastUpdate) * 1000.0f;
            float msTooSleep = m_targetTime - elapsed;

            m_lastUpdate = std::chrono::steady_clock::now();
            if (msTooSleep > 0)
            {
#if defined(_WIN32)
                Sleep(msTooSleep);
#else
                usleep(msTooSleep * 1000);
#endif
            }
            else
                msTooSleep = 0;
            m_deltaTime = (elapsed + msTooSleep) / 1000.0f;
        }

    private:
        float m_fps;
        float m_targetTime;

        std::chrono::steady_clock::time_point m_lastUpdate;
        float m_deltaTime; // in seconds
    };
}

#endif /* !FRAMERATE_H_ */