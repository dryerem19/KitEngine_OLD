//
// Created by dryerem19 on 21.10.22.
//

#pragma once

namespace KitEngine::Graphics
{
    class IndexBuffer
    {
    private:
        unsigned int mIndicesBufferId;
        unsigned int mIndicesCount;
    public:
        IndexBuffer(const unsigned int* src, unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        [[nodiscard]] inline unsigned int GetCount() const { return mIndicesCount; }
    };
}