/*
 *  Strategos - Dictionary.cpp
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "Dictionary.h"
#include "Global.h"

using namespace std;
using namespace std;

Dictionary::Dictionary()
{
	//DICIONARIO VAZIO, APENAS COM AS UNIDADES GENERICAS, DEVE VIR AQUI
}

Dictionary::~Dictionary()
{
	vector<DictKey*>::iterator iter;
	iter = keys.begin();
	while (iter != keys.end())
	{
	    delete *iter;
		keys.erase(iter);
		iter = keys.begin();
	}
}

/*void Dictionary::generateSprites()
{
    if (shipsGFX) return;

    shipsGFX = new Image**[keys.size()];

    for (unsigned int i = 0; i < keys.size(); ++i)
    {
        printf("Gerando para type %d\n", i);

        Image* cut = baseGFX->cutFrame(i);
        if (cut == nullptr)
        {
            shipsGFX[i] = nullptr;
            printf("ERROR! - nullptr Surface!");
        }else{
            shipsGFX[i] = Image::generateRotatedImage(cut, 360, _ROTATION_FRAMES_);
        }

        keys[i]->gfx_sfx.shipsGFX = shipsGFX[i];
    }

    printf("Sprites gerados!\n");
}*/

int Dictionary::loadDictionary(const char *inputFile, Resource &resource)
{
    fstream dictInput(inputFile, fstream::in);
    if (!dictInput.is_open())
    {
        printf("Arquivo de configuracao nao pode ser carregado: %s\n", inputFile);
        return -1;
    }

    printf("Loading Dictionary: %s\n", inputFile);
    title = inputFile;
    title = title.substr( 0, title.find_last_of('.') );
    title = title.substr( title.find_last_of("\\/")+1 );
    printf("\tName: %s\n", title.c_str());

    while (!dictInput.eof())
    {
        string tag;
        dictInput >> tag;
        if (tag == "DESCRP:")
        {
            int reading = 0;
            char chr = 0;
            while ( 1 )
            {
                dictInput.get(chr);
                if (chr == '@')
                {
                    ++reading;
                    if (reading == 2)   break;
                    continue;
                }

                if (reading == 1)
                description += chr;
            }
//            printf("Description:\n%s\n---------\n", description.c_str());
        }
        else if (tag == "SQUADS"){
            break;
        }
    }

    int nTypes=0;
    while (!dictInput.eof())
    {
        DictKey *key = readAttribute( dictInput, resource);
        key->type = nTypes;
        if (key){
            keys.push_back(key);
//            printf("Adicionado squad %u\n", keys.size());
        }

        ++nTypes;
    }

    return (int)keys.size();
}

const DictKey* Dictionary::getInfoFor(unsigned int pos) const
{
//    printf("Getting pos: %d\n", pos);
    if (pos < keys.size())
        return keys[pos];

    return nullptr;
}

DictKey* Dictionary::readAttribute(fstream &input, Resource &resource)
{
    DictKey *key = new DictKey();
    string tag;

    while (1)
    {
        input >> tag;
//        printf("TAG: %s\n", tag.c_str());

        if(tag.compare("ship:") == 0){
            input >> key->name;
        }
        else if(tag.compare("cost:") == 0){
            input >> key->cost;
        }
        else if(tag.compare("hp:") == 0){
           input >>key->stats.maxHP;
        }
        else if(tag.compare("damage:") == 0){
            input >> key->stats.damage;
        }
        else if(tag.compare("atkCD:") == 0){
            input >> key->stats.maxAtkCD;
        }
        else if(tag.compare("range:") == 0)
        {
            input >> key->stats.range;
            key->stats.range *= SPACIAL_UNIT;
            key->stats.range2 = key->stats.range*key->stats.range;
        }
        else if(tag.compare("shield:") == 0){
            input >> key->stats.shield;
        }
        else if(tag.compare("dodge:") == 0){
            input >> key->stats.dodge;
        }
        else if(tag.compare("speed:") == 0){
            input >> key->stats.speed;
        }
        else if(tag.compare("squad:") == 0){
            input >> key->squadSize;
        }
        else if(tag.compare("gfxShips:") == 0)
        {
            string keyImg;
            input >> tag;
            input >> keyImg;
            key->gfx_sfx.shipIdle = resource.AddImage( tag.c_str(), keyImg );
//            printf("Path: %s, Key: %s, %p\n", path.c_str(), keyImg.c_str(), key->shootGFX);
        }
        else if(tag.compare("gfxShoot:") == 0)
        {
            string keyImg;
            input >> tag;
            input >> keyImg;
            key->gfx_sfx.shootGFX = resource.AddImage( tag.c_str(), keyImg );
//            printf("Path: %s, Key: %s, %p\n", path.c_str(), keyImg.c_str(), key->shootGFX);
        }
        else if(tag.compare("gfxExplode:") == 0)
        {
            string keyImg;
            input >> tag;
            input >> keyImg;
            key->gfx_sfx.explosionGFX = resource.AddImage( tag.c_str(), keyImg );
//            printf("Path: %s, Key: %s, %p\n", path.c_str(), keyImg.c_str(), key->shootGFX);
        }
        else if(tag.compare("sfxExplode1:") == 0)
        {
            string keySfx;
            input >> tag;
            input >> keySfx;
            key->gfx_sfx.explosionsSFX[0] = resource.AddSound( tag.c_str(), keySfx );
        }
        else if(tag.compare("sfxExplode2:") == 0)
        {
            string keySfx;
            input >> tag;
            input >> keySfx;
            key->gfx_sfx.explosionsSFX[1] = resource.AddSound( tag.c_str(), keySfx );
        }
        else if(tag.compare("sfxExplode3:") == 0)
        {
            string keySfx;
            input >> tag;
            input >> keySfx;
            key->gfx_sfx.explosionsSFX[2] = resource.AddSound( tag.c_str(), keySfx );
        }
        else if(tag.compare("sfxExplode4:") == 0)
        {
            string keySfx;
            input >> tag;
            input >> keySfx;
            key->gfx_sfx.explosionsSFX[3] = resource.AddSound( tag.c_str(), keySfx );
        }
        else if(tag.compare("sfxShoot:") == 0)
        {
            string keySfx;
            input >> tag;
            input >> keySfx;
            key->gfx_sfx.shootSFX = resource.AddSound( tag.c_str(), keySfx );
        }
        else if(tag.compare("END_SHIP") == 0)
        {
            break;
        }

        if (input.eof()){
            delete key;
            return nullptr;
        }
    }

	return key;
}
