package main

import "fmt"

type iPahEr interface {
	pah(i int)
}

type PahEr struct {
	i int
}

func (p *PahEr) pah() {
	fmt.Printf("i = %d\n", p.i)
}

func main() {
	var num int = 120
	p := &PahEr{i: num}

	p.pah()
}
