/*
---------------------------------------------------------------
    A SCRIPT TO CONVERT MARKDOWN TO HTML CODE
---------------------------------------------------------------
*/

#include <iostream>
#include <getopt.h>

using namespace std;

// Removes the path from a string
string base_name(string const &path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

// Removes a file extension
string remove_ext(string filename)
{
    return filename.substr(0, filename.find_last_of("."));
}

// Available Command line options
struct Options
{
    string title = "";
    string output_file_name = "";
    // The style file path is generated with sed when compiling the code
    // If you want to use another default css style, change this path
    string style_file = "<DIR_SED>/markdown.css";
};

void show_help()
{
    cout << "Usage: markdown [OPTIONS] <FILE_TO_PARSE>" << endl
         << endl;
    cout << "OPTIONS:" << endl;
    cout << "   -t, --title    HTML title, displayed in browser tab (defaults to file name)" << endl;
    cout << "   -o, --out      File name of the generated html (defaults to the name of the provided FILE)" << endl;
    cout << "   -s, --style    CSS file to change use a custom style instead of default" << endl;
    cout << "   -h, --help     Display help" << endl;
}

int main(int argc, char *argv[])
{
    Options options;
    // Get options
    int c;
    while (c != -1)
    {
        int option_index = 0;
        static struct option long_options[] = {
            {"title", required_argument, 0, 't'},
            {"out", required_argument, 0, 'o'},
            {"style", required_argument, 0, 's'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0},
        };
        c = getopt_long(argc, argv, "o:t:s:h",
                        long_options, &option_index);
        switch (c)
        {
        case 'o':
            options.output_file_name = optarg;
            break;
        case 't':
            options.title = optarg;
            break;
        case 's':
            options.style_file = optarg;
            break;
        case 'h':
            show_help();
            exit(0);
        }
    }
    // Verify that a markdown file was provided after the options.
    if (optind == argc)
    {
        cout << "You must provide a file in order to generate html." << endl;
        cout << "Pass --help or -h for more information about command" << endl;
        exit(1);
    }
    // Get the provided file
    string file = argv[optind++];
    string filename = remove_ext(base_name(file));

    // Default the options if not set
    if (options.output_file_name == "")
        options.output_file_name = filename + ".html";
    if (options.title == "")
        options.title = filename;

    // Run the command
    string command = "pandoc -s " + file + " -c " + options.style_file + " -f markdown -t html -o " + options.output_file_name + " --metadata title=" + options.title;
    system(command.c_str());
}
