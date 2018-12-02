/*
 * mainGm.cpp
 *
 *  Created on: Nov 28, 2018
 *      Author: ShadRS
 */

#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>

#include "District.h"
#include "GameState.h"

void printDistricts(std::vector<std::shared_ptr<AIProj::District>> &districts, AIProj::GameState &gState)
{
  std::ofstream fout("./results.csv");
  std::ofstream fout2("./results2.csv");
  (districts[0])->dumpMetricHeader(fout2);

  for(auto dis : districts)
    {
      dis->dump(fout);

      dis->dumpMetrics(fout2);
    }

  //Print any remaining tracts
  if(gState.getAvailableTracts()->size() > 0)
    {
      auto tracts = gState.getAvailableTracts();
      for(auto tct : *tracts)
	{
	  fout << "-" //Not assigned a district
	      << "," << tct->getCountyId()
	      << "," << tct->getFullTract()
	      << "," << tct->getId()
	      << std::endl;
	}
    }

  fout.close();
}

bool districtSorter(const std::shared_ptr<AIProj::District> &left, const std::shared_ptr<AIProj::District> &right)
{
  return left->getCurrentPopulation() < right->getCurrentPopulation();
}

int main(int argc, char *argv[])
{
  //Create GameState object
  AIProj::GameState gState;

  //Load Data (districts)
  std::cout << "Creating Districts\n" << std::flush;
  std::vector<std::shared_ptr<AIProj::District>> districts;
  std::map<AIProj::districtId, AIProj::tractId> starterTracts
  = AIProj::District::createDistricts("./startingDistricts.csv", districts);

  std::cout << districts.size() << " Districts created\n" << std::flush;

  //Load Data (tracts)
  std::cout << "Creating Tracts\n" << std::flush;
  gState.initializeGameStateFromFile("./tractinfo/tract.txt", "./tractinfo/relationship.txt", districts.size());
  std::cout << gState.getAvailableTracts()->size() << " Tracts created\n" << std::flush;

  AIProj::District::setTargetPopulation(gState.getTargetDistrictSize());

  std::cout << "Pairing Districts with starter tracts\n" << std::flush;

  for(auto dis : districts)
    {
      //Add districts to game state
      AIProj::tractId tId = starterTracts[dis->getId()];
      gState.addDistrict(dis);

      //Pair tracts and Districts
      dis->addTract(gState.getTract(tId));
      gState.setUsedTract(tId,dis->getId());
    }

  std::cout << "Files loaded, preparing to start!\n"
      << gState.getAvailableTracts()->size()
      << " Tracts to be sorted.\n";

  // Get starting timepoint
  auto mainstart = std::chrono::high_resolution_clock::now();

  //Play the game
  bool movesMade = true;
  size_t moves = 0;
  while( gState.getAvailableTracts()->size() && movesMade )
    {
      // Get starting timepoint
      auto start = std::chrono::high_resolution_clock::now();
      moves++;
      std::cout << "Playing round " << moves
	  << ", Remaining tracts: " << gState.getAvailableTracts()->size()
	  << std::endl << std::flush;

      //To prevent getting stuck due to size constraints
      movesMade = false;

      //Sort the districts in low pop to high
      std::sort(districts.begin(), districts.end(), districtSorter);

      //Cycle through the districts
      for(auto dist : districts)
	{
	  std::cout << " District(" << dist->getId() << ") - "
	      << std::flush;

	  //Make Decision
	  AIProj::tractId tctId = dist->makeTractDecision(gState);

	  std::cout << "Tract(" << tctId << ")\n" << std::flush;

	  if(tctId != 0)
	    {
	      //Commit to Tract
	      gState.setUsedTract(tctId,dist->getId());
	      movesMade = true;
	    }
	}

      // Get ending timepoint
      auto stop = std::chrono::high_resolution_clock::now();

      // use duration cast method
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
      std::cout << "Elapsed time: "
	  << duration.count() <<  " seconds"
	  << std::endl << std::flush;
    }

  // Get ending timepoint
  auto mainstop = std::chrono::high_resolution_clock::now();

  // use duration cast method
  auto duration = std::chrono::duration_cast<std::chrono::minutes>(mainstop - mainstart);
  std::cout << "Total Elapsed time: "
	  << duration.count() << " minutes"
	  << std::endl << std::flush;

  //Print the results
  printDistricts(districts,gState);

  if( !movesMade )
    {
      std::cerr << "Stalled on improper moves!\n";
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}


