APPLICATION_ROOT = applications/MagnetBall
OUTPUT = _build

default: nucleo

.PHONY: test clean format format_check flash_nucleo

clean: 
	rm -rf $(APPLICATION_ROOT)/$(OUTPUT)

nucleo:
	@echo "Compiling MagnetBall for nucleo..."
	@make -C $(APPLICATION_ROOT)

test:
	@echo "Running tests..."
	@./test/run_tests.sh

format:
	@echo "Formatting Source Code..."
	@./tools/run_formatter.sh

format_check:
	@echo "Checking Source Code Formatting..."
	@./tools/run_formatter.sh -c

flash_nucleo:
	@make -C $(APPLICATION_ROOT) flash BOARD_VERSION=NUCLEO

flash_nucleo_jlink:
	@make -C $(APPLICATION_ROOT) flash_jlink BOARD_VERSION=NUCLEO
