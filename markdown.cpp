/*
---------------------------------------------------------------
    A SCRIPT TO CONVERT MARKDOWN TO HTML CODE
---------------------------------------------------------------
*/

#include <iostream>
#include <filesystem>
#include <getopt.h>
#include <regex>

using namespace std;
namespace fs = filesystem;

const string ENV_DEFAULT_THEME = "MARKDOWN_DEFAULT_THEME";

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

// Checks if the string is a url
bool verify_url(string url)
{
    string url_pattern = "\\b((?:https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:, .;]*[-a-zA-Z0-9+&@#/%=~_|])";

    // Construct regex object
    regex url_regex(url_pattern);

    return regex_match(url, url_regex);
}

string get_default_theme()
{
    char *theme = getenv(ENV_DEFAULT_THEME.c_str());
    return theme == NULL ? "github" : string(theme);
}

// Goes in the themes directory and lists the files
void list_themes()
{
    for (const auto &entry : fs::directory_iterator("<DIR_SED>/themes"))
    {
        cout << "   -" << base_name(remove_ext(entry.path())) << endl;
    }
}

// Goes in the themes directory and compares the files name with the passed one to verify that exists
bool validate_theme(string theme)
{
    // First check if the theme is a url
    bool isValid = false;

    for (const auto &entry : fs::directory_iterator("<DIR_SED>/themes"))
    {
        if (theme == base_name(remove_ext(entry.path())))
        {
            isValid = true;
            break;
        }
    }

    return isValid;
}

void show_help()
{
    cout << "Usage: markdown [OPTIONS] <MARKDOWN_FILE>" << endl
         << endl;
    cout << "OPTIONS:" << endl;
    cout << "   -t, --title    HTML title, displayed in browser tab (defaults to file name)" << endl;
    cout << "       --theme    HTML theme. You can pass a url to a css file or use one of the available themes" << endl;
    cout << "   -o, --out      Generated HTML output (defaults to the name of the provided file)" << endl;

    cout << endl;
    cout << "THEMES:" << endl;
    list_themes();
    cout << "To set a default theme run: [export MARKDOWN_DEFAULT_THEME=<THEME>]" << endl;
}

void show_incorrect_theme(string theme)
{
    cout << theme << " is not a valid theme" << endl
         << endl;
    cout << "Available theme options:" << endl;

    list_themes();
}

int main(int argc, char *argv[])
{
    // Available program options
    struct Options
    {
        string title = "";
        string output_file_name = "";
        // The style file path is generated with sed when compiling the code
        // If you want to use another default css style, change this path
        string style_file = "<DIR_SED>/themes/" + get_default_theme() + ".css";
    } options;

    // Get options
    int c;
    while (c != -1)
    {
        int option_index = 0;
        static struct option long_options[] = {
            {"title", required_argument, 0, 't'},
            {"theme", required_argument, 0, 0},
            {"out", required_argument, 0, 'o'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0},
        };
        c = getopt_long(argc, argv, "t:0:o:h",
                        long_options, &option_index);
        switch (c)
        {
        case 0:
        {
            string theme = optarg;
            bool is_url = verify_url(theme);
            if (!is_url && !validate_theme(theme))
            {
                show_incorrect_theme(theme);
                exit(1);
            }
            if (is_url)
                options.style_file = theme;
            else
                options.style_file = "<DIR_SED>/themes/" + theme + ".css";
            break;
        }
        case 'o':
            options.output_file_name = optarg;
            break;
        case 't':
            options.title = optarg;
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
    string command = "pandoc -s --lua-filter=<DIR_SED>/headers_anchor.lua --section-divs " + file + " -c " + options.style_file + " -f markdown -t html -o " + options.output_file_name + " --metadata title=" + options.title;
    system(command.c_str());
}
