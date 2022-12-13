/**
 * @file WindowCloseEvent.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Event.h"

namespace Core
{
    class WindowCloseEvent final : public Event
    {
    public:
        bool close;
    public:
        explicit WindowCloseEvent()
            : Event("WindowCloseEvent", EventType::WindowCloseEvent),
            close(true) { }

        std::string ToString() const override final
        {
            std::stringstream format;
            format << "[" << mName << "] : " << "{ close: " << (close == true ? "true" : "false") << "}\n";

            return format.str();     
        }            
    };
}