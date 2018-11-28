/*
 * District.cpp
 *
 *      Author: scarbors
 */

#include "District.h"

namespace AIProj
{

  size_t District::idCounter_ = 0;
  size_t District::targetPopulation_ = 0;

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
    const std::shared_ptr<std::set<std::shared_ptr<AIProj::Tract> > >)
{
  //TODO
  return tractId();
}

bool
District::testTractForAdd (const Tract&)
{
  //TODO
  return false;
}

} /* namespace AIProj */
