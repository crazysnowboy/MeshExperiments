//
// Created by collin on 17-10-26.
//

#include "myMesh_wrap.h"

bool myMesh_wrap::Read(string obj_name,string texture_name,float scale)
{
    bool res_obj = myLoadOBJ(obj_name.c_str(),scale);
    if(res_obj == true)
    {

        printf("vertices size = %d \r\n",(int)my_vertices.size());
        printf("tri_list size = %d \r\n",(int)my_triangle_list.size());
        printf("uvs size = %d \r\n",(int)my_uvs.size());

    }
    bool res_texture = myLoadTexture(texture_name.c_str());
    if(res_texture==true)
    {
        printf("texture size = [%d %d} \r\n",(int)my_Texture.rows,(int)my_Texture.cols);

    }
    return res_obj&&res_texture;

}
