/*
 * This file is part of ElasticFusion.
 *
 * Copyright (C) 2015 Imperial College London
 *
 * The use of the code within this file and all code within files that
 * make up the software that is ElasticFusion is permitted for
 * non-commercial purposes only.  The full terms and conditions that
 * apply to the code within this file are detailed within the LICENSE.txt
 * file and at <http://www.imperial.ac.uk/dyson-robotics-lab/downloads/elastic-fusion/elastic-fusion-license/>
 * unless explicitly stated.  By downloading this file you agree to
 * comply with these terms.
 *
 * If you wish to use any of this code for commercial purposes then
 * please email researchcontracts.engineering@imperial.ac.uk.
 *
 */

#include "myRender.h"





const std::string myRender::Test = "Test";




void myRender::UploadGeometry(std::vector<glm::vec3> &vertices,std::vector<glm::vec2>&uvs,std::vector<long int> &tri_list)
{



    Triangle_Num=tri_list.size()/3;
    GLfloat *g_vertex_buffer_data = new GLfloat[Triangle_Num*3*3];
    GLfloat *g_uv_buffer_data = new GLfloat[Triangle_Num*3*2];


//    Triangle_Num = 1000;
    for (int j = 0;  j < Triangle_Num*3;  j++)
    {
        g_vertex_buffer_data[j*3+0]=vertices[tri_list[j]-1].x;
        g_vertex_buffer_data[j*3+1]=-vertices[tri_list[j]-1].y;
        g_vertex_buffer_data[j*3+2]=-vertices[tri_list[j]-1].z;

        g_uv_buffer_data[j*2+0]=uvs[tri_list[j]-1].x;
        g_uv_buffer_data[j*2+1]=uvs[tri_list[j]-1].y;

    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, Triangle_Num*3*3*sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    glGenBuffers(1, &uvo);
    glBindBuffer(GL_ARRAY_BUFFER, uvo);
    glBufferData(GL_ARRAY_BUFFER, Triangle_Num*3*2*sizeof(GLfloat), g_uv_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    With_Geometry = true;

}
myRender::~myRender()
{

}
void myRender::UploadTexture(cv::Mat texture)
{


    RGB_Image = new pangolin::GlTexture(texture.cols, texture.rows, GL_RGBA, true, 0, GL_RGB, GL_UNSIGNED_BYTE);
    RGB_Image->Upload(texture.data, GL_RGB, GL_UNSIGNED_BYTE);
    With_Texture = true;
}

void myRender::Shader_Render_with_Texture()
{




    drawProgram->Bind();
    drawProgram->setUniform(Uniform("MVP", render_mvp));
    drawProgram->setUniform(Uniform("pose", view_pose));


    /////////////// vertex ////////////////
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        0            // array buffer offset
    );




    /////////////// texture ////////////////
    ///////　把纹理ID和纹理单元绑定在一起////////
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, RGB_Image->tid);
    GLint texLoc  = glGetUniformLocation(drawProgram->programId(), "myTextureSampler");
    glUniform1i(texLoc, 0);

    ///////2nd attribute buffer : UVs///////
    glBindBuffer(GL_ARRAY_BUFFER, uvo);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                                // size : U+V => 2
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );


    glDrawArrays(GL_TRIANGLES, 0, Triangle_Num*3); // Triangle_Num*3 = vertex num

    //vertex
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //texture
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    drawProgram->Unbind();
}
void myRender::Shader_Render_without_Texture()
{




    drawProgram->Bind();
    drawProgram->setUniform(Uniform("MVP", render_mvp));
    drawProgram->setUniform(Uniform("pose", view_pose));


    /////////////// vertex ////////////////
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        0            // array buffer offset
    );


    glDrawArrays(GL_TRIANGLES, 0, Triangle_Num*3); // Triangle_Num*3 = vertex num

    //vertex
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);





    drawProgram->Unbind();
}

void myRender::Shader_Render(pangolin::OpenGlMatrix mvp, const Eigen::Matrix4f  pose)
{
    render_mvp =mvp;
    view_pose = pose;
    if(With_Geometry)
    {
        if(With_Texture)
        {
            Shader_Render_with_Texture();
        }
        else
        {
            Shader_Render_without_Texture();
        }

    }

}


void myRender::myGlDraw(void)
{
//    ////------------- draw points cloud---------------------------////
//    double s, t, x, y, z, nx, ny, nz, twopi;
//	static int cnt=0;
//
//    glBegin(GL_POINTS);
//    glColor3f(0.0f, 0.0f, 1.0f);
//    if(my3DMM!= nullptr)
//    {
//        for (int j = 0;  j < my3DMM->res_mesh.vertices.size();  j++)
//        {
//            float scale_data=my3DMM->GL_Draw_Scale!=0?my3DMM->GL_Draw_Scale:1000.0f;
//            x = my3DMM->res_mesh.vertices.at(j)[0]/scale_data;
//            y = my3DMM->res_mesh.vertices.at(j)[1]/scale_data;
//            z = my3DMM->res_mesh.vertices.at(j)[2]/scale_data;
//
//            glVertex3f((float) x, (float) y, (float) z);
//
//        }
//    }
//    glEnd();
//
//
//    glLineWidth(0.5);
//    glColor3f(1.0, 0.0, 0.0);
//
//    if(my3DMM!= nullptr)
//    {
//        for (int j = 0;  j < my3DMM->res_mesh.tvi.size();  j++)
//        {
//
//
//            float scale_data=my3DMM->GL_Draw_Scale!=0?my3DMM->GL_Draw_Scale:1000.0f;
//            int index[3][2]={0,1,1,2,2,0};
//            for(int k=0;k<3;k++)
//            {
//                glBegin(GL_LINES);
//                if(my3DMM->res_mesh.vertices.size()>0)
//                {
//                    //point 1 of line
//					int Point1_index=my3DMM->res_mesh.tvi.at(j)[index[k][0]];
//					int Point2_index=my3DMM->res_mesh.tvi.at(j)[index[k][1]];
//					if(Point1_index<my3DMM->res_mesh.vertices.size()&&Point2_index<my3DMM->res_mesh.vertices.size())
//					{
//						x = my3DMM->res_mesh.vertices.at(Point1_index)[0]/scale_data;
//						y = my3DMM->res_mesh.vertices.at(Point1_index)[1]/scale_data;
//						z = my3DMM->res_mesh.vertices.at(Point1_index)[2]/scale_data;
//						glVertex3f((float) x, (float) y, (float) z);
//
//						//point 2 of line
//						x = my3DMM->res_mesh.vertices.at(Point2_index)[0]/scale_data;
//						y = my3DMM->res_mesh.vertices.at(Point2_index)[1]/scale_data;
//						z = my3DMM->res_mesh.vertices.at(Point2_index)[2]/scale_data;
//						glVertex3f((float) x, (float) y, (float) z);
//
////						printf("right index= [j=%d k=%d p1_index=%d p2_index=%d] \r\n",j,k,Point1_index,Point2_index);
//					}
//					else
//					{
//						if(cnt++<5)
//						{
//							printf("error index= [j=%d k=%d p1_index=%d p2_index=%d] \r\n",j,k,Point1_index,Point2_index);
//						}
//
//					}
//
//                }
//
//
//                glEnd();
//
//            }
//
//        }
//    }



//
//    ////------------- draw triangles surface---------------------------////
//    double x, y, z;
//    static double r=0,g=0,b=0;
//
//    glShadeModel(GL_SMOOTH);
//
//    glBegin(GL_TRIANGLES);
//
//    if(my3DMM!= nullptr)
//    {
//        for (int j = 0;  j < my3DMM->mesh.tvi.size();  j++)
//        {
//
//
//            float scale_data=my3DMM->GL_Draw_Scale!=0?my3DMM->GL_Draw_Scale:1000.0f;
//            if(j<my3DMM->mesh.tci.size())
//            {
//                b = (double)my3DMM->mesh.tci.at(j)[0]/255.0;
//                g = (double)my3DMM->mesh.tci.at(j)[1]/255.0;
//                r = (double)my3DMM->mesh.tci.at(j)[2]/255.0;
//            }
//
//            glColor3f(r, g, b);
//            for(int k=0;k<3;k++)
//            {
//                if(my3DMM->res_mesh.vertices.size()>0)
//                {
//                    //point 1 of line
//                    int Point_index = my3DMM->res_mesh.tvi.at(j)[k];
//                    if ( Point_index < my3DMM->res_mesh.vertices.size() )
//                    {
//                        x = my3DMM->mesh.vertices.at(Point_index)[0]/scale_data;
//                        y = -my3DMM->mesh.vertices.at(Point_index)[1]/scale_data;
//                        z = my3DMM->mesh.vertices.at(Point_index)[2]/scale_data;
//                        glVertex3f((float) x, (float) y, (float) z);
//                    }
//                }
//
//            }
//
//        }
//    }
//    glEnd();


}
void myRender::Draw_gear_Test(GLfloat inner_radius, GLfloat outer_radius, GLfloat width, GLint teeth, GLfloat tooth_depth)
{
    GLint i;
    GLfloat r0, r1, r2;
    GLfloat angle, da;
    GLfloat u, v, len;

    r0 = inner_radius;
    r1 = outer_radius - tooth_depth / 2.f;
    r2 = outer_radius + tooth_depth / 2.f;

    da = 2.f * (float) M_PI / teeth / 4.f;

    glShadeModel(GL_SMOOTH);

    glNormal3f(0.f, 0.f, 1.f);

    /* draw front face */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++)
    {
        angle = i * 2.f * (float) M_PI / teeth;
        glVertex3f(r0 * (float) cos(angle), r0 * (float) sin(angle), width * 0.5f);
        glVertex3f(r1 * (float) cos(angle), r1 * (float) sin(angle), width * 0.5f);
        if (i < teeth)
        {
            glVertex3f(r0 * (float) cos(angle), r0 * (float) sin(angle), width * 0.5f);
            glVertex3f(r1 * (float) cos(angle + 3 * da), r1 * (float) sin(angle + 3 * da), width * 0.5f);
        }
    }
    glEnd();

    /* draw front sides of teeth */
    glBegin(GL_QUADS);
    da = 2.f * (float) M_PI / teeth / 4.f;
    for (i = 0; i < teeth; i++)
    {
        angle = i * 2.f * (float) M_PI / teeth;

        glVertex3f(r1 * (float) cos(angle), r1 * (float) sin(angle), width * 0.5f);
        glVertex3f(r2 * (float) cos(angle + da), r2 * (float) sin(angle + da), width * 0.5f);
        glVertex3f(r2 * (float) cos(angle + 2 * da), r2 * (float) sin(angle + 2 * da), width * 0.5f);
        glVertex3f(r1 * (float) cos(angle + 3 * da), r1 * (float) sin(angle + 3 * da), width * 0.5f);
    }
    glEnd();

    glNormal3f(0.0, 0.0, -1.0);

    /* draw back face */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++)
    {
        angle = i * 2.f * (float) M_PI / teeth;
        glVertex3f(r1 * (float) cos(angle), r1 * (float) sin(angle), -width * 0.5f);
        glVertex3f(r0 * (float) cos(angle), r0 * (float) sin(angle), -width * 0.5f);
        if (i < teeth)
        {
            glVertex3f(r1 * (float) cos(angle + 3 * da), r1 * (float) sin(angle + 3 * da), -width * 0.5f);
            glVertex3f(r0 * (float) cos(angle), r0 * (float) sin(angle), -width * 0.5f);
        }
    }
    glEnd();

    /* draw back sides of teeth */
    glBegin(GL_QUADS);
    da = 2.f * (float) M_PI / teeth / 4.f;
    for (i = 0; i < teeth; i++)
    {
        angle = i * 2.f * (float) M_PI / teeth;

        glVertex3f(r1 * (float) cos(angle + 3 * da), r1 * (float) sin(angle + 3 * da), -width * 0.5f);
        glVertex3f(r2 * (float) cos(angle + 2 * da), r2 * (float) sin(angle + 2 * da), -width * 0.5f);
        glVertex3f(r2 * (float) cos(angle + da), r2 * (float) sin(angle + da), -width * 0.5f);
        glVertex3f(r1 * (float) cos(angle), r1 * (float) sin(angle), -width * 0.5f);
    }
    glEnd();

    /* draw outward faces of teeth */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < teeth; i++)
    {
        angle = i * 2.f * (float) M_PI / teeth;

        glVertex3f(r1 * (float) cos(angle), r1 * (float) sin(angle), width * 0.5f);
        glVertex3f(r1 * (float) cos(angle), r1 * (float) sin(angle), -width * 0.5f);
        u = r2 * (float) cos(angle + da) - r1 * (float) cos(angle);
        v = r2 * (float) sin(angle + da) - r1 * (float) sin(angle);
        len = (float) sqrt(u * u + v * v);
        u /= len;
        v /= len;
        glNormal3f(v, -u, 0.0);
        glVertex3f(r2 * (float) cos(angle + da), r2 * (float) sin(angle + da), width * 0.5f);
        glVertex3f(r2 * (float) cos(angle + da), r2 * (float) sin(angle + da), -width * 0.5f);
        glNormal3f((float) cos(angle), (float) sin(angle), 0.f);
        glVertex3f(r2 * (float) cos(angle + 2 * da), r2 * (float) sin(angle + 2 * da), width * 0.5f);
        glVertex3f(r2 * (float) cos(angle + 2 * da), r2 * (float) sin(angle + 2 * da), -width * 0.5f);
        u = r1 * (float) cos(angle + 3 * da) - r2 * (float) cos(angle + 2 * da);
        v = r1 * (float) sin(angle + 3 * da) - r2 * (float) sin(angle + 2 * da);
        glNormal3f(v, -u, 0.f);
        glVertex3f(r1 * (float) cos(angle + 3 * da), r1 * (float) sin(angle + 3 * da), width * 0.5f);
        glVertex3f(r1 * (float) cos(angle + 3 * da), r1 * (float) sin(angle + 3 * da), -width * 0.5f);
        glNormal3f((float) cos(angle), (float) sin(angle), 0.f);
    }

    glVertex3f(r1 * (float) cos(0), r1 * (float) sin(0), width * 0.5f);
    glVertex3f(r1 * (float) cos(0), r1 * (float) sin(0), -width * 0.5f);

    glEnd();

    glShadeModel(GL_SMOOTH);

    /* draw inside radius cylinder */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++)
    {
        angle = i * 2.f * (float) M_PI / teeth;
        glNormal3f(-(float) cos(angle), -(float) sin(angle), 0.f);
        glVertex3f(r0 * (float) cos(angle), r0 * (float) sin(angle), -width * 0.5f);
        glVertex3f(r0 * (float) cos(angle), r0 * (float) sin(angle), width * 0.5f);
    }
    glEnd();

}
void myRender::drawTorus_Test(void)
{

#define TORUS_MAJOR     1.5
#define TORUS_MINOR     0.5
#define TORUS_MAJOR_RES 32
#define TORUS_MINOR_RES 32

    static GLuint torus_list = 0;
    int    i, j, k;
    double s, t, x, y, z, nx, ny, nz, scale, twopi;

    if (!torus_list)
    {
        // Start recording displaylist
        torus_list = glGenLists(1);
        glNewList(torus_list, GL_COMPILE_AND_EXECUTE);

        // Draw torus
        twopi = 2.0 * M_PI;
        for (i = 0;  i < TORUS_MINOR_RES;  i++)
        {
            glBegin(GL_QUAD_STRIP);///////////////////////////

            for (j = 0;  j <= TORUS_MAJOR_RES;  j++)
            {
                for (k = 1;  k >= 0;  k--)
                {
                    s = (i + k) % TORUS_MINOR_RES + 0.5;
                    t = j % TORUS_MAJOR_RES;

                    // Calculate point on surface
                    x = (TORUS_MAJOR + TORUS_MINOR * cos(s * twopi / TORUS_MINOR_RES)) * cos(t * twopi / TORUS_MAJOR_RES);
                    y = TORUS_MINOR * sin(s * twopi / TORUS_MINOR_RES);
                    z = (TORUS_MAJOR + TORUS_MINOR * cos(s * twopi / TORUS_MINOR_RES)) * sin(t * twopi / TORUS_MAJOR_RES);

                    // Calculate surface normal
                    nx = x - TORUS_MAJOR * cos(t * twopi / TORUS_MAJOR_RES);
                    ny = y;
                    nz = z - TORUS_MAJOR * sin(t * twopi / TORUS_MAJOR_RES);
                    scale = 1.0 / sqrt(nx*nx + ny*ny + nz*nz);
                    nx *= scale;
                    ny *= scale;
                    nz *= scale;

                    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
                    glNormal3f((float) nx, (float) ny, (float) nz);
                    glVertex3f((float) x, (float) y, (float) z);
                }
            }

            glEnd();///////////////////////////////////////////////
        }

        // Stop recording displaylist
        glEndList();
    }
    else
    {
        // Playback displaylist
        glCallList(torus_list);
    }
}