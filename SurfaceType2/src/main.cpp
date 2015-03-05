#include <iostream>
#include <cstdlib>

#include <Engine.hpp>
#include <Scene.hpp>

static bool checkArg(int ac, char **av, int *drawingMode)
{
	if (ac == 3)
	{
		std::string	mode(av[2]);
		if (mode.compare("multi") || mode.compare("MULTI"))
			*drawingMode = Engine::MULTI;
	}
	return (ac > 1);
}

static void displayError(char *prgm)
{
	std::cout << prgm
		  << " <file> <drawing mode>[simple][multi]"
		  << std::endl;
}

int main(int ac, char **av)
{
	Engine	e;
	Scene	sc(Engine::SIZE_MAP);
	int	drawingMode = Engine::SIMPLE;

	if (!checkArg(ac, av, &drawingMode))
	{
		displayError(av[0]);
		return (1);
	}

	if (sc.setPts(av[1]) == false) {
		return (1);
	}

	if (e.init(drawingMode) == false)
		return (1);

	e.launch(sc);

	return 0;
}
