/*
 *  Strategos - Game.h
 *
 *  Esta classe eh um dos 'Controller' (@see MVC) do nosso software.
 *	Ela vai comunicar o mundo (@see World.h), que contem a simulacao
 *	do jogador com o exercito selecionado pelo Algoritmo Genetico,
 *  com a visualizacao, isto eh, os elementos graficos e a SDL (@see View.h).
 *
 *	Last update: 17/05/2014
 */

#ifndef _GAME_H_
#define _GAME_H_

#include "View.h"
#include "StateMachine.h"

#include "Resource.h"
#include "Dictionary.h"
#include "Algorithm.h"
#include "CombatLog.h"

#define CONFIG_FILE  "setup.cfg"

class Game
{
    public:
		~Game();
		static Game* getGlobalGame(){
		    if (globalGame)
                return globalGame;
            return new Game();
        }

		bool isRunning();
		void setRunning(bool state);
		bool update();

		SDL_Texture* getRendererFrameBuffer();
		int getWidth() const;
		int getHeight() const;
        int getScreenBPP() const;

		Resource *getResourceMNGR();
		Dictionary *getDictionary(int id);
		Dictionary *getDictionary(const std::string& name) const;
		int getNDictionary() const;

        void generateSprites(const Dictionary *d);

		//Por enquanto vou colocar aqui
		unsigned long createNewGID();
		void readCFGKey(const char *key, void *info);

		Army* getEditingArmy() const;
		void setEditingArmy(Army* editingArmy);

		Army* getArmy1() const;
		void setArmy1(const std::string& str);
		void setArmy1(Army *a);

		Army* getArmy2() const;
		void setArmy2(const std::string& str);
		void setArmy2(Army *a);

        Algorithm **getAlgorithm();

		CombatLog* getCombatLog(int i);

		SDL_Renderer *getRenderer();


		bool winner;

	private:
	    static Game *globalGame;

		std::fstream cfgFile;
		Resource resources;
		View *view;
		std::vector<Dictionary*> dict;

		Army *editingArmy;
		Army *armySim1, *armySim2;
		CombatLog *log1, *log2;

		StateMachine *gameState;

		bool run;
		int globalSeed;
        Algorithm *algorithm[3];

        ///
		Game();

		void loadDictionaries();
};

#endif
