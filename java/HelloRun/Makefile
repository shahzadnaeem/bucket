
DOCKERAPP=hellorun
DOCKERRUNARGS="Hello from docker" 5

all: docker

build: Main.java
	if [ ! -d build ]; then mkdir build; fi; javac -d ./build Main.java

pkg: build
	cd ./build; echo "Main-Class: sn.Main" > Manifest.txt
	cd ./build; rm -f hello.jar; jar cvfm hello.jar Manifest.txt sn/*

runner: pkg
	cat runjar.sh build/hello.jar > hello.run
	chmod 755 hello.run

docker: runner
	docker build -t $(DOCKERAPP) .

docker-run: docker
	docker run hellorun /hello.run $(DOCKERRUNARGS)

docker-run-die: docker
	$(MAKE) DOCKERRUNARGS='"This will not end well" -10' docker-run

clean:
	rm -rf ./build hello.run
