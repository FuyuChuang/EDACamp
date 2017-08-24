#!/usr/bin/env bash

exe="./checker"
output_dir="output"

for f in "$output_dir"/*; do
  command=""$exe" ./testcase/case1 "$f"/1.txt"
  echo "$command"
  result="$($command)"
  echo "$result"
  echo ""

  command=""$exe" ./testcase/case2 "$f"/2.txt"
  echo "$command"
  result="$($command)"
  echo "$result"
  echo ""

  command=""$exe" ./testcase/case3 "$f"/3.txt"
  echo "$command"
  result="$($command)"
  echo "$result"
  echo ""

  command=""$exe" ./testcase/case4 "$f"/4.txt"
  echo "$command"
  result="$($command)"
  echo "$result"
  echo ""

  command=""$exe" ./testcase/case5 "$f"/5.txt"
  echo "$command"
  result="$($command)"
  echo "$result"
  echo ""
done
