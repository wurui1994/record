(define-syntax add
	(syntax-rules ()
		(
			(_ x y)
			(+ x y)
		)
	)
)
(write (add 1 2))