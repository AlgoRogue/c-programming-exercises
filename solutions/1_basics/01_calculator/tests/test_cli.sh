#!/bin/sh
set -u
BIN="${1:?binary path required}"
TMPDIR=$(mktemp -d)
trap 'rm -rf "$TMPDIR"' EXIT

total=0; failures=0

run_command() { rm -f "$TMPDIR/stdout" "$TMPDIR/stderr" "$TMPDIR/status"; "$BIN" "$@" < /dev/null > "$TMPDIR/stdout" 2> "$TMPDIR/stderr"; echo $? > "$TMPDIR/status"; }
assert_status() { expected="$1"; [ "$expected" = "$(cat "$TMPDIR/status")" ]; }
assert_stdout_exact() { expected="$1"; printf '%s\n' "$expected" | diff -q - "$TMPDIR/stdout" >/dev/null 2>&1; }
assert_stdout_empty() { [ ! -s "$TMPDIR/stdout" ]; }
assert_stderr_empty() { [ ! -s "$TMPDIR/stderr" ]; }
assert_stdout_contains() { grep -F -- "$1" "$TMPDIR/stdout" >/dev/null 2>&1; }
assert_stderr_contains() { grep -F -- "$1" "$TMPDIR/stderr" >/dev/null 2>&1; }

# Each CMD: one function body running command + ALL assertions as a single boolean chain.
cmd01() { run_command 3 + 4; assert_status 0 && assert_stdout_exact "7.00" && assert_stderr_empty; }
cmd02() { run_command 3 - 4; assert_status 0 && assert_stdout_exact "-1.00" && assert_stderr_empty; }
cmd03() { run_command 3 x 4; assert_status 0 && assert_stdout_exact "12.00" && assert_stderr_empty; }
cmd04() { run_command 3 "*" 4; assert_status 0 && assert_stdout_exact "12.00" && assert_stderr_empty; }
cmd05() { run_command 3 / 4; assert_status 0 && assert_stdout_exact "0.75" && assert_stderr_empty; }
cmd06() { run_command -2.5 + 1.5; assert_status 0 && assert_stdout_exact "-1.00" && assert_stderr_empty; }
cmd07() { run_command 12abc + 1; assert_status 1 && assert_stdout_empty && assert_stderr_contains "Geçersiz sayı"; }
cmd08() { run_command 3 % 4; assert_status 1 && assert_stdout_empty && assert_stderr_contains "Geçersiz işlem"; }
cmd09() { run_command 3 / 0; assert_status 1 && assert_stdout_empty && assert_stderr_contains "Sıfıra bölme"; }
cmd10() { run_command 3 +; assert_status 1 && assert_stdout_empty && assert_stderr_contains "Kullanım:"; }

run_one() {
    id="$1"; fn="$2"
    total=$((total+1))
    if $fn; then echo "$id PASSED"; else echo "$id FAILED"; failures=$((failures+1)); fi
}

run_one CMD-01 cmd01
run_one CMD-02 cmd02
run_one CMD-03 cmd03
run_one CMD-04 cmd04
run_one CMD-05 cmd05
run_one CMD-06 cmd06
run_one CMD-07 cmd07
run_one CMD-08 cmd08
run_one CMD-09 cmd09
run_one CMD-10 cmd10

echo "---"
echo "10 test çalıştırıldı: $total başarılı, $failures başarısız."
[ "$failures" -eq 0 ] || exit 1
