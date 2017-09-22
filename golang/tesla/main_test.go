package main

import (
  "fmt"
  "testing"
)

// -----------------------------------------------------------------------------

var equationGoodSet []string = []string {
  "offset = 4 + random + 1",
  "location = 1 + origin + offset",
  "origin = 3 +     5",
  "random = 2",
}


var equationBadSet []string = []string {
  "offset1 = 4 + random + 1",
  "location here  = 1 + origin + offset",
  "origin+ = 3 +     5",
  "= 2",
}

var lhsPositiveSet []string = []string {
  "offset",
  "location",
  "origin",
  "random",
}

var rhsPositiveSet [][]string = [][]string {
  {"4", "random", "1"},
  {"1", "origin", "offset"},
  {"3", "5"},
  {"2"},
}

// -----------------------------------------------------------------------------

func TestPositiveParseLHS (t * testing.T) {
  for i, eq := range (equationGoodSet) {
    lhs, _ := parseLHS ((*Equation)(&eq))
    if lhs != lhsPositiveSet[i] {
      t.Error ("lhs != %s", lhsPositiveSet[i])
    } else {
      fmt.Printf ("%s == %s\n", lhs, lhsPositiveSet[i])
    }
  }
}

// -----------------------------------------------------------------------------

func TestNegativeParseLHS (t * testing.T) {
  for _, eq := range (equationBadSet) {
    lhs, err := parseLHS ((*Equation)(&eq))
    if err != nil {
      fmt.Printf ("lhs: %s. Err=%v\n", lhs, err)
    } else {
      t.Error ("lhs: %s should not be valid", lhs)
    }
  }
}

// -----------------------------------------------------------------------------

// func TestPositiveParseRHS (t * testing.T) {
//   for i, eq := range (equationGoodSet) {
//     rhs, _ := parseRHS ((*Equation)(&eq))
//     if rhs != rhsPositiveSet[i]{
//       t.Error ("lhs != %s", lhsPositiveSet[i])
//     } else {
//       fmt.Printf ("%s == %s\n", lhs, lhsPositiveSet[i])
//     }
//   }
// }
