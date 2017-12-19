all:bin/pfsb

bin/pfsb: obj/pfMon.o obj/main.o
	@mkdir -p bin/
	g++ -v -ansi -std=c++14 -o bin/pfsb obj/main.o obj/pfMon.o

obj/pfMon.o:
	@mkdir -p obj/
	g++ -c -v -ansi -std=c++14 -o obj/pfMon.o src/pfMon.cpp

obj/main.o:
	@mkdir -p obj/
	g++ -c -v -ansi -std=c++14 -o obj/main.o src/main.cpp




.PHONY: install clean distclean uninstall total-uninstall
install:
	@mkdir -p /usr/share/pfsb/pfrpg/html/

	@mkdir -p /usr/share/pfsb/pfrpg/images/environ/
	@mkdir -p /usr/share/pfsb/pfrpg/images/temp/
	@mkdir -p /usr/share/pfsb/pfrpg/images/type/

	cp html/pfrpg.html html/pfrpg.css -t /usr/share/pfsb/pfrpg/html/
	cp images/type/* /usr/share/pfsb/pfrpg/images/type/
#	-cp images/temp/* /usr/share/pfsb/pfrpg/images/temp/
#	-cp images/environ/* /usr/share/pfsb/pfrpg/images/environ/
	
	cp bin/pfsb /usr/bin/

clean:
	@rm -rf bin/
	@rm -rf obj/

distclean: clean



#CSS file left alone so that generated monsters still display correctly
uninstall:
	@rm -f  /usr/bin/pfsb
	@rm -rf /usr/share/pfsb/pfrpg/images
	@rm -f  /usr/share/pfsb/pfrpg/html/pfrpg.html

total-uninstall: uninstall
	@rm -rf  /usr/share/pfsb/
