set shell := ["powershell.exe", "-c"]
set dotenv-load


dependencies $LIBRARY_PATH="" $CPLUS_INCLUDE_PATH="":
    ./compile_dependencies.ps1


setup-environment:
    ./setup_environment.ps1


compile: setup-environment
    ./compile_src.ps1


main: compile
    ./run_main.ps1


test: compile
    ./run_tests.ps1
