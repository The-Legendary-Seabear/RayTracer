#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Random.h"
#include "Material.h"

#include <iostream>

int main() {
    constexpr int SCREEN_WIDTH = 800;
    constexpr int SCREEN_HEIGHT = 600;

    // create renderer
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

    Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    float aspectRatio = (float)framebuffer.width / framebuffer.height;
    Camera camera(70.0f, aspectRatio);
    camera.SetView({ 0, 2, 5 }, { 0, 0, 0 });

    Scene scene;

    // create materials
    auto red = std::make_shared<Lambertian>(color3_t{ 1.0f, 0.0f, 0.0f });
    auto green = std::make_shared<Lambertian>(color3_t{ 0.0f, 1.0f, 0.0f });
    auto blue = std::make_shared<Lambertian>(color3_t{ 0.0f, 0.0f, 1.0f });
    auto light = std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 10.0f);
    auto metal = std::make_shared<Metal>(color3_t{ 1.0f, 1.0f, 1.0f }, 0.0f);

    std::shared_ptr<Material> materials[] = { red, green, blue, metal };

    // place random spheres in the scene
    for (int i = 0; i < 15; i++) {

        float radius = random::getReal(0.2f, 0.5f);
        glm::vec3 position = random::getReal(
            glm::vec3{ -3.0f, radius, -3.0f },
            glm::vec3{ 3.0f, radius,  3.0f }
        );

        auto sphere = std::make_unique<Sphere>(
            Transform{ position },
            radius,
            materials[random::getInt(4)]
        );

        scene.AddObject(std::move(sphere));
    }

    // place infinite plane in the scene with gray material
    auto gray = std::make_shared<Lambertian>(color3_t{ 0.2f, 0.2f, 0.2f });
    auto plane = std::make_unique<Plane>(
        Transform{ glm::vec3{ 0.0f, 0.0f, 0.0f } },
        gray
    );
    scene.AddObject(std::move(plane));


    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) quit = true;
            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.scancode == SDL_SCANCODE_ESCAPE) quit = true;
        }

        framebuffer.Clear({ 0, 0, 0, 255 });
        scene.Render(framebuffer, camera, 10);
        framebuffer.Update();

        renderer.CopyFramebuffer(framebuffer);
        renderer.Show();
    }
}
