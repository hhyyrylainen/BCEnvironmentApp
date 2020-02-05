default: run

build:
	mkdir -p build

setup:
	ruby setup.rb

cmake: build
	cd build && cmake ..

compile:
	$(MAKE) -C build

# test: cmake
# 	$(MAKE) -C build test

run: cmake compile 
	build/src/bcenvironmentapp --docroot build/src/ --http-address 0.0.0.0 \
	    --http-port 9090 -c config/wt_config.xml

.PHONY: default setup cmake compile run
