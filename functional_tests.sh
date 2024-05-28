#!/bin/bash

# Recompile binary file
make re
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'


# Check wether compilation succeeded and exits if it failed
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Makefile compilation successful${NC}"
else
    echo -e "${RED}Makefile compilation failed${NC}"
    exit 1
fi

# Check if binary exists
if [ ! -x "./syntax_analyzer" ]; then
    echo -e "${RED}Error: syntax_analyzer executable not found!${NC}"
    exit 1
fi

#Declare a counter; user to count how many test cases passed, on succeed
COUNTER=0;
# Get all files in sample/ directory
for file in sample/*; do
    # Proceed only if they are files (exclude directorys and symlinks)
    if [ -f "$file" ]; then
        # Run syntax_analyzer on file but redirect outputs to /dev/null to prevent flooding
        ./syntax_analyzer "$file" > /dev/null 2>/dev/null
        OUTPUT=$?
        # Output test case result and exit if needed
        if [ $OUTPUT -ne 0 ]; then
            echo -e "$file returned $OUTPUT, expected 0: ${RED}testing failed!${NC}"
            exit 1
        else
            echo -e "$file returned $OUTPUT, expected 0: ${GREEN}testing succeeded${NC}"
            let COUNTER=COUNTER+1
        fi
    fi
done

for file in sample/long/*; do
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

# Slightly different as we are checking if the program returns 1 (EXIT_FAILURE) since those test cases are supposed to fail
for file in sample/fail/*; do
    if [ -f "$file" ]; then
        ./syntax_analyzer "$file" > /dev/null 2>/dev/null
        OUTPUT=$?
        if [ $OUTPUT -eq 1 ]; then
            echo -e "$file returned $OUTPUT, expected 1: ${GREEN}testing succeeded${NC}"
            let COUNTER=COUNTER+1
        else
            echo -e "$file returned $OUTPUT, expected 1: ${RED}testing failed!${NC}"
            exit 1
        fi
    fi
done

echo -e "$COUNTER ${GREEN}files succesfully tested${NC}"