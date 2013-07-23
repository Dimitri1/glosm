/*
 * Copyright (C) 2010-2012 Dmitry Marakasov
 *
 * This file is part of glosm.
 *
 * glosm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * glosm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with glosm.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "GlosmViewer.hh"

#include <glosm/util/gl.h>
#if defined(__APPLE__)
#	include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif
#if defined(WIN32)
#	include <winuser.h>
#endif

#include <cstdio>


#include "trafic-simulation/CarGlosm.hh"


//Librairie ajoutée pour les thread

#include <linux/sched.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>




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








//Librairie ajoutée pour le XML Writer 


#include "MyGlobalVariables.hh"

#include <glosm/GeometryOperations.hh>

//DIMITRI : The Writer must be accessible for all functions 




class GlosmViewerImpl : public GlosmViewer {
protected:
	virtual void WarpCursor(int x, int y) {
		glutWarpPointer(x, y);
	}

	virtual void Flip() {
		glutSwapBuffers();
	}

	virtual void ShowCursor(bool show) {
		glutSetCursor(show ? GLUT_CURSOR_INHERIT : GLUT_CURSOR_NONE);
	}
};

GlosmViewerImpl app;

void Display() {
	app.Render();
}

void Reshape(int w, int h) {
	app.Resize(w, h);
}

void Mouse(int x, int y) {
	app.MouseMove(x, y);
}

void Button(int button, int state, int x, int y) {
	int b = GlosmViewer::BUTTON_LEFT;
	switch (button) {
	case GLUT_LEFT_BUTTON: b = GlosmViewer::BUTTON_LEFT; break;
	case GLUT_RIGHT_BUTTON: b = GlosmViewer::BUTTON_RIGHT; break;
	case GLUT_MIDDLE_BUTTON: b = GlosmViewer::BUTTON_MIDDLE; break;
	}

	app.MouseButton(b, state == GLUT_DOWN, x, y);
}

void SpecialDown(int key, int, int) {
	switch (key) {
	case GLUT_KEY_UP: app.KeyDown(GlosmViewer::KEY_UP); break;
	case GLUT_KEY_DOWN: app.KeyDown(GlosmViewer::KEY_DOWN); break;
	case GLUT_KEY_LEFT: app.KeyDown(GlosmViewer::KEY_LEFT); break;
	case GLUT_KEY_RIGHT: app.KeyDown(GlosmViewer::KEY_RIGHT); break;
	default: break;
	}
}

void SpecialUp(int key, int, int) {
	switch (key) {
	case GLUT_KEY_UP: app.KeyUp(GlosmViewer::KEY_UP); break;
	case GLUT_KEY_DOWN: app.KeyUp(GlosmViewer::KEY_DOWN); break;
	case GLUT_KEY_LEFT: app.KeyUp(GlosmViewer::KEY_LEFT); break;
	case GLUT_KEY_RIGHT: app.KeyUp(GlosmViewer::KEY_RIGHT); break;
	default: break;
	}
}

void KeyDown(unsigned char key, int, int) {
	app.KeyDown(key);
}

void KeyUp(unsigned char key, int, int) {
	app.KeyUp(key);
}

int real_main(int argc, char** argv) {

  	int argc_osm ; 
 	std::string opt1("GPX_write_mode") ;
 	std::string on("ON") ;
   	std::string off("OFF") ;

      for (int narg = 0; narg < argc; ++narg) {
	       std::string file = argv[narg]; 
	         if (file == "-" || file.rfind(".osm") == file.length() - 4) {
			 argc_osm = narg ;
			 
		 } 
	
        	 else if ((opt1.compare(argv[narg]) == 0) && (on.compare(argv[narg + 2]) == 0  )) {
			writemode = true ; 	
		 	} 
	         else if ((opt1.compare(argv[narg]) == 0) && (on.compare(argv[narg + 2]) == 0  )) {
		        writemode = false ; 	
		 } 


	}

        if (writemode == true )		
 	{  
	    CarGlosmContainer container ;
	    fprintf( stderr,"Chaine: (%s) \n", argv[argc_osm]) ;
	    container.LoadOSMFile((const char *)argv[argc_osm] ) ;
            container.add_car_to_Container( new Vector3i((int)(-29.53850173950195*10000000),(int)(53.89432144165039*10000000) ) ) ;  

	    //container.add_car_to_Container(new Vector3i((int)(-29.53850173950195*10000000  + float(500) ),(int)(53.89432144165039*10000000 -    float(1000)) )  ) ;
//           container.add_car_to_Container(-29.53850173950195*10000000  + float(500) ,53.89432144165039*10000000 - 2*float(1000) ) ;
//	   container.add_car_to_Container(-29.53850173950195*10000000  + float(500) ,53.89432144165039*10000000 - 3*float(1000) ) ;
	   //container.add_car_to_Container(-29.53850173950195*10000000  + float(500) ,53.89432144165039*10000000 - 4*float(1000) ) ;
	   //container.add_car_to_Container(-29.53850173950195*10000000  + float(500) ,53.89432144165039*10000000 - 5*float(1000) ) ;
	   //container.add_car_to_Container(-29.53850173950195*10000000  + float(500) ,53.89432144165039*10000000 - 6*float(1000) ) ;
   
		
	 //  BBoxf b(-29.53850173950195*10000000 + float(1000),53.89432144165039*10000000 - float(1000),-29.53850173950195*10000000 + float(1000),53.89432144165039*10000000  - float(1000) ) ;

 	   for (container.it_car_=container.CarContainer_.begin();container.it_car_ < container.CarContainer_.end(); container.it_car_++)
           {   
		container.it_car_->Start_thread() ;
	    //container.it_car_->Start_thread_detatched() ;  
	    /*Warning : The thread_deatatched call in instable at yet. 
			Preferable to use joigned thread "Start_thread" instead of "Start_thread_detatched".
	    */ 
	   }
	}




	glutInit(&argc, argv);

	app.Init(argc, argv);

	/* glut init */
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("glosm viewer");

	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Button);
	glutMotionFunc(Mouse);
	glutPassiveMotionFunc(Mouse);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialDown);
	glutSpecialUpFunc(SpecialUp);
	app.InitGL();




 
//      DIMITRI : INITIALISATION DU CODE DE MAXIM 
	/*Construct human driven car*/
 	//pthread_create (&th1, NULL, my_thread_process, "1") ; 

 	//Player player(20,0,4,5,100,1,2,-3);
	/*Numbee of lanes*/
	//Simulation::nbLanes_ = 10;
	/*Maximum number of cars per line*/
	//Simulation::nbRows_ =  3;
	//Simulation * simulation = new Simulation();
	/*Construct Command instance from command filename*/
	//Command command(simulation,"commands.txt");
	/*Associate simulation and Command instance*/
	//simulation->setCommand(&command);
	/*Set simulation timeStep*/
	//Simulation::timeStep_ = atoi(argv[1]);
	//Simulation::timeStep_ = 1;
	/*Set simulation speed (acceleration factor: 1=real time, 2=realtime x2 etc...)*/
 	//Simulation::simulationSpeed_ = atoi(argv[2]);
  	//Simulation::simulationSpeed_ = 100;
	/*Associate Player and Simulation instance*/
	//player.setSimulation(simulation);
	//simulation->addPlayer(&player);
	//simulation->start();
///////////////////////////////////////////////////////////////////





	/* main loop */
	/* note that this never returns and objects created above
	 * are never properly destroyed; should dump GLUT ASAP */
	glutMainLoop();
	

	return 0;
}

int main(int argc, char** argv) {
	try {  

		return real_main(argc, argv);
	} catch (std::exception &e) {
#if defined(WIN32)
              

		MessageBox(NULL, e.what(), "Fatal error", MB_OK | MB_ICONERROR);
#else
		fprintf(stderr, "Fatal error: %s\n", e.what());
#endif
	} catch (...) {
#if defined(WIN32)
		MessageBox(NULL, "Unknown exception", "Fatal error", MB_OK | MB_ICONERROR);
#else
		fprintf(stderr, "Fatal error: unknown exception\n");
#endif
	}

	return 1;
}
