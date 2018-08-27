(define (print x)
	(write x)(newline)
)
;;input
(define i (open-input-string "hello world"))

(print (read-char i))
(print (read i))
(print (read i))
;;output
(define o (open-output-string))

(write 'hello o)
(write-char #\, o)
(display " " o)
(display "world" o)
(display (get-output-string o))

