package main

import "golang.org/x/tour/pic"

func Pic(dx, dy int) [][]uint8 {
	
	a := make([][]uint8, dy)
	
	for row := range a {
		a[row] = make([]uint8, dx)
		for col := range a[row] {
			a[row][col] = uint8(row*col)
		}
	}
	
	return a;
}

func main() {
	pic.Show(Pic)
}
