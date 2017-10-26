//
// Created by collin on 17-10-26.
//

#ifndef EXPERIMENTPROJECT_OPENMESH_WRAP_H
#define EXPERIMENTPROJECT_OPENMESH_WRAP_H

#include "string"
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<>  OM;

using namespace std;


class openmesh_wrap:public OM
{
public:
    bool OpenMeshRead(string file_name);
    void DrawOpenMesh(const std::string& _draw_mode);
};


#endif //EXPERIMENTPROJECT_OPENMESH_WRAP_H
