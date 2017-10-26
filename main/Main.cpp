//
// Created by snowboy on 17-6-23.
//
#include "myGUI.h"
#include "myRender.h"
#include "Mesh.h"

using namespace std;


class  myGUItest
{
public:

    myGUI * gui;
    Mesh mesh_;
    std::map<std::string, myRender*> RenderTool;

//    string mode = "Solid Smooth";
//    string mode = "Solid Colored Faces";
    string mode = "Solid Flat";


    myGUItest()
    {

        gui = new myGUI(GL_FALSE, GL_FALSE);
        gui->GL_Init();

        RenderTool[myRender::Test] = new myRender(loadProgramFromFile("TransformVertexShader.vert", "TextureFragmentShader.frag"));

    }

    void Launch(void);
    void gui_run(void);

    void Test1(void);
    int Test2(void);



};
void myGUItest::Test1(void)
{
    float obj_scale=1000000.0;
    bool res = mesh_.MyMesh_.Read("data/human/exp00.obj","data/human/diffuse.png",obj_scale);
    if(res)
    {
        RenderTool[myRender::Test]->UploadGeometry(mesh_.MyMesh_.my_vertices,mesh_.MyMesh_.my_uvs,mesh_.MyMesh_.my_triangle_list);
        RenderTool[myRender::Test]->UploadTexture(mesh_.MyMesh_.my_Texture);
    }
}
int myGUItest::Test2(void)
{


//    string file_name = "/home/collin/Documents/MyProjects/AAAAAA/face/bs2dfitting/3rdpart/vrn-face-reconstruction/data/GeneratedData/face_mesh/yuhao.off";
//    string file_name = "/home/collin/Documents/MyProjects/AAAAAA/face/bs2dfitting/3rdpart/vrn-face-reconstruction/data/GeneratedData/face_result_mesh/yuhao.obj";
    string file_name = "data/current_merged.obj";
//    string file_name = "data/head-reference2.obj";

    mesh_.OpenMesh_.OpenMeshRead(file_name);



}
void myGUItest::Launch(void)
{

    gui_run();
}

void myGUItest::gui_run(void)
{



    Test2();
    while(!pangolin::ShouldQuit())
    {
        /////////////////////////
        gui->preCall();
        /////////////////////////

//        RenderTool[myRender::Test]->Shader_Render(gui->s_cam.GetProjectionModelViewMatrix(), Eigen::Matrix4f::Identity());
//        RenderTool[myRender::Test]->Draw_gear_Test(1.f, 4.f, 1.f, 20, 0.7f);


        mesh_.OpenMesh_.DrawOpenMesh(mode);



        /////////////////////////
        gui->postCall();
        /////////////////////////



    }
    printf(" close down \r\n");
}

int main(int argc, char *argv[])
{



    myGUItest ui_test;
    ui_test.Launch();

    return 0;
}
