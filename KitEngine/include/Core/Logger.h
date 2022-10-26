//
// Created by dryerem19 on 10/26/22.
//

#pragma once
#include <string>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>

namespace KitEngine::Core
{
    class Log
    {
    public:
        static void ShowMessage(const std::string& message)
        {
            BOOST_LOG_TRIVIAL(debug) << message;
        }
    };
}