set shell := ["powershell.exe", "-c"]
set dotenv-load


dependencies $LIBRARY_PATH="" $CPLUS_INCLUDE_PATH="":
    ./scripts/compile_dependencies.ps1

clean:
    Remove-Item -Recurse out

setup-environment:
    ./scripts/setup_environment.ps1


compile: setup-environment
    ./scripts/compile_src.ps1


run main_file: compile
    ./scripts/run_main.ps1 {{ main_file }}


test: compile
    ./scripts/run_tests.ps1
