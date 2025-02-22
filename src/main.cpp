#include <stdlib.h>
#include <curses.h> // includes stdio.h
#include <signal.h>
#include <unistd.h>
#include <cstring>
#include "colorspaces.hpp"
#include "python_bindings.hpp"

#define OPTIONS "aaa"

static void finish(int sig);

int
main(int argc, char *const argv[])
{
    (void) signal(SIGINT, finish);  // terminate on SIGNINT

    Py_Initialize();
    // Add current directory to path
    PyObject *sysPath = PySys_GetObject("path");
    PyList_Append(sysPath, PyUnicode_DecodeFSDefault("."));

    /*
    if (argc > 1)   // CLI Mode 
    {
        int opt = -1;
        while ((opt = getopt(argc, argv, OPTIONS)) != -1) 
        {
            switch (opt) 
            {
                //case ${1:option}:
                // ${2:description}
                    break;
                case 'h':
                // Output some helpful text about command line options.
                    //print_help(argv[0]);
                    exit(EXIT_FAILURE);
                    break;
                default:
                    // __builtin_unreachable(); ??
                    break;
            } // end switch
        } // end while
    }
    else    // TUI Mode 
    */
    {
        (void) initscr();               // initialize the curses library

        // settings
        (void) keypad(stdscr, TRUE);    // enable keyboard mapping
        (void) scrollok(stdscr, TRUE);  // allow stdscr to scroll
        (void) leaveok(stdscr, TRUE);   // leave cursor after refresh
    }

    color::rgb_t rgb{0.5f, 0.5f, 0.5f};
    color::xyz_t xyz = color::rgb_to_xyz(rgb);
    color::rgb_t rgb2 = color::xyz_to_rgb(xyz);
    color::lab_t lab = color::xyz_to_lab(xyz);

    color::rgb_t rgb3 = rgb + rgb2;

    for (;;)
    {
        mvprintw(10, 10, "rgb:  %f, %f, %f", rgb.x, rgb.y, rgb.z);
        mvprintw(11, 10, "xyz:  %f, %f, %f", xyz.x, xyz.y, xyz.z);
        mvprintw(12, 10, "back: %f, %f, %f", rgb2.x, rgb2.y, rgb2.z);
        mvprintw(13, 10, "lab:  %f, %f, %f", lab.x, lab.y, lab.z);
        mvprintw(14, 10, "rgb:  %f, %f, %f", rgb3.x, rgb3.y, rgb3.z);
        getch();
        refresh();
    }

    finish(0);
}

static void finish(int sig)
{
    endwin(); // this could be a problem with CLI mode

    Py_FinalizeEx();

    printf("\nCTRL-C pressed -- goodbye\n\n");
    // want to print saved colors and gradients here as well

    exit(EXIT_SUCCESS);
}
