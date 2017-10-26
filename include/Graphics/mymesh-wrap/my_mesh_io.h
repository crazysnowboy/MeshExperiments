//
// Created by collin on 17-10-25.
//

#ifndef EXPERIMENTPROJECT_MESH_IO_H
#define EXPERIMENTPROJECT_MESH_IO_H

#include "opencv2/opencv.hpp"
#include "vector"
#include "string"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "openmesh_wrap.h"

using namespace std;

class myMeshIO
{
public:
    myMeshIO()
    {

    }
    bool myLoadTexture(const char *image_path);
    bool myLoadOBJ(const char * path,float scale=1);

public:
    std::vector<glm::vec3> my_vertices;
    std::vector<glm::vec2> my_uvs;
    std::vector<long int> my_triangle_list;

    cv::Mat my_Texture;



private:



};


#endif //EXPERIMENTPROJECT_MESH_IO_H
