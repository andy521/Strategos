/*
 *  Strategos - Resource.h
 *
 *  Esta eh uma estrutura para armazenar os assets.
 *	carregados do jogo.
 *  Dessa forma, assets repetidos nao sao carregados
 *  multiplas vezes, e economizados o tempo de load
 *  na transicao dos estados
 *
 *	Last update: 24/08/2012
 */

#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Image.h"
#include "SoundManager.h"

class Font;

SDL_Texture *loadImageToMemory(const std::string &fileName);

class Resource
{
    public:
        std::map<std::string, Image*> images;
        std::map<std::string, Font*> fonts;
        std::map<std::string, Mix_Chunk*> chunks;
        std::map<std::string, Mix_Music*> musics;

        Resource();
        ~Resource();

        // Retorna a imagem inserida (Se ela ja existe retorna a ocorrencia)
        // Ou NULL caso ocorra algum erro no carregamento
        Image* AddImage(const char *filepath, const std::string& key);
        void AddFont(const char *filepath, const std::string& key);
        Mix_Chunk* AddSound(const char *filepath, const std::string& key);

        const Image* GetImage(const std::string& key);
        Font* GetFont(const std::string& key);
        Mix_Chunk* GetSound(const std::string& key);

        // Retorna uma lista com o nome dos arquivos
        // O usuario se encarrega de liberar a memoria do vetor (das strings)
        static void getListOfFiles(std::vector<std::string> &myVec, std::string insideDirectory, std::string extension);

    private:
        Image* LoadImage(std::fstream &file, const std::string& key);
        void LoadFont(std::fstream &file, const std::string& key);
        Mix_Chunk* LoadSound(std::fstream &file, const std::string& key);
};

#endif
