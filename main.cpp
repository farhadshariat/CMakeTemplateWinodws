#include <iostream>
#include "SDL.h"

static bool is_running = false;
static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static uint32_t* color_buffer = nullptr;
static SDL_Texture* color_buffer_texture = nullptr;
uint32_t window_height = 600;
uint32_t window_width = 800;

void destroye_window()
{
	delete[] color_buffer;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool initialize_window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	//maximizing our screen buffer(Fake Full Screen)
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	//maximize width and height
	window_width = display_mode.w;
	window_height = display_mode.h;

	//create sdl widnow
	window = SDL_CreateWindow(
		nullptr,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);

	if (!window)
	{
		std::cout << "SDL window object doesnt created" << std::endl;
		return false;
	}

	//create sdl renderer
	//index: -1 for default widnow type (one widnow)
	//falgs: 0 no flag needed
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		std::cout << "SDL renderer object doesnt created" << std::endl;
		return false;
	}

	//have sdl to be real full screen
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}

void draw_grid()
{
	for (int y = 0; y < window_height; y += 10)
		for (int x = 0; x < window_width; x += 10)
			color_buffer[window_width * y + x] = 0xFF333333;
}

void draw_rect(int x_a, int y_a, int width, int height, uint32_t color)
{
	for (int y = y_a; y < height + y_a; ++y)
		for (int x = x_a; x < width + x_a; ++x)
			color_buffer[window_width * y + x] = color;

	//for (int i = 0; i < width; i++)
	//{
	//	for (int j = 0; j < height; j++)
	//	{
	//		int current_x = x + i;
	//		int current_y = y + j;
	//		color_buffer[window_width * current_y + current_x] = color;
	//	}
	//}
}

void setup()
{
	color_buffer = new uint32_t[window_width * window_height];

	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			is_running = false;
		break;

	default:
		break;
	}
}

void update()
{

}

void clear_color_buffer(uint32_t color)
{
	for (int y = 0; y < window_height; ++y)
		for (int x = 0; x < window_width; ++x)
			color_buffer[window_width * y + x] = color;
}

void render_color_buffer()
{
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t))
	);

	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void render()
{
	//r.g.b.a(transparency)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_grid();
	draw_rect(300, 200, 300, 150, 0xFFFF00FF);

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
	is_running = initialize_window();

	setup();

	while (is_running)
	{
		process_input();
		update();
		render();
	}

	destroye_window();
    std::cout<<"i hate cmake"<<'\n';
    return 0;
}