#!/bin/bash
INPUT_DIR=inputs
RESULT_DIR=overall_test_roule

mkdir -p $RESULT_DIR
rm -f $RESULT_DIR/*.result

make clean
make all

for name in $(ls $INPUT_DIR)
do
  echo "Running for input $name..."
  touch $RESULT_DIR/$name.result
  for i in {1..20}
  do
    ./mcut $INPUT_DIR/$name maxcut.out >> $RESULT_DIR/$name.result
  done
done
