#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#define _PLATFAM __unix
#define _PLATFORM __linux

#if (_PLATFAM == __unix)
	#define _PFRPG_TEMPLATE "/usr/share/pfsb/pfrpg/html/pfrpg.html"
#endif

#endif
