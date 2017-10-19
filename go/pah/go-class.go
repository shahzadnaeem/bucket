package main

import "fmt"

type iPahEr interface {
	pah()
}

type PahEr struct {
	I int
	J float64
}

type BlahEr struct {
	P PahEr
}

type PahErAlias = PahEr;

func (p *PahEr) pah() {
	fmt.Printf("*p = %v\n", p)
}

func (b BlahEr) pah() {
	fmt.Printf("b = %v\n", b)
}

func main() {
	var num int = 120
	var pah = PahEr{I: num, J: float64(num)/3.0}
	var p_pah = &pah

	p_pah.pah()

	var blah = BlahEr{ P: pah }
	blah.pah()
}
