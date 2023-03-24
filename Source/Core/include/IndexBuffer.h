//
// Created by dryerem19 on 21.10.22.
//

#pragma once

class IndexBuffer
{
private:
    uint32_t mIndicesBufferId;
    uint32_t mIndicesCount;
public:
    IndexBuffer() = default;
    ~IndexBuffer();

    inline uint32_t id() const { return mIndicesBufferId; }

    void Init(const uint32_t* src, const uint32_t count);
    void Bind() const;
    void Unbind() const;

    [[nodiscard]] inline uint32_t GetCount() const { return mIndicesCount; }
};