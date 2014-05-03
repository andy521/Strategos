#ifndef COMBATDATA_H
#define COMBATDATA_H

#include <Unit.h>
#include <Ship.h>

class CombatData
{
    public:
        CombatData(int nU1, int nU2);
        ~CombatData();

        double getUnitDistance(const Unit* a, const Unit* b);
//        double getShipDistance(const Ship* a, const Ship* b);

        Unit* getNearestUnit(const Unit* from, const std::vector<Unit*>& to, double &outDist);
//        Ship* getNearestShip(const Ship* from, const std::vector<Ship*>& to);

        //Unit* getWeakestUnit(const Unit* from, const std::vector<Unit*>& to);

        void ClearDistances();

        RandomEngine randomengine;

    private:

        int miss, total;

        // [team0][team1]
        double** distancesUnit;
        int nUnits1, nUnits2;
};


#endif // COMBATDATA_H
