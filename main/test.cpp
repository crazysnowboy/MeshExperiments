#include "cgal_wrap.h"

void Test1()
{

    CGAL::Geomview_stream gv(CGAL::Bbox_3(0, 0, 0, 350, 350, 350));


    K::Point_3 p;

    std::ifstream iFile("data/points3", std::ios::in);
    while ( iFile >> p )
    {

//        std::cout << "p=" << p << " x = "<< p.x() <<" y = "<<p.y() << " z =  " << p.z() << std::endl ;
//        printf(" --x  =  %d \r\n",(int)p.x());
//        sleep(1);
        gv << p;
        gv << CGAL::RED;
    }

    sleep(100);


}

void Test2()
{
    CGAL::Geomview_stream gv(CGAL::Bbox_3(-100, -100, -100, 600, 600, 600));
    gv.set_line_width(4);
    // gv.set_trace(true);
    gv.set_bg_color(CGAL::Color(0, 200, 200));
    // gv.clear();

    Delaunay D;
    Delaunay3d D3d;
    Terrain T;
    std::ifstream iFile("data/points3", std::ios::in);
    Point3 p;

    while ( iFile >> p )
    {
        D.insert( Point2(p.x(), p.y()) );
        D3d.insert( p );
        T.insert( p );
    }

    // use different colors, and put a few sleeps/clear.

    gv << CGAL::BLUE;
    std::cout << "Drawing 2D Delaunay triangulation in wired mode.\n";
    gv.set_wired(true);
    gv << D;
#if 1 // It's too slow !  Needs to use OFF for that.
    gv << CGAL::RED;
    std::cout << "Drawing its Voronoi diagram.\n";
    gv.set_wired(true);
    D.draw_dual(gv);
#endif

    sleep(5);
    gv.clear();

    std::cout << "Drawing 2D Delaunay triangulation in non-wired mode.\n";
    gv.set_wired(false);
    gv << D;
    sleep(5);
    gv.clear();

    std::cout << "Drawing 3D Delaunay triangulation in wired mode.\n";
    gv.set_wired(true);
    gv << D3d;
    sleep(5);
    gv.clear();
    std::cout << "Drawing 3D Delaunay triangulation in non-wired mode.\n";
    gv.set_wired(false);
    gv << D3d;
    sleep(5);
    gv.clear();

    std::cout << "Drawing Terrain in wired mode.\n";
    gv.set_wired(true);
    gv << T;
    sleep(5);
    gv.clear();
    std::cout << "Drawing Terrain in non-wired mode.\n";
    gv.set_wired(false);
    gv << T;

    std::cout << "Enter a key to finish" << std::endl;
    char ch;
    std::cin >> ch;
}

void Test3()
{
    CGAL::Geomview_stream gv(CGAL::Bbox_3(0, 0, 0, 350, 350, 350));

    // gv.set_trace(true);
    gv.clear(); // remove the pickplane.

    gv << K::Point_2 (200, 100);
    gv << CGAL::BLUE;
    gv << K::Point_3 (200, 100, 100);
    gv << CGAL::RED;
//    gv << K::Segment_2 (K::Point_2(200, 100),
//                        K::Point_2(300, 100));
//    gv << CGAL::GREEN;
//    gv << K::Segment_3 (K::Point_3(200, 100, 100),
//                        K::Point_3(300, 100, 200));
//    gv << CGAL::DEEPBLUE;
//    gv << K::Sphere_3 (K::Point_3(100, 100, 100), 1000);
//    gv << CGAL::VIOLET;
//    gv << K::Triangle_2 (K::Point_2(200, 200),
//                         K::Point_2(220, 220),
//                         K::Point_2(180, 220));
//    gv << CGAL::ORANGE;
//    gv << K::Triangle_3 (K::Point_3(200, 200, 50),
//                         K::Point_3(220, 220, 80),
//                         K::Point_3(180, 220, 100));
//    gv << CGAL::PURPLE;
//    gv << K::Tetrahedron_3 (K::Point_3(100, 100, 180),
//                            K::Point_3(120,  70, 220),
//                            K::Point_3(100, 100, 220),
//                            K::Point_3(120, 150, 250));
//    gv << CGAL::Bbox_2(10, 10, 30, 30);
//    gv << CGAL::Bbox_3(10, 10, 10, 30, 30, 30);
//
//    gv << CGAL::RED;
//    gv << K::Ray_2(K::Point_2(205,205), K::Point_2(500,500));
//    gv << K::Ray_3(K::Point_3(250,250,250), K::Point_3(500,500,500));
//    gv << K::Line_2(K::Point_2(195,195), K::Point_2(500,500));
//    gv << K::Line_3(K::Point_3(150,150,150), K::Point_3(500,500,500));

    gv.look_recenter();

    std::cout << "Stopping in 1 minute" << std::endl;
    sleep(60);


}

void Test4()
{

    char inputfile[100]= {"data/model.off"};
    // Read the data.
    std::vector<Point> points;
    std::ifstream in(inputfile);
    std::cerr << "Reading " << std::flush;

    if( !in || !CGAL::read_off_points( in, std::back_inserter( points ) ) )
    {
        std::cerr << "Error: cannot read file" << std::endl;

    }

    std::cerr << "done: " << points.size() << " points." << std::endl;

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
    for (it = reconstruct.points_begin(); it != reconstruct.points_end(); ++it)
    {
//        std::cout << "points = " << *it <<std::endl;

//        float x = it->x();
//        float y = it->y();
//        float z = it->z();
//
//        printf("[%f %f %f]\r\n",x,y,z);

    }



    std::cerr << "Writing result in " << t.time() << " sec." << std::endl;
    std::cerr << "Done." << std::endl;
}

void Test5()
{


    P3DT3 T;

    T.insert(Point(0,0,0));
    T.insert(Point(.1,0,0));
    T.insert(Point(0,.1,0));
    T.insert(Point(0,0,.1));
    T.insert(Point(.2,.2,.2));
    T.insert(Point(.9,0,.1));

    // Set the color of finite vertices of degree 6 to red.
    P3DT3::Vertex_iterator vit;
    for (vit = T.vertices_begin(); vit != T.vertices_end(); ++vit)
    {

        if (T.degree(vit) == 16)
        {
            vit->info() = CGAL::RED;
        }
    }
}
int main()
{

//    Test1();
//    Test3();
    Test4();
    return 0;
}
