/*
 *    Copyright (C) 2017 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of t		he GNU General Public License as published by
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

/**
       \brief
       @author authorname
*/







#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>

class SpecificWorker : public GenericWorker
{
Q_OBJECT
public:
  
	SpecificWorker(MapPrx& mprx);	
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);
	
	void setPick(const Pick &myPick);
	
	
	
public slots:

	void compute();

private:
  
	struct Target
	{
	  bool active=false;
	  mutable QMutex mutex;
	  QVec aux = QVec::zeros(3);
	  
	  bool isActive(){
	    return active;
	  }
	  void setActive(bool act){
	    QMutexLocker lm(&mutex);
	    active = act;
	  }
	  void copy(float x, float z){
	    QMutexLocker lm(&mutex);
	    aux.setItem(0,x);
	    aux.setItem(1,0);
	    aux.setItem(2,z);
	  }
	  QVec getAux(){
	    QMutexLocker lm(&mutex);
	    return aux;
	  }
	};
	
	InnerModel* innerModel;
	Target pick;
	QLine2D linea;
	


	
};

#endif

