// -----------------------------------------------------------------------------
// Tesla Coding Challenge
// -----------------------------------------------------------------------------
// Date:
//  20 Septemeber 2017
// Author:
//  Barry Winata
// -----------------------------------------------------------------------------

package main

import (
  "os"
  "fmt"
  "bufio"
  "sort"
  "strings"
  "strconv"
  "unicode"
)

type Equation string

// -----------------------------------------------------------------------------

type Set struct {
  fileDesc    *os.File
  equationMap map[string][]string
}

// -----------------------------------------------------------------------------
// -- Unexported
// -----------------------------------------------------------------------------

// isAlpha checks whether each character of the provided string is part of the
// english alphaet. Return false if it's malforned, otherwise return true
func isAlpha (str string) bool {
  for _, char := range str {
    if !unicode.IsLetter (char) { return false }
  }
  return true
}

// -----------------------------------------------------------------------------

// parseLHS processes an incoming equation and returns a single variable or an
// error if it's malformed based on the provided dependent variable.
func parseLHS (e * Equation) (string, error) {
  var err error

  eString := string (*e)

  // Split equation into two separate arrays; LHS and RHS
  sides := strings.Split (eString, "=")
  lhs := sides[0] // Save LHS only for parsing

  contents := strings.Fields (lhs) // Partition string around single space

  // Check to see that not only should there be one variable but it's also
  // part of the alphabet. Otherwise, throw an error.
  if len (contents) == 1 {
    if isAlpha (contents[0]) {
      return contents[0], nil
    }
    err = fmt.Errorf ("LHS variable must be alphebetic: %s", contents[0])
  } else if len (contents) > 1 {
    err = fmt.Errorf ("Too many LHS variables")
  } else {
    err = fmt.Errorf ("LHS is empty!")
  }

  return "", err
}

// -----------------------------------------------------------------------------

// parseRHS processes an incoming equation and returns a slice of strings
// representing an unsigned integer or a well formed variable. An error is returned
// if the RHS is malforned.
func parseRHS (e * Equation) ([]string, error) {
  eString := string (*e)

  // Split equation tin arrays; LHS and RHS
  sides := strings.Split (eString, "=")
  rhs := sides[1]

  // Remove all spaces
  rhs = strings.Replace (rhs, " ", "", -1)

  // Split string to array around "+" operator
  contents := strings.Split (rhs, "+")

  if len (contents) == 0 {
    return nil, fmt.Errorf ("Invalid equation: %s. RHS cannot be empty", eString)
  }

  // Iterate through each element of the slice and check that it's either an
  // unsigned integer or a well formed variable
  for _, elem := range contents {
    _, numErr := strconv.ParseUint (elem, 10, 64)
    if !isAlpha (elem) && numErr != nil {
      return nil, fmt.Errorf ("Malformed equation: %s. Only '+' operators are accepted", eString)
    }
  }

  return contents, nil
}

// -----------------------------------------------------------------------------

// parseEquation evaluates the given equation to ensure that it meets the
// expected format i.e. <LHS> = <RHS>
func parseEquation (e * Equation) (string, []string, error) {
  eString := string (*e)

  if strings.Count (eString, "=") != 1 {
    return "", nil, fmt.Errorf ("Invalid format: %s\n", eString)
  }

  lhs, err := parseLHS (e)
  if err != nil { return "", nil, err }

  rhs, err := parseRHS (e)
  if err != nil { return "", nil, err }

  return lhs, rhs, nil
}

// -----------------------------------------------------------------------------

// evaluate is a recursive function which provides the summation of the provided
// equation. It checks if a LHS variable is in the Set. If it exists then return the sum,
// otherwise return an error if it cannot be found or exists in the same line as the
// currently evaluated equation
func (this * Set) evaluate (lhs string, rhs []string) (uint64, error) {
  var total uint64 = 0

  for _, elem := range (rhs) {
    if num, err := strconv.ParseUint (elem, 10, 64); err == nil {
      total += num
    } else {
      if next_rhs, ok := this.equationMap[elem]; !ok {
        return 0, fmt.Errorf ("Cannot find LHS variable: '%s' in equation set\n", elem)
      } else if (elem == lhs) {
        return 0, fmt.Errorf ("RHS variable '%s' is in the same equation", elem)
      } else {
        sum, err := this.evaluate (elem, next_rhs)
        if err != nil { return 0, err }
        total += sum
      }
    }
  }
  return total, nil
}

// -----------------------------------------------------------------------------

// evaluateNprint simply prints out the evaluated equation set in sorted order
func (this * Set) evaluateNprint () {
  if len (this.equationMap) == 0 {
    fmt.Printf ("Invalid map. Cannot be empty")
    os.Exit (1)
  }

  var equationList []string

  for k, v := range this.equationMap {
    sum, err := this.evaluate (k, v)
    if err != nil {
      fmt.Printf ("Bad equation set. Err=%v\n", err)
      os.Exit (1)
    }

    equationList = append (equationList, fmt.Sprintf ("%s = %d", k, sum))
  }

  sort.Strings (equationList)
  for _, eq := range equationList {
    fmt.Printf ("%s\n", eq)
  }
}

// -----------------------------------------------------------------------------

// store places each equation given by its LHS / RHS components into the Set's
// equation map, with the key being the LHS and the value being the RHS.
func (this * Set) store (lhs string, rhs []string) (*Set, error) {
  if _, ok := this.equationMap[lhs]; ok {
    return nil, fmt.Errorf ("LHS variable: '%s' already exists", lhs)
  }
  this.equationMap[lhs] = rhs

  return this, nil
}

// -----------------------------------------------------------------------------
// -- Entry Point
// -----------------------------------------------------------------------------

func main () {
  var err error

  if len (os.Args) == 1 {
    fmt.Printf ("Invalid input. Please enter a valid file path\n")
    os.Exit (1)
  }

  s := &Set { equationMap : make (map[string][]string) }

  filePath := os.Args[1]
  s.fileDesc, err = os.Open (filePath)
  if err != nil { fmt.Printf ("Invalid file. Cannot open data. Err=%v\n", err) }

  scan := bufio.NewScanner (s.fileDesc)
  for scan.Scan () {
    equation := scan.Text ()
    lhs, rhs, err := parseEquation ((*Equation)(&equation))
    if err != nil {
      fmt.Printf ("Cannot parse equation. Err=%v\n", err)
      os.Exit (1)
    } else {
      _, err := s.store (lhs, rhs)
      if err != nil {
        fmt.Printf ("Invalid equation set. Err=%v\n", err)
      }
    }
  }

  // Print evaluated equations to stdout in sorted order
  s.evaluateNprint ()

  // Close opened file
  if err = s.fileDesc.Close (); err != nil { fmt.Printf ("Cannot close file. Err=%v\n", err) }
}
