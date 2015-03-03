#include <iostream>
#include <cstdlib>

#include <Engine.hpp>
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

int main(int ac, char **av)
{
	Engine e;
	Scene	sc;

	if (!checkArg(ac, av))
	{
		displayError(av[0]);
		return 1;
	}

	if (sc.setPts(av[1]) == false) {
		return (1);
	}
	sc.setMinXYZ();
	sc.setMaxXYZ();
	sc.setScalePts();
	//sc.setExtremeControlPoint();

	srand(time(NULL));
	e.init();
	//e.createMap(sc);
	e.launch(sc);

	return 0;
}
