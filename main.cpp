#include "Renderer3D.h"
#include <vector>
#include <SDL.h>

// cube
std::vector<Point3D> points{ Point3D{-1.0f, -1.0f, -1.0f}, Point3D{-1.0, -1.0f, 1.0f},
                             Point3D{1.0f, -1.0f, -1.0f}, Point3D{-1.0, 1.0f, -1.0f},
                             Point3D{-1.0f, 1.0f, 1.0f}, Point3D{1.0, -1.0f, 1.0f},
                             Point3D{1.0f, 1.0f, -1.0f}, Point3D{1.0, 1.0f, 1.0f} };

std::vector<Edge> edges{ Edge{0,1}, Edge{0,2}, Edge{0,3},
                         Edge{2,5}, Edge{3,6}, Edge{3,4},
                         Edge{4,7}, Edge{6,7}, Edge{7,5},
                         Edge{5,1}, Edge{4,1}, Edge{2,6} };


int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    Renderer3D renderer3D(window, renderer, points, edges);

    while(running) {
        if(SDL_QuitRequested()) {
            running = false;
            break;
        }
        renderer3D.render();
    }
    
    return 0;
}