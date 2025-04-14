build:
	@echo "[INFO]: building..."
	@[ -d build ] || mkdir -p build
	@cd build && cmake .. -G Ninja && ninja && cd ..
	@cp build/bin/r-type_client build
	@cp build/bin/r-type_server build

build_clang:
	@echo "[INFO]: compiling with clang..."
	@[ -d build ] || mkdir -p build
	@cd build && cmake -DCLANG=ON .. -G Ninja && ninja && cd ..

clear:
	@echo "[INFO]: cleaning..."
	@rm -rf build/

tests:
	@echo "[INFO]: building tests..."
	@[ -d build ] || mkdir -p build
	@cd build && cmake -DTESTS=ON .. -G Ninja && ninja && cd .. && cp build/bin/r-type_tests build && ./build/r-type_tests

coverage:
	@echo "[INFO]: generating coverage report..."
	@just tests && gcovr -r . --exclude "src/Engine" --exclude "build/" --exclude "tests/" --exclude "src/Client/main.cpp" --exclude "src/Server/" --exclude "include/" > tests/results.txt
	@./scripts/utils/test_coverage.sh

pkg:
	@echo "[INFO]: packaging..."
	@[ -d build ] || just build
	@cd build && cpack -G TGZ && cd ..

doc:
	doxygen Doxyfile

re: clear build
