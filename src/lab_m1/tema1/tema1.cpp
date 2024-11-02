#include "lab_m1/tema1/tema1.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
= default;

Tema1::~Tema1()
= default;

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // Left bottom corner
    glm::vec3 corner = glm::vec3(0, -1, 0);

    // Initialize terrain
    terrainCoordinates = terrain.getTerrainCoordinates(resolution);

    for (int startIndex = 0; startIndex < terrainCoordinates.size() - 1; startIndex++) {
        glm::vec3 pointA = terrainCoordinates[startIndex];
        glm::vec3 pointB = terrainCoordinates[startIndex + 1];

        // Create standard square
        Mesh* square = objects::CreateSquare("square" + std::to_string(startIndex), corner, 1, glm::vec3(1, 0, 0), true);
        
        AddMeshToList(square);
    }

    // // Disk
    // Mesh* disk = objects::CreateDisk("disk", 400, 100, glm::vec3(0, -1, 0), glm::vec3(1, 1, 0), true);
    // AddMeshToList(disk);

    // // Half disk
    // Mesh* halfDisk = objects::CreateDiskHalf("halfDisk", 400, 360, glm::vec3(0, -1, 0), glm::vec3(1, 1, 0), true);
    // AddMeshToList(halfDisk);

    // // Trapezoid
    // Mesh* trapezoid = objects::CreateTrapezoid("trapezoid", glm::vec3(0, -1, 0), 400, 70, glm::vec3(0.796, 0.686, 0.533), true);
    // AddMeshToList(trapezoid);

    // Initialize tank model
    tanks::Tank *tank = tanks::Tank::CreateTankModel("tank", corner);
    
    tank->setTurretAngle(glm::radians(30.0f));
    tanks.push_back(tank);

    for (auto &tankPart : tank->getTankParts()) {
        AddMeshToList(tankPart);
    }
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    // Render terrain
    for (int startIndex = 0; startIndex < terrainCoordinates.size() - 1; startIndex++) {
        glm::vec3 pointA = terrainCoordinates[startIndex];
        glm::vec3 pointB = terrainCoordinates[startIndex + 1];

        modelMatrix = glm::mat3(1);

        // (1) Translation
        modelMatrix *= transform::Translate(pointA.x, pointA.y);

        // (2) Shearing
        float shearY = (pointB.y - pointA.y) / (pointB.x - pointA.x);
        modelMatrix *= transform::ShearOY(shearY);

        float segmentHeight = max(pointA.y, pointB.y);
        float segmentWidth = pointB.x - pointA.x;

        // (3) Scaling
        modelMatrix *= transform::Scale(segmentWidth, segmentHeight);

        RenderMesh2D(meshes["square" + std::to_string(startIndex)], shaders["VertexColor"], modelMatrix);
    }

    glClear(GL_DEPTH_BUFFER_BIT);

    // Render tanks
    for (auto &tank : tanks) {
        for (auto &tankPart : tank->getTankParts()) {
            modelMatrix = tank->getRenderMatrix(tankPart, tank->getTurretAngle());

            RenderMesh2D(tankPart, shaders["VertexColor"], modelMatrix);
            glClear(GL_DEPTH_BUFFER_BIT);
        }
    }

    // Render disk
    // glClear(GL_DEPTH_BUFFER_BIT);
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform::Translate(1000, 500);
    // RenderMesh2D(meshes["disk"], shaders["VertexColor"], modelMatrix);

    // Render trapezoid
    // glClear(GL_DEPTH_BUFFER_BIT);
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform::Translate(1000, 500);
    // RenderMesh2D(meshes["trapezoid"], shaders["VertexColor"], modelMatrix);

    // Render half disk
    // glClear(GL_DEPTH_BUFFER_BIT);
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform::Translate(1000, 500);
    // RenderMesh2D(meshes["halfDisk"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
