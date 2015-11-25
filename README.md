# pseudo-code
Interpreter for course - Analysis of Programing Languagues.
The idea of this language is based on simple fact, that all algorithms are already written in some kind of pseudo code, so why do not write a simple interpreter for that.

##PseduCode
####Basic Operation
Like every language even ours PseudoCode supports basic arithmetic operation as ```+-/*```.
Each vraiable must be defined this way ```var A as integer```, but currently we are supporting only integer, char and bool values. 
####Loops
This language support two types of loops. The frist is ```repeat``` - ```until``` and basic ```for``` loops with syntax like that
```
repeat
    n = n - 1;
until n = 0
```
```
 for i from 1 to N do
    print i
 end for
```

####Conditions
This language support just basic ```if``` and ```else``` condtion with syntax like that
```
if A > B then      
    //DO SOMETHING
end if
```
or example of if-else statement
```
if A > B then      
    //DO SOMETHING
else
    //DO SOMETHING ELSE
end if
```
####Functions
Functions are defined just with special keyword ```func``` and every function must be ended with function ending ```end func```. Here is simple example
```
func foo( var a as integer )
    return a + 1
end func
```
####Examples
As for every language let's start with the most important
```
print 'Hello World!'
```
Next example is simple bubble sort on array of integers
```
func bubbleSort( var A as array of integers )
    n = length(A)
    repeat
       swapped = false
       for i = 1 to n-1 inclusive do
          if A[i-1] > A[i] then
             swap(A[i-1], A[i])
             swapped = true
          end if
       end for
       n = n - 1
    until not swapped
end func
```


