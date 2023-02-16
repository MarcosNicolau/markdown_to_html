SHELL = /bin/sh
markdown: markdown.cpp
		sed "s|<DIR_SED>|$(PWD)|" markdown.cpp > generated.cpp && sudo g++ generated.cpp -o /usr/bin/markdown && rm generated.cpp
