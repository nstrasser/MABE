//  MABE is a product of The Hintze Lab @ MSU
//     for general research information:
//         hintzelab.msu.edu
//     for MABE documentation:
//         github.com/Hintzelab/MABE/wiki
//
//  Copyright (c) 2015 Michigan State University. All rights reserved.
//     to view the full license, visit:
//         github.com/Hintzelab/MABE/wiki/License

#include "DualWorld.h"

std::shared_ptr<ParameterLink<std::string>> DualWorld::scenarioPL = Parameters::register_parameter("WORLD_DUAL-scenario", (std::string) "noSelPressureBoth",
	"Desired scenario on how agents from type A and B are combined (noSelPressureBoth, noSelPressureB, independentAddition, lockstep or bFollowsA are available).");
std::shared_ptr<ParameterLink<double>> DualWorld::aMutationRatePL = Parameters::register_parameter("WORLD_DUAL-aMutationRate", 0.01,
	"Mutation rate of agents from type A.");
std::shared_ptr<ParameterLink<double>> DualWorld::bMutationRatePL = Parameters::register_parameter("WORLD_DUAL-bMutationRate", 0.01,
	"Mutation rate of agents from type B.");


DualWorld::DualWorld(std::shared_ptr<ParametersTable> PT_) : AbstractWorld(PT_) 
{
	// columns to be added to ave file
	popFileColumns.clear();
	popFileColumns.push_back("genomeScore");
	popFileColumns.push_back("score");
}

void DualWorld::evaluate(std::map<std::string, std::shared_ptr<Group>>& groups,	int analyze, int visualize, int debug) 
{
	int popSize = groups["A::"]->population.size();
	std::vector<std::shared_ptr<Agent>> popA(popSize);
	std::vector<std::shared_ptr<Agent>> popB(popSize);
	std::vector<DualAgent> popDual(popSize);
	std::vector<double> scoreDual(popSize, 0.0);

	initializeGeneration(popA, popB, popDual, groups, popSize);

	do 
	{
		for (int i = 0; i < popSize; i++) 
		{
			scoreDual[i] = evalDual(popDual[i]);
			killList.insert(popDual[i].A->org);
			killList.insert(popDual[i].B->org);
		}

		for (int i = 0; i < popSize; i++) {
			auto newA = std::make_shared<Agent>();
			auto newB = std::make_shared<Agent>();

			tie(newA, newB) = doTournamentSelection(popSize, scoreDual, popDual, groups, 7);
			mutateSelection(newA, newB);

			popDual.push_back(DualAgent(newA, newB));
			popA.push_back(newA);
			popB.push_back(newB);
		}

		groups["A::"]->archive();
		groups["B::"]->archive();

		killOldAndMakeNewGeneration(popA, popB, popDual, groups, popSize);

		std::cout << "finished update: " << Global::update << std::endl;
		Global::update++;
	} while (!groups["A::"]->archivist->finished_ && !groups["B::"]->archivist->finished_);
	
	std::cout << "finished run!" << std::endl;
}

void DualWorld::initializeGeneration(std::vector<std::shared_ptr<Agent>>& popA, std::vector<std::shared_ptr<Agent>>& popB, std::vector<DualAgent>& popDual, std::map<std::string, std::shared_ptr<Group>>& groups, int popSize)
{
	for (int i = 0; i < popSize; i++)
	{
		popA[i] = std::make_shared<Agent>(groups["A::"]->population[i], std::bitset<tagSize>());
		popB[i] = std::make_shared<Agent>(groups["B::"]->population[i], std::bitset<tagSize>());
		popDual[i] = DualAgent(popA[i], popB[i]);
		for (int j = 0; j < tagSize; j++)
		{
			//popA[i]->genome[j] = Random::getInt(0, 1);
			//popB[i]->genome[j] = Random::getInt(0, 1);

			popA[i]->genome[j] = 0;
			popB[i]->genome[j] = 0;
			//popB[i]->genome = Random::getIndex(std::pow(2.0, tagSize)); // issues with a lot of leading zeros when tagSize > 32...
			//popB[i]->genome = Random::getIndex(std::pow(2.0, tagSize));
		}
		//std::cout << "genome A: " << popA[i]->genome << "\ngenome B: " << popB[i]->genome << std::endl;
	}
}

std::tuple<std::shared_ptr<DualWorld::Agent>, std::shared_ptr<DualWorld::Agent>> DualWorld::doTournamentSelection(int popSize, std::vector<double> scoreDual, std::vector<DualAgent>& popDual, std::map<std::string, std::shared_ptr<Group>>& groups, int tournamentSize)
{
	int parentId = Random::getIndex(popSize);
	int challenger;
	for (int j = 0; j < tournamentSize; j++)
	{
		challenger = Random::getIndex(popSize);
		if (scoreDual[challenger] > scoreDual[parentId])
		{
			parentId = challenger;
		}
	}

	auto newOrgA = popDual[parentId].A->org->makeMutatedOffspringFrom(popDual[parentId].A->org);
	groups["A::"]->population.push_back(newOrgA);
	auto newOrgB = popDual[parentId].B->org->makeMutatedOffspringFrom(popDual[parentId].B->org);
	groups["B::"]->population.push_back(newOrgB);
	auto newA = std::make_shared<Agent>(newOrgA, popDual[parentId].A->genome);
	auto newB = std::make_shared<Agent>(newOrgB, popDual[parentId].B->genome);

	return std::make_tuple(newA, newB);
}

void DualWorld::mutateSelection(std::shared_ptr<Agent>& newA, std::shared_ptr<Agent>& newB)
{
    //emp::Binomial binomial(0.01, 1000);
    //std::cout << "pickPosition: " << binomial.PickPosition(0.01) << std::endl;
	int numMutations = Random::getBinomial(tagSize, aMutationRatePL->get(PT));
	//std::cout << "numMutations: " << numMutations << std::endl;
	for (int m = 0; m < numMutations; m++)
	{
		newA->genome.flip(Random::getIndex(tagSize));
	}

	numMutations = Random::getBinomial(tagSize, bMutationRatePL->get(PT));
	for (int m = 0; m < numMutations; m++)
	{
		newB->genome.flip(Random::getIndex(tagSize));
	}
}

void DualWorld::killOldAndMakeNewGeneration(std::vector<std::shared_ptr<Agent>>& popA, std::vector<std::shared_ptr<Agent>>& popB, std::vector<DualAgent>& popDual, std::map<std::string, std::shared_ptr<Group>>& groups, int popSize)
{
	popA = std::vector<std::shared_ptr<Agent>>(popA.begin() + popSize, popA.end());
	popB = std::vector<std::shared_ptr<Agent>>(popB.begin() + popSize, popB.end());
	popDual = std::vector<DualAgent>(popDual.begin() + popSize, popDual.end());

	std::vector<std::shared_ptr<Organism>> newOrgsA;
	std::vector<std::shared_ptr<Organism>> newOrgsB;
	for (size_t i = 0; i < popSize*2; i++)
	{
		if (killList.find(groups["A::"]->population[i]) == killList.end())
		{ // not in killList -> move to new population
			newOrgsA.push_back(groups["A::"]->population[i]);
		}
		if (killList.find(groups["B::"]->population[i]) == killList.end())
		{ // not in killList -> move to new population
			newOrgsB.push_back(groups["B::"]->population[i]);
		}
	}

	groups["A::"]->population = newOrgsA;
	groups["B::"]->population = newOrgsB;

	for (auto org : killList)
	{
		org->kill();
	}
	killList.clear();
}

double DualWorld::evalDual(DualAgent& dualAgent) {
	//std::cout << "A: " << dualAgent.A->genome << std::endl;
	//std::cout << "B: " << dualAgent.B->genome << std::endl << std::endl;

	if (scenarioPL->get(PT) == "noSelPressureBoth") // fitness for A and B is always 1 --> no selective pressure
	{
		dualAgent.A->score = 1.0;
		dualAgent.B->score = 1.0;
		getDualScore(dualAgent, false);
	}
	else if (scenarioPL->get(PT) == "noSelPressureB")
	{
		dualAgent.A->score = evalGenomeCountingInitialOnes(dualAgent.A->genome);
		dualAgent.B->score = 0.0;
		getDualScore(dualAgent, true);
	} 
	else if (scenarioPL->get(PT) == "independentAddition")
	{
		dualAgent.A->score = evalGenomeCountingInitialOnes(dualAgent.A->genome);
		dualAgent.B->score = evalGenomeCountingInitialOnes(dualAgent.B->genome);
		getDualScore(dualAgent, true);
	}
	else if (scenarioPL->get(PT) == "lockstep")
	{
		double intermediateResultA = evalGenomeCountingInitialOnes(dualAgent.A->genome);
		double intermediateResultB = evalGenomeCountingInitialOnes(dualAgent.B->genome);
		if (intermediateResultA == intermediateResultB)
		{
			dualAgent.A->score = intermediateResultA;
			dualAgent.B->score = intermediateResultB;
		}
		else
		{
			dualAgent.A->score = -1.0;
			dualAgent.B->score = -1.0;
		}
		getDualScore(dualAgent, false);
	}
	else if (scenarioPL->get(PT) == "bFollowsA")
	{
		//std::cout << "A: " << dualAgent.A->genome << std::endl;
		double intermediateResultA = evalGenomeCountingInitialOnesNeutral(dualAgent.A->genome);
		//std::cout << "A - intermediate result: " << intermediateResultA << std::endl;
		//std::cout << "B: " << dualAgent.B->genome << std::endl;
		double intermediateResultB = evalGenomeCountingInitialOnesNeutral(dualAgent.B->genome);
		//std::cout << "B - intermediate result: " << intermediateResultB << std::endl;
		if (intermediateResultA >= intermediateResultB)
		{
			dualAgent.A->score = evalGenomeCountingInitialOnes(dualAgent.A->genome);
			dualAgent.B->score = evalGenomeCountingInitialOnes(dualAgent.B->genome);
		}
		else
		{
			dualAgent.A->score = -1.0;
			dualAgent.B->score = -1.0;
		}
		getDualScore(dualAgent, false);
	}
	else if (scenarioPL->get(PT) == "bExactlyFollowsA")
	{
		double intermediateResultA = evalGenomeCountingInitialOnes(dualAgent.A->genome);
		double intermediateResultB = evalGenomeCountingInitialOnes(dualAgent.B->genome);
		if (intermediateResultA == (intermediateResultB+1) or intermediateResultA == intermediateResultB)
		{
			dualAgent.A->score = intermediateResultA;
			dualAgent.B->score = intermediateResultB;
		}
		else
		{
			dualAgent.A->score = -1.0;
			dualAgent.B->score = -1.0;
		}
		getDualScore(dualAgent, false);
	}
	else
	{
		std::cout << "Given scenario is unknown. Please provide a valid one." << std::endl;
		return 0.0;
	}

	addToDataMap(dualAgent);

	return dualAgent.score;
}

void DualWorld::addToDataMap(DualAgent& dualAgent) 
{
	dualAgent.A->org->dataMap.append("genome", dualAgent.A->genome.to_string());
	dualAgent.B->org->dataMap.append("genome", dualAgent.B->genome.to_string());
	dualAgent.A->org->dataMap.append("genomeScore", dualAgent.A->score);
	dualAgent.B->org->dataMap.append("genomeScore", dualAgent.B->score);
	dualAgent.A->org->dataMap.append("score", dualAgent.score);
	dualAgent.B->org->dataMap.append("score", dualAgent.score);
	//dualAgent.A->org->dataMap.append("optimizeValue", dualAgent.score);
	//dualAgent.B->org->dataMap.append("optimizeValue", dualAgent.score);
}

//double DualWorld::evalGenomeMaxOne(std::bitset<tagSize>& testGenome)
//{
//	return testGenome.count();
//}

//double DualWorld::evalGenomeLongestRunOne(std::bitset<tagSize>& testGenome)
//{
//	double currentLongest = 0.0;
//	double bestLongest = 0.0;
//	for (int i = 0; i < tagSize; i++)
//	{
//		if (testGenome[i] == 1)
//		{
//			currentLongest++;
//			for (int j = i+1; j < tagSize; j++)
//			{
//				if (testGenome[j] == 1)
//				{
//					currentLongest++;
//				}
//				else
//				{
//					break;
//				}
//			}
//			if (currentLongest > bestLongest)
//			{
//				bestLongest = currentLongest;
//			}
//			i += currentLongest;
//			currentLongest = 0.0;
//		}
//	}
//	return bestLongest;
//}

double DualWorld::evalGenomeCountingInitialOnesNeutral(std::bitset<tagSize>& testGenome)
{
	double score = 0.0;
	for (int i = tagSize-1; i >= 0; i--)
	{
		if (testGenome[i] == 1)
		{
			score++;
		}
		else
		{
			return score;
		}
		
	}
}

double DualWorld::evalGenomeCountingInitialOnes(std::bitset<tagSize>& testGenome)
{
	bool allOnes = true;
	double score = 0.0;
	for (int i = tagSize-1; i >= 0; i--)
	{
		if (testGenome[i] == 0)
		{
			allOnes = false;
		}
		
		if (allOnes == true && testGenome[i] == 1)
		{
			score++;
		} 
		
		if (allOnes == false && testGenome[i] == 1) 
		{
			score -= (1.0/tagSize); // 0.01
		}
		//std::cout << i << ", " << allOnes << ", " << testGenome[i] << " : " << score << std::endl;

	}
	return score;
}

void DualWorld::getDualScore(DualAgent& dualAgent, bool addition)
{
	if (addition)
	{
		dualAgent.score = dualAgent.A->score + dualAgent.B->score;
	}
	else
	{
		dualAgent.score = dualAgent.B->score;
	}
	dualAgent.A->dualScore = dualAgent.score;
	dualAgent.B->dualScore = dualAgent.score;
}

std::unordered_map<std::string, std::unordered_set<std::string>> DualWorld::requiredGroups() {
	return { {"A::", {}}, {"B::", {}} };
}
