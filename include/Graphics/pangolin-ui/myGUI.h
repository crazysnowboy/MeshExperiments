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

#ifndef MYGUI_H_
#define MYGUI_H_

#include <pangolin/pangolin.h>
#include <pangolin/gl/gl.h>
#include <pangolin/gl/gldraw.h>
#include <map>
#include <Shaders.h>

#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049

class myGUI
{
public:
    myGUI(bool liveCap, bool showcaseMode);

    ~myGUI();

    void preCall();
    void GL_Init();
    void postCall();

    bool showcaseMode;

    int width;
    int height;
    int panel;

    pangolin::Var<bool> * pause,
             * step,
             * save;

    pangolin::Var<float> * confidenceThreshold,
             * depthCutoff,
             * icpWeight;

    pangolin::Var<int> * gpuMem;

    pangolin::OpenGlRenderState s_cam;


};


#endif /* GUI_H_ */
