(define loop
	 (lambda(x y)
		 (if (<= x y)
			(begin 
				(display x) 
				(display #\space) 
				(set! x (+ x 1))
				(loop x y)
			)
		)
	)
)
(write (loop 1 10))