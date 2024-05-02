#pragma once
#include <SDL2/SDL_render.h>
#include "../include/Board.h"
#include <array>

using Color = std::array<int, 4>;

class Circle{
private:
    SDL_Renderer* render;
    int x_param;
    int y_param;
    int radius;
    Color color;
public:
    Circle(SDL_Renderer* renderer,int x, int y, int r, const Color& color)  
    : render(renderer), x_param(x), y_param(y), radius(r), color(color) {}

    void setX(int x_param){
        this->x_param = x_param;
    }

    void setY(int y_param){
        this->y_param = y_param;
    }

    void setRadius(int r){
        this->radius = r;
    }

    int getX() const {
        return x_param;
    }

    int getY() const {
        return y_param;
    }
    int getRadius() const {
        return radius;
    }

    const Color& getColor() const {
        return color;
    }
};