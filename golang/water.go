package main


/*
 * The objective of this program is to create a water molecule (H20). The client
 * is given two functions; H () and O () representing Hydrogen and Oxygen
 * respectively. The server handles said calls and must produce a water molecule to
 * each caller of either H() or O().
 *
 * Note: The calls to H and O are synchronous and thus the clients will wait
 * until a water molecule is ready.
 */

import (
  "fmt"
)

var H_chan chan bool
var O_chan chan bool
var W_chan chan Water

type Water struct {
  H1, H2 bool
  O bool
}

func H () Water {
  H_chan <- true

  w := <- W_chan
  return w
}

func O () Water {
  O_chan <- true

  w := <- W_chan
  return w
}

/// ----------------------------------------------------------------------------
/// -- Entry Point
/// ----------------------------------------------------------------------------
func main () {

  H_chan = make (chan bool)
  O_chan = make (chan bool)
  W_chan = make (chan Water)

  go func () {
    for {
      <- H_chan
      fmt.Println ("Got a H")
      <- H_chan
      fmt.Println ("Got a H again")
      <- O_chan
      fmt.Println ("Got a O")

      W_chan <- Water {}
    }
  } ()

  fmt.Println ("Waiting...")
  forever := make (chan bool)
  <-forever
}
