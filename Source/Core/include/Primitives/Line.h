/**
 * @file Line.h
 * @author Денис Еременко (mamayma8@gmail.com)
 * @brief Линия
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright Денис Еременко (c) 2022
 * 
 */
#include "../VertexArray.h"
#include "../Shader.h"
#include "../ResourceManager.h"

class Line
{
private:
    glm::vec3 mStart;
    glm::vec3 mEnd;
    glm::vec3 mColor;
    glm::mat4 mMvp;
    std::shared_ptr<Shader> mShader;
    Render::VertexArray mVertexArray;
public:
    explicit Line(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color = glm::vec3(1.f, 0.f, 0.f));
    void SetColor(const glm::vec3& color);
    void SetMVP(const glm::mat4& mvp);
    void Draw() const;
};