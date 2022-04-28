(defun without-last (lst)
    (if (null (rest lst)) 
        () 
        (cons (first lst) (without-last (rest lst)))))

(defun without-first-last (lst)
    (if (null (rest lst)) 
        ()
        (without-last (rest lst))))

(defun mult_sum-first-last (lst)
    (if (null (rest lst))
        (+ (first lst) (first lst))
        (* 
            (+ (first lst) (first (last lst))) 
            (+ (first lst) (first (last lst))))))

(defun product-sum2 (lst)
    (if (null (without-first-last lst))
        (mult_sum-first-last lst)
        (* 
            (mult_sum-first-last lst)
            (product-sum2 (without-first-last lst)))))