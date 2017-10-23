package main

import (
  "fmt"
)

type node struct {
  Value int
  Next * node
  Prev * node
}

type LL struct {
  Head * node
  Tail * node
  Count uint
}

/// ----------------------------------------------------------------------------

func (this * LL) Append (value int) {
  if this.Head == nil {
    this.Head = &node {
      Value : value,
      Next  : nil,
      Prev  : nil,
    }
  } else {
    current := this.Head
    for current.Next != nil {
      current = current.Next
    }

    current.Next = &node {
      Value : value,
      Next  : nil,
      Prev  : current,
    }

    this.Tail = current.Next
  }

  this.Count++
}

/// ----------------------------------------------------------------------------

func (this * LL) AddInOrder (value int) {
  current := this.Head
  this.Count++

  for current != nil {
    if value >= current.Value {
      current = current.Next
    } else {
      prev_original := current.Prev
      current.Prev = &node {
        Value  : value,
        Next   : current,
        Prev   : prev_original,
      }
      if current == this.Head {
        this.Head = current.Prev
      } else {
        prev_original.Next = current.Prev
      }
      return
    }
  }

  if this.Head == nil && this.Tail == nil {
    this.Head = &node {
      Value : value,
      Next  : nil,
      Prev  : nil,
    }
    this.Tail = this.Head
    return
  }

  // If reached here, then it indicates that this is the biggest value thus
  // far in the LL and so it needs to be appended to the tail
  this.Tail.Next = &node {
    Value  : value,
    Next   : nil,
    Prev   : this.Tail,
  }

  this.Tail = this.Tail.Next // This becomes the new tail
}

/// ----------------------------------------------------------------------------

func (this * LL) Num () uint {
  return this.Count
}

/// ----------------------------------------------------------------------------

func (this * LL) Print () {
  if this.Head != nil {
    current := this.Head
    for current != nil {
      fmt.Printf ("%d, ", current.Value)
      current = current.Next
    }
    fmt.Println ()
  }
}

/// ----------------------------------------------------------------------------

func (this * LL) GetNode (index uint) (*node, error) {
  if this.Count == 0 {
    return nil, fmt.Errorf ("LL is empty")
  }

  if index > this.Count - 1 || index < 0 {
    return nil, fmt.Errorf ("Invalid index: %d", index)
  }

  var count uint = 0
  current := this.Head
  for current != nil {
    if index == count {
      return current, nil
    }
    current = current.Next
    count++
  }

  return nil, fmt.Errorf ("Shouldn't get to this point")

}

/// ----------------------------------------------------------------------------

func (this * LL) Median () float32 {
  var median float32

  if this.Count % 2 == 0 { // even
    node1, _ := this.GetNode (this.Count >> 1)
    node2, _ := this.GetNode ((this.Count >> 1) - 1)

    median = float32 ((node1.Value + node2.Value) >> 1)
  } else { // odd
    node, _ := this.GetNode ((this.Count - 1) >> 1)
    median = float32 (node.Value)
  }
  return median
}

/// ----------------------------------------------------------------------------

func main () {
  list := new (LL)
  list.AddInOrder (10)
  list.AddInOrder (20)
  list.AddInOrder (15)
  list.AddInOrder (22)
  list.AddInOrder (100)
  list.AddInOrder (99)
  // list.AddInOrder (17)
  list.Print ()
  fmt.Printf ("Median = %f\n", list.Median ())
  fmt.Printf ("Count = %d\n", list.Num ())

}
