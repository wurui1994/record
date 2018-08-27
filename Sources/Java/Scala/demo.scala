object - {
    def add(x:var,y:var): var =
    {
        return x+y;
    }
    //
    val func = (x:Int,y:Int) => x + y
    //
    def main(args: Array[String]): Unit = 
    {
        println("Hello, world!")
        println(add(2,3))
        println(func(2,3))
        //
        // println(add("hello","world"))
    }
} 