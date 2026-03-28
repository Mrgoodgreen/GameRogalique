#pragma once
#include <memory>
#include <vector>

namespace XYZRoguelike {
    class Player;
    class Enemy;
    class Wall;
    class Floor;

    class ILevelSegment {
    public:
        virtual ~ILevelSegment() = default;
        virtual void Build(float offsetX, float offsetY) = 0;
        virtual bool IsCleared() const = 0;
        virtual void OpenDoor() = 0;
        virtual bool IsDoorOpened() const = 0;
    };
}
