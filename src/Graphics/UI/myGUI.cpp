#include "myGUI.h"

myGUI::myGUI(bool liveCap, bool showcaseMode) : showcaseMode(showcaseMode)
{
    width = 1280;
    height = 980;
    panel = 205;

    width += panel;

    pangolin::Params windowParams;

    windowParams.Set("SAMPLE_BUFFERS", 0);
    windowParams.Set("SAMPLES", 0);

    pangolin::CreateWindowAndBind("Main", width, height, windowParams);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);


    pangolin::SetFullscreen(showcaseMode);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    s_cam = pangolin::OpenGlRenderState(pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.1, 1000),
                                        pangolin::ModelViewLookAt(0, 0, 100, 0, 0, 1, pangolin::AxisY));

    pangolin::Display("cam").SetBounds(0, 1.0f, 0, 1.0f, -640 / 480.0).SetHandler(new pangolin::Handler3D(s_cam));


    // Add named Panel and bind to variables beginning 'ui'
    // A Panel is just a View with a default layout and input handling
    pangolin::CreatePanel("ui").SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(panel));

    gpuMem = new pangolin::Var<int>("ui.GPU memory free", 0);
    pause = new pangolin::Var<bool>("ui.Pause", false, true);
    step = new pangolin::Var<bool>("ui.Step", false, false);
    save = new pangolin::Var<bool>("ui.Save", false, false);


    confidenceThreshold = new pangolin::Var<float>("ui.Confidence threshold", 10.0, 0.0, 24.0);
    depthCutoff = new pangolin::Var<float>("ui.Depth cutoff", 3.0, 0.0, 12.0);
    icpWeight = new pangolin::Var<float>("ui.ICP weight", 10.0, 0.0, 100.0);

}

myGUI:: ~myGUI()
{
    delete pause;
    delete step;
    delete save;

    delete gpuMem;
    delete confidenceThreshold;
    delete depthCutoff;
    delete icpWeight;

}

void myGUI::preCall()
{
    glClearColor(0.05 * !showcaseMode, 0.05 * !showcaseMode, 0.3 * !showcaseMode, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    width = pangolin::DisplayBase().v.w;
    height = pangolin::DisplayBase().v.h;

    pangolin::Display("cam").Activate(s_cam);
}

void myGUI::GL_Init()
{

    //材质反光性设置
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 10.0 };  //镜面反射参数
    GLfloat mat_shininess[] = { 100.0 };               //高光指数



    GLfloat light1_position[] = { 0.0, 0.0, 10.0, 1.0 };
    GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //环境光参数
    GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

    glClearColor(0.0, 0.0, 0.0, 0.0);  //背景色


    //材质属性
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    //灯光设置
    glLightfv(GL_LIGHT0,  GL_DIFFUSE/*漫反射*/,  light1_diffuse);
    glLightfv(GL_LIGHT0,  GL_POSITION,  light1_position);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数

    glEnable(GL_LIGHTING);   //开关:使用光
    glEnable(GL_LIGHT0);     //打开0#灯
    glEnable(GL_DEPTH_TEST); //打开深度测试
}


void myGUI::postCall()
{
    GLint cur_avail_mem_kb = 0;
    glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, &cur_avail_mem_kb);

    int memFree = cur_avail_mem_kb / 1024;

    gpuMem->operator=(memFree);

    pangolin::FinishFrame();

    glFinish();
}

