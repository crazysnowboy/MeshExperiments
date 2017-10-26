//
// Created by collin on 17-10-26.
//

#ifndef EXPERIMENTPROJECT_MESH_H
#define EXPERIMENTPROJECT_MESH_H

#include "openmesh_wrap.h"
#include "myMesh_wrap.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();
    openmesh_wrap OpenMesh_;
    myMesh_wrap MyMesh_;

};


#endif //EXPERIMENTPROJECT_MESH_H
