#include "BulletOpenGLApplication.h"
BulletOpenGLApplication::BulletOpenGLApplication()
	:
	m_cameraPosition(10.0f, 5.0f, 0.0f),
	m_cameraTarget(0.0f, 0.0f, 0.0f),
	m_nearPlane(1.0f),
	m_farPlane(1000.0f),
	m_upVector(0.0f, 1.0f, 0.0f),
	m_screenWidth(1024),
	m_screenHeight(768) 
{
	std::cout << "call BulletOpenGLApplication::BulletOpenGLApplication" << std::endl;
}
BulletOpenGLApplication::~BulletOpenGLApplication() {}
void BulletOpenGLApplication::Initialize() {
	glClearColor(0.6, 0.65, 0.85, 0);
}
void BulletOpenGLApplication::Keyboard(unsigned char key, int x, int y) { 
	std::cout << "call BulletOpenGLApplication::Keyboard" << std::endl;
}
void BulletOpenGLApplication::KeyboardUp(unsigned char key, int x, int y) {
	std::cout << "call BulletOpenGLApplication::KeyboardUp" << std::endl;
}
void BulletOpenGLApplication::Special(int key, int x, int y) {
	std::cout << "call BulletOpenGLApplication::Special" << std::endl;
}
void BulletOpenGLApplication::SpecialUp(int key, int x, int y) {
	std::cout << "call BulletOpenGLApplication::SpecialUp" << std::endl;
}
void BulletOpenGLApplication::Reshape(int w, int h) {
	m_screenWidth = w;
	m_screenHeight = h;
	glViewport(0, 0, w, h);
	UpdateCamera();
}
void BulletOpenGLApplication::Idle() {
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// update the camera
	UpdateCamera();
	// swap the front and back buffers
	glutSwapBuffers();
}
void BulletOpenGLApplication::Mouse(int button, int state, int x, int y) {
	std::cout << "call BulletOpenGLApplication::Mouse" << std::endl;
}
void BulletOpenGLApplication::PassiveMotion(int x, int y) {
	std::cout << "call BulletOpenGLApplication::PassiveMotion" << std::endl;
}
void BulletOpenGLApplication::Motion(int x, int y) {
	std::cout << "call BulletOpenGLApplication::Motion" << std::endl;
}
void BulletOpenGLApplication::Display() {
	std::cout << "call BulletOpenGLApplication::Display" << std::endl;
}

void BulletOpenGLApplication::UpdateCamera() {
	// exit in erroneous situations
	if (m_screenWidth == 0 && m_screenHeight == 0)
		return;
	// select the projection matrix
	glMatrixMode(GL_PROJECTION);
	// set it to the matrix-equivalent of 1
	glLoadIdentity();
	// determine the aspect ratio of the screen
	float aspectRatio = m_screenWidth / (float)m_screenHeight;
	// create a viewing frustum based on the aspect ratio and the
	// boundaries of the camera
	glFrustum(-aspectRatio * m_nearPlane, aspectRatio * m_nearPlane, -m_nearPlane, m_nearPlane, m_nearPlane, m_farPlane);
	// the projection matrix is now set

	// select the view matrix
	glMatrixMode(GL_MODELVIEW);
	// set it to '1'
	glLoadIdentity();
	// create a view matrix based on the camera's position and where it's
	// looking
	gluLookAt(m_cameraPosition[0], m_cameraPosition[1], m_cameraPosition[2], m_cameraTarget[0], m_cameraTarget[1], m_cameraTarget[2], m_upVector.getX(), m_upVector.getY(), m_upVector.getZ());
	// the view matrix is now set
}