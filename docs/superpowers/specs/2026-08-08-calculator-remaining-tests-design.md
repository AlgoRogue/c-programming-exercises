# Calculator Remaining Tests Design

## Purpose

Add the six unimplemented calculator unit-test cases specified in
`solutions/1_basics/01_calculator/docs/TEST_PLAN.md`: `CALC-04` through
`CALC-09`.

## Scope

Only `solutions/1_basics/01_calculator/tests/test_calculator.c` changes.
Production calculator behavior and shared test helpers stay unchanged.

## Test cases

| ID | Input | Expected status | Expected result |
|---|---|---|---|
| CALC-04 | `-3.0 - (-5.0)` | `CALC_STATUS_SUCCESS` | `2.0` |
| CALC-05 | `2.5 * 4.0` | `CALC_STATUS_SUCCESS` | `10.0` |
| CALC-06 | `0.0 * 7.25` | `CALC_STATUS_SUCCESS` | `0.0` |
| CALC-07 | `7.5 / 2.5` | `CALC_STATUS_SUCCESS` | `3.0` |
| CALC-08 | `12.0 / 0.0` | `CALC_STATUS_DIVISION_BY_ZERO` | Unchanged sentinel |
| CALC-09 | Unsupported `enum CalcOp` | `CALC_STATUS_UNSUPPORTED_OPERATION` | Unchanged sentinel |

## Test structure

Each case is a dedicated `static bool test_calc_nn(const char *test_id)`
function, matching the existing `CALC-01` through `CALC-03` pattern.
Success cases first assert the status code and then compare the `double`
result using the existing `TEST_TOLERANCE` constant.

Error cases initialize `result` with a nonzero sentinel, first assert the
returned error status, and then assert that the sentinel remains unchanged.
This makes the API rule that failed calculations do not publish a result
observable and regression-protected.

All six functions are registered in ascending test-ID order in `main`.

## Verification

Run `make test` in `solutions/1_basics/01_calculator`. The test executable
must compile with the existing warning policy and report ten passing tests,
including `CALC-04` through `CALC-09`.
