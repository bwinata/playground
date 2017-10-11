// -----------------------------------------------------------------------------
// Futures Prototype
// -----------------------------------------------------------------------------
// Date:
//  25 Septemeber 2017
// Author:
//  Barry Winata
// -----------------------------------------------------------------------------

package main

import (
  "os"
  "fmt"
  "time"
)


// -----------------------------------------------------------------------------

func InsertValueFuture (value int, valChan chan int) error {
  if valChan == nil { return fmt.Errorf ("Invalid channel. Cannot be nil") }

  go func () {
    fmt.Printf ("Inserting value: %d\n", value)
    t := time.NewTimer (time.Millisecond * 5000) // Create timer
    timeout := <- t.C
    fmt.Printf ("Timeout happened. Time: %v\n", timeout.Unix ())

    valChan <- 200
  } ()

  return nil
}

// -----------------------------------------------------------------------------

func InsertValueFuncFuture (f func (value int) error, value int, valChan chan int) error {
  if valChan == nil { return fmt.Errorf ("Invalid channel. Cannot be nil") }

  go func () {
    f (value)

    t := time.NewTimer (time.Millisecond * 5000) // Create timer
    timeout := <- t.C
    fmt.Printf ("Timeout happened. Time: %v\n", timeout.Unix ())

    valChan <- 200
  } ()

  return nil
}

// -----------------------------------------------------------------------------

func f (value int) error {
  fmt.Printf ("Inserting value: %d\n", value)
  return nil
}

// -----------------------------------------------------------------------------
// Entry Point
// -----------------------------------------------------------------------------

func main () {
  channel := make (chan int)

  val := 10
  // err := InsertValueFuture (val, channel)
  // if err != nil {
  //   fmt.Printf ("Cannot insert value: %d\n", val)
  //   os.Exit (1)
  // }
  //
  // result := <- channel

  err := InsertValueFuncFuture (f, val, channel)
  if err != nil {
    fmt.Printf ("Cannot insert value: %d\n", val)
    os.Exit (1)
  }
  result := <- channel

  fmt.Printf ("Result = %d\n", result)

}
