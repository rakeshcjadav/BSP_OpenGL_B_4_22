#include"MeshFilter.h"

CMeshFilter* CMeshFilter::CreateMesh(const SMeshData & pMeshData)
{
    CMeshFilter* pMesh = new CMeshFilter();
    if (!pMesh->LoadPrivate(pMeshData))
    {
        pMesh->Destroy();
        pMesh = nullptr;
    }
    return pMesh;
}

void CMeshFilter::Destroy()
{
    delete this;
}

void CMeshFilter::Render()
{
    glBindVertexArray(m_idMesh);
    glDrawElements((GLenum)m_RenderType, m_nIndices, GL_UNSIGNED_INT, 0); // If you have EBOs defined
}

CMeshFilter::CMeshFilter()
{

}

bool CMeshFilter::LoadPrivate(const SMeshData & pMeshData)
{
    glGenVertexArrays(1, &m_idMesh);
    glBindVertexArray(m_idMesh);
    {
        // Creating Vertex Buffer Object
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex) * pMeshData.aVertices.size(), &(pMeshData.aVertices.front()), GL_STATIC_DRAW);

        // location 0, read 3 GL_FLOAT and jump(stride) 3 * sizeof(float) and offset is 0
        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);

        // Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)(sizeof(glm::vec3)));
        glEnableVertexAttribArray(1);

        // UV : Texture Coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)(2*sizeof(glm::vec3)));
        glEnableVertexAttribArray(2);

        // Color ID
        glVertexAttribIPointer(3, 1, GL_INT, sizeof(SVertex), (void*)(2*sizeof(glm::vec3) + sizeof(glm::vec2)));
        glEnableVertexAttribArray(3);

        // location 2, read 3 GL_FLOAT and jump(stride) 4 * sizeof(float) and offset is 1
        // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(1 * sizeof(float)));
        // glEnableVertexAttribArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pMeshData.aIndices.size(), &(pMeshData.aIndices.front()), GL_STATIC_DRAW);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
    m_nIndices = pMeshData.aIndices.size();
    m_RenderType = pMeshData.renderType;
    return true;
}