(define (user-profile name email mobile)
	`(
		(name ,name)
		(email ,email)
		(mobile ,mobile)
	)
)
(define (print x)
	(write x)(newline)
)
(for-each print
	(user-profile "Richard" "rms@gnu.org" "Noooo!")
)