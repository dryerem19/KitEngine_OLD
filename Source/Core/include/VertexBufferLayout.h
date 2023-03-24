//
// Created by dryerem19 on 10/24/22.
//

#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout
{
private:
    std::vector<VertexBufferAttribute> mAttributes;
    uint32_t mStride{};

public:
    explicit VertexBufferLayout() = default;
    VertexBufferLayout(const VertexBufferLayout&) = default;
    explicit VertexBufferLayout(std::vector<VertexBufferAttribute>  attributes);
    ~VertexBufferLayout() = default;

    void AddFloatElement(uint32_t count, bool normalized = false);

    [[nodiscard]] inline uint32_t GetStride() const { return mStride; }
    [[nodiscard]] inline const std::vector<VertexBufferAttribute>& GetAttributes() const { return mAttributes; }

};