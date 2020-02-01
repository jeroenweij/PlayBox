#!/bin/bash

prog="$1Program"

cp ToggleProgram.h "$prog.h"
cp ToggleProgram.cpp "$prog.cpp"

sed -i "s/ToggleProgram/$prog/g" "$prog.h"
sed -i "s/ToggleProgram/$prog/g" "$prog.cpp"

echo ""
echo "    src/$prog.h"
echo "    src/$prog.cpp"
echo ""
