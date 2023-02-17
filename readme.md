# Markdown to HTML converter

A CLI program to convert your markdown into a github styled HTML.

## How to use it

This program requires the cli tool **pandoc**. To install it simply run `sudo apt install pandoc`. You can check their docs [here](https://github.com/jgm/pandoc).

1. Clone the repo: <br />
   `git clone https://github.com/MarcosNicolau/markdown_to_html.git`

2. Generate the executable: <br />
   `make`

3. Start using it: <br />
   `markdown ./<MY_MARKDOWN>.md` or see the options `markdown --help`

## Customize the style

If you wish to change the generated css, you can simply modify the `markdown.css` file or pass your own custom file: <br />
`markdown --style <MY_STYLE>.css ./<MY_MARKDOWN>.md`

<hr/>

### Warning

Before running `make`, make sure you don't have any other program by the name of "markdown" because it will replace it.

You can rename the program in the Makefile: <br />
`... -o /usr/bin/<YOUR_NAME>`
