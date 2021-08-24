;zeller.ss

(define (NOT? x?) 
(= 0(cond (x? 1)(else 0)))
)



(define (day-of-week)
 (zeller dd
      (cond ((NOT?(>= mm 3))(+ mm 10))(else (- mm 2)))
      (remainder (cond((NOT?(>= mm 3))(- yyyy 1))(else yyyy))100)
      (quotient (cond((NOT?(>= mm 3))(- yyyy 1))(else yyyy))100)
 )
)
(define (zeller d m y c)
 (neg-to-pos (remainder (+ d y
                          (quotient (-(* 26 m)2) 10)
                          (quotient y 4)
                          (quotient c 4)
                          (* 2(- c))
                       )
          7)
 )
)
(define (neg-to-pos d)
     (cond ((NOT?(>= d 0))(+ d 7))(else d))
)

(define (birthday dw)
;                  ^{0,...,6}
 (display "Your were born on ")
       (display (if(= dw 1) "Monday " ""))
       (display (if(= dw 2) "Tuesday " ""))
       (display (if(= dw 3) "Wednesday " ""))
       (display (if(= dw 4) "Thursday " ""))
       (display (if(= dw 5) "Friday " ""))
       (display (if(= dw 6) "Saturday " ""))
       (display (if(= dw 7) "Sunday " ""))
  (display dd)(display ".")
  (display mm)(display ".")
 yyyy
)
(define dd 11)
(define mm 07)
(define yyyy 2001)
(birthday (day-of-week))
