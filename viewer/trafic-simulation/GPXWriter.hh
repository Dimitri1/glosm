#ifndef Included_GPXWriter_H
#define Included_GPXWriter_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <glosm/GeometryOperations.hh>




using namespace std;


class   GPXWriter {

public:

   std::ofstream a_file ;

    GPXWriter()  ;
   ~GPXWriter()  ;

   void  Init()  ;
   void  Init(const char *out_file_name) ;
   //   void  fct(int a) ; 
   void  WritePoint(float X,float Y) ;
   void  WritePoint(Vector3i *v) ;

   void  Close()  ; 

} ;


#endif 

