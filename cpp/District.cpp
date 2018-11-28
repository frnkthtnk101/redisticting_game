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

} /* namespace AIProj */
