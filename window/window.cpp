#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

void handleEvents(bool& quit, SDL_Event& event, SDL_Color& textColor) {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_r: textColor = {255, 0, 0}; break; // Red
                case SDLK_g: textColor = {0, 255, 0}; break; // Green
                case SDLK_b: textColor = {0, 0, 255}; break; // Blue
            }
        }
    }
}

int cleanupAndExit(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int status) {
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
 
    TTF_Quit();
    SDL_Quit();
    return status;
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return cleanupAndExit(nullptr, nullptr, nullptr, 1);
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return cleanupAndExit(nullptr, nullptr, nullptr, 1);
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("RGB Color Change", SDL_WINDOWPOS_UNDEFINED, 
SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return cleanupAndExit(nullptr, nullptr, nullptr, 1);
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return cleanupAndExit(window, nullptr, nullptr, 1);
    }

    // Load a font
    TTF_Font* font = TTF_OpenFont("/Users/kimnordin/Documents/Projects/cpp/window/fFinish.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return cleanupAndExit(window, renderer, nullptr, 1);
    }

    SDL_Color textColor = {255, 255, 255}; // Initial white color
    bool quit = false;
    SDL_Event event;

    while (!quit) {
	handleEvents(quit, event, textColor);

        // Clear screen
        SDL_RenderClear(renderer);

        // Render text
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "R G B", textColor);
        if (!textSurface) {
            std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << 
std::endl;
        } else {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (!textTexture) {
                std::cerr << "Unable to create texture from rendered text! SDL Error: " << 
SDL_GetError() << std::endl;
            } else {
                // Render the texture
                SDL_RenderCopy(renderer, textTexture, NULL, NULL);
                SDL_DestroyTexture(textTexture);
            }
            SDL_FreeSurface(textSurface);
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Return success (0) or failure (1) based on program execution
    return cleanupAndExit(window, renderer, font, 0);
}

