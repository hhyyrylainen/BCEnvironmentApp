
RUN_COMMAND=build/src/bcenvironmentapp config/bce_options.json --docroot \
				"build/src/;/resources" --http-address 0.0.0.0 --http-port 9090 \
				-c config/wt_config.xml

BCE_COMMAND_BASE=build/src/bcetool config/bce_options.json

# For GDB run in emacs:
# build/src/bcenvironmentapp
# r ../../config/bce_options.json --docroot ".;/resources" --http-address 0.0.0.0 --http-port 9090 -c ../../config/wt_config.xml

default: run

build:
	mkdir -p build

build/gdb_commands:
	echo "run" > build/gdb_commands

setup:
	ruby setup.rb

cmake: build
	cd build && cmake ..

compile:
	$(MAKE) -C build

# test: cmake
# 	$(MAKE) -C build test

config/bce_options.json:
	echo "EDIT THE SETTINGS IN 'config/bce_options.json'!"
	cp config/bce_options_template.json config/bce_options.json

base-run: compile config/bce_options.json

run: cmake base-run
	$(RUN_COMMAND)

# Prints table SQL
bce-tables: base-run
	$(BCE_COMMAND_BASE) tables

# Attempts to create all needed tables
bce-create-tables: base-run
	$(BCE_COMMAND_BASE) create-tables

debug: compile
	gdb -ex=run --args $(RUN_COMMAND)

.PHONY: default setup cmake compile run debug base-run
