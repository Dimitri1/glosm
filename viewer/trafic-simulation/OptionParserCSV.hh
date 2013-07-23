#ifndef Included_Parser_options_H
#define Included_Parser_options_H






#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>




struct car_list_element
{

  int Id ; 
  float x; 
  float y; 

}  ; 




class   OptionParserCSV
{

 public : 

	    std::vector< struct car_list_element > conatainer_car_list_element  ; 
        OptionParserCSV() ; 
       ~OptionParserCSV() ;
        int taille(void);
	void disp_car_list_element(struct car_list_element *n)  ;
        void display_conatainer_car_list_element(void) ; 
	int  csv_line_to_( std::string  *l ,struct car_list_element *n)  ;
        int  get_data(std::string filename_in)  ;

} ;
















#endif 


