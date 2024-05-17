#!/bin/sh

. /etc/profile
module avail
module load gcc/12.1.0

project-release/fluid/fluid 100 small.fld out/output.fld
