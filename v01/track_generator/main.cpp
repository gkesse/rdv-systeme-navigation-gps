#include "rdv_track_generator.hpp"
#include "xml/rdv_xml_parser.hpp"
#include <iostream>

int main(int _argc, char **_argv)
{
    std::cout << "Demarrage de l'application..." << std::endl;
    rdv::xml_parser_init();
    rdv::track_generator app(_argc, _argv);
    app.run();
    rdv::xml_parser_clean();
    return 0;
}