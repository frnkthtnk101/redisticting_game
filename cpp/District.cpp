/*
 * District.cpp
 *
 *      Author: scarbors
 */

#include "District.h"

#include "GameState.h"

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>

namespace AIProj
{

  int District::targetPopulation_ = 0;
  size_t District::similarityLimit_ = 55;
  size_t District::tractChoiceDepth_ = 1;

  District::District (districtId dId)
  : districtId_(dId),
	population_(0)
  {
  }

  District::~District ()
  {
    // TODO Auto-generated destructor stub
  }

tractId
District::makeTractDecision (AIProj::GameState &gState )
{
  //Get Available Tracts
  const std::shared_ptr< std::set< std::shared_ptr<AIProj::Tract> > > availableTracts
           = gState.getAvailableTracts(getId());

  //Create Value mapping
  std::map<std::shared_ptr<AIProj::Tract>, int> bestChoices;

  //The best
  int bestVoice = 0;
  double bestCohesion = 0.0;
  std::shared_ptr<AIProj::Tract> bestTract;

  //The weighted best
  int wBestVoice = 0;
  double wBestCohesion = 0.0;
  double weight = 0.0;
  std::shared_ptr<AIProj::Tract> wBestTract;


  for(auto tct :*availableTracts)
    {
      //????????????
//      std::cout << "   Start Tract " << tct->getId()
//	  << std::endl << std::flush;
      //????????????
      //Determine the tracts voice
      int voice = 0;
      std::set<tractId> ignoreList;
      calculateChoice(voice, tct, tractChoiceDepth_,gState,ignoreList);
      double cohesion = tct->getCohesionValue(districtId_);

      //Test for best case
      if( (voice > bestVoice)
	  && (cohesion > bestCohesion ))
	{
	 bestVoice = voice;
	 bestTract = tct;
	 bestCohesion = cohesion;
	}

      //Test for weighted best
      double newWeight = double(voice) * cohesion;
      if( newWeight > weight)
	{
	 wBestVoice = voice;
	 wBestTract = tct;
	 wBestCohesion = cohesion;
	 weight = newWeight;
	}

      //????????????
//      std::cout << "   -->End Tract " << tct->getId()
//	  << std::endl << std::flush;
      //????????????
    }

  //Select the best tract
  tractId rValue = 0;
  if(bestTract || wBestTract)
    {
      double newWeight = double(bestVoice) * bestCohesion;
      std::shared_ptr<AIProj::Tract> finalBest = decideOnBestTract(bestTract,
								    bestVoice,
								    bestCohesion,
								    newWeight,
								    wBestTract,
								    wBestVoice,
								    wBestCohesion,
								    weight);
      rValue = finalBest->getId();
    }

  return rValue;
}

void
District::calculateChoice (int &voice,
			   std::shared_ptr<AIProj::Tract> tct,
			   int depthToGo,
			   AIProj::GameState &gState,
			   std::set<tractId> &ignoreList)
{
  //if( std::abs(targetPopulation_- (tct->getPopulation() + getCurrentPopulation())) == 0
  if( targetPopulation_> (tct->getPopulation() + population_)
      && noRacialBias(tct) )
    {
      voice++; //???? Is this supposed to be here? why yes it is
      if(similar(tct))
	{
	  voice++;
	}

      //Make sure we don't reconsider this tract
      ignoreList.insert(tct->getId()); //ok i like it. I think i know why you did this

      //Get Available Tracts
      const std::shared_ptr< std::set< std::shared_ptr<AIProj::Tract> > > availableTracts
               = gState.getAvailableTractsForATract(tct->getId(),ignoreList);

      //Calculate each of their voice
      for(auto tctItr : *availableTracts)
      {
        calculateChoice(voice, tctItr, --depthToGo, gState,ignoreList);
      }
    }
}

bool District::noRacialBias(std::shared_ptr<AIProj::Tract> tract)
{
  //TODO
  return true;
}


bool
District::similar(std::shared_ptr<AIProj::Tract>  tct)
{
  size_t disimilarity = 0;
  auto tctMetrics = tct->getAttributeFractionMap();

  for(auto metric : tctMetrics )
    {
      if( similarityLimit_ > disimilarity)
	{
	  double mtf= metricFractions_.at(metric.first);
	  double mtfRange = mtf * 0.1;
	  if(  ((mtf - mtfRange)<= metric.second )
	      && (metric.second <= (mtf + mtfRange)) )//??
	    {
	      continue;
	    }
	  else
	    {
	      disimilarity++;
	    }
	}
      else
	{
	  return false;
	}
    }

  return true;
}

std::map<districtId, tractId>
District::createDistricts (std::string starterFile, std::vector<std::shared_ptr<AIProj::District>> &districts)
{
  std::map<districtId, tractId> alignmentMap;

  //Open the district data file
  std::ifstream dFile(starterFile);
  std::string temp;

  if(! dFile.is_open())
    {
      const char * errorStr = std::strerror(errno);

      std::cerr << "Failure to open starter file "
	  << starterFile << ": " << errorStr
	  << std::endl << std::flush;
      exit(EXIT_FAILURE);
    }
  //Get the header
  std::getline(dFile,temp);

  //Read in the pairs, saving them off and creating districts for each
  while(std::getline(dFile,temp))
    {
      //Read input line
      std::stringstream line(temp);

      size_t dId, tId;
      char comma;
      line >> dId >> comma >> tId;

      //Process into map
      alignmentMap[dId] = tId;

      //Create a district
      std::shared_ptr<District> district(new District(dId));
      districts.push_back(district);
    }

  return alignmentMap;
}

void
District::dump (std::ofstream& fout)
{
    for(auto tct : ownedTracts_)
      {
	fout << districtId_
	    << "," << tct->getCountyId()
	    << "," << tct->getFullTract()
	    << "," << tct->getId()
	    << std::endl;
      }
}

std::shared_ptr<Tract>
District::decideOnBestTract(std::shared_ptr<Tract> &bestVoiceT,
			    int &bestVoice,
			    double &bestCohesion,
			    double &bestWeight,
			    std::shared_ptr<Tract> &bestWeightT,
			    int &wBestVoice,
			    double &wBestCohesion,
			    double &wBestWeight)
{
  std::shared_ptr<Tract> finalBest;

  if(bestVoiceT && bestWeightT)
    {
      //If they're the same, easy
      if(bestVoiceT == bestWeightT )
	{
	  finalBest = bestVoiceT;
	  addTract(bestVoiceT);
	}
      //Need to actually decide between them
      else
	{
	  double bestWeight = double(bestVoice) * bestCohesion;

	  //If they'e close in weight, go with the one most reflective of the tract
	  if( std::abs(bestWeight-wBestWeight) > 0.10)
	    {
	      finalBest = bestVoiceT;
	      addTract(bestVoiceT);
	    }
	  else //Go with the most cohesive
	    {
	      finalBest = bestWeightT;
	      addTract(bestWeightT);
	    }
	}

    }
  //If only one exists, go with that
  else if(bestVoiceT)
    {
      finalBest = bestVoiceT;
      addTract(bestVoiceT);
    }
  else if(bestWeightT)//Go with the most cohesive
    {
      finalBest = bestWeightT;
      addTract(bestWeightT);
    }

  return finalBest;
}



} /* namespace AIProj */

