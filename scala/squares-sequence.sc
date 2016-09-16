import java.util.function.ToIntFunction
import scala.collection.mutable.ArrayBuffer


object puzzle {
  println("Welcome to the Scala worksheet")       //> Welcome to the Scala worksheet
  
	def max_root( max_num : Int ) : Int = {
	
		Math.floor( Math.sqrt( max_num + ( max_num - 1 ) ) ).asInstanceOf[Int]
	}                                         //> max_root: (max_num: Int)Int
	
	val mr  = max_root( 16 )                  //> mr  : Int = 5
	val msq = mr * mr                         //> msq  : Int = 25

	def possibles( num : Int, max_num : Int ) : Array[Int] = {
		val mr  = max_root( max_num )
		val msq = mr * mr
		
		val res = ArrayBuffer.empty[Int]
		
		for ( i <- 1 to max_num ) {
			if ( ( i != num ) ) {
				val root = Math.sqrt( i + num )
				
				if ( Math.floor( root ) == root ) {
					res += i
				}
			}
		}
	
		res.toArray
	}                                         //> possibles: (num: Int, max_num: Int)Array[Int]
	
	def allPossibles( max_num : Int ) : Array[Array[Int]] = {
		val res = ArrayBuffer.empty[Array[Int]]

		val zero = ArrayBuffer( 0 ).toArray
		
		res += zero

		for ( i <- 1 to max_num ) {
			val item = possibles( i, max_num )
			
			res += item
		}
		
		res.toArray
	}                                         //> allPossibles: (max_num: Int)Array[Array[Int]]
  
                                                  
	def solveForNum( max_num: Int, num: Int, res: ArrayBuffer[Int], possibleOptions: Array[Array[Int]] ) : Unit = {
	
		res += num

		if ( res.length == max_num ) {
			println( "We have an answer!" )
			
			val ans = res.toArray
			
			//println( ans.deep.mkString("[", "-", "]\n") )
			println( ans.mkString( "{", "-", "}\n" ) )
		} else {

      for (poss_num <- possibleOptions(num)) {

        if (!res.contains(poss_num)) {
          solveForNum(max_num, poss_num, res, possibleOptions)
        }
      }
    }
    
    res -= num
  }                                               //> solveForNum: (max_num: Int, num: Int, res: scala.collection.mutable.ArrayBu
                                                  //| ffer[Int], possibleOptions: Array[Array[Int]])Unit

	val answer = ArrayBuffer.empty[Int]       //> answer  : scala.collection.mutable.ArrayBuffer[Int] = ArrayBuffer()

	for ( o <- 25 to 25 ) {
	
		println( s"Trying $o..." )
		
		val all = allPossibles( o )

		for ( i <- 1 to o ) {
			solveForNum( o, i, answer, all )
		}
	}                                         //> Trying 25...
                                                  //| We have an answer!
                                                  //| {2-23-13-12-24-25-11-14-22-3-1-8-17-19-6-10-15-21-4-5-20-16-9-7-18}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {3-22-14-2-23-13-12-4-21-15-10-6-19-17-8-1-24-25-11-5-20-16-9-7-18}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {4-21-15-10-6-19-17-8-1-3-22-14-2-23-13-12-24-25-11-5-20-16-9-7-18}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {8-17-19-6-10-15-21-4-12-13-23-2-14-22-3-1-24-25-11-5-20-16-9-7-18}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {9-16-20-5-4-21-15-10-6-19-17-8-1-3-22-14-11-25-24-12-13-23-2-7-18}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {10-15-21-4-12-13-23-2-14-22-3-6-19-17-8-1-24-25-11-5-20-16-9-7-18}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {11-25-24-12-13-23-2-14-22-3-1-8-17-19-6-10-15-21-4-5-20-16-9-7-18}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {13-23-2-14-22-3-1-8-17-19-6-10-15-21-4-12-24-25-11-5-20-16-9-7-18}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-2-23-13-12-24-25-11-14-22-3-1-8-17-19-6-10-15-21-4-5-20-16-9}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-9-16-20-5-4-21-15-10-6-19-17-8-1-3-22-14-2-23-13-12-24-25-11}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-9-16-20-5-4-21-15-10-6-19-17-8-1-3-22-14-11-25-24-12-13-23-2}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-9-16-20-5-11-25-24-1-3-22-14-2-23-13-12-4-21-15-10-6-19-17-8}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-9-16-20-5-11-25-24-1-8-17-19-6-3-22-14-2-23-13-12-4-21-15-10}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-9-16-20-5-11-25-24-1-8-17-19-6-10-15-21-4-12-13-3-22-14-2-23}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-9-16-20-5-11-25-24-1-8-17-19-6-10-15-21-4-12-13-23-2-14-22-3}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-9-16-20-5-11-25-24-12-4-21-15-10-6-19-17-8-1-3-13-23-2-14-22}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-9-16-20-5-11-25-24-12-4-21-15-10-6-19-17-8-1-3-22-14-2-23-13}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {18-7-9-16-20-5-11-25-24-12-13-23-2-14-22-3-1-8-17-19-6-10-15-21-4}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {22-14-2-23-13-3-1-8-17-19-6-10-15-21-4-12-24-25-11-5-20-16-9-7-18}
                                                  //| 
                                                  //| We have an answer!
                                                  //| {23-2-14-22-3-13-12-4-21-15-10-6-19-17-8-1-24-25-11-5-20-16-9-7-18}
                                                  //| 
	
	println( "Done!" )                        //> Done!
}
