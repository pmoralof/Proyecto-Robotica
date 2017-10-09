/*
 *    Copyright (C) 2017 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"
#include <qt4/QtCore/qdebug.h>

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{

}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
	innerModel = new InnerModel ( "/home/pablo/robocomp/files/innermodel/simpleworld.xml" );
 
	
	timer.start(Period);
	

	return true;
}

void SpecificWorker::compute()
{
//   qDebug() << "Hola"; 
  
  
//   float umbral =300;
//   
//   TLaserData data =laser_proxy->getLaserData();
// 
//   
//    std::sort(data.begin()+15, data.end()-15, [](TData a, TData b) {
//         return a.dist < b.dist;   
//     });
//    
//    float frente = data[20].dist;
//    
//   
//    qDebug("Frente %f: Umbral:%f\n",frente, umbral);
//    
//    if(frente<umbral){
// 
//      differentialrobot_proxy->setSpeedBase(2,0.3);
//    
//    usleep(rand()%(1000000-100000+1) + 100000);
//      
//   }else{
//    differentialrobot_proxy->setSpeedBase(300,0);
//   }
  
  	  
	  
// 	  try
// 	  {
// 		camera_proxy->getYImage(0,img, cState, bState);
// 		memcpy(image_gray.data, &img[0], m_width*m_height*sizeof(uchar));
// 		searchTags(image_gray);
// 	}
// 	catch(const Ice::Exception &e)
// 	{
// 		std::cout << "Error reading from Camera" << e << std::endl;
// 	}
//   
  	try{
	  
	  RoboCompDifferentialRobot::TBaseState bState;
	  differentialrobot_proxy->getBaseState ( bState );
	  innerModel->updateTransformValues ( "base", bState.x,0,bState.z,0,bState.alpha,0 );
	  QVec ini;
	
  
    
	  //si no hay target no hago nada
	  //si hay, corrijo la velocidad del robot
	  //si he llegado, elimino el target	
	  if(pick.isActive()){
	  
// 	  ini = QVec::vec3(bState.x, 0, bState.z);
// 	  linea = QLine2D( ini, pick.getAux());
	  
	    QVec tr = innerModel->transform ( "base",pick.getAux(),"world" );

	    float angulo = atan2 ( tr.x(),tr.z() );
	    float distanciaObjetivo = tr.norm2();
	  
	    if ( distanciaObjetivo <= 300 )
	    {
		pick.setActive (false);
		differentialrobot_proxy->stopBase();
		return;
	    }

	    if ( abs ( angulo ) > 0.05 )
		distanciaObjetivo = 0;
	    if( distanciaObjetivo > 300) distanciaObjetivo = 300;

	   differentialrobot_proxy->setSpeedBase(distanciaObjetivo, angulo);
	    
	    
	  }		
	}catch ( const Ice::Exception &ex ){
			std::cout << ex << std::endl;
	}
	    
     
}

void SpecificWorker::setPick(const Pick &myPick)
{
  
    qDebug() << "New target selected: " << myPick.x << myPick.z;
    pick.copy(myPick.x, myPick.z);
    pick.setActive(true);

}








