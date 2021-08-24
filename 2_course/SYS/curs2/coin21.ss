;coin21

(define VARIANT 22)
(define LAST-DIGIT-OF-GROUP-NUMBER 5)
(define KINDS-OF-COINS 4)

(define (first-denomination kinds-of-coins)
  (cond((= kinds-of-coins 1) 1)
        ((= kinds-of-coins 2) 2)
        ((= kinds-of-coins 3) 5)
        ((= kinds-of-coins 4) 10)
        (else 0)
        )
)



(define (NOT? x?) 
(= 0(cond (x? 1)(else 0)))
)

(define (AND? x? y?)
(NOT? (or (NOT? x?) (NOT? y?)))
)

(define (MORE? x y)
(AND? (>= x y) (NOT? (= x y)))
)

(define (LESS? x y)
(NOT?(>= x y))
)


(define (count-change amount)
  (display "______\n amount: ")
  (display amount)
  (newline)
  (display "KINDS-OF-COINS: ")
  (display KINDS-OF-COINS)
  (newline)
  (let((largest-coin (first-denomination KINDS-OF-COINS)))
  (display "largest-coin: ")
  (display largest-coin)
  (newline)
    
    
  ( cond((AND? (AND? (MORE? amount 0) (MORE? KINDS-OF-COINS 0)) (MORE? largest-coin 0))
           (display "List of coin denominations: ")
           (denomination-list KINDS-OF-COINS)
           (display "count-change= ")
           (cc amount KINDS-OF-COINS)
           )
        (else
           (display "Improper parameter value!\ncount-change= ")
           -1)
        )
    )
  )

(define (pier? x? y?)
  (NOT? (or x? y?))
  )

(define (cc amount kinds-of-coins)
  (cond ((= amount 0 ) 1)
        ((pier? (LESS? amount 0) (= kinds-of-coins 0))
         (+ (cc amount (- kinds-of-coins 1)) (cc (- amount (first-denomination  kinds-of-coins)) kinds-of-coins)))
        ( else 0)
        )
  )



(define (denomination-list kinds-of-coins)
  (cond ((= kinds-of-coins 0) (newline) 0)
        (else 
                (display (first-denomination kinds-of-coins))
                (display " ")
                (denomination-list (- kinds-of-coins 1))
                )
              
        )
  )

                

(define (GR-AMOUNT)
  (remainder (+ (* 100 LAST-DIGIT-OF-GROUP-NUMBER) VARIANT) 231)
  )

(display "Variant ")
VARIANT
(newline)
(count-change 100)
(count-change (GR-AMOUNT))
(set! KINDS-OF-COINS 13)
(count-change 100)
(display "(c) Mohliakov P.A. 2021\n")
