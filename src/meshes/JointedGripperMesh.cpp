// JointedGripperMesh.cpp
#include "JointedGripperMesh.hpp"
#include "CylinderMesh.hpp"
#include "BoxMesh.hpp"

using namespace Eigen;

const Vector4f JointedGripperMesh::JOINT_COLOR = Vector4f(0.05, 0.6, 0.4, 1.0);
const Vector4f JointedGripperMesh::GRIPPER_COLOR = Vector4f(0.8, 0.2, 0.2, 1.0);


JointedGripperMesh::JointedGripperMesh(float gripper_length) :
    Mesh()
{
    float radius = 0.05f; // joint radius
    float gripper_height = gripper_length;

    // create meshes
    // joint mesh is centered at origin and oriented along z
    BoxMesh gripper_left(0.02, 0.04, gripper_height, GRIPPER_COLOR);
    BoxMesh gripper_right(0.02, 0.04, gripper_height, GRIPPER_COLOR);
    CylinderMesh joint(radius, 0.04, JOINT_COLOR);

    // TODO: move grippers to their correct position


    // Compose all mesh vertices into one vector
    std::vector<Vertex> gripper_verts;
    gripper_verts = gripper_left.getVertices();
    gripper_verts = gripper_right.getVertices();
    gripper_verts = joint.getVertices();
    vertices_.insert(vertices_.end(), gripper_verts.begin(), gripper_verts.end());

    
}