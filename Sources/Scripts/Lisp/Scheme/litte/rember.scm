(define (print x)
	(write x)(newline)
)
(define rember
	(lambda (a lat)
		(cond
			((null? lat) (quote ()))
			((eq? (car lat) a) (cdr lat))
			(else 
				(cons (car lat)(rember a (cdr lat)))
			)
		)
	)
)

(print 
	(rember 'b '(a b c))
)
