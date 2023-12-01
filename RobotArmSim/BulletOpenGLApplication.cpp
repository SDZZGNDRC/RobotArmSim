#include "BulletOpenGLApplication.h"
BulletOpenGLApplication::BulletOpenGLApplication() {}
BulletOpenGLApplication::~BulletOpenGLApplication() {}
void BulletOpenGLApplication::Initialize() {
	std::cout << "call BulletOpenGLApplication::Initialize" << std::endl;
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
	std::cout << "call BulletOpenGLApplication::Reshape" << std::endl;
}
void BulletOpenGLApplication::Idle() {
	std::cout << "call BulletOpenGLApplication::Idle" << std::endl;
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
