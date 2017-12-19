#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#define _PLATFAM __unix
#define _PLATFORM __linux

//_PLATFORM currently unused

#ifdef __unix
	#define _PFRPG_TEMPLATE "/usr/share/pfsb/pfrpg/html/pfrpg.html"
	#define _DIR_SEPARATOR_CHAR '/'
	//Pretty sure the char is unused
	#define _DIR_SEPARATOR_STRING "/"
#endif

/*#ifdef (_WIN32)

 * Commented out because unfinished
 * Also because I didn't bother to look up the Windows preprocessor test
 * Also because I don't like to release untested code

	#define _PFRPG_TEMPLATE "/usr/share/pfsb/pfrpg/html/pfrpg.html"
	#define _DIR_SEPARATOR_CHAR '\'
	#define _DIR_SEPARATOR_STRING "\"
#endif*/

#endif