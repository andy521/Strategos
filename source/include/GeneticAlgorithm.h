//
//  GeneticAlgorithm.h
//  Strategos
//
//

#ifndef _GENETIC_ALGORITHM_
#define _GENETIC_ALGORITHM_

#include <stdio.h>

#include <Algorithm.h>
#include <Army.h>
#include <CrossoverManager.h>
#include <MutationManager.h>
#include <Objective.h>

#define INDIVIDUOS_GERACAO  30
#define SELECT_FROM_POP 2
#define GOLD_AMOUNT 350

struct PairAF
{
    Army *ind;
    double fitness;

    PairAF(Army *army, double fit)
        : ind(army), fitness(fit)
    {}
};

class GeneticAlgorithm : public Algorithm
{
    public:
        GeneticAlgorithm(int _armyType);
        ~GeneticAlgorithm();
        void run() override;

        void selection();
        void randomArmies(int size);
        void normalizeFitness(std::vector<PairAF> *pairs);
        

        static bool highToLow(PairAF p1, PairAF p2)
        {
            return (p1.fitness > p2.fitness);
        }

        Army *generateRandomArmy();

    protected:
        virtual void addInitialArmy(Army *army);
    private:
        
        std::vector<Army*> individuos;

        int allowedThreads;

        /**
         * \param selected Retorna os individuos selecionados para a PROXIMA geracao
         *          Ordenados em ordem decrescente de fitness
         * \param n Numero de individuos para selecionar
         */
        void selectFromPop(unsigned int n, std::vector<Army*>& selected, std::vector<Army*>& rejected);

        /// Efetua o crossover ateh popular os INDIVIDUOS_GERACAO indivudos
        void crossOver(std::vector<Army*>& selected);

        /// Efetua mutacao nos individuos
        void mutate(std::vector<Army*>& selected);

        //
        void threadSimulate( unsigned int from, unsigned int n );

        void repair(std::vector<Army *> selected);
        /// Gen things
        static Trigger* generateRandomTrigger();
        static Tactic* generateRandomTactic( const Army* forArmy, int forUnitID );

        virtual Army* higherFitnessArmy();
        virtual std::vector<Army*>& getSelectedArmies();

        CrossoverManager *crossover;
        MutationManager *mutation;
        Objective *objective;
};

#endif
