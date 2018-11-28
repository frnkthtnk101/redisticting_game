/*
 * Tract.cpp
 *
 *      Author: scarbors, frnkthtnk100
 */

#include "Tract.h"

namespace AIProj
{

  Tract::Tract (tractId tId, size_t pop, std::map<tractMetric, size_t> metricMap)
  :  tractId_(tId),
     population_(pop),
     attributeMap_(metricMap)
  {
  }
/*
  Tract::Tract (char C_STATE, int C_TRACT, int C_AREALAND, int C_POP100, int C_H001001, int C_H002001, int C_H002005, int C_H003001, int C_H003002, int C_H003003, int C_P001001, int C_P002001, int C_P002002, int C_P002005, int C_P003001, int C_P003002, int C_P003003, int C_P003004, int C_P003005, int C_P003006, int C_P003007, int C_P003008, int C_P003009, int C_P003010, int C_P003026, int C_P003047, int C_P003063, int C_P003070, int C_P004001, int C_P004002, int C_P004003, int C_P012001, int C_P012002, int C_P012026, int C_P012A001, int C_P012A002, int C_P012A026, int C_P012B001, int C_P012B002, int C_P012B026, int C_P012C001, int C_P012C002, int C_P012C026, int C_P012D001, int C_P012D002, int C_P012D026, int C_P012E001, int C_P012E002, int C_P012E026, int C_P012F001, int C_P012F002, int C_P012F026, int C_P012G001, int C_P012G002, int C_P012G026, int C_P012H001, int C_P012H002, int C_P012H026, int C_P012I001, int C_P012I002, int C_P012I026, int C_P013001, int C_P013A001, int C_P013B001, int C_P013C001, int C_P013D001, int C_P013E001, int C_P013F001, int C_P013G001, int C_P013H001, int C_P013I001)
  {
    // TODO Auto-generated constructor stub
    _STATE = C_STATE;
    _TRACT = C_TRACT;
    _AREALAND = C_AREALAND;
    _POP100 = C_POP100;
    _H001001 = C_H001001;
    _H002001 = C_H002001;
    _H002005 = C_H002005;
    _H003001 = C_H003001;
    _H003002 = C_H003002;
    _H003003 = C_H003003;
    _P001001 = C_P001001;
    _P002001 = C_P002001;
    _P002002 = C_P002002;
    _P002005 = C_P002005;
    _P003001 = C_P003001;
    _P003002 = C_P003002;
    _P003003 = C_P003003;
    _P003004 = C_P003004;
    _P003005 = C_P003005;
    _P003006 = C_P003006;
    _P003007 = C_P003007;
    _P003008 = C_P003008;
    _P003009 = C_P003009;
    _P003010 = C_P003010;
    _P003026 = C_P003026;
    _P003047 = C_P003047;
    _P003063 = C_P003063;
    _P003070 = C_P003070;
    _P004001 = C_P004001;
    _P004002 = C_P004002;
    _P004003 = C_P004003;
    _P012001 = C_P012001;
    _P012002 = C_P012002;
    _P012026 = C_P012026;
    _P012A001 = C_P012A001;
    _P012A002 = C_P012A002;
    _P012A026 = C_P012A026;
    _P012B001 = C_P012B001;
    _P012B002 = C_P012B002;
    _P012B026 = C_P012B026;
    _P012C001 = C_P012C001;
    _P012C002 = C_P012C002;
    _P012C026 = C_P012C026;
    _P012D001 = C_P012D001;
    _P012D002 = C_P012D002;
    _P012D026 = C_P012D026;
    _P012E001 = C_P012E001;
    _P012E002 = C_P012E002;
    _P012E026 = C_P012E026;
    _P012F001 = C_P012F001;
    _P012F002 = C_P012F002;
    _P012F026 = C_P012F026;
    _P012G001 = C_P012G001;
    _P012G002 = C_P012G002;
    _P012G026 = C_P012G026;
    _P012H001 = C_P012H001;
    _P012H002 = C_P012H002;
    _P012H026 = C_P012H026;
    _P012I001 = C_P012I001;
    _P012I002 = C_P012I002;
    _P012I026 = C_P012I026;
    _P013001 = C_P013001;
    _P013A001 = C_P013A001;
    _P013B001 = C_P013B001;
    _P013C001 = C_P013C001;
    _P013D001 = C_P013D001;
    _P013E001 = C_P013E001;
    _P013F001 = C_P013F001;
    _P013G001 = C_P013G001;
    _P013H001 = C_P013H001;
    _P013I001 = C_P013I001;
  }*/

  Tract::~Tract ()
  {
    // TODO Auto-generated destructor stub
  }

  void
  Tract::addAttributes (std::vector<std::pair<tractMetric, size_t> > attributes)
  {
    for(auto vecItr : attributes )
      {
	attributeMap_[vecItr.first] = vecItr.second;
      }
  }

  void
  Tract::addAttribute (const tractMetric& metric, size_t value)
  {
    attributeMap_[metric] = value;
  }

  bool
  Tract::hasAttribute (const tractMetric& metric) const
  {
    return attributeMap_.find(metric) != attributeMap_.end();
  }

  size_t
  Tract::getAttributeValue (const tractMetric& metric) const
  {
    return attributeMap_.at(metric);
  }

} /* namespace AIProj */
