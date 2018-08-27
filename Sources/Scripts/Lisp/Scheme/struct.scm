(define (print x)
	(write x)(newline)
)
(define greeting "Hello; Hello!")
(define hello (string #\H #\e #\l #\l #\o)) 
;;chapter2
(for-each print
	`(,
	"Hello, World!",
	(string #\h #\e #\l #\l #\o),
	(string-ref greeting 0),
	(string-append "E " "Pluribus " "Unum"),
	(string-set! hello 1 #\a),hello
	)
) 
;;
(define y (list 1 2 3 4))

(for-each print
	`(,
	(vector 0 1 2 3 4),
	(list-ref y 0),
	(list-ref y 3),
	(list-tail y 1),
	(list-tail y 3)
	)
) 
;;
(for-each print
	`(,
	(char->integer #\d),
	(integer->char 50),
	(string->list "hello"),
	(string->number "16"),
	(string->number "Am I a not number?"),
	(symbol->string 'symbol),
	(string->symbol "string")
	)
)
;;chapter3
(for-each print
	`(,
	((lambda (x) (+ x 2)) 5)
	)
)
;;
(define x '(1 2 3))
(print (apply + x))
;;chapter4
(define a 10)
(define b 20)
(when (< a b)
   (display "a is ")
   (print a)
   (display "b is ")
   (print b)
   (print "a is bigger than b")
)
(define c #\c)
(print
	(case c
	  ((#\a) 1)
	  ((#\b) 2)
	  ((#\c) 3)
	  (else 4))
)