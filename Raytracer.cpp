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

RayTracer::RayTracer():m_width(DEFAULT_WIDTH), m_height(DEFAULT_HEIGHT) {
	init();
}

RayTracer::RayTracer(int w, int h):m_width(w), m_height(h) {
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
	m_lpPixmap = new Pixmap(m_width, m_height);
	m_lpPixmap->checkers(rgba8(255, 0, 0, 255));
	//m_lpPixmap->save("checkboard.png");
	glGenTextures(1, &m_uTexture);
	glBindTexture(GL_TEXTURE_2D, m_uTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_lpPixmap->const_data());
	glBindTexture(GL_TEXTURE_2D, 0);

	//System Setup
	m_eye = vec3f(m_width/2, m_height/2, -10.0f);
	m_near = 0.0f;
	m_far = 100.0f;
	m_bgColor = rgba8(128, 128, 128, 255);

	//Read Model
	m_prims.count = 1;
	m_prims.prims[0].type = primExplicitSphere;
	m_prims.prims[0].pos = vec4f(0, 2, 20, 1);
	m_prims.prims[0].dir = vec4f(0, 0, 0, 1);
	m_prims.prims[0].res = vec4f(2, 0, 0, 0);
	m_prims.prims[0].color = vec4f(1, 0, 0, 1);
}

void RayTracer::grabFrame() {
	glBindTexture(GL_TEXTURE_2D, m_uTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_lpPixmap->const_data());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RayTracer::run() {

	//Fill with background color
	m_lpPixmap->fill(m_bgColor);

	//Shoot Primary Rays
	Ray r;
	for(int i=0; i < m_width; i++) {
		for(int j=0; j < m_height; j++) {
			vec3f dir = vec3f(0.5f + static_cast<float>(i) * (float)m_width,
							  0.5f + static_cast<float>(i) * (float)m_height,
							  m_near);
			dir = (dir - m_eye).normalized();
			r.set(m_eye, dir);

			int ctIntersected = intersect(r);
		}
	}

	//Grab new frame
	grabFrame();
}

int RayTracer::intersect(const Ray& ray) {
	for(int i=0; i< m_prims.count; i++) {
		switch(m_prims.prims[i].type) {

		case(primExplicitSphere): {

			break;
		}

		}
	}
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





