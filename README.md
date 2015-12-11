#Pseudo-Code
Interpreter for course - Analysis of Programing Languagues.
The idea of this language is based on simple fact, that all algorithms are already written in some kind of pseudo code, so why do not write a simple interpreter for that.

##Build
To build this interpreter just run bash script
``` ./make.bash ```

####Requirements
For building is necessary flex and bison.
Current code is supported only by GNU/Linux and Mac OS X operating systems.

##Usage
The starting point of every code is the main function, which is mandatory.

####Basic Operations
Like every language even ours Pseudo-Code supports basic arithmetic operation as ```+-/*<>!=```.
Each variable must be defined this way ```A``` and currently we are supporting only integers.

####Arrays
Arrays are indexed from 1 and can be defined by the following way
```
func main ()
  A = 1,2,3
end func
```

Access or modify array elements is possible by the usual way
```
func main ()
  A = 1,2,3
  print A[1] //1
  A[1] = 99 
  print A[1] //99
end func 
```

####Loops
This language support only one type of loops. It's basic ```for``` loops with syntax like that
```
func main ()
 for i from 1 to N do
    print i
 end for
end func
```

####Conditions
This language support just basic ```if``` and ```else``` condtion with syntax like that
```
func main ()
  if A > B then      
      //DO SOMETHING
  end if
end func
```
or example of if-else statement
```
func main ()
  if A > B then      
      //DO SOMETHING
  else
      //DO SOMETHING ELSE
  end if
end func
```

####Functions
Functions are defined just with special keyword ```func``` and every function must be ended with function ending ```end func```. Return variable has the same name as function. Here is a simple example
```
func foo( A )
    foo = A + 1
end func
```

####Built-in functions
The following functions are natively built in Pseudo-Code

#####void swap(var, var) 
```
func main ()
  a=5
  b=6
  swap(a, b)
  print a // 6
  print b // 5 
end func
```

#####int len(array)
```
func main ()
  A=1,2,3,4,5,6
  print len(A) // 6
end func
```

####Examples

As for every language let's start with the most important
```
func main ()
  print 'Hello World!'
end func
```

Example of calling function with an argument
```
func foo (c)
  print c
end func

func main ()
  c = 10
  foo(c) // 10
end func
```

Next example is simple bubble sort on array of integers
```
func bubblesort( a )
	N = len(a)
    for i from 1 to N do
        for j from 0 to N - 1 do
           if a[j] > a[j + 1] then
              swap( a[j], a[j + 1] )
           end if
        end if
    end for   
end func
```



