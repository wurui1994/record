(define (print x)
	(write x)(newline)
)
(define  rember*
	(lambda  (a l)
		(cond
			((null? l)  (quote  ()))
			((atom? (car l))
			(cond
				((eq? (car l) a)
				(rember* a (cdr l)))
				(else  (cons (car l)
					(rember* a (cdr l))))))
			(else  (cons ( rember* a (car l))
				(rember* a (cdr l)))))))
(set! a 'sauce)
(set! l
	'(((tomato sauce))
	((bean) sauce)
	(and ((flying)) sauce))
)
(for-each print 
	(rember* a l)
)


