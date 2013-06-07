/*
 * Raytracer.cpp
 *
 *  Created on: May 30, 2013
 *      Author: pourya
 */
#include "RayTracer.h"
#include "GL/glew.h"

#define DEFAULT_WIDTH	800
#define DEFAULT_HEIGHT 600

RayTracer::RayTracer():m_nx(DEFAULT_WIDTH), m_ny(DEFAULT_HEIGHT) {
	init();
}

RayTracer::RayTracer(int w, int h):m_nx(w), m_ny(h) {
	init();
}

RayTracer::~RayTracer() {
	cleanup();
}

void RayTracer::cleanup() {
	SAFE_DELETE(m_lpPixmap);

	glDeleteTextures(1, &m_uTexture);
}

void RayTracer::init() {
	m_lpPixmap = new Pixmap(m_nx, m_ny);
	m_lpPixmap->checkers(rgba8(255, 0, 0, 255));
	//m_lpPixmap->save("checkboard.png");
	glGenTextures(1, &m_uTexture);
	glBindTexture(GL_TEXTURE_2D, m_uTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_nx, m_ny, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_lpPixmap->const_data());
	glBindTexture(GL_TEXTURE_2D, 0);

	//FrameSequencer
	m_iFrameSeq = 0;

	//System Setup
	m_eye = vec3f(0.0f, 0.0f, -10.0f);
	m_near = 0.0f;
	m_far = 1000.0f;
	m_left = -1;
	m_right = 1;
	m_bottom = -1;
	m_top = 1;
	m_bgColor = rgba8(128, 128, 128, 255);

	//Read Model
	m_prims.count = 1;
	m_prims.prims[0].type = primExplicitSphere;
	m_prims.prims[0].pos = vec4f(0, 0, 5, 1);
	m_prims.prims[0].dir = vec4f(0, 0, 0, 1);
	m_prims.prims[0].res = vec4f(1, 0, 0, 0);
	m_prims.prims[0].ambient = vec4f(0.2, 0, 0, 1);
	m_prims.prims[0].diffused = vec4f(0.8, 0, 0, 1);
	m_prims.prims[0].specular = vec4f(1, 1, 1, 1);
	m_prims.prims[0].shininess = 16.0f;

	//Lights
	m_lights.count = 1;
	m_lights.pos[0] = vec4f(0, 2, 2, 1);
	m_lights.color[0] = vec4f(1,1,1,1);
}

void RayTracer::grabFrame() {
	glBindTexture(GL_TEXTURE_2D, m_uTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_nx, m_ny, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_lpPixmap->const_data());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RayTracer::saveFrame() {
	char buffer[256];
	sprintf(buffer, "frame_%d.png", m_iFrameSeq++);

	if(m_lpPixmap) {
		m_lpPixmap->save(buffer);
		grabFrame();
	}
}

void RayTracer::run() {

	//Fill with background color
	m_lpPixmap->fill(m_bgColor);

	//Shoot Primary Rays
	Ray ray;
	Interval interval;
	IntersectRecord record;
	for(int i=0; i < m_nx; i++) {
		for(int j=0; j < m_ny; j++) {

			vec3f px;
			px.x = m_left + ((m_right - m_left) * static_cast<float>(i) + 0.5) / static_cast<float>(m_nx);
			px.y = m_bottom + ((m_top - m_bottom) * static_cast<float>(j) + 0.5) / static_cast<float>(m_ny);
			px.z = m_near;
			vec3f dir = (px - m_eye).normalized();
			ray.set(m_eye, dir);
			interval.set(vec3f::distance(px, m_eye), FLT_MAX);

			//Primary Intersection
			int ctIntersected = intersect(ray, interval, record);
			if(ctIntersected > 0) {
				m_lpPixmap->putPixel(i, j, convertToRGBA8(record.color));
			}
		}
		//grabFrame();

		//sleep(1);
	}

	//Grab new frame
	grabFrame();
}

//Returns number of intersections
int RayTracer::intersect(const Ray& ray, const Interval& interval, IntersectRecord& output) {

	//Zero Intersection Record
	memset(&output, 0, sizeof(IntersectRecord));

	for(U32 i=0; i< m_prims.count; i++) {
		switch(m_prims.prims[i].type) {

		case(primExplicitSphere): {
			//sphere center and radius
			vec3 sc = m_prims.prims[i].pos.xyz();
			float sr = m_prims.prims[i].res.x;

			float a = vec3f::dot(ray.direction, ray.direction);
			float b = 2.0f * vec3f::dot(ray.start - sc, ray.direction);
			float c = vec3f::dot(ray.start - sc, ray.start - sc) - sr*sr;
			float delta = b*b - 4.0f * a * c;
			if(delta < 0.0f)
				continue;
			else {
				float droot = sqrtf(delta);
				float t1 = (- b - droot) / (2 * a);
				float t2 = (- b + droot) / (2 * a);
				bool isFirst = interval.isInside(t1);
				bool isSecond = interval.isInside(t2);

				output.t = MATHMIN(t1, t2);

				/*
				if(isFirst && isSecond)
					output.t = MATHMIN(t1, t2);
				else if(isFirst)
					output.t = t1;
				else if(isSecond)
					output.t = t2;
				else {
					//printf("Error in computing intersections!\n");
					continue;
				}
				*/
				if(output.t < 0.0f)
					float gg = output.t;

				vec3f p = ray.point(output.t);
				vec3f n = (p - sc).normalized();
				output.ctIntersections = 1;
				output.color = computePhong(i, ray.direction, p, n);

				return 1;
			}

			break;
		}

		}
	}

	return 0;
}

vec4f RayTracer::computePhong(int idxPrim, const vec3f& eye, const vec3f& p, const vec3f& n) {
	vec3f l = (m_lights.pos[0].xyz() - p).normalized();
	vec3f r = vec3f::reflect(l, n);
	vec3f h = (l - eye).normalized();

	vec4f ambient = vec4f::mul(m_prims.prims[idxPrim].ambient, m_lights.color[0]);
	vec4f diffused = m_prims.prims[idxPrim].diffused * maxf(0.0f, vec3f::dot(n, l));
	vec4f specular = m_prims.prims[idxPrim].specular * powf(maxf(vec3f::dot(n, h), 0.0), m_prims.prims[idxPrim].shininess);
	vec4f output = diffused + specular;
	return vec4f::clamped(output, 0.0f, 1.0f);
}

rgba8 RayTracer::convertToRGBA8(const vec4f& incolor) {
	rgba8 pixel = rgba8(static_cast<U8>(incolor.x * 255.0f),
						static_cast<U8>(incolor.y * 255.0f),
						static_cast<U8>(incolor.z * 255.0f),
						static_cast<U8>(incolor.w * 255.0f));
	return pixel;
}

void RayTracer::draw() {
	//Draw texture as quad
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_uTexture);
	glBegin(GL_QUADS);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);

		glVertex2f(1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);

		glVertex2f(1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);

		glVertex2f(0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);

	glEnd();
}





