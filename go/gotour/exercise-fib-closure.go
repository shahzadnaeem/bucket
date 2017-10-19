package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
	sum := 0
	last := 0
	
	return func() int {
		ret := sum + last
		if ( last == 0 ) {
			last = 1
		} else {
			sum, last = sum + last, sum
		}
		
		return ret
	}
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
