package main


import (
    "fmt"
    "time"
)

// This program quickly assesses the impact of sending a sequence of values in
// quick succession down both a buffered and unbuffered channel.

func main () {
    recvUnbuffered := make (chan int)
    recvBuffered := make (chan int, 5)

    numArray := make ([]int, 10)

    // Populate array with numbers
    for i := 0; i < len (numArray); i++ { numArray[i] = i }

    // Spin-off go routine to listen on channel
    go func () {
        fmt.Printf ("Running go routine: Unbuffered channel\n")
        for {
            select {
            case x := <- recvUnbuffered:
                fmt.Printf ("Unbuffered Received: %d\n", x)
                time.Sleep (500 * time.Millisecond)

            }
        }
    } ()

    go func () {
        for {
            select {
            case y := <- recvBuffered:
                fmt.Printf ("Buffered Received: %d\n", y)
                time.Sleep (500 * time.Millisecond)
            }
        }
    } ()

    // Send values in sequence to channels
    for i := 0; i < len (numArray); i++ {
        fmt.Printf ("Sending to unbuff channel: %d\n", numArray[i])
        recvUnbuffered <- numArray[i]
    }

    for i := 0; i < len (numArray); i++ {
        fmt.Printf ("Sending to buff channel: %d\n", numArray[i])
        recvBuffered <- numArray[i]
    }

    time.Sleep (10000 * time.Millisecond)
}
