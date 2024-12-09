set shell := ["powershell.exe", "-c"]
set dotenv-load


dependencies $LIBRARY_PATH="" $CPLUS_INCLUDE_PATH="":
    ./scripts/compile_dependencies.ps1


setup-environment:
    ./scripts/setup_environment.ps1


compile: setup-environment
    ./scripts/compile_src.ps1


main: compile
    ./scripts/run_main.ps1


test: compile
    ./scripts/run_tests.ps1
