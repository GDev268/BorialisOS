all: run

# create:
# docker build buildenv -t myos-buildenv
# docker run --rm -it -v "${pwd}:/root/env" myos-buildenv
run:
	docker run --rm -it -v "$(CURDIR):/root/env" myos-buildenv /bin/bash -c "cd kernel && make build-x86_64"

clean:
	docker run --rm -it -v "$(CURDIR):/root/env" myos-buildenv /bin/bash -c "rm -rf build && rm -rf target"
