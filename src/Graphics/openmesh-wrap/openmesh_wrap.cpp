//
// Created by collin on 17-10-26.
//

#include "openmesh_wrap.h"
#include "gl.h"

bool openmesh_wrap::OpenMeshRead(string file_name)
{


    this->request_face_normals();
    this->request_face_colors();
    this->request_vertex_normals();
    this->request_vertex_colors();
    this->request_vertex_texcoords2D();

    bool res =  OpenMesh::IO::read_mesh(*this,file_name);

    if(res ==true)
    {

        this->update_face_normals();
        this->update_vertex_normals();

        printf(" ----open mesh read successfully------  \r\n");
        printf("mesh has_vertex_normals = %s  \r\n",this->has_vertex_normals()== false?"false":"true");
        printf("mesh has_face_normals = %s  \r\n",this->has_face_normals()==false?"false":"true");
        printf("mesh has_vertex_texcoords2D = %s  \r\n",this->has_vertex_texcoords2D()== false?"false":"true");
        printf("mesh has_vertex_colors = %s  \r\n",this->has_vertex_colors()==false?"false":"true");


    }
    return res;
}
void openmesh_wrap::DrawOpenMesh(const std::string& _draw_mode)
{
    typename OM::ConstFaceIter    fIt(faces_begin()), fEnd(faces_end());
    typename OM::ConstFaceVertexIter fvIt;

    if (_draw_mode == "Wireframe") // -------------------------------------------
    {
        glBegin(GL_TRIANGLES);
        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = cfv_iter(*fIt);
            glVertex3fv( &point(*fvIt)[0] );
            ++fvIt;
            glVertex3fv( &point(*fvIt)[0] );
            ++fvIt;
            glVertex3fv( &point(*fvIt)[0] );
        }
        glEnd();
    }

    else if (_draw_mode == "Solid Flat") // -------------------------------------
    {
        glBegin(GL_TRIANGLES);
        for (; fIt!=fEnd; ++fIt)
        {
            glNormal3fv( &normal(*fIt)[0] );

            fvIt = cfv_iter(*fIt);
            glVertex3fv( &point(*fvIt)[0] );
            ++fvIt;
            glVertex3fv( &point(*fvIt)[0] );
            ++fvIt;
            glVertex3fv( &point(*fvIt)[0] );
        }
        glEnd();

    }


    else if (_draw_mode == "Solid Smooth") // -----------------------------------
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, points());

        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, vertex_normals());


        glBegin(GL_TRIANGLES);
        glShadeModel(GL_SMOOTH);
        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = cfv_iter(*fIt);
            glArrayElement(fvIt->idx());
            ++fvIt;
            glArrayElement(fvIt->idx());
            ++fvIt;
            glArrayElement(fvIt->idx());
        }
        glEnd();

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);


    }

    else if (_draw_mode == "Colored Vertices") // --------------------------------
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, points());

        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, vertex_normals());

        if ( has_vertex_colors() )
        {
            glEnableClientState( GL_COLOR_ARRAY );
            glColorPointer(3, GL_UNSIGNED_BYTE, 0,vertex_colors());
        }

        glBegin(GL_TRIANGLES);
        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = cfv_iter(*fIt);
            glArrayElement(fvIt->idx());
            ++fvIt;
            glArrayElement(fvIt->idx());
            ++fvIt;
            glArrayElement(fvIt->idx());
        }
        glEnd();

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }


    else if (_draw_mode == "Solid Colored Faces") // -----------------------------
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, points());

        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, vertex_normals());

        glBegin(GL_TRIANGLES);
        for (; fIt!=fEnd; ++fIt)
        {
//            glColor3fv( *fIt );

            fvIt = cfv_iter(*fIt);
            glArrayElement(fvIt->idx());
            ++fvIt;
            glArrayElement(fvIt->idx());
            ++fvIt;
            glArrayElement(fvIt->idx());
        }
        glEnd();

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    }


    else if (_draw_mode == "Smooth Colored Faces") // ---------------------------
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, points());

        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, vertex_normals());

        glBegin(GL_TRIANGLES);
        for (; fIt!=fEnd; ++fIt)
        {
//            glMaterial( *fIt );

            fvIt = cfv_iter(*fIt);
            glArrayElement(fvIt->idx());
            ++fvIt;
            glArrayElement(fvIt->idx());
            ++fvIt;
            glArrayElement(fvIt->idx());
        }
        glEnd();

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    }
    else if( _draw_mode == "Points" ) // -----------------------------------------
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, points());

        if (has_vertex_colors())
        {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_UNSIGNED_BYTE, 0, vertex_colors());
        }

        glDrawArrays( GL_POINTS, 0, static_cast<GLsizei>(n_vertices()) );
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }
}