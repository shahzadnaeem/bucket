

PHPUNIT=phpunit
CONFIG=--configuration=phpunitconfig.xml --verbose

test1:
	$(PHPUNIT) $(CONFIG) $@.php

test2:
	$(PHPUNIT) $(CONFIG) $@.php

test3:
	$(PHPUNIT) $(CONFIG) $@.php

tar:
	tar czvf ../php-tape-archive-compressed .

TOP := $(lastword $(MAKEFILE_LIST))

show: targets
help: targets

targets:
	grep -e ':$$' $(TOP) | grep -v '$@:' | sed -e 's/^/  /'
