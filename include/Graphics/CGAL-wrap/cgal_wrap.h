//
// Created by collin on 17-10-27.
//

#ifndef EXPERIMENTPROJECT_CGAL_WRAP_H
#define EXPERIMENTPROJECT_CGAL_WRAP_H

#include <fstream>
#include <iostream>

#include <CGAL/Cartesian.h>
#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/IO/Triangulation_geomview_ostream_2.h>
#include <CGAL/IO/Triangulation_geomview_ostream_3.h>
typedef CGAL::Cartesian<double>  K;

typedef K::Point_2 Point2;
typedef CGAL::Projection_traits_xy_3<K> Gt3;
typedef Gt3::Point Point3;
typedef CGAL::Delaunay_triangulation_2<K>   Delaunay;
typedef CGAL::Delaunay_triangulation_2<Gt3> Terrain;
typedef CGAL::Delaunay_triangulation_3<K>   Delaunay3d;





#include <Scale_space_surface_reconstruction_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/read_off_points.h>
#include <CGAL/Timer.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel     Kernel;
typedef CGAL::Scale_space_surface_reconstruction_3<Kernel>    Reconstruction;
typedef Kernel::Point_3 Point;
typedef Reconstruction::Facet_const_iterator                   Facet_iterator;

#include <unistd.h>
#include <CGAL/intersections.h>
#include <CGAL/IO/Geomview_stream.h>


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Periodic_3_Delaunay_triangulation_traits_3.h>
#include <CGAL/Periodic_3_Delaunay_triangulation_3.h>
#include <CGAL/Triangulation_vertex_base_with_info_3.h>

#include <CGAL/IO/Color.h>

#include "gl.h"
typedef CGAL::Exact_predicates_inexact_constructions_kernel mK;
typedef CGAL::Periodic_3_Delaunay_triangulation_traits_3<mK> Gt;

typedef CGAL::Periodic_3_triangulation_ds_vertex_base_3<> VbDS;
typedef CGAL::Triangulation_vertex_base_3<Gt, VbDS>       Vb;

typedef CGAL::Periodic_3_triangulation_ds_cell_base_3<> CbDS;
typedef CGAL::Triangulation_cell_base_3<Gt, CbDS>       Cb;

typedef CGAL::Triangulation_vertex_base_with_info_3<CGAL::Color, Gt, Vb> VbInfo;
typedef CGAL::Triangulation_data_structure_3<VbInfo, Cb>                 TDS;
typedef CGAL::Periodic_3_Delaunay_triangulation_3<Gt, TDS>               P3DT3;




#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/triangulate_hole.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/foreach.hpp>


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>     Polyhedron;


#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/HalfedgeDS_vector.h>
#include <CGAL/HalfedgeDS_list.h>
#include <CGAL/HalfedgeDS_vertex_base.h>
#include <CGAL/HalfedgeDS_halfedge_base.h>
#include <CGAL/HalfedgeDS_face_base.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <iostream>
#include <fstream>
//#include "performance_2.h"


typedef CGAL::Simple_cartesian<double>  CGALKernel;
typedef CGALKernel::Point_3             Point_3_;


class cgal_wrap
{

public:
    std::vector<Point> points;

    bool read_off_points(const char * file_name);
    bool read_off_poly(const char * file_name);
    void DrawCGALMesh(const std::string& _draw_mode);
    void TriangulatePoints(void);

};


#endif //EXPERIMENTPROJECT_CGAL_WRAP_H
