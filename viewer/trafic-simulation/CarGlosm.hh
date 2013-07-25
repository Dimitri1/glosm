#ifndef Included_CarGlosm_H
#define Included_CarGlosm_H




#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#include <pthread.h>

#include <cstdio>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream> 


#include <glosm/DummyHeightmap.hh>
#include <glosm/FirstPersonViewer.hh>
#include <glosm/GPXLayer.hh>
#include <glosm/GeometryGenerator.hh>
#include <glosm/GeometryLayer.hh>
#include <glosm/PreloadedGPXDatasource.hh>
#include <glosm/PreloadedXmlDatasource.hh>
#include <glosm/Projection.hh>
#include <glosm/SRTMDatasource.hh>
#include <glosm/TerrainLayer.hh>




#include <glosm/OsmDatasource.hh>
#include <glosm/Exception.hh>
#include <glosm/XMLParser.hh>
#include <glosm/NonCopyable.hh>
#include <glosm/id_map.hh>

#include <memory>
#include <glosm/util/gl.h>
#include <glosm/BBox.hh>


#include <cmath>
#define PI 3.14159265


#include <glosm/GeometryOperations.hh>



#include "GPXWriter.hh"
#include "CarListLoader.hh"

class CarListLoader ;
class GPXWriter ;
class CarGlosmContainer ; 
class CarGlosm ; 

struct CarPos
{ int    ID ; 
  float  x  ; 
  float  y  ;  
} ;


typedef std::map<std::string, std::string> TagsMap;

	struct Node {
		Vector2i Pos;

		Node() {}
		Node(int x, int y) : Pos(x, y) {}
	};

struct Way {
		typedef std::vector<osmid_t> NodesList;

		NodesList Nodes;

		TagsMap Tags;
		bool Closed;
		bool Clockwise;
		BBoxi BBox;

		Way() : Closed(false), Clockwise(false), BBox(BBoxi::Empty()) {
		}
	};





class  CarGlosm{

 public : 

    CarGlosm(Vector3i  *v,CarGlosmContainer *CarContainer) ; 
    CarGlosm() ; 
    ~CarGlosm() ; 
    
    void Start_thread() ;
    void Start_thread_detatched() ;

    int is_way_in_BBox(BBoxi *b,std::auto_ptr<PreloadedXmlDatasource> osm_datasource_) ;  
    Vector3i pos_  ;
    int ID ;	
    


     Vector3i step_move(Vector3i& pos_,int dir,double angle,double step ); 
     double mod_meter(Vector3i& from,Vector3i& to) ; 
     std::vector<Vector3i> GetPointsTrajectoryFromTo(Vector3i *pos_init,Vector3i *pos_final,double step,double stop_dist ) ; 
     Vector3i move_from_to(Vector3i& pos_init,Vector3i& pos_final,double step ) ; 
     void WriteTrajectory(GPXWriter *writer,std::vector<Vector3i> *vect)  ; 

     CarGlosmContainer *CarContainer_ ; 
     const char *OSMfileName ;

 private : 
   

} ;



class CarGlosmContainer:public CarListLoader
{
  public : 
 
   std::vector<class CarGlosm> CarContainer_ ;
   std::vector<class CarGlosm>::iterator it_car_ ;
   std::string OSMfileName ; 
    
    int nb_car()  ;
    CarGlosmContainer() ;
   ~CarGlosmContainer() ; 
    void add_car_to_Container( Vector3i  *v) ; 
    void LoadCarList(std::string filename_in) ;
    void LoadOSMFile(std::string filename_in) ;
    void start_all_thread()  ; 

} ;



#endif 
