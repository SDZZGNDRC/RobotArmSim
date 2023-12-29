// JointedGripper.hpp
#pragma once

#include <vector>
#include <memory>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Eigen/Dense"

#include "meshes/JointedGripperMesh.hpp"
#include <core/PidController.hpp>

class JointedGripper {
public:
    JointedGripper(float gripper_length, float initial_gripper_angle);

    // updates gripper angle based on current gripper speed and time passed since last update
    // also updates the gripper matrix and mesh position
    void update(float dt, Eigen::Affine3f current_world_transform);

    // setters
    void setGripperLength(float length) { gripper_length_ = length; recreateMesh(); };
    void setToWorld(const Eigen::Affine3f& to_world) { to_world_ = to_world; };
    void setGripperAngle(float angle) { gripper_angle_ = angle; };
    void setGripperTargetAngle(float target_angle) { target_gripper_angle_ = target_angle; };
    void setControllerGains(float p, float i, float d) { controller_.setGains(p, i, d); };

    // matching getters
    float getGripperLength() const { return gripper_length_; };
    Eigen::Affine3f getToWorld() const { return to_world_; };
    float getGripperAngle() const { return gripper_angle_; };
    float getGripperSpeed() const { return gripper_speed_; };
    float getGripperTargetAngle() const { return target_gripper_angle_; };

    // no setter
    Eigen::Affine3f getGripperMatrix() const { return gripper_matrix_; };

    // returns the vertices of the mesh that represents the gripper
    std::vector<Vertex> getMeshVertices() const;

private:
    void updateGripperMatrix(float gripper_angle);
    void updateMesh();
    void recreateMesh();

    float gripper_length_;             // length of the gripper
    JointedGripperMesh mesh_;                 // mesh used for graphical representation
    PidController controller_;         // controls the gripper

    float gripper_speed_;              // current speed of the gripper in rad/s
    float gripper_angle_;              // angle of the gripper
    float target_gripper_angle_;       // target angle for the gripper, current angle will move towards this when update() is called

    // combination of applying z_screw and then x_screw
    // relates this gripper's frame to the frame of the previous link
    Eigen::Affine3f gripper_matrix_;

    // transforms the coordinates of this gripper frame to world frame
    // created by multiplying together all link matrices of the previous links and the current link
    // needs to be set by the Robot class
    Eigen::Affine3f to_world_;
};
