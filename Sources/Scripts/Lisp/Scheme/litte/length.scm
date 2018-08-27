(define (print x)
	(write x)(newline)
)
(define (len l)
	(cond
	((null? l)0)
	(else (+ 1 (len (cdr l))))
	)
)
(print (length '(a b c)))
(print (len '(a b c)))



