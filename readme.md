# Markdown to HTML converter

A CLI program to convert your markdown into an awesome styled HTML.

## How to use it

This program requires the cli tool **pandoc**. To install it simply run `sudo apt install pandoc`. You can check their docs [here](https://github.com/jgm/pandoc).

1. Clone the repo: <br />
   `git clone https://github.com/MarcosNicolau/markdown_to_html.git`

2. Generate the executable: <br />
   `make`

3. Start using it: <br />
   `markdown ./<MY_MARKDOWN>.md` or see the options `markdown --help`

4. Choose your theme: <br/>

    Currently there are 4 available themes:

    - [github](https://sindresorhus.com/github-markdown-css/) (default)
    - [air](http://markdowncss.github.io/air/)
    - [modest](http://markdowncss.github.io/modest/)
    - [retro](http://markdowncss.github.io/retro/)
    - [splendor](http://markdowncss.github.io/splendor/)

    And choose by running: <br />
    `markdown --theme modest ./<MY_MARKDOWN>.md`

## Add your custom themes

If you want to add your own themes, simply create a file in the [themes](https://github.com/MarcosNicolau/markdown_to_html/themes) folder. Then, to use it, simply pass the file name: <br/>
`markdown --theme <MY_THEME> ./<MY_MARKDOWN>.md`

Or pass a url: <br />
`markdown --theme https://<MY_STYLE_URL> ./<MY_MARKDOWN>.md`

If you wish to change the default theme run: <br />
`export MARKDOWN_DEFAULT_THEME="<YOUR_THEME>"`

<hr/>

### Warning

Before running `make`, make sure you don't have any other program by the name of "markdown" because it will replace it.

You can rename the program in the Makefile: <br />
`... -o /usr/bin/<YOUR_NAME>`

Before running `make`, make sure you don't have any other program by the name of "markdown" because it will replace it.

You can rename the program in the Makefile: <br />
`... -o /usr/bin/<YOUR_NAME>`
