#pragma once

#include<vector>
#include"GLM.h"
#include"glad/glad.h"
#include<GLFW\glfw3.h>


// Forward Declartion
struct SMeshData;
struct SVertex;

class CMeshFilter
{
public:
    enum class RENDER_TYPE {
        TRIANGLES = GL_TRIANGLES,
        TRIANGLE_STRIP = GL_TRIANGLE_STRIP
    };
public:
    static CMeshFilter* CreateMesh(const SMeshData & pMeshData);
    void Destroy();
    void Render();
protected:
    CMeshFilter();
    bool LoadPrivate(const SMeshData & pMeshData);
private:
    unsigned int m_idMesh;
    unsigned int m_nIndices;
    RENDER_TYPE m_RenderType;
};

struct SVertex
{
    glm::vec3 position; // 3 floats = 3 * 4 bytes = 12 bytes
    glm::vec3 normal; // 3 floats = 3 * 4 bytes = 12 bytes
    glm::vec2 uv; // 2 floats = 2 * 4 bytes = 8 bytes
    int colorID; // 4 bytes

    SVertex()
    {
        position = glm::zero<glm::vec3>();
        normal = glm::zero<glm::vec3>();
        uv = glm::zero<glm::vec2>();
        colorID = 0;
    }

    SVertex(glm::vec3 _position, glm::vec3 _normal, glm::vec2 _uv, int _colorID)
    {
        position = _position;
        normal = _normal;
        uv = _uv;
        colorID = _colorID;
    }
};

struct SMeshData
{
    enum class MESH_TYPE {
        PLANE_MESH,
        CUBE_MESH
    };
    CMeshFilter::RENDER_TYPE    renderType;
    std::vector<SVertex>        aVertices;
    std::vector<unsigned int>   aIndices;

    SMeshData(MESH_TYPE meshType)
    {
        switch (meshType)
        {
        case MESH_TYPE::PLANE_MESH:
            {
                std::vector<SVertex> vertices = {
                    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {-0.01f, -0.01f}, {0}},  // left bottom
                    {{-0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {-0.01f, 1.01f}, {0}},   // left top
                    {{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.01f, -0.01f}, {0}},   // right bottom
                    {{ 0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.01f, 1.01f}, {0}}     // right top
                };
                std::vector<unsigned int> indices = { 0, 2, 1, 3 };  // 
                aVertices = vertices;
                aIndices = indices;
                renderType = CMeshFilter::RENDER_TYPE::TRIANGLE_STRIP;
                break;
            }
        case MESH_TYPE::CUBE_MESH:
            {
                std::vector<SVertex> vertices = {
                    // Front
                    {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {0}},
                    {{-1.0f,  1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {0}},
                    {{ 1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {0}},
                    {{ 1.0f,  1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {0}},
                };
                std::vector<unsigned int> indices = { 0, 2, 1, 2, 3, 1 };
                struct SAngle
                {
                    float fAngle;
                    glm::vec3 vAxis;
                };
                std::vector<SAngle> aAngles = {
                    {{0.0f}, {1.0f, 0.0f, 0.0f}},    // Front
                    {{90.0f}, {1.0f, 0.0f, 0.0f}},   // Top
                    {{180.0f}, {1.0f, 0.0f, 0.0f}},  // Back
                    {{90.0f}, {-1.0f, 0.0f, 0.0f}},  // Bottom
                    {{90.0f}, {0.0f, 1.0f, 0.0f}},   // left
                    {{90.0f}, {0.0f, -1.0f, 0.0f}}   // right
                };

                unsigned int face = 0;
                for (const SAngle& angle : aAngles)
                {
                    glm::mat4 matRotate = glm::mat4(1.0f);
                    matRotate = glm::rotate(matRotate, glm::radians(angle.fAngle), angle.vAxis);
                    for (SVertex vertex : vertices)
                    {
                        vertex.position = matRotate * glm::vec4(vertex.position, 1.0f);
                        vertex.normal = matRotate * glm::vec4(vertex.normal, 1.0f);
                        vertex.colorID = face;
                        aVertices.push_back(vertex);
                    }
                    aIndices.push_back(indices[0] + 4 * face);
                    aIndices.push_back(indices[1] + 4 * face);
                    aIndices.push_back(indices[2] + 4 * face);
                    aIndices.push_back(indices[3] + 4 * face);
                    aIndices.push_back(indices[4] + 4 * face);
                    aIndices.push_back(indices[5] + 4 * face);
                    face++;
                }
                renderType = CMeshFilter::RENDER_TYPE::TRIANGLES;
                break;
            }
        }
    }

};