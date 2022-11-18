#pragma once
#include "Event.h"

namespace Core
{
    class FrameBufferResizeEvent : public Event
    {
    private:
        int mWidth, mHeight;
    public:
        explicit FrameBufferResizeEvent(int width, int height)
            : Event("FrameBufferResizeEvent", EventType::FrameBufferResizeEvent),
            mWidth(width), mHeight(height) { }

        inline int GetWidth() const { return mWidth; }
        inline int GetHeight() const { return mHeight; }    

        std::string ToString() const override
        {
            std::stringstream format;
            format << "[" << mName << "] : " << "{ width: " << std::to_string(mWidth) 
                << ", height: " << std::to_string(mHeight) << " }";

            return format.str();     
        }            
    };
}