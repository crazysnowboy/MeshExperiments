//
// Created by collin on 17-10-26.
//

#ifndef EXPERIMENTPROJECT_OPENMESH_WRAP_H
#define EXPERIMENTPROJECT_OPENMESH_WRAP_H

#include "string"
#include "gl.h"
#include<iostream>

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<>  OM;

using namespace std;


class openmesh_wrap:public OM
{
public:
    openmesh_wrap();
    bool OpenMeshRead(string file_name);
    void DrawOpenMesh(const std::string& _draw_mode);
    void Update();
    void Test();
};


#endif //EXPERIMENTPROJECT_OPENMESH_WRAP_H
