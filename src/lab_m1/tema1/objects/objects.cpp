#include "objects.h"


const glm::vec3 tank_base_colour = glm::vec3(0.451, 0.392, 0.306);
const glm::vec3 tank_body_colour = glm::vec3(0.796, 0.686, 0.533);
const glm::vec3 tank_turret_colour = glm::vec3(0.227, 0.227, 0.235);

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

Mesh *objects::CreateTank(const std::string &name, glm::vec3 leftBottomCorner) {
    /* Vertices 0, 1, 2, 3 -> tank body */
    /* Vertices 4, 5, 6, 7 -> tank base */
    /* Vertices 8 .. 8 + vertexCount -> tank dome */
    std::vector<VertexFormat> vertices =
        {
            // Tank body
            VertexFormat(leftBottomCorner, tank_body_colour),
            VertexFormat(leftBottomCorner + glm::vec3(TANK_BODY_LENGTH, 0, 0), tank_body_colour),
            VertexFormat(leftBottomCorner + glm::vec3(TANK_BODY_LENGTH - TANK_BODY_HEIGHT * 0.6, TANK_BODY_HEIGHT, 0), tank_body_colour),
            VertexFormat(leftBottomCorner + glm::vec3(TANK_BODY_HEIGHT * 0.6, TANK_BODY_HEIGHT, 0), tank_body_colour),
            // Tank base
            VertexFormat(leftBottomCorner + glm::vec3(TANK_BASE_START_X, 0, 0),
                         tank_base_colour),
            VertexFormat(leftBottomCorner + glm::vec3(TANK_BASE_START_X +
                                                          TANK_BASE_HEIGHT * 0.6,
                                                      -TANK_BASE_HEIGHT, 0),
                         tank_base_colour),
            VertexFormat(leftBottomCorner + glm::vec3(TANK_BASE_START_X +
                                                          TANK_BASE_LENGTH - TANK_BASE_HEIGHT * 0.6,
                                                      -TANK_BASE_HEIGHT, 0),
                         tank_base_colour),
            VertexFormat(leftBottomCorner + glm::vec3(TANK_BASE_START_X +
                                                          TANK_BASE_LENGTH,
                                                      0, 0), tank_base_colour),
        };

    // Tank dome
    glm::vec3 domeCenter = leftBottomCorner + glm::vec3(DOME_CENTER_X, DOME_CENTER_Y, 0);
    float theta = glm::radians(180.0f / DISK_VERTEX_COUNT);

    // Generate vertex coordinates
    for (int index = 0; index < DISK_VERTEX_COUNT; index++) {
        float x = TANK_DOME_RADIUS * cos(index * theta);
        float y = TANK_DOME_RADIUS * sin(index * theta);
        glm::vec3 vertex = glm::vec3(x, y, 0);

        vertices.push_back(VertexFormat(domeCenter + vertex, tank_body_colour));
    }

    std::vector<unsigned int> indices;

    // Specify triangle indices
    // Tank body
    {
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(0);
        indices.push_back(2);
    }

    // Tank base
    {
        indices.push_back(4);
        indices.push_back(5);
        indices.push_back(6);
        indices.push_back(7);
        indices.push_back(4);
        indices.push_back(6);
    }

    // Tank dome
    {
        for (int index = 9; index < 8 + DISK_VERTEX_COUNT - 1; index++) {
            indices.push_back(8);
            indices.push_back(index);
            indices.push_back(index + 1);
        }
    }

    Mesh *tank = new Mesh(name);
    tank->InitFromData(vertices, indices);

    return tank;
}
