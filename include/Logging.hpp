#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include "Utils.hpp"

namespace lib
{
    namespace log
    {
        struct ChannelState
        {
            bool enabled;
            bool flush;
            std::string prefix;
            std::string suffix;

            inline ChannelState(
                bool enabled,
                std::string prefix,
                std::string suffix,
                bool flush)
                : enabled(enabled),
                  flush(flush),
                  prefix(prefix),
                  suffix(suffix) {}
        };

        struct State
        {
            ChannelState debug;
            ChannelState info;
            ChannelState warning;
            ChannelState error;

            inline State(
                ChannelState debug,
                ChannelState info,
                ChannelState warning,
                ChannelState error)
                : debug(debug),
                  info(info),
                  warning(warning),
                  error(error)
            {
            }
        };

        State &GetState();

        void Debug(const std::string &text);
        void Info(const std::string &text);
        void Warning(const std::string &text);
        void Error(const std::string &text);

        template <class TFirst, class... TArgs>
        void Debug(const std::string &format, const TFirst &first, const TArgs &... args)
        {
            if constexpr (IsDebug)
            {
                if (!lib::log::GetState().debug.enabled)
                {
                    return;
                }

                lib::log::Debug(Format(format, first, args...));
            }
        }

        template <class TFirst, class... TArgs>
        void Info(const std::string &format, const TFirst &first, const TArgs &... args)
        {
            if (!lib::log::GetState().info.enabled)
            {
                return;
            }

            lib::log::Info(Format(format, first, args...));
        }

        template <class TFirst, class... TArgs>
        void Warning(const std::string &format, const TFirst &first, const TArgs &... args)
        {
            if (!lib::log::GetState().warning.enabled)
            {
                return;
            }

            lib::log::Warning(Format(format, first, args...));
        }

        template <class TFirst, class... TArgs>
        void Error(const std::string &format, const TFirst &first, const TArgs &... args)
        {
            if (!lib::log::GetState().error.enabled)
            {
                return;
            }

            lib::log::Error(Format(format, first, args...));
        }
    } // namespace log
} // namespace lib