#include <iostream>
#include <EnvSDL.hpp>
#include <Scene.hpp>

static bool checkArg(int ac, char **av)
{
	(void)av;
	return (ac > 1);
}

static void displayError(char *prgm)
{
	std::cout << prgm << " <file>" << std::endl;
}

int main(int ac, char ** av)
{
	if (!checkArg(ac, av))
	{
		displayError(av[0]);
		return 1;
	}

	EnvSDL	env(1900, 1200, "SDL Window", std::cout);
	Scene	sc;

	if (sc.setPts(av[1]) == false) {
		return (1);
	}
	env.init();
	env.launch(sc);
	return 0;
}
