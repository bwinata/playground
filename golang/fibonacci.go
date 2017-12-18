package main

import (
  "fmt"
)

var array []uint

// Recursive "slow" implementation
func fibSlow (n uint) uint {
  if n == 0           { return 0 }
  if n == 1 || n == 2 { return 1 }

  v := fibSlow (n-1) + fibSlow (n-2)

  return v
}

func fibFast (n uint) uint {
  if n == 0           { return 0 }
  if n == 1 || n == 2 { return 1 }

  if len (array) > int (n-3) {
    return array[n-3]
  }

  a := fibFast (n-1)
  b := fibFast (n-2)
  array = append (array, a+b)

  return a + b
}

func main () {
  fmt.Printf ("Fib Slow Value: %d\n", fibSlow (50))
  fmt.Printf ("Fib Fast Value: %d\n", fibFast (50))
}
