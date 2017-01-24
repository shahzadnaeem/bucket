
all: runner

build: Main.java
	if [ ! -d build ]; then mkdir build; fi; javac -d ./build Main.java

pkg: build
	cd ./build; echo "Main-Class: sn.Main" > Manifest.txt
	cd ./build; rm -f hello.jar; jar cvfm hello.jar Manifest.txt sn/*

runner: pkg
	cat runjar.sh build/hello.jar > hello.run
	chmod 755 hello.run

clean:
	rm -rf ./build hello.run
