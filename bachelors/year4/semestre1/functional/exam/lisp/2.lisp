(defun mult (ll)
    (if (null ll) 1 (* (car ll) (mult (cdr ll))))
)
(print (mult '(1 2 3 4 5)))