#!/usr/bin/env bash

######################################
# DO NOT CHANGE THIS FOLLOWING LINE: #
OP2_BASELINE_FILE="baseline_op_02.c" #
######################################

############################################
# HOWEVER, CHANGE THESE LINES:             #
# Replace the filenames with your variants #
############################################
OP2_SUBMISSION_VAR01_FILE="optimized_op_02_var_01.c" # <-- CHANGE ME!
OP2_SUBMISSION_VAR02_FILE="optimized_op_02_var_02.c" # <-- CHANGE ME!
OP2_SUBMISSION_VAR03_FILE="optimized_op_02_var_03.c" # <-- CHANGE ME!

######################################################
# You can even change the compiler flags if you want #
######################################################
# CFLAGS="-std=c99 -O2"
CFLAGS="-std=c99 -O2 -mavx2 -mfma -pthread"

