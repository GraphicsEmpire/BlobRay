#include "../PS_Base/PS_Logger.h"
#include "PS_GLSurface.h"
#include "lodepng.h"

#include <GL/glew.h>


using namespace PS::RASTER;

GLSurface::GLSurface()
{
	init(DEFAULT_SURFACE_WIDTH, DEFAULT_SURFACE_HEIGHT);
}

GLSurface::GLSurface(U32 w, U32 h)
{
	init(w, h);
}

GLSurface::~GLSurface()
{
	cleanup();
}

/*!
*  Initialize the Surface
*/
void GLSurface::init(U32 w, U32 h)
{
	LogInfoArg2("Init surface with dimensions [%d, %d]", w, h);

	m_width = w;
	m_height = h;
	initTextures(w, h);

	//Generate 2 Textures and 2 frame buffers, 1 Render Buffer
	glGenFramebuffers(2, m_glFBO);

	//First Frame with RenderBuffer (Depth) and Texture
	glBindFramebuffer(GL_FRAMEBUFFER, m_glFBO[0]);
	glGenRenderbuffers(1, &m_glRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_width, m_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glRBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glTex[0], 0);
	GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(fboStatus != GL_FRAMEBUFFER_COMPLETE){
		fprintf(stderr, "FBO #1 Error!");
	}

	//Second Frame and Texture
	glBindFramebuffer(GL_FRAMEBUFFER, m_glFBO[1]);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glTex[1], 0);
	fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(fboStatus != GL_FRAMEBUFFER_COMPLETE){
		fprintf(stderr, "FBO #2 Error!");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	  /*
	//Create an openGL framebuffer object
	glGenFramebuffers(1, &m_glFBO);

	//Bind FrameBuffer to pipeline
	glBindFramebuffer(GL_FRAMEBUFFER, m_glFBO);

	//Attach 2D Texture to render 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
						   GL_TEXTURE_2D, m_glRenderTexture, 0);

	//Render Buffer
	//Create Render Buffer for Depth Testing
	glGenRenderbuffers(1, &m_glRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glRBO);

	//Specify width and height for storage of render buffer
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_width, m_height);

	//Attach Render Buffer to Frame Buffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glRBO);
	*/
}

void GLSurface::initTextures(U32 w, U32 h)
{
	glGenTextures(2, m_glTex);

	for (GLint i = 0; i < 2; i++){
		glBindTexture(GL_TEXTURE_2D, m_glTex[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// this may change with window size changes
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLSurface::cleanup()
{
	//Detach Buffers
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//Cleanup by deleting all buffers
	glDeleteFramebuffers(2, (GLuint*)&m_glFBO);
	glDeleteTextures(1, (GLuint*)&m_glTex);
}


//Attach to surface
void GLSurface::attach()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_glFBO[0]);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glRBO);

	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_width, m_height);
}

//Detach from surface
void GLSurface::detach()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void GLSurface::testDrawTriangle()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	glOrtho(0.0, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 1.0f, 0.0f);
	glEnd();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glFlush();
}


void GLSurface::drawAsQuad()
{
	glViewport(0, 0, m_width, m_height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_glTex[0]);
	glBegin(GL_QUADS);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);

		glVertex2f(1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);

		glVertex2f(1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);

		glVertex2f(0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);

	glEnd();


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

//	glFlush();
}


//Save the framebuffer output as a ppm
void GLSurface::saveAsPPM(const char* lpFilePath)
{
	CPixelMap* lpMap = new CPixelMap(m_width, m_height);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_glTex[0]);

	//Saving to ppm
	glReadPixels(0, 0, m_width, m_height, GL_RGBA8, GL_UNSIGNED_BYTE, (GLvoid*)lpMap->buffer());
	glBindTexture(GL_TEXTURE_2D, 0);

	lpMap->save(lpFilePath);

	SAFE_DELETE(lpMap);
}

void GLSurface::saveAsPNG(const char* lpFilePath) {

	vector<U8> data;
	data.resize(m_width * m_height * 4);

	//Bind Texture and then write
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_glTex[0]);

	glReadPixels(0, 0, m_width, m_height, GL_RGBA8, GL_UNSIGNED_BYTE, &data[0]);
	for(int i=0; i<16; i++)
		data[i] = 255;

	U32 err = lodepng::encode(lpFilePath, data, m_width, m_height);
	glBindTexture(GL_TEXTURE_2D, 0);


	if(err)
		printf("Error while encoding: %s", lodepng_error_text(err));
}
