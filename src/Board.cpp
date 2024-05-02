#include "../include/Board.h" // Подключение класса Board
#include <SDL2/SDL.h>         // Подключение SDL2
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include "../include/Circle.h"

SDL_Window* Board::window = nullptr;         // Инициализация начальных значений
bool Board::quit = false;
SDL_Event Board::event;
SDL_Renderer* Board::renderer = nullptr;
const int width = 1280;
const int height = 720;



// Метод для создания окна приложения
int Board::createWindow(){

        if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
            return -1;
        }
        // Создание начального окна
        window = SDL_CreateWindow("Connect Four", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if(!window){
            return -1;
        }

        // Отрисовка ячеек игры
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer){
            return -1;
        }


        renderBoard(renderer);

        // Обработка событий
        quit = false;
        while(!quit){
            while(SDL_PollEvent(&event) != 0){
                if(event.type == SDL_QUIT){
                    quit = true;
                }
            }
        }


        // Очистка памяти от использования SDL2
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
}





// Метод заполнения окна цветом и игровым полем
void Board::renderBoard(SDL_Renderer* renderer){

    const int ROW = 6;                                                                 // Длина строки
    const int COWL = 7;                                                                // Длина колонки
    const int CELL_PADDING  = 10;                                                      // Отступ между ячейками
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);                           // Устанавливаем цвет окна
    SDL_RenderClear(renderer);                                                         // Очистка буффера окна



    int cellWidth = (width - CELL_PADDING * (COWL + 1)) / COWL;                        // Вычисление ширины ячейки
    int cellHeight = ((height + CELL_PADDING * (ROW + 1)) / ROW) - 23;                 // Вычисление высоты ячейки



    for(int i = 0; i < ROW; ++i){                                                      // Циклы для отрисовки ячеек
        for(int j = 0; j < COWL; ++j){
            int cellX = j * (cellWidth + CELL_PADDING) + CELL_PADDING;                 // Вычисление начальной точки X для ячейки
            int cellY = i * (cellHeight + CELL_PADDING) + CELL_PADDING;                // Вычисление начальной точки Y для ячейки



            SDL_Rect cellRect = {cellX, cellY, cellWidth, cellHeight};     // Создание ячейки
            SDL_SetRenderDrawColor(renderer, 150,150, 150, 255);             // Цвет самой ячейки
            SDL_RenderFillRect(renderer, &cellRect);                             // Создаем в определенной области ячейки
            SDL_SetRenderDrawColor(renderer, 255,255, 255, 255);             // Задаем цвет обводки ячейки
            SDL_RenderDrawRect(renderer, &cellRect);                             // Отрисовывет наши ячейки



            int x_param = cellX + (cellWidth / 2);                                    // Вычисление параметра X для круга внутри ячейки
            int y_param = cellY + (cellHeight / 2);                                   // Вычисление параметра Y для круга внутри ячейки



            int radius = std::min(cellWidth, cellHeight) / 2 - 2;                // Вычесление радиуса круга
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);              // Задаем цвет для кругов
            renderCircle(renderer, x_param, y_param, radius);                         // Вызываем метод для отрисовки кругов в ячейках
        }
    }

    SDL_RenderPresent(renderer);                                                      // Отображение ячеек
}



// Метод для создания кругов внутри ячеек
void Board::renderCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius){
    /*
        С помощью этих двух циклов мы проходимся по каждой точке на окружности 
        и соединяем их между собой с помощью метода SDL_RenderDrawPoint(renderer, x, y);
    */
    
   for (int x = centerX - radius; x <= centerX + radius; ++x) {
        for (int y = centerY - radius; y <= centerY + radius; ++y) {
            if ((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) <= radius * radius) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}