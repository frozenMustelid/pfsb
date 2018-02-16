all:bin/pfsb

bin/pfsb: obj/commonFunctions.o obj/main.o obj/PfMon.o obj/PfSpell.o
	@mkdir -p bin/
	g++ -std=c++14 -o bin/pfsb obj/commonFunctions.o obj/main.o obj/PfMon.o obj/PfSpell.o




obj/commonFunctions.o: src/commonFunctions.cpp
	@mkdir -p obj/
	g++ -c -std=c++14 -o obj/commonFunctions.o src/commonFunctions.cpp

obj/main.o: src/main.cpp
	@mkdir -p obj/
	g++ -c -std=c++14 -o obj/main.o src/main.cpp

obj/PfMon.o: src/PfMon.cpp
	@mkdir -p obj/
	g++ -c -std=c++14 -o obj/PfMon.o src/PfMon.cpp

obj/PfSpell.o: src/PfSpell.cpp
	@mkdir -p obj/
	g++ -c -std=c++14 -o obj/PfSpell.o src/PfSpell.cpp




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
