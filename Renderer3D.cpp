#include "Renderer3D.h"

Renderer3D::Renderer3D(SDL_Window* window, SDL_Renderer* renderer, std::vector<Point3D>& points, std::vector<Edge> edges) : renderer(renderer), points(points), edges(edges) {
    SDL_GetWindowSize(window, &WindowSizeX, &WindowSizeY);
}

void Renderer3D::render() {
    auto time1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration(0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 205, 105, 255, SDL_ALPHA_OPAQUE);

    rotation += 1 * DeltaTime;

    for(auto& edge : edges) {
        Point2D start = projection(rotate(points[edge.start], true, true));
        Point2D end = projection(rotate(points[edge.end], true, true));

        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }
    SDL_RenderPresent(renderer);

    auto time2 = std::chrono::high_resolution_clock::now();
    duration = time2 - time1;
    DeltaTime = duration.count();
    time1 = time2;
}

Point3D Renderer3D::rotate(Point3D point, bool x, bool y) {
    Point3D rotatedX{point.x, point.y, point.z};
    if(y) {
        rotatedX.x = cos(rotation) * point.x - sin(rotation) * point.z;
        rotatedX.z = sin(rotation) * point.x + cos(rotation) * point.z;
    }
    Point3D rotatedY{rotatedX.x, rotatedX.y, rotatedX.z};
    if(x){
        rotatedY.y = cos(rotation) * rotatedX.y - sin(rotation) * rotatedX.z;
        rotatedY.z = sin(rotation) * rotatedX.y + cos(rotation) * rotatedX.z;
    }
    return rotatedY;
}

Point2D Renderer3D::projection(Point3D point) {
    return Point2D{ WindowSizeX/2+(FOV*point.x)/(FOV+point.z)*100, WindowSizeY/2+(FOV*point.y)/(FOV+point.z)*100 };
}