#!/bin/bash

make
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Makefile compilation successful${NC}"
else
    echo -e "${RED}Makefile compilation failed${NC}"
    exit 1
fi

if [ ! -x "./syntax_analyzer" ]; then
    echo -e "${RED}Error: syntax_analyzer executable not found!${NC}"
    exit 1
fi

COUNTER=0;
for file in sample/*; do
    if [ -f "$file" ]; then
        ./syntax_analyzer "$file" > /dev/null 2>/dev/null
        OUTPUT=$?
        if [ $OUTPUT -ne 0 ]; then
            echo -e "$file returned $OUTPUT, expected 0: ${RED}testing failed!${NC}"
            exit 1
        else
            echo -e "$file returned $OUTPUT, expected 0: ${GREEN}testing succeeded${NC}"
            let COUNTER=COUNTER+1
        fi
    fi
done

for file in sample/fail/*; do
    if [ -f "$file" ]; then
        ./syntax_analyzer "$file" > /dev/null 2>/dev/null
        OUTPUT=$?
        if [ $OUTPUT -eq 0 ]; then
            echo -e "$file returned $OUTPUT, expected != 0: ${RED}testing failed!${NC}"
            exit 1
        else
            echo -e "$file returned $OUTPUT, expected != 0: ${GREEN}testing succeeded${NC}"
            let COUNTER=COUNTER+1
        fi
    fi
done

echo -e "$COUNTER ${GREEN}files succesfully tested${NC}"