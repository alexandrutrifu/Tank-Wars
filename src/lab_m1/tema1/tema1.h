#ifndef TEMA1_H
#define TEMA1_H

#pragma once

#include "components/simple_scene.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform.h"
#include "lab_m1/tema1/terrain.h"
#include "lab_m1/tema1/objects/objects.h"
#include "lab_m1/tema1/tank/tank.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1() override;

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        terrain::Terrain terrain{};
        float cx{}, cy{};
        glm::mat3 modelMatrix{};
        float translateX{}, translateY{};
        float scaleX{}, scaleY{};
        float scaleCar1{}, scaleCar2{};
        float angularStep{};

        std::vector<glm::vec3> terrainCoordinates{};

        std::vector<tanks::Tank *> tanks{};

    };
}   // namespace m1


#endif
