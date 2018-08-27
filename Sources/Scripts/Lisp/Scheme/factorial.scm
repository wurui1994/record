(define factoral (
	lambda (x) (
		if (<= x 1) 
		1 
		(* x (factoral (- x 1)))
		)
	)
)
(write (factoral 5))