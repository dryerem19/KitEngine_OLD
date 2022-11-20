//
// Created by piokxix on 14.11.22.
//

#ifndef KITENGINE_FRAMEBUFFER_H
#define KITENGINE_FRAMEBUFFER_H


namespace Render
{
    class FrameBuffer
    {
    public:
        FrameBuffer();
        ~FrameBuffer();

        void Init(uint32_t width, uint32_t height);
        void Delete();

        void Bind() const;
        void Unbind() const;
        void GetFlipTexture();

        inline uint32_t GetTextureRenderID() const { return mTextureId; }
    private:
        uint32_t mFrameBufferId;
        uint32_t mTextureId;
        uint32_t mDepthId;

        /*uint32_t**/
    };
}

#endif //KITENGINE_FRAMEBUFFER_H
