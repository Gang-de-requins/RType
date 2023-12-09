@echo off

set PROJECT_CLIENT_NAME=r-type_client
set PROJECT_SERVER_NAME=r-type_server

rd /s /q build
del %PROJECT_CLIENT_NAME%
del %PROJECT_SERVER_NAME%

echo Cleanup complete.
