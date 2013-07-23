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

Vector3i step_move(Vector3i& pos_,int dir,double angle,double step ); 
double mod_meter(Vector3i& from,Vector3i& to) ; 


//Movement functions////////////////////////////////////////////////////////////////////:::


Vector3i move_from_to(Vector3i& pos_init,Vector3i& pos_final,double step )
{  Vector3i  tmp = pos_final - pos_init ;
   tmp*= 1000; 
   Vector3d  p(tmp.x/(METTRE_VECT_3I_x*step) ,tmp.y/(METTRE_VECT_3I_y*step),1.) ; 
   double module  =  sqrt(pow(p.x,2.) + pow(p.y,2.)) ;
   p.x *= step*1000/module ;
   p.y *= step*1000/module ;		
   p /=   1000 ;	
   return  FromLocalMetric(p,pos_init) ;
 
/*
     angle = (180 * atan(double(tmp.y*METTRE_VECT_3I_x/100)/double(tmp.x*METTRE_VECT_3I_y/100)) /PI) ;

     if(tmp.x + tmp.y < 2*step*METTRE_VECT_3I_x ) 
     {return  pos_final ;} 
  
     return step_move(pos_init,FORWARD,angle,step) ;  

*/

} 
  


Vector3i step_move(Vector3i& pos_,int dir,double angle,double step )
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




//////////////////////////////////////////////////////////////////////


double mod_meter(Vector3i& from,Vector3i& to)
{  Vector3i vect = to - from ; 
  return sqrt(pow(vect.x/METTRE_VECT_3I_x,2) + pow(vect.y/METTRE_VECT_3I_y,2)) ;

}


void*  my_thread_process(void* arg) 
{
  int i; 
  std::string name("GPX_out_thread/GPX_out_")  ; 
  CarGlosm* car = static_cast<CarGlosm*>(arg) ;
  std::auto_ptr<PreloadedXmlDatasource> osm_datasource_;
  osm_datasource_.reset(new PreloadedXmlDatasource);
//  osm_datasource_->Load("map/las_vegas.osm");
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




///////TESTING step_move functions 


    Vector3d step(1.,1.,1.)  ;    
    int coef = 100 ; 
   //  writer.WritePoint(&(c0)) ;
   // writer.WritePoint(&(c1)) ;
   // writer.WritePoint(&(c2)) ;
   //  writer.WritePoint(&(c3)) ;
   //  writer.WritePoint(&(c4)) ;

   //   c0 = step_move(c0,RIGHT,1) ; 

    int nb  = 20;

    Vector3i c0((int)(-29.53850173950195*10000000),(int)(53.89432144165039*10000000) );
    Vector3i c1((int)(-29.53850173950195*10000000) + METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) + METTRE_VECT_3I_y*coef   );  
    Vector3i c2((int)(-29.53850173950195*10000000) + METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) - METTRE_VECT_3I_y*coef   );
    Vector3i c3((int)(-29.53850173950195*10000000) - METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) + METTRE_VECT_3I_y*coef   );
    Vector3i c4((int)(-29.53850173950195*10000000) - METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) - METTRE_VECT_3I_y*coef   );



    //writer.WritePoint(&(c0)) ;
    writer.WritePoint(&(c1))  ;
    writer.WritePoint(&(c2))  ;
    writer.WritePoint(&(c3))  ;
    writer.WritePoint(&(c4))  ;

  /*  
   for(angle = 0 ; angle<=200;angle += 10)  
   {for(i=0;i<nb;i++,c0 = step_move(c0,FORWARD,angle,1), writer.WritePoint(&(c0))){ }
      c0 =   Vector3i((int)(-29.53850173950195*10000000),(int)(53.89432144165039*10000000) );}
   for(angle = 0 ; angle<=200;angle += 10)  
   {for(i=0;i<nb;i++,c1 = step_move(c1,BACKWARD,angle,1), writer.WritePoint(&(c1))){ }
      c1 =  Vector3i ((int)(-29.53850173950195*10000000) + METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) + METTRE_VECT_3I_y*coef   );  }
   for(angle = 0 ; angle<=200;angle += 10)  
   {for(i=0;i<nb;i++,c2 = step_move(c2,RIGHT,angle,1), writer.WritePoint(&(c2))){ }
      c2 =  Vector3i ((int)(-29.53850173950195*10000000) + METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) - METTRE_VECT_3I_y*coef   );}
   for(angle = 0 ; angle<=200;angle += 10)  
   {for(i=0;i<nb;i++,c3 = step_move(c3,LEFT,angle,1), writer.WritePoint(&(c3))){ }
      c3 =  Vector3i  ((int)(-29.53850173950195*10000000) - METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) - METTRE_VECT_3I_y*coef   );    
   }


*/
//////   



//Testing  move_from_to///

  /*
    c0 = Vector3i((int)(-29.53850173950195*10000000),(int)(53.89432144165039*10000000) );
    c1 = Vector3i((int)(-29.53850173950195*10000000) + METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) + METTRE_VECT_3I_y*coef   );  
    c2 = Vector3i((int)(-29.53850173950195*10000000) + METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) - METTRE_VECT_3I_y*coef   );
    c3 = Vector3i((int)(-29.53850173950195*10000000) - METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) + METTRE_VECT_3I_y*coef   );
    c4 = Vector3i((int)(-29.53850173950195*10000000) - METTRE_VECT_3I_x*coef ,(int)(53.89432144165039*10000000) - METTRE_VECT_3I_y*coef   );

*/

  nb = 500 ; 
  for(i=0;  mod_meter(c0,c1)>10 ;i++,c0=move_from_to(c0,c1,10), writer.WritePoint(&c0)  )  
  {fprintf(stderr,"Dist : %f \n", mod_meter(c0,c1) )  ;} 

 
    c0 = Vector3i((int)(-29.53850173950195*10000000),(int)(53.89432144165039*10000000) );
  for(i=0;i<nb;i++,c0=move_from_to(c0,c2,10), writer.WritePoint(&c0)  )  
  {}
    c0 = Vector3i((int)(-29.53850173950195*10000000),(int)(53.89432144165039*10000000) );
  for(i=0;i<nb;i++,c0=move_from_to(c0,c3,10), writer.WritePoint(&c0)  )  
  {}

    c0 = Vector3i((int)(-29.53850173950195*10000000),(int)(53.89432144165039*10000000) );
  for(i=0;i<nb;i++,c0=move_from_to(c0,c4,10), writer.WritePoint(&c0)  )  
  {}



////



    car->pos_ = Vector3i((int)(-29.53850173950195*10000000)  ,(int)(53.89432144165039*10000000) ) ;

    BBoxi b(  car->pos_.x - METTRE_VECT_3I_x*coef   , car->pos_.y + METTRE_VECT_3I_y*coef  , car->pos_.x + METTRE_VECT_3I_x*coef , car->pos_.y - METTRE_VECT_3I_y*coef )  ;
    osm_datasource_->GetWays(ways,b) ;
    fprintf(stderr,"Nb way%d \n", ways.size() ) ;
    std::map<std::string, std::string>::iterator it_TagsMap;
   
    if(ways.size() != 0 )
    { 
        for(it = ways.begin(); it != ways.end(); it++)
        { fprintf(stderr," Nb Tags  : %d \n",(it->Tags).size()) ;
          if( (it->Tags).size() != 0  )
          { for(it_TagsMap = it->Tags.begin(); it_TagsMap != it->Tags.end(); it_TagsMap++)
            { fprintf(stderr,"	Tags : (%s), (%s)\n",(it_TagsMap->first).c_str() , (it_TagsMap->second).c_str() ) ; }
          }
        } 
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


CarGlosm::CarGlosm(Vector3i *pos, std::vector<class CarGlosm> *CarContainer)
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


void CarGlosmContainer::LoadCarList(std::string filename_in)
{ get_data(filename_in) ;}

void CarGlosmContainer::add_car_to_Container( Vector3i  *v)
{       CarGlosm car(v,&CarContainer_) ;
	car.OSMfileName =  OSMfileName.c_str() ; 
	car.ID = nb_car() ; 
  	CarContainer_.push_back(car) ; 

}



CarGlosmContainer::~CarGlosmContainer(){}

void CarGlosmContainer::LoadOSMFile(std::string filename_in)
{ OSMfileName = filename_in ; }







