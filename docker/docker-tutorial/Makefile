
.PHONY:	build run images

NAME ?= friendlyhello

build: Dockerfile
	docker build -t $(NAME) .

images:
	docker images

run:	build
	docker run -p4000:80 $(NAME)
