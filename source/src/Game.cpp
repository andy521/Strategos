/*
 *  Strategos - Game.cpp
 *
 */

#include <time.h>

#include "RandomEngine.h"
#include "Game.h"
#include "CombatLog.h"


Game* Game::globalGame = 0;

Game::Game()
    : armySim1(nullptr), armySim2(nullptr), log1(nullptr), log2(nullptr)
{
	int screenWidth = 1024, screenHeight = 768, screenBPP = 0;
    globalGame = this;

	cfgFile.open(CONFIG_FILE);

	readCFGKey("Screen Width:", &screenWidth);
	readCFGKey("Screen Height:", &screenHeight);
	readCFGKey("Screen Bpp:", &screenBPP);
	readCFGKey("Global Seed:", &globalSeed);

	view = new View();
	view->createWindow(screenWidth, screenHeight, screenBPP, 0); // SDL_DOUBLEBUF | SDL_HWSURFACE

	run = true;
	editingArmy = nullptr;

    // Criar um GA para cada tipo de Army
	algorithm[0] = new GeneticAlgorithm(0);
	algorithm[1] = new GeneticAlgorithm(1);
	algorithm[2] = new GeneticAlgorithm(2);

	srand((unsigned int) time(nullptr));
	loadDictionaries();

    printf("Starting GA\n");
    clock_t time = clock();
    for (int i = 0; i < 1; ++i) // TODO: Alterar para 3 na versao final 1 apenas para agilizar debugs
    {
        algorithm[i]->initialize();
        algorithm[i]->run();
    }
    printf("GA time: %lfs\n", (clock()-time) / (double)CLOCKS_PER_SEC);
}

Game::~Game()
{
	if (editingArmy != nullptr)
		delete editingArmy;

	while (dict.size())
	{
		delete dict[dict.size() - 1];
		dict.pop_back();
	}

	delete algorithm[0];
	delete algorithm[1];
	delete algorithm[2];

	globalGame = 0;

	delete view;
}

bool Game::isRunning()
{
	return run;
}

void Game::setRunning(bool state)
{
	this->run = state;
}

void Game::update()
{
	run = view->update();
}

Resource *Game::getResourceMNGR()
{
	return &resources;
}

//TODO: N�O REMOVER ESTE METODO, NECESSARIO PARA OS COMBOBOXES
Dictionary* Game::getDictionary(int id)
{
	return dict[id];
}

Dictionary *Game::getDictionary(const std::string& name) const
{
	for (unsigned int i = 0; i < dict.size(); ++i)
	{
		if (dict[i]->title == name)
		{
			return dict[i];
		}
	}

	return nullptr;
}

int Game::getNDictionary() const
{
    return dict.size();
}

SDL_Renderer *Game::getRenderer()
{
    return view->getRenderer();
}

void Game::readCFGKey(const char *key, void *info)
{

}

unsigned long Game::createNewGID()
{
	return 0;
}

Army* Game::getEditingArmy() const
{
	return editingArmy;
}

void Game::setEditingArmy(Army* editingArmy)
{
	this->editingArmy = editingArmy;
}

void Game::loadDictionaries()
{
	std::vector<std::string> dnyFiles;
	Resource::getListOfFiles(dnyFiles, "assets/dictionary/", ".dny");

	for (unsigned int i = 0; i < dnyFiles.size(); ++i)
	{
		Dictionary *dny = new Dictionary();
		dny->loadDictionary(dnyFiles[i].c_str(), resources);
		if (dny)
			dict.push_back(dny);
	}

	printf("== Loaded %u dictionaries ==\n", dict.size());
}

Army* Game::getArmy1() const
{
	return armySim1;
}

void Game::setArmy1(const std::string& str)
{
	if (armySim1 != nullptr)
		delete armySim1;
	armySim1 = Army::loadArmy(str);

	if (log1)
        delete log1;

    log1 = new CombatLog(armySim1->nUnits());
}

void Game::setArmy1(Army *a)
{
	if (armySim1 != nullptr)
		delete armySim1;
	armySim1 = a;


	if (log1)
        delete log1;

    log1 = new CombatLog(armySim1->nUnits());
}

Army* Game::getArmy2() const
{
	return armySim2;
}

void Game::setArmy2(const std::string& str)
{
	if (armySim2 != nullptr)
		delete armySim2;
	armySim2  = Army::loadArmy(str);

	if (log2)
        delete log2;

    log2 = new CombatLog(armySim2->nUnits());
}

void Game::setArmy2(Army *a)
{
	if (armySim2 != nullptr)
		delete armySim2;
	armySim2 = a;

	if (log2)
        delete log2;

    log2 = new CombatLog(armySim2->nUnits());
}

Algorithm** Game::getAlgorithm()
{
	return algorithm;
}

CombatLog* Game::getCombatLog(int i)
{
    if (i == 0)
        return log1;

	return log2;
}
