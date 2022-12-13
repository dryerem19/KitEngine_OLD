#pragma once

namespace Core
{
    enum class EventType : int8_t
    {
        None = 0,
        WindowResizeEvent,
        FrameBufferResizeEvent,
        WindowCloseEvent
    };

    class Event
    {
    protected:
        EventType mType;
        std::string mName;
        Event(std::string name, EventType type)
            : mName(std::move(name)), mType(type) { }
    public:
        virtual ~Event() = default;
        
        inline std::string GetName() const { return mName; }
        inline EventType GetType() const { return mType; }
        virtual std::string ToString() const = 0;
    };
}