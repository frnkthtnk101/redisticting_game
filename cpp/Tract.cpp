/*
 * Tract.cpp
 *
 *      Author: scarbors
 */

#include "Tract.h"

namespace AIProj
{

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

  }

  Tract::~Tract ()
  {
    // TODO Auto-generated destructor stub
  }

  char Tract::get_STATE(){
		return _STATE;
  }
  int Tract::get_TRACT(){
		return _TRACT;
  }
  int Tract::get_AREALAND(){
		return _AREALAND;
  }
  int Tract::get_POP100(){
		return _POP100;
  }
  int Tract::get_H001001(){
		return _H001001;
  }
  int Tract::get_H002001(){
		return _H002001;
  }
  int Tract::get_H002005(){
		return _H002005;
  }
  int Tract::get_H003001(){
		return _H003001;
  }
  int Tract::get_H003002(){
		return _H003002;
  }
  int Tract::get_H003003(){
		return _H003003;
  }
  int Tract::get_P001001(){
		return _P001001;
  }
  int Tract::get_P002001(){
		return _P002001;
  }
  int Tract::get_P002002(){
		return _P002002;
  }
  int Tract::get_P002005(){
		return _P002005;
  }
  int Tract::get_P003001(){
		return _P003001;
  }
  int Tract::get_P003002(){
		return _P003002;
  }
  int Tract::get_P003003(){
		return _P003003;
  }
  int Tract::get_P003004(){
		return _P003004;
  }
  int Tract::get_P003005(){
		return _P003005;
  }
  int Tract::get_P003006(){
		return _P003006;
  }
  int Tract::get_P003007(){
		return _P003007;
  }
  int Tract::get_P003008(){
		return _P003008;
  }
  int Tract::get_P003009(){
		return _P003009;
  }
  int Tract::get_P003010(){
		return _P003010;
  }
  int Tract::get_P003026(){
		return _P003026;
  }
  int Tract::get_P003047(){
		return _P003047;
  }
  int Tract::get_P003063(){
		return _P003063;
  }
  int Tract::get_P003070(){
		return _P003070;
  }
  int Tract::get_P004001(){
		return _P004001;
  }
  int Tract::get_P004002(){
		return _P004002;
  }
  int Tract::get_P004003(){
		return _P004003;
  }
  int Tract::get_P012001(){
		return _P012001;
  }
  int Tract::get_P012002(){
		return _P012002;
  }
  int Tract::get_P012026(){
		return _P012026;
  }
  int Tract::get_P012A001(){
		return _P012A001;
  }
  int Tract::get_P012A002(){
		return _P012A002;
  }
  int Tract::get_P012A026(){
		return _P012A026;
  }
  int Tract::get_P012B001(){
		return _P012B001;
  }
  int Tract::get_P012B002(){
		return _P012B002;
  }
  int Tract::get_P012B026(){
		return _P012B026;
  }
  int Tract::get_P012C001(){
		return _P012C001;
  }
  int Tract::get_P012C002(){
		return _P012C002;
  }
  int Tract::get_P012C026(){
		return _P012C026;
  }
  int Tract::get_P012D001(){
		return _P012D001;
  }
  int Tract::get_P012D002(){
		return _P012D002;
  }
  int Tract::get_P012D026(){
		return _P012D026;
  }
  int Tract::get_P012E001(){
		return _P012E001;
  }
  int Tract::get_P012E002(){
		return _P012E002;
  }
  int Tract::get_P012E026(){
		return _P012E026;
  }
  int Tract::get_P012F001(){
		return _P012F001;
  }
  int Tract::get_P012F002(){
		return _P012F002;
  }
  int Tract::get_P012F026(){
		return _P012F026;
  }
  int Tract::get_P012G001(){
		return _P012G001;
  }
  int Tract::get_P012G002(){
		return _P012G002;
  }
  int Tract::get_P012G026(){
		return _P012G026;
  }
  int Tract::get_P012H001(){
		return _P012H001;
  }
  int Tract::get_P012H002(){
		return _P012H002;
  }
  int Tract::get_P012H026(){
		return _P012H026;
  }
  int Tract::get_P012I001(){
		return _P012I001;
  }
  int Tract::get_P012I002(){
		return _P012I002;
  }
  int Tract::get_P012I026(){
		return _P012I026;
  }
  int Tract::get_P013001(){
		return _P013001;
  }
  int Tract::get_P013A001(){
		return _P013A001;
  }
  int Tract::get_P013B001(){
		return _P013B001;
  }
  int Tract::get_P013C001(){
		return _P013C001;
  }
  int Tract::get_P013D001(){
		return _P013D001;
  }
  int Tract::get_P013E001(){
		return _P013E001;
  }
  int Tract::get_P013F001(){
		return _P013F001;
  }
  int Tract::get_P013G001(){
		return _P013G001;
  }
  int Tract::get_P013H001(){
		return _P013H001;
  }
  int Tract::get_P013I001(){
		return _P013I001;
  }

} /* namespace AIProj */

//compile testing
/*int main(){
  return 1;
}*/