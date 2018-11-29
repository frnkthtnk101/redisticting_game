/*
 * District.cpp
 *
 *      Author: scarbors
 */

#include "District.h"

#include "GameState.h"

#include <cstdlib>
#include <map>
#include <set>

namespace AIProj
{

  size_t District::idCounter_ = 0;
  int District::targetPopulation_ = 0;
  size_t District::similarityLimit_ = 55;
  size_t District::tractChoiceDepth_ = 1;

  District::District ()
  : districtId_(idCounter_),
	population_(0)
  {
	  idCounter_++;
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
  tractId rValue = std::make_pair(0,0);
  if(bestTract)
    {
      rValue = bestTract->getId();
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
  //TODO: Populations of all districts must be within 10% of each other
  if( std::abs(targetPopulation_- (tct->getPopulation() + getCurrentPopulation())) == 0
      && noRacialBias(tct) )
    {
      voice++; //???? Is this supposed to be here?
      if(similar(tct))
	{
	  voice++;
	}

      //Make sure we don't reconsider this tract
      ignoreList.insert(tct->getId());

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
  //TODO
//  disimilarity = 0 ;
//  Tract_index = -1

  size_t disimilarity = 0;
  auto tctMetrics = tct->getAttributeMap();

  for(auto metric : tctMetrics )
    {
      if( similarityLimit_ > disimilarity)
	{
	  if(metric.second == metricTotals_.at(metric.first)) //TODO:?? Is equality the right thing here
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


} /* namespace AIProj */
