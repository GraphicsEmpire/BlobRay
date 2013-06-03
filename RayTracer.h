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
#include "PS_Graphics/PS_Pixmap.h"

using namespace PS;
using namespace PS::MATH;
using namespace PS::RASTER;

#define MAX_PRIM_COUNT 1024

//Primitives can be explicit or implicit primitives
typedef enum PrimTypes {primExplicitSphere, ptExplicitTriangle, ptExplicitTriangleMesh};

//20 FLTS
struct Primitive {
	U32 type;
	U32 idxMatrix;
	U32 idxParent;
	U32 idxSibling;
	vec4f pos;
	vec4f dir;
	vec4f res;
	vec4f color;
};

struct ScenePrimitives {
	U32 count;
	Primitive prims[MAX_PRIM_COUNT];
};

/*!
 * High-Performance RayTracer using OpenCL
 */
class RayTracer {
public:
	RayTracer();
	RayTracer(int w, int h);
	virtual ~RayTracer();

	void init();
	void cleanup();

	void run();

	//Texture handle
	U32 texture() const {return m_uTexture;}

	void draw();
protected:

//	void primaryRays();
	int intersect(const Ray& ray);

	void grabFrame();
private:

private:
	//Input
	int m_width;
	int m_height;
	float m_near;
	float m_far;
	vec3f m_eye;
	rgba8 m_bgColor;

	ScenePrimitives m_prims;


	//Output
	Pixmap* m_lpPixmap;
	U32 m_uTexture;
};



#endif /* RAYTRACER_H_ */
