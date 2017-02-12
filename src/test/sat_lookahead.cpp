#include "sat_solver.h"
#include "sat_lookahead.h"
#include "dimacs.h"

void tst_sat_lookahead(char ** argv, int argc, int& i) {
    if (argc != i + 2) {
        std::cout << "require dimacs file name\n";
        return;
    }
    enable_trace("sat");
    reslimit limit;
    params_ref params;
    sat::solver solver(params, limit);
    sat::lookahead lh(solver);
    char const* file_name = argv[i + 1];
    ++i;

    {
        std::ifstream in(file_name);
        if (in.bad() || in.fail()) {
            std::cerr << "(error \"failed to open file '" << file_name << "'\")" << std::endl;
            exit(ERR_OPEN_FILE);
        }
        parse_dimacs(in, solver);
    }
   
    IF_VERBOSE(20, solver.display_status(verbose_stream()););

    std::cout << lh.check() << "\n";
}
