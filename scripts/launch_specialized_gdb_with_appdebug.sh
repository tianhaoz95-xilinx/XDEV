#!/bin/bash

export PYTHONPATH=$PYTHONHOME/lib/python2.7/lib-dynload/:$PYTHONHOME/lib/python2.7/
exec "$SPECIAL_GDB_PATH/bin/gdb" -ex "source $XILINX_XRT/share/appdebug/appdebug.py" "${@:1}"
