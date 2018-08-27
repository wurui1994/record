(define (print x)
	(write x)(newline)
)
;1
; (for-each print
	; `(
	; 486,
	; (+ 137 349),
	; (- 1000 334),
	; (* 5 99),
	; (/ 10 5),
	; (+ 2.7 10),
	; (+ 21 35 12 7),
	; (* 25 4 12)
	; )
; )
;2
; (for-each print
	; `(,
	; (+ (* 3 5) (- 10 6)),
	; (+ (* 3 (+ (* 2 4) (+ 3 5)))(+ (- 10 7) 6))
	; )
; )
;3
; (define size 2)
; (define pi 3.14159)
; (define radius 10)
; (define circumference (* 2 pi radius))
; (for-each print
	; `(,
	; size,
	; (* 5 size),
	; (* pi (* radius radius)),
	; circumference,
	; (* (+ 2 (* 4 6))
	   ; (+ 3 5 7))
	; )
; )
;4
; (define (square x)(* x x))
; (define (sum-of-squares x y)
	; (+ (square x)(square y))
; )
; (define (f a)
	; (sum-of-squares (+ a 1)(* a 2)))
; (for-each print 
	; `(,
	; (square 5),
	; (square (+ 2 5)),
	; (square (square 3)),
	; (sum-of-squares 3 4),
	; (f 5)
	; )
; )
(define (A x y)
    (cond ((= y 0)
            0)
          ((= x 0)
            (* 2 y))
          ((= y 1)
            2)
          (else
            (A (- x 1)
               (A x (- y 1))))))
(set! a (real-time))
(print (A 1 100000))
(set! b (real-time))
(print (- b a))
; (define (sum term a next b)
	; (if (> a b)
		; 0
		; (+ (term a)
			; (sum term (next a) next b))
	; )
; )
; (define (integral f a b dx)
	; (define (add-dx x) (+ x dx))
	; (* (sum f (+ a (/ dx 2.0)) add-dx b)
	; dx)
; )
; (define (cube x)(* x x x))
; (print 
; (integral cube 0 1 0.01)
; )
(define (square x)(* x x))
(define (f g) (g 2))
(print (f f))
;统计叶子数
(define (print x)
	(write x)(newline)
)
(define (count-leaves x)
	(cond ((null? x) 0)
		((not (pair? x)) 1)
		(else (+ (count-leaves (car x))
				(count-leaves (cdr x))	
			)
		)
	)
)
(define x (cons (list 1 2)(list 3 4)))
(print
	(count-leaves x)
)