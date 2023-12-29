// JointedGripper.cpp
#include <assert.h>

#include "JointedGripper.hpp"
#include "Utility.hpp"

using namespace Eigen;

JointedGripper::JointedGripper(float gripper_length, float initial_gripper_angle) :
    mesh_(gripper_length),
    gripper_length_(gripper_length),
    gripper_angle_(initial_gripper_angle),
    target_gripper_angle_(initial_gripper_angle),
    gripper_speed_(0),
    to_world_(Affine3f::Identity()),
    controller_(0.05, 0.00, 0.001)
{
    this->updateGripperMatrix(gripper_angle_);
}

void JointedGripper::update(float dt, Affine3f current_world_transform)
{
    float control_signal = controller_.update(target_gripper_angle_ - gripper_angle_, dt);
    gripper_angle_ += control_signal;
    gripper_speed_ = control_signal / dt;
    updateGripperMatrix(gripper_angle_);
    setToWorld(current_world_transform * gripper_matrix_);
    updateMesh();
}

void JointedGripper::updateGripperMatrix(float gripper_angle)
{
    // This matrix should represent the gripper's transformation relative to the last link.
    // For example, this could be a simple rotation around the Z-axis.
    gripper_matrix_ = AngleAxisf(gripper_angle, Vector3f::UnitZ());
}

void JointedGripper::updateMesh()
{
    Affine3f joint_to_world = to_world_ * gripper_matrix_.inverse();
    // Apply the world transformation to the gripper mesh.
    mesh_.setToWorldTransform(to_world_);
}

void JointedGripper::recreateMesh()
{
    mesh_ = JointedGripperMesh(gripper_length_);
}

std::vector<Vertex> JointedGripper::getMeshVertices() const
{
    return mesh_.getVertices();
}
