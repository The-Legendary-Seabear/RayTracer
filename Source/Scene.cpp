#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"
#include "Random.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples) {
	// trace ray for every framebuffer pixel
	for (int y = 0; y < framebuffer.height; y++) {
		for (int x = 0; x < framebuffer.width; x++) {
			// set pixel (x,y) coordinates)
			glm::vec2 pixel = {(float)x , (float)y};// set pixel x and y
				// normalize (0 <-> 1) the pixel value (pixel / { framebuffer.width, framebuffer.height }
			glm::vec2 point = pixel / glm::vec2{ framebuffer.width, framebuffer.height };
				// flip the y value (bottom = 0, top = 1)
				point.y = 1 - point.y;

			// get ray from camera
				ray_t ray = camera.GetRay(point);// call GetRay() from camera
				// trace ray
				color3_t color = Trace(ray, 0.001f, 1000.0f, maxDepth);// class Trace with ray;

				// draw pixel (x,y) to frame buffer using color (make sure to convert color)
				SDL_Color sdlColor;
				sdlColor.r = (Uint8)(glm::clamp(color.r, 0.0f, 1.0f) * 255);
				sdlColor.g = (Uint8)(glm::clamp(color.g, 0.0f, 1.0f) * 255);
				sdlColor.b = (Uint8)(glm::clamp(color.b, 0.0f, 1.0f) * 255);
				sdlColor.a = 255;

				framebuffer.DrawPoint(x, y, sdlColor);
		}
	}
}



void Scene::AddObject(std::unique_ptr<class Object> object) {
	// add object to objects vector
	objects.push_back(std::move(object));
	
}


color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, int maxDepth) {

	// reached max depth (bounce) return black color
	if (maxDepth == 0) return color3_t{ 0, 0, 0 };

		bool rayHit = false;
	float closestDistance = maxDistance;
	raycastHit_t raycastHit;

	// check if scene objects are hit by the ray
	for (auto& object : objects) {
		// !! get nearest hit object (already completed in previous assignment) !!
		if (object->Hit(ray, minDistance, closestDistance, raycastHit)) {
			rayHit = true;
			// set closest distance to the raycast hit distance (only hit objects closer than closest distance)
			closestDistance = raycastHit.distance;// raycast hit distance;
	}

	// check if ray hit object
	if (rayHit) {
		color3_t attenuation;
		ray_t scattered;
		// get raycast hit matereial, get material color and scattered ray 
		if (raycastHit.material->Scatter(ray, raycastHit, attenuation, scattered)) {
			// trace scattered ray, final color will be the product of all the material colors
			return attenuation * Trace(scattered, minDistance, maxDistance, maxDepth - 1);//<reduce max depth by 1>);
		}
		else {
			return raycastHit.material->GetEmissive();
		}
	}

	// no ray hit, draw sky colors based on the ray y position
	// !! already completed in previous assignment !!
	// draw sky colors based on the ray y position
	glm::vec3 direction = glm::normalize(ray.direction);// normalize ray direction
		// shift direction y from -1 <-> 1 to 0 <-> 1
		float t = (direction.y + 1.0f) * 0.5f;

		// interpolate between sky bottom (0) to sky top (1)
		// mix is the same as lerp, interpolates between values using t (0-1)
		color3_t color = glm::mix(skyBottom, skyTop, t);

	return color;
}

