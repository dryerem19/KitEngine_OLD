#pragma once

namespace Render
{
    struct KitTag
    {
        std::string Tag;

        KitTag() = default;
        KitTag(const std::string& tag)
            : Tag(tag) {}
        KitTag(const KitTag&) = default;
    };
}