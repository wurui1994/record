# *Part1.There are some equations and some websites.*
>
<center>

> **Hello** 
<font color="skyblue">
*World*
</font>
</center>

## 1.1 Simple Equation

$$E=mc^2$$
$$f(a,b,c) = (a^2+b^2+c^2)^3$$
$$f(x) = \sqrt{1+x} \quad (x \ge  -1)$$

## 1.2 Calculus
$$\int u \frac{dv}{dx}\,dx=uv-\int \frac{du}{dx}v\,dx$$

## 1.3 Summation notation
$$\left( \sum_{k=1}^n a_k b_k \right)^2 \leq \left( \sum_{k=1}^n a_k^2 \right) \left( \sum_{k=1}^n b_k^2 \right)$$

## 1.4 Repeating fractions
$$\frac{1}{\Bigl(\sqrt{\phi \sqrt{5}}-\phi\Bigr) e^{\frac25 \pi}} = 1+\frac{e^{-2\pi}} {1+\frac{e^{-4\pi}} {1+\frac{e^{-6\pi}} {1+\frac{e^{-8\pi}} {1+\cdots} } } }$$

## 1.6 Lorenz Equations
$$
\begin{aligned}
\dot{x} & = \sigma(y-x) \\
\dot{y} & = \rho x - y - xz \\
\dot{z} & = -\beta z + xy
\end{aligned}
$$

## 1.7 Maxwell's Equations
$$
\begin{aligned}
\nabla \times \vec{\mathbf{B}} -\, \frac1c\, \frac{\partial\vec{\mathbf{E}}}{\partial t} & = \frac{4\pi}{c}\vec{\mathbf{j}} \\   
\nabla \cdot \vec{\mathbf{E}} & = 4 \pi \rho \\
\nabla \times \vec{\mathbf{E}}\, +\, \frac1c\, \frac{\partial\vec{\mathbf{B}}}{\partial t} & = \vec{\mathbf{0}} \\
\nabla \cdot \vec{\mathbf{B}} & = 0 \end{aligned}
$$

>These equations are quite cramped. We can add vertical spacing using (for example) [1em] after each line break (\\). as you can see here:

$$
\begin{aligned}
\nabla \times \vec{\mathbf{B}} -\, \frac1c\, \frac{\partial\vec{\mathbf{E}}}{\partial t} & = \frac{4\pi}{c}\vec{\mathbf{j}} \\[1em]   
\nabla \cdot \vec{\mathbf{E}} & = 4 \pi \rho \\[0.5em]
\nabla \times \vec{\mathbf{E}}\, +\, \frac1c\, \frac{\partial\vec{\mathbf{B}}}{\partial t} & = \vec{\mathbf{0}} \\[1em]
\nabla \cdot \vec{\mathbf{B}} & = 0 \end{aligned}
$$

## 1.8 Some Websites

>I get 10 times more traffic from [Google][1] than from [Yahoo][2] or [MSN][3].
> **How about you?**

[1]: http://google.com/ "Google"
[2]: http://search.yahoo.com/ "Yahoo Search"
[3]: http://search.msn.com/ "MSN Search"


# *Part2.There are the examples of some programming language.*
> 给出一些例子代码：
>
## 2.1 This is the C. 
```C
#include <stdio.h>
int main(int argc, char const *argv[])
{
    puts("hello");
    return 0;
}
```

## 2.2 This is the Java.
```Java
//package console;
public class Print {
    static void print(Object obj){
        System.out.println(obj);
    }
    public static void main(String[] args){
        print("Hello World");
    }
}
```

## 2.3 This is the MATLAB
```MATLAB
set(0,'DefaultFigureVisible','off')
ezplot('cos(x)');grid minor
print -dps main.ps
!main.ps
```

## 2.4 This is the Python
```Python
from turtle import *
from math import*
speed('fastest')
x=list(range(-50,50));
y=[]
for i in range(100):
    x[i]=x[i]/10
    y.append(sin(x[i]))
    x[i]=50*x[i]
    y[i]=100*y[i]
color('white')
setpos(x[0],y[0])
color('blue')
for i in range(1,100):
    setpos(x[i],y[i])
!main.ps
```

## 2.5 This is the short code in a sentence.
> Use the `printf()` function.   

# *Part3.These are the origin three colors.*

<font face="Consolas" color="Magenta">

>1. Red.**波长大约为630到750纳米，类似于新鲜血液的颜色.**
>2. Green.**大自然界中常见的颜色。植物的绿色来自于叶绿素.**
>3. Blue.**是天空的颜色，象征虚空、无穷以及神圣的.**

</font>

<img src="test.jpg" width="640" height="480" />


# *Part4.There are some sentences.*
<font face="Consolas">

* Lorem ipsum dolor sit amet, consectetuer adipiscing elit.
Aliquam hendrerit mi posuere lectus. Vestibulum enim wisi,viverra nec, 
fringilla in, laoreet vitae, risus.
* Donec sit amet nisl. Aliquam semper ipsum sit amet velit.
Suspendisse id sem consectetuer libero luctus adipiscing.

</font>

This is [an example](http://example.com/ "Title") inline link.
[This link](http://example.net/) has no title attribute.

# *Part5.This is example for the picture*
>
<center>
<img src="test.jpg" width="640" height="480" />
</center>

*Reference* `vscode plugin`: [Markdown All in One](https://github.com/neilsustc/vscode-markdown)

