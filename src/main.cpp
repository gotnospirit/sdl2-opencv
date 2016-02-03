#include <iostream>

#include "SDL.h"
#include "opencv2/highgui.hpp"

void fillTexture(SDL_Texture * texture, cv::Mat const &mat)
{
    IplImage * img = &(IplImage)mat;

    unsigned char * texture_data = NULL;
    int texture_pitch = 0;

    SDL_LockTexture(texture, 0, (void **)&texture_data, &texture_pitch);
    memcpy(texture_data, (void *)img->imageData, img->width * img->height * img->nChannels);
    SDL_UnlockTexture(texture);
}

int main(int argc, char * argv[])
{
    cv::VideoCapture cap;

    cap.open(0);

    if (!cap.isOpened())
    {
        std::cerr << "***Could not initialize capturing...***" << std::endl;
        return -1;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;

    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) < 0)
    {
        std::cerr << "Error creating window or renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Texture * texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_BGR24,
        SDL_TEXTUREACCESS_STREAMING,
        (int)cap.get(cv::CAP_PROP_FRAME_WIDTH),
        (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)
    );

    cv::Mat frame;

    std::cout << "Hot keys:" << std::endl;
    std::cout << "\tESC - quit the program" << std::endl;
    std::cout << "\tp - pause video" << std::endl;

    bool paused = false;
    bool quit = false;

    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
		{
            switch (e.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;

                        case SDLK_p:
                            paused = !paused;
                            break;
                    }
                    break;
            }
        }

        if (!paused)
        {
            cap >> frame;

            if (frame.empty())
            {
                quit = true;
                continue;
            }

            fillTexture(texture, frame);
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    cap.release();

    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
