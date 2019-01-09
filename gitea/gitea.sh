#!/usr/bin/bash

CMD=${1:-ps}

case "x-${CMD}" in

    x-up)
        docker-compose up -d
    ;;

    x-down)
        docker-compose down
    ;;

    x-ps)
        docker-compose ps
    ;;

    x-log*)
        docker-compose logs
    ;;

    *)
        echo "Please enter a command... up, down, ps or log"
        exit 1
    ;;
esac