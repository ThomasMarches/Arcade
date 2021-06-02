# Makefile

JOBS = $(nproc)
BUILD_DIRECTORY = build
BUILD_TYPE = Debug

all:
	@if [ ! -e $(BUILD_DIRECTORY) ]; then \
		$(MAKE) dependances -s;\
		$(MAKE) config -s;\
	fi
	@$(MAKE) build_arcade -s

config:
	@cmake -B $(BUILD_DIRECTORY) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build_arcade:
	@(cd $(BUILD_DIRECTORY) && make -s -j $(JOBS))

dependances:
	@cmake -B $(BUILD_DIRECTORY) -DFETCH_DEPENDENCIES=True -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

clean:
	@cmake --clean $(BUILD_DIRECTORY)

fclean:
	@echo "-> CLEAN"
	@./clean.sh

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all