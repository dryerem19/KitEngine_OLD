#pragma once
#include <string>

namespace LevelEditor
{
    enum class EventType
    {
        None = -1,
        
        SelectGizmo,
    };

    class Event
    {
    protected:
        std::string mName;
        EventType mType;
        Event(std::string name, EventType type) : mName(name), mType(type) { }

    public:
        inline EventType GetType() const { return mType; }
        virtual std::string ToString() const = 0;
        virtual ~Event() = default;
    };
}