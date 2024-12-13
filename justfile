set shell := ["powershell.exe", "-c"]
set dotenv-load


dependencies $LIBRARY_PATH="" $CPLUS_INCLUDE_PATH="":
    ./scripts/01-compile_dependencies.ps1

clean:
    Remove-Item -Recurse out

setup-environment:
    ./scripts/02-setup_environment.ps1


compile: setup-environment
    ./scripts/03-compile_src.ps1


run main_file: compile
    ./scripts/04-run_main.ps1 {{ main_file }}


test: compile
    ./scripts/05-run_tests.ps1
