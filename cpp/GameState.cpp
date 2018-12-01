/*
 * GameState.cpp
 *
 *      Author: scarbors
 */

#include <cmath>
#include <cstring>

#include <fstream>
#include <iostream>
#include <sstream>

#include "GameState.h"
#include "Tract.h"

namespace AIProj
{

  GameState::GameState ()
  :  targetDistrictSize_ (0),
     unusedTractList_(new std::set<std::shared_ptr<AIProj::Tract> >() ),
     usedTractList_(new std::set<std::shared_ptr<AIProj::Tract> >() )
  {

  }

  GameState::~GameState ()
  {
    //Using shared_ptrs so no need to manually delete
  }

  void
  GameState::initializeGameStateFromFile(std::string tractFile, std::string adjacencyFile, size_t dCount)
  {
    //Districts must be created first
    if( dCount == 0)
      return;

    //Open the data files and ensure they're both good before we do any processing
    std::ifstream tFile(tractFile);
    std::ifstream aFile(adjacencyFile);

    if( !tFile.is_open() || !aFile.is_open())
      {
	if(tFile.fail())
	  {
	      const char * errorStr = std::strerror(errno);
	      std::cerr << "Failure to open Tract file "
		  << tractFile << ": " << errorStr
		  << std::endl << std::flush;
	  }

	if(aFile.fail())
	  {
	      const char * errorStr = std::strerror(errno);
	      std::cerr << "Failure to open Adjacency file "
		  << adjacencyFile << ": " << errorStr
		  << std::endl << std::flush;
	  }

	exit(EXIT_FAILURE);
      }

    std::string temp;

    //Get the header
    std::getline(tFile,temp);
    std::stringstream header(temp);

    //Unused portion of the header
    header >> temp >> temp >> temp >> temp >> temp >> temp >> temp;
    std::vector<std::string> metricHeaders;
    while(header.good())
      {
	header >> temp;
	metricHeaders.push_back(temp);
      }

    //Loop until end of file
    while(std::getline(tFile,temp))
      {
	//Read in the elements
	std::stringstream line(temp);
	int state = -1,tract = -1,county = -1,arealand = -1, pop = -1;
	size_t fid, metric;
	std::string gisjoin = "";
	std::vector<int> metricValues;

	line >> state;
	line >> tract;
	line >> county;
	line >> gisjoin;
	line >> fid;
	line >> arealand;
	line >> pop;

	//Test print
	//	std::cout << "\nTest Dump: "
	//	    << state << " - "
	//	    << tract << " - "
	//	    << county << " - "
	//	    << gisjoin<< " - "
	//	    << fid << " - "
	//	    << arealand
	//	    << std::endl << std::flush;

	//Metrics
	while(line.good())
	  {
	    line >> metric;
	    metricValues.push_back(metric);
	  }

	//Create metric map object
	std::map<std::string, size_t> metricMap;
	for(size_t idx = 0; idx < metricHeaders.size() && idx < metricValues.size(); idx++)
	  {
	    metricMap[metricHeaders.at(idx)] = metricValues.at(idx);
	  }

	//Create Tract Objects
	std::shared_ptr<Tract> nTract(new Tract(fid,pop,metricMap));

	//Add the tract to our lists
	tractId tId = nTract->getId();
	unusedTractList_->insert(nTract);
	tractMap_[tId] = nTract;

	//Keep track of the population
	targetDistrictSize_ += pop;
      }

    //Close the file
    tFile.close();

    //Remove the header
    std::getline(aFile,temp);

    //Loop until the end of the file
    while(std::getline(aFile,temp))
      {
	//Read in the elements
	std::stringstream line(temp);
	size_t fid, nid;

	line >> fid >> nid;

	//Add adjacancies to the tracts
	if( (tractMap_.find(fid) != tractMap_.end())
	    && (tractMap_.find(nid) != tractMap_.end())) //Only include adjacensies from this state
	  {
	    (tractMap_[fid])->addNeighbor(tractMap_[nid]);
	  }
      }

    aFile.close();

    //Determine total Pop and set targetDistrictSize_
    targetDistrictSize_ = targetDistrictSize_ / dCount;

    //Allow for a 5% variance
    targetDistrictSize_ = std::ceil( ((double) targetDistrictSize_) * 1.05);
  }

} /* namespace AIProj */
