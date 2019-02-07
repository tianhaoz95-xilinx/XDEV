#!/bin/bash

exec "$SPECIAL_GDB_PATH/bin/gdb" -ex "source $XILINX_XRT/share/appdebug/appdebug.py" "${@:1}"
