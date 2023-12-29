// JointedGripperMesh.hpp
#pragma once
#include "Mesh.hpp"

class JointedGripperMesh : public Mesh {
public:
    JointedGripperMesh(float gripper_length);

	static const Eigen::Vector4f JOINT_COLOR;
    static const Eigen::Vector4f GRIPPER_COLOR;
};
