#pragma once

#include "declarations.h"

#include <framework/core/declarations.h>
#include <framework/core/timer.h>
#include "protobuf/appearances.pb.h"

#ifdef APPEARANCES_PROTOBUF_GENERATED

using namespace otclient::protobuf;
#endif

enum AnimationPhase : int16_t {
    AnimPhaseAutomatic = -1,
    AnimPhaseRandom = 254,
    AnimPhaseAsync = 255,
};

enum AnimationDirection : uint8_t {
    AnimDirForward = 0,
    AnimDirBackward = 1
};

class Animator : public std::enable_shared_from_this<Animator> {
public:
    void unserializeAppearance(const appearances::SpriteAnimation& animation);
    void unserialize(int animationPhases, const FileStreamPtr& fin);
    void serialize(const FileStreamPtr& fin) const;
    void setPhase(int phase);
    void resetAnimation();

    int getPhase();
    int getPhaseAt(Timer& timer, float durationFactor = 1.f) const;
    int getStartPhase() const;
    int getAnimationPhases() const { return m_animationPhases; }
    int getAverageDuration() const { return getTotalDuration() / getAnimationPhases(); }

    uint16_t getMinDuration() const { return m_minDuration; }

    bool isAsync() const { return m_async; }
    bool isComplete() const { return m_isComplete; }

    uint16_t getTotalDuration() const;

private:
    int getPingPongPhase();
    int getLoopPhase();
    int getPhaseDuration(int phase) const;

    void calculateSynchronous();

    int8_t m_startPhase{ 0 };
    int8_t m_loopCount{ 0 };

    uint8_t m_currentLoop{ 0 };
    uint8_t m_phase{ 0 };

    uint16_t m_minDuration{ 0 };
    uint16_t m_currentDuration{ 0 };
    uint16_t m_animationPhases{ 0 };

    bool m_isComplete{ false };
    bool m_async{ false };

    std::vector<std::pair<uint16_t, uint16_t>> m_phaseDurations;
    AnimationDirection m_currentDirection{ AnimDirForward };
    ticks_t m_lastPhaseTicks{ 0 };
};
