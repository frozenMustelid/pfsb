bin/pfsb:
	mkdir bin/
	g++ -v -std=c++14 -o bin/pfsb src/pfsb.cpp

.PHONY: install clean uninstall
install:
	mkdir -p /usr/share/pfsb/pfrpg/html
	mkdir -p /usr/share/pfsb/pfrpg/images/environ /usr/share/pfsb/pfrpg/images/temp /usr/share/pfsb/pfrpg/images/type

	cp html/pfrpg.html html/pfrpg.css -t /usr/share/pfsb/pfrpg/html/
	-cp images/type/* /usr/share/pfsb/pfrpg/images/type
	-cp images/temp/* /usr/share/pfsb/pfrpg/images/temp
	-cp images/environ/* /usr/share/pfsb/pfrpg/images/environ
	
	cp bin/pfsb /usr/bin

clean:
	@rm -r bin/


#CSS file left alone so that generated monsters still display correctly
uninstall:
	rm /usr/bin/pfsb
	rm -r /usr/share/pfsb/pfrpg/images
	rm /usr/share/pfsb/pfrpg/html/pfrpg.html
	
