#!/bin/bash

# One liner to find all top level `node_modules` directories and sort them by size
# Now a two liner!

# Usage: 1st parameter is where to start finding (defaults to '.' if not specified)

FROM=${1:-.}

find $FROM -name node_modules -prune -exec du -sh {} \; | grep -E "^[0-9]+M" | sort -rn -k1,1
