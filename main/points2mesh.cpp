
#include "cgal_wrap.h"

int main(int argc, char** argv)
{
  if (argc!=3){
    std::cerr << "Error, no input output file provided\n example: scale_space input.off output.off";
    return 1;
  }
  // Read the data.
  std::vector<Point> points;
  std::ifstream in(argv[1]);
  std::cerr << "Reading " << std::flush;

  if( !in || !CGAL::read_off_points( in, std::back_inserter( points ) ) )
  {
    std::cerr << "Error: cannot read file" << std::endl;
    return EXIT_FAILURE;
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

  std::ofstream out (argv[2]);
  out << reconstruct;


  std::cerr << "Writing result in " << t.time() << " sec." << std::endl;
  std::cerr << "Done." << std::endl;
  return EXIT_SUCCESS;
}
