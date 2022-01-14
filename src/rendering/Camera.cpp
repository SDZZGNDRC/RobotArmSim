#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "Camera.hpp"
#include <GLFW/glfw3.h>

using namespace Eigen;

Camera::Camera(
    const Eigen::Vector3f& position,
    const Eigen::Vector3f& forward,
    const Eigen::Vector3f& up, float speed, float mouse_sensitivity
):
    position_(position),
    forward_(forward),
    up_(up),
    speed_(speed),
    mouse_sensitivity_(mouse_sensitivity),
    fov_(70.0f),
    near_(0.001f),
    far_(3.0f),
    dragLeft_(false),
    dragMiddle_(false),
    dragRight_(false)
{
}

void Camera::handleEvent(int button, int action, int posX, int posY)
{
    Matrix3f orient = getOrientation();
    Vector3f rotate = Vector3f::Zero();
    Vector3f move = Vector3f::Zero();

#if 1
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) dragLeft_ = true;
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) dragLeft_ = false;

    if (button == GLFW_KEY_A)    move.x() -= 1.0f;
    if (button == GLFW_KEY_D)    move.x() += 1.0f;
    if (button == GLFW_KEY_F)    move.y() -= 1.0f;
    if (button == GLFW_KEY_R)    move.y() += 1.0f;
    if (button == GLFW_KEY_W)    move.z() -= 1.0f;
    if (button == GLFW_KEY_S)    move.z() += 1.0f;
    move *= 0.1f * speed_;

    Vector3f delta = Vector3f(posX - last_x_, last_y_ - posY, 0.0f);

    if (dragLeft_) {
        rotate += delta * mouse_sensitivity_;
        std::cout << rotate << std::endl;
    }

    if (!move.isZero())
        position_ += orient * move;

    if (rotate.x() != 0.0f || rotate.y() != 0.0f)
    {
        Vector3f tmp = orient.col(2) * cos(rotate.x()) - orient.col(0) * sin(rotate.x());
        forward_ = (orient.col(1) * sin(rotate.y()) - tmp * cos(rotate.y())).normalized();
        up_ = (orient.col(1) * cos(rotate.y()) + tmp * sin(rotate.y())).normalized();
    }

    if (rotate.z() != 0.0f)
    {
        Vector3f up = orient.transpose() * up_;
        up_ = orient * Vector3f(up.x() * cos(rotate.z()) - sin(rotate.z()), up.x() * sin(rotate.z()) + up.y() * cos(rotate.z()), up.z());
    }

    last_x_ = posX;
    last_y_ = posY;
 
#else
	switch (ev.type)
	{
        case Window::EventType_KeyDown:
            if (ev.key == FW_KEY_MOUSE_LEFT)    dragLeft_ = true;
            if (ev.key == FW_KEY_MOUSE_MIDDLE)  dragMiddle_ = true;
            if (ev.key == FW_KEY_MOUSE_RIGHT)   dragRight_ = true;
            break;

        case Window::EventType_KeyUp:
            if (ev.key == FW_KEY_MOUSE_LEFT)    dragLeft_ = false;
            if (ev.key == FW_KEY_MOUSE_MIDDLE)  dragMiddle_ = false;
            if (ev.key == FW_KEY_MOUSE_RIGHT)   dragRight_ = false;
            break;

        case Window::EventType_Mouse:
        {
            Vector3f delta = Vector3f((F32)ev.mouseDelta.x, (F32)-ev.mouseDelta.y, 0.0f);
            if (dragLeft_) rotate += delta * mouse_sensitivity_;
            break;
        }
        case Window::EventType_Paint:
        {
            bool    alt = ev.window->isKeyDown(FW_KEY_ALT);

            if (ev.window->isKeyDown(FW_KEY_A) || (ev.window->isKeyDown(FW_KEY_LEFT) && alt))     move.x() -= 1.0f;
            if (ev.window->isKeyDown(FW_KEY_D) || (ev.window->isKeyDown(FW_KEY_RIGHT) && alt))    move.x() += 1.0f;
            if (ev.window->isKeyDown(FW_KEY_F) || ev.window->isKeyDown(FW_KEY_PAGE_DOWN))         move.y() -= 1.0f;
            if (ev.window->isKeyDown(FW_KEY_R) || ev.window->isKeyDown(FW_KEY_PAGE_UP))           move.y() += 1.0f;
            if (ev.window->isKeyDown(FW_KEY_W) || (ev.window->isKeyDown(FW_KEY_UP) && alt))       move.z() -= 1.0f;
            if (ev.window->isKeyDown(FW_KEY_S) || (ev.window->isKeyDown(FW_KEY_DOWN) && alt))     move.z() += 1.0f;
            move *= dt * speed_;
            break;
        }
	}

    if (!move.isZero())
        position_ += orient * move;

    if (rotate.x() != 0.0f || rotate.y() != 0.0f)
    {
        Vector3f tmp = orient.col(2) * FW::cos(rotate.x()) - orient.col(0) * FW::sin(rotate.x());
        forward_ = (orient.col(1) * FW::sin(rotate.y()) - tmp * FW::cos(rotate.y())).normalized();
        up_ = (orient.col(1) * FW::cos(rotate.y()) + tmp * FW::sin(rotate.y())).normalized();
    }

    if (rotate.z() != 0.0f)
    {
        Vector3f up = orient.transpose() * up_;
        up_ = orient * Vector3f(up.x() * FW::cos(rotate.z()) - FW::sin(rotate.z()), up.x() * FW::sin(rotate.z()) + up.y() * FW::cos(rotate.z()), up.z());
    }
#endif
}

Eigen::Matrix4f Camera::getWorldToCamera(void) const
{
    Matrix3f orient = getOrientation();
    Vector3f pos = orient.transpose() * position_;
    Affine3f r;
    r.linear() = orient.transpose();
    r.translation() = -pos;
    return r.matrix();
}

Eigen::Matrix4f Camera::getCameraToClip() const
{
    // Camera points towards -z.  0 < near < far.
    // Matrix maps z range [-near, -far] to [-1, 1], after homogeneous division.
    float f = tan(fov_ * M_PI / 360.0f);
    float d = near_ - far_;
    f = f ? 1 / f : 0;
    d = d ? 1 / d : 0;

    Matrix4f r;
    r.row(0) = Vector4f(f, 0.0f, 0.0f, 0.0f);
    r.row(1) = Vector4f(0.0f, f, 0.0f, 0.0f);
    r.row(2) = Vector4f(0.0f, 0.0f, (near_ + far_) * d, 2.0f * near_ * far_ * d);
    r.row(3) = Vector4f(0.0f, 0.0f, -1.0f, 0.0f);
    return r;
    return Matrix4f{};
}


Eigen::Matrix3f Camera::getOrientation() const
{
    Eigen::Matrix3f r;
    r.col(2) = -forward_.normalized();
    r.col(0) = up_.cross(r.col(2)).normalized();
    r.col(1) = (r.col(2)).cross(r.col(0)).normalized();
    return r;
}