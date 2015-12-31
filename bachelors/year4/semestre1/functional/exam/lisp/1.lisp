(defun poly (k x)
    (if (< k 0) NIL
        (if (= k 0) 1
            (if (= k 1) x (progn 
                (setf t0 1)
                (setf t1 x)
                (loop for i from 2 to k
                    do (progn 
                        (setf t2 (* 2 (* x (- t1 t0))))
                        (setf t0 t1)
                        (setf t1 t2)
                    )
                )
                t1
                )
            )
        )
    )
)

(print (poly 2 3))