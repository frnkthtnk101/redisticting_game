/*
 * District.cpp
 *
 *      Author: scarbors
 */

#include "District.h"

#include "GameState.h"

#include <cstring>
#include <cstdlib>
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

  int bestVoice = 0;
  std::shared_ptr<AIProj::Tract> bestTract;

  for(auto tct :*availableTracts)
    {
      //Determine the tracts voice
      int voice = 0;
      std::set<tractId> ignoreList;
      calculateChoice(voice, tct, tractChoiceDepth_,gState,ignoreList);

      if(voice > bestVoice)
	{
	 bestVoice = voice;
	 bestTract = tct;
	}
    }

  //Select the best tract
  tractId rValue = 0;
  if(bestTract)
    {
      rValue = bestTract->getId();

      addTract(bestTract);
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
  if( targetPopulation_> (tct->getPopulation() + getCurrentPopulation())
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

} /* namespace AIProj */

