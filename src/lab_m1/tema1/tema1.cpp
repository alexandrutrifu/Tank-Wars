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
    // TODO : refactor class and make methods return mesh array
    terrainCoordinates = terrain.getTerrainCoordinates(resolution);

    for (int startIndex = 0; startIndex < terrainCoordinates.size() - 1; startIndex++) {
        glm::vec3 *pointA = terrainCoordinates[startIndex];
        glm::vec3 *pointB = terrainCoordinates[startIndex + 1];

        // Create standard square
        Mesh* square = objects::CreateSquare("square" + std::to_string(startIndex), corner, 1, glm::vec3(0.94, 0.87, 0.71), true);
        
        AddMeshToList(square);
    }

    // Initialize tank models
    tanks::Tank *tankA = tanks::Tank::CreateTankModel("tankA", corner, tanks::tankA_body_colour,
            tanks::tankA_base_colour, tanks::tankA_turret_colour);
    tanks::Tank *tankB = tanks::Tank::CreateTankModel("tankB", corner, tanks::tankB_body_colour,
            tanks::tankB_base_colour, tanks::tankB_turret_colour);

    // Set tankA initial position
    tankA->setCenterPosition(500, 700);
    tankA->setTurretPosition(500, 700 + TANK_BASE_HEIGHT + DOME_CENTER_Y);
    tankA->setTurretAngle(glm::radians(30.0f));

    // Set tankB initial position
    tankB->setCenterPosition(2000, 700);
    tankB->setTurretPosition(1000, 700 + TANK_BASE_HEIGHT + DOME_CENTER_Y);
    tankB->setTurretAngle(glm::radians(150.0f));

    tanks.push_back(tankA);
    tanks.push_back(tankB);

    for (auto &tankPart : tankA->getTankParts()) {
        AddMeshToList(tankPart);
    }

    for (auto &tankPart : tankB->getTankParts()) {
        AddMeshToList(tankPart);
    }

    // Initialize projectile pool
    for (int index = 0; index < PROJECTILE_POOL_SIZE; index++) {
        projectile::Projectile *projectile = projectile::Projectile::CreateProjectileModel("projectile" + std::to_string(index));
        
        projectiles.push_back(projectile);
        AddMeshToList(projectile->getProjectileModel());
    }
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(skyBlue.x, skyBlue.y, skyBlue.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    // Render terrain
    for (int startIndex = 0; startIndex < terrainCoordinates.size() - 1; startIndex++) {
        glm::vec3 *pointA = terrainCoordinates[startIndex];
        glm::vec3 *pointB = terrainCoordinates[startIndex + 1];

        modelMatrix = glm::mat3(1);

        // (1) Translation
        modelMatrix *= transform::Translate(pointA->x, pointA->y);

        // (2) Shearing
        float shearY = (pointB->y - pointA->y) / (pointB->x - pointA->x);
        modelMatrix *= transform::ShearOY(shearY);

        float segmentHeight = max(pointA->y, pointB->y);
        float segmentWidth = pointB->x - pointA->x;

        // (3) Scaling
        modelMatrix *= transform::Scale(segmentWidth, segmentHeight);

        RenderMesh2D(meshes["square" + std::to_string(startIndex)], shaders["VertexColor"], modelMatrix);
    }

    glClear(GL_DEPTH_BUFFER_BIT);

    // Render tanks
    for (auto &tank : tanks) {
        for (auto &tankPart : tank->getTankParts()) {
            glm::mat3 modelMatrix = glm::mat3(1);

            modelMatrix *= tank->getRenderMatrix(tankPart, terrainCoordinates);

            RenderMesh2D(tankPart, shaders["VertexColor"], modelMatrix);
            glClear(GL_DEPTH_BUFFER_BIT);
        }
    }

    // Render projectiles
    for (int index = 0; index < PROJECTILE_POOL_SIZE; index++) {
        projectile::Projectile *projectile = projectiles[index];

        if (projectile->isOnScreen()) {
            printf("Projectile %d position: %f %f\n", index, projectile->getCenterPosition().x, projectile->getCenterPosition().y);

            // Handle collision with terrain
            float yUnderProjectile =
                terrain::Terrain::getCorrespondingY(terrainCoordinates,
                        terrain::Terrain::getTerrainSegmentIndex(projectile->getCenterPosition().x),
                        projectile->getCenterPosition().x);

            if (projectile->getCenterPosition().y - yUnderProjectile < COLLISION_THRESHOLD) {
                projectile->setOnScreen(false);
                projectile->setTimeToLive(PROJECTILE_TTL);

                // Destroy terrain
                terrain::Terrain::destroyTerrain(terrainCoordinates, projectile->getCenterPosition().x);

                continue;
            }

            // Decrement time to live
            if (projectile->getTimeToLive() > 0) {
                projectile->setTimeToLive(projectile->getTimeToLive() - deltaTimeSeconds);
            } else {
                projectile->setOnScreen(false);
                projectile->setTimeToLive(PROJECTILE_TTL);

                continue;
            }

            glm::mat3 modelMatrix = glm::mat3(1);

            modelMatrix *= projectile->getRenderMatrix(deltaTimeSeconds);

            RenderMesh2D(projectile->getProjectileModel(), shaders["VertexColor"], modelMatrix);
            glClear(GL_DEPTH_BUFFER_BIT);
        }
    }
}


void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // Tank A
    if (window->KeyHold(GLFW_KEY_S)) {
        // Rotate turret -> left
        tanks::Tank *tank = tanks[0];

        if (tank->getTurretAngle() < glm::radians(150.0f)) {
            tank->setTurretAngle(tank->getTurretAngle() + deltaTime);
        }
    }

    // Tank A
    if (window->KeyHold(GLFW_KEY_W)) {
        // Rotate turret -> right
        tanks::Tank *tank = tanks[0];

        if (tank->getTurretAngle() > glm::radians(30.0f)) {
            tank->setTurretAngle(tank->getTurretAngle() - deltaTime);
        }
    }

    // Tank B
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        // Rotate turret -> left
        tanks::Tank *tank = tanks[1];

        if (tank->getTurretAngle() < glm::radians(150.0f)) {
            tank->setTurretAngle(tank->getTurretAngle() + deltaTime);
        }
    }

    // Tank B
    if (window->KeyHold(GLFW_KEY_UP)) {
        // Rotate turret -> right
        tanks::Tank *tank = tanks[1];

        if (tank->getTurretAngle() > glm::radians(30.0f)) {
            tank->setTurretAngle(tank->getTurretAngle() - deltaTime);
        }
    }

    // Tank A
    if (window->KeyHold(GLFW_KEY_A)) {
        // Move tank -> left
        tanks::Tank *tank = tanks[0];
        glm::vec2 centerPosition = tank->getCenterPosition();
        glm::vec2 turretPosition = tank->getTurretPosition();

        tank->setCenterPosition(centerPosition.x - 100 * deltaTime, centerPosition.y);
        tank->setTurretPosition(turretPosition.x - 100 * deltaTime, turretPosition.y);
    }

    // Tank A
    if (window->KeyHold(GLFW_KEY_D)) {
        // Move tank -> right
        tanks::Tank *tank = tanks[0];
        glm::vec2 centerPosition = tank->getCenterPosition();
        glm::vec2 turretPosition = tank->getTurretPosition();

        tank->setCenterPosition(centerPosition.x + 100 * deltaTime, centerPosition.y);
        tank->setTurretPosition(turretPosition.x + 100 * deltaTime, turretPosition.y);
    }

    // Tank B
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        // Move tank -> left
        tanks::Tank *tank = tanks[1];
        glm::vec2 centerPosition = tank->getCenterPosition();
        glm::vec2 turretPosition = tank->getTurretPosition();

        tank->setCenterPosition(centerPosition.x - 100 * deltaTime, centerPosition.y);
        tank->setTurretPosition(turretPosition.x - 100 * deltaTime, turretPosition.y);
    }

    // Tank B
    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        // Move tank -> right
        tanks::Tank *tank = tanks[1];
        glm::vec2 centerPosition = tank->getCenterPosition();
        glm::vec2 turretPosition = tank->getTurretPosition();

        tank->setCenterPosition(centerPosition.x + 100 * deltaTime, centerPosition.y);
        tank->setTurretPosition(turretPosition.x + 100 * deltaTime, turretPosition.y);
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Projectiles for tank A
    if (key == GLFW_KEY_SPACE) {
        // Fire projectile
        for (int index = 0; index < PROJECTILE_POOL_SIZE; index++) {
            projectile::Projectile *projectile = projectiles[index];

            if (!projectile->isOnScreen()) {
                projectile->setOnScreen(true);
                projectile->setTimeToLive(PROJECTILE_TTL);

                tanks::Tank *tank = tanks[0];
                glm::vec2 turretEndPosition = tank->computeProjectileStartPos();

                projectile->setCenterPosition(turretEndPosition.x, turretEndPosition.y);
                projectile->setMovementVector(glm::vec2(INITIAL_MAGNITUDE * cos(tank->getTurretAngle() + tank->getTankAngle()),
                                                        INITIAL_MAGNITUDE * sin(tank->getTurretAngle() + tank->getTankAngle())));

                break;
            }
        }
    }

    // Projectiles for tank B
    if (key == GLFW_KEY_ENTER) {
        // Fire projectile
        for (int index = 0; index < PROJECTILE_POOL_SIZE; index++) {
            projectile::Projectile *projectile = projectiles[index];

            if (!projectile->isOnScreen()) {
                projectile->setOnScreen(true);
                projectile->setTimeToLive(PROJECTILE_TTL);

                tanks::Tank *tank = tanks[1];
                glm::vec2 turretEndPosition = tank->computeProjectileStartPos();

                projectile->setCenterPosition(turretEndPosition.x, turretEndPosition.y);
                projectile->setMovementVector(glm::vec2(INITIAL_MAGNITUDE * cos(tank->getTurretAngle() + tank->getTankAngle()),
                                                        INITIAL_MAGNITUDE * sin(tank->getTurretAngle() + tank->getTankAngle())));

                break;
            }
        }
    }
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
