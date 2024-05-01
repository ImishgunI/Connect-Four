#include "../include/Board.h" // Подключение класса Board
#include <SDL2/SDL.h> // Подключение SDL2

SDL_Window* Board::window = nullptr;         // Инициализация начальных значений
bool Board::quit = false;
SDL_Event Board::event;
SDL_Renderer* Board::renderer = nullptr;
int width = 1280;
int height = 720;
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
                }else if(event.type == SDL_WINDOWEVENT){
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                        int newWidth = event.window.data1;
                        int newHeight = event.window.data2;

                        width = newWidth;
                        height = newHeight;

                        SDL_SetWindowSize(window ,width, height);
                    }
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

    const int ROW = 6; // Длина строки
    const int COWL = 7; // Длина колонки
    const int CELL_SIZE = 16; // Размер одной ячейки

    SDL_SetRenderDrawColor(renderer, 0,0,255,255); // Устанавливаем цвет окна
    SDL_RenderClear(renderer); // Очистка буффера окна


    int cellWidth = (width / COWL + 1);
    int cellHeight = (height / ROW);

    for(int i = 0; i < ROW; ++i){  // Циклы для отрисовки ячеек
        for(int j = 0; j < COWL; ++j){
            SDL_Rect cellRect = {j * cellWidth, i * cellHeight, cellWidth, cellHeight};
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &cellRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cellRect);
        }
    }

    SDL_RenderPresent(renderer); // Отображение ячеек

}
