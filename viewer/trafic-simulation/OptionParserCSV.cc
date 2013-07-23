#include "OptionParserCSV.hh"


        OptionParserCSV::OptionParserCSV(){} ; 
        OptionParserCSV::~OptionParserCSV(){} ;


        int OptionParserCSV::taille(void)
	{return conatainer_car_list_element.size() ;}

	void OptionParserCSV::disp_car_list_element(struct car_list_element *n) 
	{
	   std::cout<< std::endl<< "node_Id :" << n->Id << std::endl     ;
	   std::cout<< "id :" <<   n->x << std::endl		         ;
	   std::cout<< "lat :"<< n->y << std::endl     			 ;			
	}

        void OptionParserCSV::display_conatainer_car_list_element(void) 
	{ std::vector< struct car_list_element >::iterator it;
	  
	  if(conatainer_car_list_element.empty())
	  { std::cerr<<std::endl<<"ERROR :conatainer_car_list_element : empty"<<std::endl ;  }
	 
	  
	  for (it=conatainer_car_list_element.begin();it < conatainer_car_list_element.end(); it++)
	  {	 
	  	  fprintf(stderr, "Id : %d\n" , it->Id)     ;
	          fprintf(stderr, "x :  %f\n" , it->x)     ;
		  fprintf(stderr, "y :  %f\n" , it->y)     ;
		
	  }
	}


	int  OptionParserCSV::csv_line_to_( std::string  *l ,struct car_list_element *n)
	{
	   char buff[500] ;  
	   char temp[200] ; 
	   int NB  = 10 ; 
	   int i ;
	   char *pt ; 
	   strcpy(&buff[0],l->c_str()) ;
	   char delimiter[10] =   " ,\"" ;
           int ignored_line_NB =  0 ; 
	 
	  i = 0  ; 
	  pt = strtok (buff,delimiter);


	  while (pt != NULL)
	  {

	  switch (i)
		 {      case 0 :  sscanf (pt,"%d",&(n->Id)) ;
				  //fprintf(stderr,"%d\n",n->Id);	
				break;
			case 1 :   // sscanf (pt,"%f",&(n->id)) ; 
				break;
			case 2 :   sscanf (pt,"%f",&(n->x)) ; 
			          // fprintf(stderr," %f",n->x);		
				break;
			case 3 :   sscanf (pt,"%f",&(n->y)) ; 
				  // fprintf(stderr,"%f",n->y);	
				break;

		  }
		  pt = strtok (NULL, delimiter);
		  i++  ; 
	      
	 }


	   return 1 ; 
	}


	int OptionParserCSV::get_data(std::string filename_in)
	{ struct car_list_element n  ;
	  int i ;
	  std::vector< struct node>::iterator it_infos ;
	  std::ifstream f_in(filename_in.c_str()) ;
          fprintf(stderr, "Loading options file (%s)\n", filename_in.c_str());
	  int ignored_line_NB  = 0  ; 

          
	  if(f_in) 
	  {      std::string  ligne ; 
		 while(getline(f_in, ligne)) 
		  {   //   fprintf(stderr,"%s\n",ligne.c_str());	
				
			 if(!csv_line_to_(&ligne,&n))
			  { std::cerr<<std::endl<<"ERROR :cvs_extraction: conatainer_car_list_element : PROBLEM  "<<std::endl ;  }
			    conatainer_car_list_element.push_back(n) ;
			  
		  }
		  f_in.close(); 
	  }
	  else 
	  {  std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;  return 0 ; }
	  
	  return 1 ; 
	}











