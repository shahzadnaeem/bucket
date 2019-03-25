package main

import (
	"fmt"
	"strings"
	"golang.org/x/tour/wc"
)

func WordCount(s string) map[string]int {
	
	var words []string = strings.Fields( s )
	
	fmt.Printf( "words = %v\n", words )
	
	var res = make( map[string]int )
	
	for _, word := range words {
		_, ok := res[word]
		if ( !ok ) {
			res[word] = 0
		}
		
		res[word]++
	}
	
	return res
	
	//return map[string]int{"x": 1}
}

func main() {
	wc.Test(WordCount)
}
