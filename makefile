###############################################################################
#  MinGW(Git Bash) / Linux-like 쉘 환경에서 사용할 규칙
###############################################################################

NAME := DX12

all: $(NAME)_release

debug: $(NAME)_debug
release: $(NAME)_release

###############################################################################
# 빌드 타겟 - Debug
###############################################################################
$(NAME)_debug:
	@echo [MinGW] Building Debug...
	@cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug .
	@cmake --build build --config Debug
	@if [ -f "./build/bin/Debug/$(NAME).exe" ]; then \
		mv "./build/bin/Debug/$(NAME).exe" "./$(NAME)_debug.exe"; \
	else \
		echo "[ERROR] ./build/bin/Debug/$(NAME).exe not found!"; \
		exit 1; \
	fi
	@echo [SUCCESS] $@ compiled successfully with debug mode!

###############################################################################
# 빌드 타겟 - Release
###############################################################################
$(NAME)_release:
	@echo [MinGW] Building Release...
	@cmake -Bbuild -DCMAKE_BUILD_TYPE=Release .
	@cmake --build build --config Release
	@if [ -f "./build/bin/Release/$(NAME).exe" ]; then \
		mv "./build/bin/Release/$(NAME).exe" "./$(NAME)_release.exe"; \
	else \
		echo "[ERROR] ./build/bin/Release/$(NAME).exe not found!"; \
		exit 1; \
	fi
	@echo [SUCCESS] $@ compiled successfully with release mode!

###############################################################################
# Clean / fclean / re
###############################################################################
clean:
	@rm -rf build
	@echo "[CLEAN] Build files removed (MinGW)!"

fclean: clean
	@rm -f "$(NAME)_debug.exe" "$(NAME)_release.exe"
	@echo "[FCLEAN] Executables removed (MinGW)!"

re: fclean all


###############################################################################
# Run
###############################################################################
run: $(NAME)_debug
	@./$(NAME)_debug.exe

.PHONY: all debug release clean fclean re shader run
