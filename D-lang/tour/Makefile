
# 

DMD=dmd

.PHONY: check clean all

all: check hello

check:
	@ if ! command -v dmd; \
	then \
		echo "You need to activate D-lang..."; \
		echo -e "\n\tsource ~/dlang/dmd-2.083.1/activate\n"; \
		exit 2; \
	fi

hello: hello.d
	$(DMD) $(<)

clean:
	rm -f hello *.o
