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

#ifndef MYRENDER_H_
#define MYRENDER_H_

#include "Shaders.h"
#include "Uniform.h"

#include <pangolin/gl/gl.h>
#include <pangolin/display/opengl_render_state.h>

#include "Defines.h"
#include <zconf.h>


#include "my_mesh_data.h"

class myRender
{
public:

    myRender(std::shared_ptr<Shader> program):drawProgram(program)
    {
        With_Texture = false;
        With_Geometry = false;
    }

    virtual ~myRender();

    void UploadTexture(cv::Mat texture);
    void UploadGeometry(std::vector<glm::vec3> &vertices,std::vector<glm::vec2>&uvs,std::vector<long int> &tri_list);
    void Shader_Render_with_Texture();
    void Shader_Render_without_Texture();
    void Shader_Render( pangolin::OpenGlMatrix mvp, const Eigen::Matrix4f pose);


    void myGlDraw(void);

    void Draw_gear_Test(GLfloat inner_radius, GLfloat outer_radius, GLfloat width, GLint teeth, GLfloat tooth_depth);
    void drawTorus_Test(void);


    static const std::string Test;

private:

    GLuint vbo;
    GLuint fid;
    GLuint uvo;
    int Triangle_Num;
    std::shared_ptr<Shader> drawProgram;

    pangolin::OpenGlMatrix render_mvp;
    Eigen::Matrix4f  view_pose;

    pangolin::GlTexture* RGB_Image;

    bool With_Texture;
    bool With_Geometry;
};

#endif /* FEEDBACKBUFFER_H_ */
