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
assert_stdout_not_contains() { ! grep -F -- "$1" "$TMPDIR/stdout" >/dev/null 2>&1; }
assert_stderr_contains() { grep -F -- "$1" "$TMPDIR/stderr" >/dev/null 2>&1; }
run_interactive() { rm -f "$TMPDIR/stdout" "$TMPDIR/stderr" "$TMPDIR/status"; printf '%b' "$1" | "$BIN" > "$TMPDIR/stdout" 2> "$TMPDIR/stderr"; echo $? > "$TMPDIR/status"; }
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

acc01() { run_interactive '3\n+\n4\nh\n'; assert_status 0 && assert_stdout_contains 'Sonuç: 7.00' && assert_stderr_empty; }
acc02() { run_interactive 'abc\n3\n+\n4\nh\n'; assert_status 0 && assert_stdout_contains 'Sonuç: 7.00' && assert_stderr_contains 'Geçersiz sayı'; }
acc03() { run_interactive '3\n%\n+\n4\nh\n'; assert_status 0 && assert_stderr_contains 'Geçersiz işlem'; }
acc04() { run_interactive '3\n+\nabc\n4\nh\n'; assert_status 0 && assert_stderr_contains 'Geçersiz sayı'; }
acc05() { run_interactive '3\n/\n0\n2\n+\n3\nh\n'; assert_status 0 && assert_stdout_contains 'Sonuç: 5.00' && assert_stderr_contains 'Sıfıra bölme'; }
acc06() { run_interactive '1\n+\n1\ne\n3\nx\n4\nh\n'; assert_status 0 && assert_stdout_contains 'Sonuç: 2.00' && assert_stdout_contains 'Sonuç: 12.00'; }
acc07() { run_interactive '1\n+\n1\nh\n2\n+\n3\nh\n'; assert_status 0 && assert_stdout_contains 'Sonuç: 2.00' && assert_stdout_not_contains 'Sonuç: 5.00' && assert_stderr_empty; }
acc08() { run_interactive '1\n+\n1\nz\ne\n2\n+\n3\nh\n'; assert_status 0 && assert_stdout_contains 'Sonuç: 2.00' && assert_stdout_contains 'Sonuç: 5.00' && assert_stderr_contains 'Geçersiz devam seçimi'; }
acc09() { run_interactive '3\n'; assert_status 0 && assert_stdout_contains 'Birinci sayı:' && assert_stdout_not_contains 'Sonuç:' && assert_stderr_empty; }
acc10() { ln=''; for i in $(seq 0 79); do ln="${ln}0"; done; ln="${ln}1"; run_interactive "${ln}\n+\n2\nh\n"; assert_status 0 && assert_stdout_contains 'Sonuç: 3.00'; }

run_one ACC-01 acc01
run_one ACC-02 acc02
run_one ACC-03 acc03
run_one ACC-04 acc04
run_one ACC-05 acc05
run_one ACC-06 acc06
run_one ACC-07 acc07
run_one ACC-08 acc08
run_one ACC-09 acc09
run_one ACC-10 acc10

echo '---'
echo "20 test çalıştırıldı: $total başarılı, $failures başarısız."
[ "$failures" -eq 0 ] || exit 1
