BCEnvironmentApp
================

This is a behaviour changing app for environmentally good
behaviours. This is implemented as a web app using Wt. Written in C++
17.

This project was done for the persuasive design course at the
University of Oulu.

See LICENSE for licensing terms of this code.

Running
-------

Runs in a docker container for maximum portability.

Available from docker hub with `docker pull hhyyrylainen/bcenvironmentapp:latest`

Running:
```sh
docker run -itd -p 9090:9090 --restart always --name bcenvironmentapp hhyyrylainen/bcenvironmentapp:latest --http-port 9090
```

That command starts a container that is in the background running the service
and automatically restarting when needed. You can use `docker ps` to
see the running container's name in order to stop it, for example when
upgrading the service version.

You can then access post 9090 on the host to access the app.

TODO: add a way to configure the database details

Building
--------

### Docker build

```
git submodule update --init
docker build .
```

### Native build

It's also possible to compile and run this on the host provided all
the needed libraries and tools are installed.

Rough steps:

```sh
gem install os colorize rubyzip json sha3
./setup.rb

```

On OSes other than Ubuntu or Fedora you will want to run the setup
with `--no-packagemanager` parameter.

Note: Windows build might work but is untested.

You can then for example run the compiled program like this:
```sh
build/src/bcenvironmentapp --docroot build/src/ --http-address 0.0.0.0 --http-port 9090 -c config/wt_config.xml
```

You can check the `Makefile` for example commands how to rebuild and
run after minimal changes.
