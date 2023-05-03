#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <chrono>
#include "Environment.h"
#include "Renderer.h"
#include "time.h"
#include "Timer.h"
#include "Agent.h"
#include "Food.h"
#include "Anthill.h"
#include "SillyAnt.h"
#include "Ant.h"
#include "AntWithRules.h"
#include "OrRule.h"

static unsigned int windowWidth() { return 1280; }
static unsigned int windowHeight() { return 700; }

/// <summary>
/// called each time a key is pressed.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="environment">The environment.</param>
void onKeyPressed(char key, Environment *environment)
{
	switch (key)
	{
	case 'f':
		new Food(environment, environment->randomPosition(), MathUtils::random(200, 2000));
		break;
	case 'a':
	{
		Anthill *a = new Anthill(environment, environment->randomPosition());

		for (int i = 0; i < 50; i++)
		{
			// new Ant(environment, a);
			AntWithRules *ant = new AntWithRules(environment, a);
			OrRule orrule = OrRule({
				AntWithRules::RuleDropFood(ant),
				AntWithRules::RuleGotoAnthill(ant),
				AntWithRules::RuleFoodOrPherFinder(ant),
				AntWithRules::RuleRandomDirection(ant),
			});
			ant->setRule(orrule);
		}
	}
	break;
	case 'd':
	{
		std::vector<Food *> instances = Agent::getAllAgentsOf<Food>();
		if (!instances.empty())
			instances.back()->setStatus(Agent::Status::destroy);
	}
	break;
	default:
		std::cout << "Key pressed: " << key << std::endl;
		break;
	}
}

static int64_t frametime = 0;

/// <summary>
/// Called at each time step.
/// </summary>
void onSimulate()
{
	Renderer::getInstance()->drawString(Vector2<float>(), std::to_string(frametime));
	Agent::simulate();
}

/// <summary>
/// The main program.
/// </summary>
/// <param name="argc">The number of arguments.</param>
/// <param name="argv">The arguments.</param>
/// <returns></returns>
int main(int /*argc*/, char ** /*argv*/)
{
	// 1 - Initialization of SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS /* | SDL_INIT_AUDIO*/) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	// 2 - Initialization of the renderer
	Renderer::initialize(windowWidth(), windowHeight());

	// 3 - Creation of an environment
	Environment environment(windowWidth(), windowHeight());

	// 4 - We change the seed of the random number generator
	srand((unsigned int)time(NULL));

	// The main event loop...
	SDL_Event event;
	bool exit = false;

	auto started = std::chrono::high_resolution_clock::now();
	while (!exit)
	{
		// Added because my pc sends way too many inputs
		// per frame for some reason. I limited it by sending only one input per key per frame
		std::set<char> pressedKeys = {};
		// 1 - We handle events
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'q'))
			{
				::std::cout << "Exit signal detected" << ::std::endl;
				exit = true;
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (pressedKeys.find((char)event.key.keysym.sym) == pressedKeys.end())
				{
					onKeyPressed((char)event.key.keysym.sym, &environment);
					pressedKeys.insert((char)event.key.keysym.sym);
				}
			}
		}
		// 2 - We update the simulation
		auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - started).count();
		// Timer::update(delay / 100.0f);
		started = std::chrono::high_resolution_clock::now();
		Timer::update(.5f);
		frametime = delay;
		onSimulate();
		// 3 - We render the scene
		Renderer::getInstance()->flush();
	}

	std::cout << "Shutting down renderer..." << std::endl;
	Renderer::finalize();
	Agent::finalize();

	std::cout << "Shutting down SDL" << std::endl;
	SDL_Quit();

	return 0;
}
