#!/usr/bin/env bash

################################################################################
# FileName  [ check.sh ]
# Synopsis  [ Check all outputs at once. ]
# Author    [ Yu-Hsuan Chang ]
# Date      [ 2017.8.26 ]
################################################################################

exe="./checker"
input_dir="$1"
output_dir="$2"

if [[ "$#" -ne 2 || ! -d "$1" || ! -d "$2" ]]; then
  echo "Usage "$0" <input dir> <output dir>"
  exit 1
fi

for user_dir in "$output_dir"/*; do
  for input in "$input_dir"/*; do
    input_base="${input##*/}"
    input_name="${input_base%%.*}"
    command=""$exe" "$input" "$user_dir"/"$input_name".out"
    echo "$command"
    result="$($command)"
    echo "$result"
    echo ""
  done
done
