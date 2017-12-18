package main

import (
        "os"
        "fmt"
        "encoding/json"
)

var (
        ordered_table map[string]int = map[string]int {
                "a" : 1,
                "b" : 2,
                "c" : 3,
                "d" : 4,
                "e" : 5,
        }
        unordered_table map[string]int = map[string]int {
                "e" : 5,
                "b" : 2,
                "a" : 1,
                "d" : 4,
        }
)

func main () {
        fmt.Printf ("Ordered Table Map: %v\n", ordered_table)
        fmt.Printf ("Unordered Table Map: %v\n", unordered_table)

        ordered_json_buf, err := json.Marshal (ordered_table)
        if err != nil {
                fmt.Printf ("Cannot marshal ordered map. Err=%v\n", err)
                os.Exit (1)
        }
        unordered_json_buf, err := json.Marshal (unordered_table)
        if err != nil {
                fmt.Printf ("Cannot marshal unordered map. Err=%v\n", err)
                os.Exit (1)
        }

        fmt.Printf ("Already Ordered JSON: %s\n", ordered_json_buf)
        fmt.Printf ("Newly Ordered JSON: %s\n", unordered_json_buf)
}
