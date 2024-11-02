#include "objects.h"


Mesh *objects::CreateSquare(const std::string &name, glm::vec3 leftBottomCorner,
                float length, glm::vec3 color, bool fill) {
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh *objects::CreateDisk(const std::string &name, float radius, int vertexCount,
                glm::vec3 leftBottomCorner, glm::vec3 color, bool fill) {
    float theta = glm::radians(360.0f / vertexCount);

    std::vector<VertexFormat> vertices;

    // Generate vertex coordinates
    for (int index = 0; index < vertexCount; index++) {
        float x = radius * cos(index * theta);
        float y = radius * sin(index * theta);
        glm::vec3 vertex = glm::vec3(x, y, 0);

        vertices.push_back(VertexFormat(leftBottomCorner + vertex, color));
    }

    Mesh *disk = new Mesh(name);
    std::vector<unsigned int> indices{};

    if (fill) {
        // Specify triangle indices
        for (int index = 1; index < vertexCount - 1; index++) {
            indices.push_back(0);
            indices.push_back(index);
            indices.push_back(index + 1);
        }
    }

    disk->InitFromData(vertices, indices);
    return disk;
}

Mesh *objects::CreateDiskHalf(const std::string &name, float radius, int vertexCount,
                glm::vec3 leftBottomCorner, glm::vec3 color, bool fill) {
    float theta = glm::radians(180.0f / vertexCount);

    std::vector<VertexFormat> vertices;

    // Generate vertex coordinates
    for (int index = 0; index < vertexCount; index++) {
        float x = radius * cos(index * theta);
        float y = radius * sin(index * theta);
        glm::vec3 vertex = glm::vec3(x, y, 0);

        vertices.push_back(VertexFormat(leftBottomCorner + vertex, color));
    }

    Mesh *diskHalf = new Mesh(name);
    std::vector<unsigned int> indices{};

    if (fill) {
        // Specify triangle indices
        for (int index = 1; index < vertexCount - 1; index++) {
            indices.push_back(0);
            indices.push_back(index);
            indices.push_back(index + 1 % vertexCount);
        }
    }

    diskHalf->InitFromData(vertices, indices);
    return diskHalf;
}

Mesh *objects::CreateTrapezoid(const std::string &name, glm::vec3 leftBottomCorner,
                float length, float height, glm::vec3 color, bool fill) {
    // height = length / 8;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(leftBottomCorner, color),
        VertexFormat(leftBottomCorner + glm::vec3(length, 0, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(length - height * 0.6, height, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(height * 0.6, height, 0), color)
    };

    Mesh *trapezoid = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2, 3};

    if (!fill) {
        trapezoid->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    trapezoid->InitFromData(vertices, indices);
    return trapezoid;
}
