#include "rdv_track_generator.hpp"
#include "base/rdv_file_loader.hpp"
#include "kml/rdv_kml_deserializer.hpp"
#include "kml/rdv_kml_file_data.hpp"
#include <gflags/gflags.h>
#include <iostream>

namespace rdv
{
    DEFINE_bool(showHelp, false, "Afficher l'aide sur tous les indicateurs.");
    DEFINE_string(inputDir, "", "Chemin vers les kmls.");
    DEFINE_string(outputDir, "", "Chemin vers les kmls convertis.");
    DEFINE_int32(vehicleType, 0, "Valeur numérique de l'énumération routing::VehicleType. Piéton par défaut.");

    track_generator::track_generator(int _argc,
                                     char **_argv)
        : m_argc(_argc),
          m_argv(_argv)
    {
    }

    track_generator::~track_generator()
    {
    }

    bool track_generator::run()
    {
        gflags::SetUsageMessage("L'outil est utilisé pour générer une piste plus fluide basée sur "
                                "les points de cheminement du kml. Le kml doit contenir des points "
                                "dans la balise LineString. Si le routeur ne peut pas créer l'itinéraire "
                                ", le chemin spécifique ne sera pas modifié. Plusieurs kmls dans "
                                " le répertoire sont pris en charge.\n\n"
                                "Exemple d'utilisation : "
                                "./track_generator -inputDir=path/to/input/ -outputDir=/path/to/output/");
        gflags::ParseCommandLineFlags(&m_argc, &m_argv, false);

        if (m_argc == 1 || FLAGS_showHelp)
        {
            gflags::ShowUsageWithFlags(m_argv[0]);
            return false;
        }

        if (FLAGS_inputDir.empty() || FLAGS_outputDir.empty())
        {
            gflags::ShowUsageWithFlags(m_argv[0]);
            return false;
        }

        std::string regex = "\\.kml$";
        rdv::FilesList inputFiles;

        file_loader loader(FLAGS_inputDir, regex);
        if (!loader.run(inputFiles))
        {
            return false;
        }

        if (inputFiles.empty())
        {
            std::cout << "Le répertoire d'entrée ne contient pas de kmls." << std::endl;
            return false;
        }

        for (const auto &file : inputFiles)
        {
            kml::FileData fileData;
            std::string filename = FLAGS_inputDir + "/" + file;
            kml_deserializer des(filename);
            if (!des.run(fileData))
            {
                continue;
            }
            // break;
        }

        return true;
    }
}
