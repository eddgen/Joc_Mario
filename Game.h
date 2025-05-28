#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "Camera.h"
#include "Object.h"
#include "Renderer.h"

extern Camera camera;
extern bool paused;
extern std::vector<Object*> objectsToDelete; // Add this to track objects for deletion

void Begin(const sf::Window& window);
void Update(float deltaTime);
void Render(Renderer& render);
void RenderUI(Renderer& renderer);
void DeleteObject(Object* object);
void ProcessPendingDeletions(); // New function to process deletions

#endif //GAME_H