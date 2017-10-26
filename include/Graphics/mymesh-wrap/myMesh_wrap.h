//
// Created by collin on 17-10-26.
//

#ifndef EXPERIMENTPROJECT_MYMESH_WRAP_H
#define EXPERIMENTPROJECT_MYMESH_WRAP_H

#include "my_mesh_io.h"
class myMesh_wrap :public myMeshIO
{
    public:
        myMesh_wrap():myMeshIO()
        {

        }
        bool Read(string obj_name,string texture_name,float scale = 1);

};


#endif //EXPERIMENTPROJECT_MYMESH_WRAP_H
