//
// Created by collin on 17-10-25.
//

#include "my_mesh_io.h"



bool myMeshIO::myLoadTexture(const char *image_path)
{
    my_Texture=cv::imread(image_path);
    if(my_Texture.empty())
    {
        printf("opencv read image failed \r\n");
        exit(-2);
        return false;

    }
    cv::flip(my_Texture,my_Texture,0);
    cv::cvtColor(my_Texture,my_Texture,CV_BGR2RGB);
    return true;
}
bool myMeshIO::myLoadOBJ(const char * path,float scale)
{

    std::vector< long int > Triangle_vertexIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    FILE * file = fopen(path, "r");
    if( file == NULL )
    {
        printf("loadOBJ : Impossible to open the file !\n");
        return false;
    }
    while( 1 )
    {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if ( res == EOF)
        {
            break;    // EOF = End Of File. Quit the loop.
        }

        // else : parse lineHeader
        if ( strcmp(lineHeader, "v") == 0 )
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

            if(scale != 0)
            {
                vertex.x = vertex.x/scale;
                vertex.y = vertex.y/scale;
                vertex.z = vertex.z/scale;
            }

            temp_vertices.push_back(vertex);
        }
        else if ( strcmp(lineHeader, "vt") == 0 )
        {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if ( strcmp(lineHeader, "vn") == 0 )
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if ( strcmp(lineHeader, "f") == 0 )
        {

            unsigned int vertexIndex[3];
            unsigned int texureIndex[3];
            int matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &texureIndex[0],
                                 &vertexIndex[1], &texureIndex[1], &vertexIndex[2], &texureIndex[2]
                                );

            if ( matches != 6 )
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            Triangle_vertexIndices.push_back(vertexIndex[0]);
            Triangle_vertexIndices.push_back(vertexIndex[1]);
            Triangle_vertexIndices.push_back(vertexIndex[2]);

        }
    }
    // For each vertex
    for( unsigned int i=0; i<temp_vertices.size(); i++ )
    {
        glm::vec3 vertex = temp_vertices[i];
        my_vertices.push_back(vertex);
    }
    // For each vertex of each triangle
    for( unsigned int i=0; i<Triangle_vertexIndices.size(); i++ )
    {
        unsigned int tri_v_Index = Triangle_vertexIndices[i];
        my_triangle_list.push_back(tri_v_Index);
    }
    for( unsigned int i=0; i<temp_uvs.size(); i++ )
    {
        glm::vec2 uv = temp_uvs[i];
        my_uvs.push_back(uv);
    }
    fclose(file);

    return true;
}