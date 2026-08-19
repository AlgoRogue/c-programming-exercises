#!/bin/sh
set -u
BIN="${1:?fault binary path required}"
TMPDIR=$(mktemp -d)
trap 'rm -rf "$TMPDIR"' EXIT

total=0; failures=0

assert_status() { expected="$1"; [ "$expected" = "$(cat "$TMPDIR/status")" ]; }
assert_stdout_contains() { grep -F -- "$1" "$TMPDIR/stdout" >/dev/null 2>&1; }
assert_stderr_contains() { grep -F -- "$1" "$TMPDIR/stderr" >/dev/null 2>&1; }
assert_free_log() { printf '%s\n' 'free' | cmp -s - "$1"; }

run_resource_case() {
    id="$1"; stdin_data="$2"; fail_at="$3"; error_type="$4"; free_log="$5"
    rm -f "$TMPDIR/stdout" "$TMPDIR/stderr" "$TMPDIR/status"
    total=$((total+1))
    export CALC_TEST_FREE_LOG="$free_log"
    export CALC_TEST_GETLINE_FAIL_AT="$fail_at"
    export CALC_TEST_GETLINE_ERROR="$error_type"
    printf '%b' "$stdin_data" | "$BIN" > "$TMPDIR/stdout" 2> "$TMPDIR/stderr"
    echo $? > "$TMPDIR/status"
}

res01() {
    free_log="$TMPDIR/res01_free.log"
    run_resource_case "RES-01" '1\n+\n2\nh\n' "-1" "none" "$free_log"
    assert_status 0 && assert_stdout_contains "Sonuç: 3.00" && assert_free_log "$free_log"
}

res02() {
    free_log="$TMPDIR/res02_free.log"
    run_resource_case "RES-02" '1\n' "-1" "none" "$free_log"
    assert_status 0 && assert_free_log "$free_log"
}

res03() {
    free_log="$TMPDIR/res03_free.log"
    run_resource_case "RES-03" '1\n' "2" "io" "$free_log"
    assert_status 1 && assert_stderr_contains "Girdi okunamadı" && assert_free_log "$free_log"
}

res04() {
    free_log="$TMPDIR/res04_free.log"
    run_resource_case "RES-04" '1\n' "2" "memory" "$free_log"
    assert_status 1 && assert_stderr_contains "Bellek ayrılamadı" && assert_free_log "$free_log"
}

run_one() {
    id="$1"; fn="$2"
    if $fn; then echo "$id PASSED"; else echo "$id FAILED"; failures=$((failures+1)); fi
}

run_one RES-01 res01
run_one RES-02 res02
run_one RES-03 res03
run_one RES-04 res04

echo '---'
successes=$((total - failures))
echo "$total test çalıştırıldı: $successes başarılı, $failures başarısız."
[ "$failures" -eq 0 ] || exit 1
