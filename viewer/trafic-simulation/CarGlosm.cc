#include "CarGlosm.hh"

#define METTRE_VECT_3I_x 152
#define METTRE_VECT_3I_y 90

  

enum directions
{
      RIGHT,
      LEFT,
      FORWARD,
      BACKWARD
};









Vector3i CarGlosm::move_from_to(Vector3i& pos_init,Vector3i& pos_final,double step )
{  Vector3i  tmp = pos_final - pos_init ;
   tmp*= 1000; 
   Vector3d  p(tmp.x/(METTRE_VECT_3I_x*step) ,tmp.y/(METTRE_VECT_3I_y*step),1.) ; 
   double module  =  sqrt(pow(p.x,2.) + pow(p.y,2.)) ;
   p.x *= step*1000/module ;
   p.y *= step*1000/module ;		
   p /=   1000 ;	
   return  FromLocalMetric(p,pos_init) ;


} 
  


Vector3i CarGlosm::step_move(Vector3i& pos_,int dir,double angle,double step )
{    Vector3d meter_vect(1.,1.,1.)  ;    //<= a definir comme un mettre
    //Vector3d ten_meters_vector(10.,10.,10.)  ;    //<= a definir comme un mettre 

   if(dir == RIGHT)
   {  meter_vect.x *=   step* cos( ((angle+90)*PI/180) )  ; 
      meter_vect.y *=   step* sin( ((angle+90)*PI/180) )  ;
      return   FromLocalMetric(meter_vect,pos_) ; 
   } 
   if(dir == LEFT)
   {  meter_vect.x *=     step* cos( ((angle-90)*PI/180) )  ; 
      meter_vect.y *=     step* sin( ((angle-90)/180) )  ;
      return   FromLocalMetric(meter_vect,pos_) ; 
   } 
   if(dir == FORWARD)
   {  meter_vect.x *= step*cos(angle*PI/180)  ; 
      meter_vect.y *= step*sin(angle*PI/180)  ;
      return   FromLocalMetric(meter_vect,pos_) ; 
   } 

   if(dir == BACKWARD)
   {  meter_vect.x *=       step* cos( ((angle-180)*PI/180))  ; 
      meter_vect.y *=       step* sin( ((angle-180)*PI/180))  ;
      return   FromLocalMetric(meter_vect,pos_) ;  
   } 


   return pos_ ; 
} 


std::vector<Vector3i> CarGlosm::GetPointsTrajectoryFromTo(Vector3i *pos_init,Vector3i *pos_final,double step,double stop_dist )
{ std::vector<Vector3i> vect_out ; 
  int nb = 500 ;
  Vector3i c0 =  *pos_init  ; 
  Vector3i c1 =  *pos_final ; 
  
  for(int i=0;mod_meter(c0,c1)>stop_dist  && i < nb    ;i++,c0=move_from_to(c0,c1,step), vect_out.push_back(c0)  )  
  { //fprintf (stderr, "\nDist : %f",mod_meter(c0,c1));
    if (mod_meter(c0,c1)>stop_dist )
       vect_out.push_back(*pos_final) ;
  }
  return vect_out ; 

}



void CarGlosm::WriteTrajectory(GPXWriter *writer,std::vector<Vector3i> *vect) 
{  std::vector<Vector3i>::iterator it ;
   Vector3i v ; 

      for(it = vect->begin(); it != vect->end(); it++)
      {   v = *it ; 
          writer->WritePoint(&v); 
      }
         
}



double CarGlosm::mod_meter(Vector3i& from,Vector3i& to)
{  Vector3i vect = to - from ; 
  return sqrt(pow(vect.x/METTRE_VECT_3I_x,2) + pow(vect.y/METTRE_VECT_3I_y,2)) ;

}


void*  my_thread_process(void* arg) 
{
  std::string name("GPX_out_thread/GPX_out_")  ; 
  CarGlosm* car = static_cast<CarGlosm*>(arg) ;
  std::auto_ptr<PreloadedXmlDatasource> osm_datasource_;
  osm_datasource_.reset(new PreloadedXmlDatasource);
  osm_datasource_->Load( car->OSMfileName );
  std::vector<OsmDatasource::Way> ways ;
  std::vector<OsmDatasource::Way>::iterator it ;


   std::string Result ;          
   ostringstream convert ;  
   convert << car->ID ;    
   Result = convert.str() ; 
   name += Result   ;
   name += ".gpx"   ;
   GPXWriter writer ;
   writer.Init(name.c_str()) ;	


    Vector3d step(1.,1.,1.)  ;    
    int coef = 100 ; 
    /* 
    //car->CarContainer_->display_conatainer_car_list_element() ;
    std::vector< struct CarGlosm >::iterator itc  ;
    itc =  car->CarContainer_->CarContainer_.begin() ;
    Vector3i c0 =  itc->pos_  ;  */  
  
      Vector3i c0((int)(-29.53850173950195*10000000),(int)(53.89432144165039*10000000) );
      Vector3i c1((int)(-29.53850173950195*10000000) + METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) + METTRE_VECT_3I_y*coef   );  
      Vector3i c2((int)(-29.53850173950195*10000000) + METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) - METTRE_VECT_3I_y*coef   );
      Vector3i c3((int)(-29.53850173950195*10000000) - METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) + METTRE_VECT_3I_y*coef   );
      Vector3i c4((int)(-29.53850173950195*10000000) - METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) - METTRE_VECT_3I_y*coef   );



//Testing many trajectories
    std::vector<Vector3i> test   = car->GetPointsTrajectoryFromTo(&c0,&c1,3.,5. ) ; 
    car->WriteTrajectory(&writer,&test)  ; 
    test   = car->GetPointsTrajectoryFromTo(&c0,&c2,3.,5. ) ; 
    car->WriteTrajectory(&writer,&test)  ; 
    test   = car->GetPointsTrajectoryFromTo(&c0,&c3,3.,5. ) ; 
    car->WriteTrajectory(&writer,&test)  ; 
    test   = car->GetPointsTrajectoryFromTo(&c0,&c4,3.,5. ) ; 
    car->WriteTrajectory(&writer,&test)  ; 



//Testing BBoxi :: In the future, all the stufs relatives to BBox must be implementer in 
// 		   Class  CarNavigationHandler

    car->pos_ = c0  ;

    BBoxi b(  car->pos_.x - METTRE_VECT_3I_x*coef   , car->pos_.y + METTRE_VECT_3I_y*coef  , car->pos_.x + METTRE_VECT_3I_x*coef , car->pos_.y - METTRE_VECT_3I_y*coef )  ;
    osm_datasource_->GetWays(ways,b) ;
    fprintf(stderr,"Nb way%d \n", ways.size() ) ;
    std::map<std::string, std::string>::iterator it_TagsMap;
   

        for(it = ways.begin(); it != ways.end(); it++)
        { fprintf(stderr," Nb Tags  : %d \n",(it->Tags).size()) ;
        
           for(it_TagsMap = it->Tags.begin(); it_TagsMap != it->Tags.end(); it_TagsMap++)
            { fprintf(stderr,"	Tags : (%s), (%s)\n",(it_TagsMap->first).c_str() , (it_TagsMap->second).c_str() ) ; }
          
        } 
    
   


  pthread_exit (0);

}



int CarGlosm::is_way_in_BBox(BBoxi *b,std::auto_ptr<PreloadedXmlDatasource> osm_datasource_) 
{  
  std::vector<OsmDatasource::Way> ways ;
  std::vector<OsmDatasource::Way>::iterator it ;

  osm_datasource_->GetWays(ways,*b) ;


  fprintf(stderr,"Nb way%d \n", ways.size() ) ;
  

  if (!ways.empty())
    return 1 ; 

  return 0 ; 
}

void CarGlosm::Start_thread_detatched()
{
  pthread_t th1;
  pthread_attr_t thread_attr;

  if (pthread_attr_init (&thread_attr) != 0) {
    fprintf (stderr, "pthread_attr_init error");
    exit (1);
  }

  if (pthread_attr_setdetachstate (&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
    fprintf (stderr, "pthread_attr_setdetachstate error");

    exit (1);
  }



  if (pthread_create (&th1, &thread_attr, my_thread_process, this) < 0) {
    fprintf (stderr, "pthread_create error for thread 1\n");
    exit (1);
  }

}


CarGlosm::CarGlosm(Vector3i *pos, CarGlosmContainer *CarContainer)
{ pos_ = *pos ; 
  CarContainer_ = CarContainer ; 
}

void CarGlosm::Start_thread()
{
  pthread_t th1;
  void *ret;

  if (pthread_create(&th1, NULL, my_thread_process,this)) {
     fprintf (stderr, "pthread_create error for thread 1\n");
     exit(0);}

  (void)pthread_join(th1, &ret);

}



CarGlosm::~CarGlosm(){}

int CarGlosmContainer::nb_car(){ return  CarContainer_.size() ; }

CarGlosmContainer::CarGlosmContainer()
{  }


void  CarGlosmContainer::LoadCarList(std::string filename_in)
{    get_data(filename_in)  ;

     std::vector< struct car_list_element >::iterator itt  ;
    
    for( itt  = conatainer_car_list_element.begin() ;itt != conatainer_car_list_element.end();itt++ ) 
         add_car_to_Container(new Vector3i((int)(itt->x*10000000 ),(int)(itt->y*10000000 ) )  ) ;
 
}

void CarGlosmContainer::start_all_thread() 
{  std::vector<class CarGlosm >::iterator it_car ; 


 	   for (it_car_= CarContainer_.begin();it_car_ < CarContainer_.end(); it_car_++)
           {  it_car_->Start_thread() ; }

}
void CarGlosmContainer::add_car_to_Container( Vector3i  *v)
{       CarGlosm car(v,this) ;
	car.OSMfileName =  OSMfileName.c_str() ; 
	car.ID = nb_car() ; 
  	CarContainer_.push_back(car) ; 

}



CarGlosmContainer::~CarGlosmContainer(){}

void CarGlosmContainer::LoadOSMFile(std::string filename_in)
{ OSMfileName = filename_in ; }







