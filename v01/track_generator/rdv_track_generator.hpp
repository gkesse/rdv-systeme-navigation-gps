#pragma once

namespace rdv
{
    class track_generator
    {
    public:
        explicit track_generator(int _argc,
                                 char **_argv);
        ~track_generator();
        bool run();

    private:
        int m_argc;
        char **m_argv;
    };
}
