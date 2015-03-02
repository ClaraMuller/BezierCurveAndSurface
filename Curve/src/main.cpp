#include <iostream>
#include <EnvSDL.hpp>
#include <Scene.hpp>

static bool checkArg(int ac, char **av)
{
	if (ac < 2)
		return false;
	std::string file(av[1]);
	if (file.length() < 5)
		return false;
	std::string ext = file.substr(file.length() - 5);
	return (ext.compare(".mod1") == 0);
}

static void displayError(char *prgm)
{
	std::cout << prgm << " <file.mod1>" << std::endl;
}

int main(int ac, char ** av)
{
	if (!checkArg(ac, av))
	{
		displayError(av[0]);
		return 1;
	}

//	EnvSDL	env(1200, 600, "SDL Window", std::cout);
	EnvSDL	env(1900, 1200, "SDL Window", std::cout);
	Scene	sc;

	if (sc.setPts(av[1]) == false) {
		return (1);
	}
	env.init();
	env.launch(sc);
	return 0;
}
