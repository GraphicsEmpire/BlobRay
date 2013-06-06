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
#include "PS_Graphics/PS_Interval.h"

using namespace PS;
using namespace PS::MATH;
using namespace PS::RASTER;

#define MAX_PRIM_COUNT 256
#define MAX_LIGHT_COUNT 8

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

	vec4f ambient;
	vec4f diffused;
	vec4f specular;
	float shininess;
};

//Primitives
struct ScenePrimitives {
	U32 count;
	Primitive prims[MAX_PRIM_COUNT];
};

//Lights
struct LightSources {
	U32 count;
	vec4f pos[MAX_LIGHT_COUNT];
	vec4f color[MAX_LIGHT_COUNT];
};

//Intersection Info
struct IntersectRecord {
	int ctIntersections;
	float t;
	vec4f color;
};

/*!
 * High-Performance RayTracer using OpenCL
 */
class RayTracer {
public:
	RayTracer();
	RayTracer(int w, int h);
	virtual ~RayTracer();

	void run();

	//Texture handle
	U32 texture() const {return m_uTexture;}

	void draw();
protected:
	void init();
	void cleanup();
	void grabFrame();

	int intersect(const Ray& ray, const Interval& interval, IntersectRecord& output);
	vec4f computePhong(int idxPrim, const vec3f& eye, const vec3f& p, const vec3f& n);

	//Shadow Rays

	//Reflections
private:
	rgba8 convertToRGBA8(const vec4f& incolor);

private:
	//Input
	int m_width;
	int m_height;
	float m_near;
	float m_far;
	vec3f m_eye;
	rgba8 m_bgColor;

	//Scene Models
	ScenePrimitives m_prims;
	LightSources m_lights;


	//Output
	Pixmap* m_lpPixmap;
	U32 m_uTexture;
};



#endif /* RAYTRACER_H_ */
