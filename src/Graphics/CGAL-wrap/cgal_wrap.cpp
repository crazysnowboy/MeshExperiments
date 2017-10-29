//
// Created by collin on 17-10-27.
//

#include "cgal_wrap.h"

bool cgal_wrap::read_off_points(const char * file_name)
{
    std::ifstream in(file_name);
    if( !in || !CGAL::read_off_points( in, std::back_inserter(points) ) )
    {
        std::cerr << "Error: cannot read file" << std::endl;
        return false;
    }
    printf("points size = %d \r\n",points.size());
    for(int j=0;j<10;j++)
    {
        std::cout << "points["<< j <<"]" <<points[j] <<std::endl;
    }
    return true;

}
bool cgal_wrap::read_off_poly(const char * file_name)
{
    std::ifstream input(file_name);
    Polyhedron poly;
    if ( !input || !(input >> poly) || poly.empty() )
    {
        std::cerr << "Not a valid off file." << std::endl;
        return false;
    }
    Polyhedron::Point_iterator p_it;
    points.clear();
    for (p_it = poly.points_begin(); p_it != poly.points_end(); ++p_it)
    {
        Point point_(p_it->x(),p_it->y(),p_it->z());
        points.push_back(point_);

    }
    Polyhedron::Face_iterator f_it;
    for (f_it = poly.facets_begin(); f_it != poly.facets_end(); ++f_it)
    {
        Polyhedron::Halfedge_handle h = f_it->halfedge();

        auto  p0 = h->vertex()->point();
        h = h->next();
        auto  p1 = h->vertex()->point();
        h = h->next();
        auto  p2 = h->vertex()->point();

//        auto  p0 = h->face();
//        h = h->next();
//        auto  p1 = h->face();
//        h = h->next();
//        auto  p2 = h->face();


        std::cout <<" "<<p0<<" " <<  p1<<" " << p2 <<" "<<std::endl;
    }
    return true;
}
void cgal_wrap::DrawCGALMesh(const std::string& _draw_mode)
{

    if( _draw_mode == "Points" ) // -----------------------------------------
    {
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);

        for (int j = 0;  j < points.size();  j++)
        {
            glVertex3f(points[j].x(),points[j].y(),points[j].z());

        }
        glEnd();
    }
}
void cgal_wrap::TriangulatePoints(void)
{
    std::cerr << "Reconstructing-------- ";
    CGAL::Timer t;
    t.start();
    // Construct the mesh in a scale space.
    Reconstruction reconstruct (points.begin(), points.end());
    reconstruct.increase_scale(4);
    reconstruct.reconstruct_surface();
    std::cerr << "done in " << t.time() << " sec." << std::endl;
    t.reset();

    Reconstruction::Point_iterator it;
    points.clear();
    for (it = reconstruct.points_begin(); it != reconstruct.points_end(); ++it)
    {
        Point point_(it->x(),it->y(),it->z());
        points.push_back(point_);
    }
    printf("new points size = %d \r\n",points.size());
    for(int j=0;j<10;j++)
    {
        std::cout << "points["<< j <<"]" <<points[j] <<std::endl;
    }

}