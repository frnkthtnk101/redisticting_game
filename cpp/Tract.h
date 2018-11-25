/*
 * Tract.h
 *
 *      Author: scarbors
 */

#ifndef TRACT_H_
#define TRACT_H_

namespace AIProj
{
  typedef size_t tractId;
  typedef std::string tractMetric;

  class Tract
  {
  public:

    Tract ();
    virtual
    ~Tract ();
  };

} /* namespace AIProj */

#endif /* TRACT_H_ */
