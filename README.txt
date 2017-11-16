I hope you find PFSB useful. It needs a lot of work right now, but even in this
primitive state it should be useful. I fully expect that nearly every line of
code I have written in this version will have be replaced in a subsequent
version.

I wanted to release this as GPL code, but due to the nature of PFRPG I felt it
was legally necessary for me to release this as OGL instead. I won't come after
you for incorporating my code into a GPL or similarly copyleft program, as long
as you return the favor if I ask. That said, I can't guarantee that another
company that the terms of the OGL won't allow me to name won't come after you.

Additional contributors, wittingly or otherwise, will be listed in CONTRIB.txt.

To build:

1. Ignore the config script. It just runs true.
2. Run make.
3. Run make install.


To use:

1. Open a terminal in the desired output folder.

2. Invoke the program from the command line. --version prints the version and
	license information. --help prints help text and a warning to not use $ in
	user input. --ogl prints information on Open Game Content and Product
	Identity. Any other switch will cause the program to error out.

3. Follow the prompts. You'll get an HTML file at the end. The HTML template and
	the CSS sheet are stored in a subdirectory of /usr/share/pfsb/.

4. Open the HTML file and read/print your monster. Or put it on a laptop and
	take it to game night/your FLGS. Or print it to a PDF and put it on your
	phone.


Also note that make uninstall intentionally leaves the CSS file where it is, so that existing files will still display correctly. To remove everything, run both "make uninstall" and "rm /usr/share/pfsb".


As written, this version of the program will only funtion on *nix systems, but
it should be trivial to make it behave on Windows. Follow development at $GITHUB/SRCFORGE LINK HERE
