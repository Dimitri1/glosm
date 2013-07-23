#include "GPXWriter.hh"







void    GPXWriter::Init() {a_file.open( "GPX_output.gpx" ) ; 
         a_file << "<?xml version='1.0' encoding='UTF-8'?>"  << "\n" ;
 	 a_file << "<gpx version=\"1.1\" creator=\"JOSM GPX export\" xmlns=\"http://www.topografix.com/GPX/1/1\""<< "\n" ;
    	 a_file << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << "\n" ;
    	 a_file << "    xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\">"<< "\n" ;
  	// a_file << "  <metadata>"<< "\n" ;
    	// a_file << "    <bounds minlat=\"53.8928649\" minlon=\"-29.5387219\" maxlat=\"53.8943217\" maxlon=\"-29.5368444\" />"<< "\n" ;
  	// a_file << "  </metadata>"<< "\n" ;
  	 a_file << "  <trk>    <trkseg>"<< "\n" ;

	  
        
}


void    GPXWriter::Init(const char *out_file_name) {
 
	 a_file.open(out_file_name) ; 
         a_file << "<?xml version='1.0' encoding='UTF-8'?>"  << "\n" ;
 	 a_file << "<gpx version=\"1.1\" creator=\"JOSM GPX export\" xmlns=\"http://www.topografix.com/GPX/1/1\""<< "\n" ;
    	 a_file << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << "\n" ;
    	 a_file << "    xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\">"<< "\n" ;
  	// a_file << "  <metadata>"<< "\n" ;
    	// a_file << "    <bounds minlat=\"53.8928649\" minlon=\"-29.5387219\" maxlat=\"53.8943217\" maxlon=\"-29.5368444\" />"<< "\n" ;
  	// a_file << "  </metadata>"<< "\n" ;
  	 a_file << "  <trk>    <trkseg>"<< "\n"  ;   
}


void    GPXWriter::WritePoint(float X,float Y)  
{ 
	
 	a_file << "\n" ;
 	a_file << "    <trkpt lat=\"" ; 
	a_file <<  std::setprecision(16)  << (Y/10000000) ;
        //fprintf(a_file,"%f",X) ; 
	a_file <<  "\" lon=\"" ;  
 	a_file <<  std::setprecision (16) << (X/10000000) ;
   	a_file << "\">" ;
	a_file << "\n" ;
        a_file << "    </trkpt>" ; 
 

}

void    GPXWriter::WritePoint(Vector3i *v)  
{ 
	
 	a_file << "\n" ;
 	a_file << "    <trkpt lat=\"" ; 
//
	a_file << std::setprecision(16)  <<(float)(v->y) /10000000 ;
        a_file <<  "\" lon=\"" ;  
//
 	a_file <<  std::setprecision(16)  <<(float)(v->x) /10000000 ;
   	a_file << "\">" ;
	a_file << "\n" ;
        a_file << "    </trkpt>" ; 
 

}

void    GPXWriter::Close()  
{    a_file << "\n" ;
    a_file << "</trkseg>" << "\n" ;
    a_file << "</trk>"    << "\n" ;
    a_file << "</gpx>"    << "\n" ; 
    a_file.close()  ; 
}

GPXWriter::GPXWriter() { }  
GPXWriter::~GPXWriter() {Close() ;}










