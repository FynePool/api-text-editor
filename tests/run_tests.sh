#!/usr/bin/env bash
# Runs the editor binary against every input/output pair under tests/*/
# Usage: tests/run_tests.sh [path-to-editor-binary]

set -u

BINARY="${1:-./editor}"
TESTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ ! -x "$BINARY" ]; then
    echo "error: editor binary not found or not executable: $BINARY" >&2
    exit 1
fi

pass=0
fail=0

for input in "$TESTS_DIR"/*/*_input.txt; do
    [ -e "$input" ] || continue
    expected="${input%_input.txt}_output.txt"
    name="${input#"$TESTS_DIR"/}"

    if [ ! -f "$expected" ]; then
        echo "SKIP  $name (no matching output file)"
        continue
    fi

    actual="$("$BINARY" < "$input")"
    if [ "$actual" == "$(cat "$expected")" ]; then
        echo "PASS  $name"
        pass=$((pass + 1))
    else
        echo "FAIL  $name"
        fail=$((fail + 1))
    fi
done

echo
echo "Results: $pass passed, $fail failed"
[ "$fail" -eq 0 ]
