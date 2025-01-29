#include <iostream>
#include <gflags/gflags.h>
#include "base/logging.hpp"

DEFINE_bool(showHelp, false, "Show help on all flags.");
DEFINE_string(inputDir, "", "Path to kmls.");
DEFINE_string(outputDir, "", "Path to converted kmls.");

int main(int argc, char **argv)
{
    std::cout << "Démarrage de l'application..." << std::endl;
    gflags::SetUsageMessage("The tool is used to generate more smooth track based on "
                            "waypoints from the kml. The kml has to contain points "
                            "within LineString tag. If the router can't build the route "
                            "than the specific path will be untouched. Multiple kmls into "
                            " the directory are supported.\n\n"
                            "Usage example: "
                            "./track_generator_tool -inputDir=path/to/input/ -outputDir=/path/to/output/");

    gflags::ParseCommandLineFlags(&argc, &argv, false);

    if (argc == 1 || FLAGS_showHelp)
    {
        gflags::ShowUsageWithFlags(argv[0]);
        return 0;
    }

    if (FLAGS_inputDir.empty() || FLAGS_outputDir.empty())
    {
        LOG(LINFO, (FLAGS_inputDir.empty() ? "Input" : "Output", "directory is required."));
        gflags::ShowUsageWithFlags(argv[0]);
        return 1;
    }

    std::cout << "FLAGS_inputDir : " << FLAGS_inputDir << std::endl;
    std::cout << "FLAGS_outputDir : " << FLAGS_outputDir << std::endl;

    return 0;
}
