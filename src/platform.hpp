#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#define PLATFAM_ __unix
//#define PLATFORM_ __linux

//PLATFORM_ currently unused
//commented out to make it compile+run on other *nixes

#ifdef __unix
	#define _pfrpg_template "/usr/share/pfsb/pfrpg/html/pfrpg.html"
	#define _dir_separator_char '/'
	//Pretty sure the char is unused
	#define _dir_separator_string "/"
#endif

/*#ifdef (WIN32_)

 * Commented out because unfinished
 * Also because I didn't bother to look up the Windows preprocessor test
 * Also because I don't like to release untested code

	#define _pfrpg_template "/usr/share/pfsb/pfrpg/html/pfrpg.html"
	#define _dir_separator_char '\\'
	#define _dir_separator_string "\\"
#endif*/

#endif