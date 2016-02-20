#!/bin/bash
TEST_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
make -f ${TEST_DIR}/Makefile && ${TEST_DIR}/../bin/all_test
