/*
 * District.cpp
 *
 *      Author: scarbors
 */

#include "District.h"

#include <map>
#include <set>

namespace AIProj
{

  size_t District::idCounter_ = 0;
  size_t District::targetPopulation_ = 0;
  size_t District::similarityLimit_ = 55;

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
District::makeTractDecision (
    const std::shared_ptr<std::set<std::shared_ptr<AIProj::Tract> > > availableTracts)
{
  //Create Value mapping
  std::map<std::shared_ptr<AIProj::Tract>, int> bestChoices;

  int bestVoice = 0;
  std::shared_ptr<AIProj::Tract> bestTract;

  for(auto tct :*availableTracts)
    {
      //Determine the tracts voice
      int voice = 0;
      calculateChoice(voice, tct);

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
District::calculateChoice (int &voice, std::shared_ptr<AIProj::Tract> tct)
{
  //TODO: Populations of all districts must be within 10% of each other
  if( (tct->getPopulation() + getCurrentPopulation() <= targetPopulation_)
      && noRacialBias(tct) )
    {
      voice++; //???? Is this supposed to be here?
      if(similar(tct))
	{
	  voice++;
	}

      //????????????????
      //TODO
      //Why look at the adjacent tracts here?
      //list-adjacent = District::get-track-boundry-tracks(tract)
      //foreach ls_ad in list-adjacent{
      //    voice = calculate_choice(voice, ls_ad)
      //????????????????
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
	  if(metric.second == metricTotals_.at(metric.first)) //??? Is equality the right thing here
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
