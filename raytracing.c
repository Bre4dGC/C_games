#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH        1280
#define HEIGHT       760
#define RAYS_NUM     10
#define COLOR_WHITE  0xffffffff
#define COLOR_BLACK  0x00000000
#define COLOR_YELLOW 0xedd15f

struct circle 
{ 
    double x, y;
    double r; 
};

struct ray 
{ 
    double x_st, y_st;
    double ang; 
};

void fill_circ(SDL_Surface* surface, struct circle crcl, Uint32 color)
{
    double radius_sqrd = pow(crcl.r, 2);
    for (double x = crcl.x - crcl.r; x <= crcl.x + crcl.r; x++)
    {
        for(double y = crcl.y - crcl.r; y <= crcl.y + crcl.r; y++)
        {
            double dist_sqr = pow(x - crcl.x, 2) + pow(y - crcl.y, 2);
            if(dist_sqr < radius_sqrd)
            {
                SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }    
}

void gen_rays(struct circle crcl, struct ray rs[RAYS_NUM])
{
    for (int i = 0; i < RAYS_NUM; i++)
    {
        double ang = ((double)i / RAYS_NUM) * 2 * M_PI;
        struct ray r = {crcl.x, crcl.y, crcl.r};
        rs[i] = r;
    }
}

void fill_rays(SDL_Surface* surface, struct ray rs[RAYS_NUM], Uint32 color)
{
    for (int i = 0; i < RAYS_NUM; i++)
    {
        struct ray r = rs[i];

        int end_of_scrn = 0;
        int obj_hit = 0;

        double step = 1;
        double x_drw = r.x_st;
        double y_drw = r.y_st;
        while(!end_of_scrn && !obj_hit)
        {
            x_drw += step * cos(r.ang);
            y_drw += step * sin(r.ang);

            SDL_Rect pixel = (SDL_Rect){x_drw, y_drw, 1, 1};
            SDL_FillRect(surface, &pixel, color);

            if(x_drw < 0 || x_drw > WIDTH)
                end_of_scrn = 1;
            if(y_drw < 0 || y_drw > HEIGHT)
                end_of_scrn = 1;
        }
    }
}

int main(int argc, char* argv[]) 
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    struct circle static_crcl = {1000, 390, 120};
    struct circle crcl = {200, 390, 80};
    SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};

    struct ray rs[RAYS_NUM];

    SDL_Event event;
    int sim_run = 1;
    while (sim_run)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                sim_run = 0;
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0)
            {
                crcl.x = event.motion.x;
                crcl.y = event.motion.y;
                gen_rays(crcl, rs);
            }                
        }
        SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
         
        fill_rays(surface, rs, COLOR_YELLOW);
        fill_circ(surface, static_crcl, COLOR_WHITE);
        fill_circ(surface, crcl, COLOR_WHITE);
        
        SDL_UpdateWindowSurface(window);

        SDL_Delay(0.1);
    }

    return 0;
}