/*
 * RayTracer.h
 *
 *  Created on: May 30, 2013
 *      Author: pourya
 */

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "PS_Graphics/PS_Vector.h"
#include "PS_Graphics/PS_Ray.h"
#include "PS_Graphics/PS_Matrix.h"

//RayTracer Settings
//class RTSettings {
//
//};

class RayTracer {
public:
	RayTracer();
	RayTracer(int w, int h);
	virtual ~RayTracer();


	void run();

private:
	int m_width;
	int m_height;
};



#endif /* RAYTRACER_H_ */
