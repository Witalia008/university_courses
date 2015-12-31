;---------------- Initial Data
(setf n 4)
(setf matr (make-array (list n n) :initial-contents
    '((0.1 0.2 0.5 0.3)
    (0.0 0.0 0.7 0.5)
    (0.1 0.2 0.2 0.3)
    (0.6 0.7 0.3 0.2))))

;------------------ PART A
(defun permute (list)
    (if list
        (mapcan
            #'(lambda (x)
                (mapcar #'(lambda (y) (cons x y))
                (permute (remove x list)))
            )
            list
        )
        '(())
    )
)
(defun func-list(f p matr)
    (setf i 0)
    (setf pr 1)
    (dolist (x p pr)
        (setf pr (funcall f pr (aref matr i x)))
        (incf i)
    )
)
(defun task-a(n matr)
    (setf el (loop for i from 0 below n collecting i))
    (setf perms (permute el))
    (setf rprod -1)
    (setf res '())
    (dolist (p perms res)
        (setf cur (func-list '* p matr))
        (if (> cur rprod) (progn (setf res p) (setf rprod cur)))
    )
)

(setf resa (task-a n matr))
(print resa)
(print (func-list '* resa matr))


;------------------- PART B
(defparameter used (make-array (list n)))
(defparameter mt (make-array (list n)))
(defun try-kuhn(v n matr)
    (if (aref used v) nil
        (progn
            (setf (aref used v) t)
            (dotimes (to n nil)
                (if (or (= (aref mt to) -1) (try-kuhn (aref mt to) n matr))
                    (progn (setf (aref mt to) v) (return t))
                )
            )
        )
    )
)
(defun kuhn(n matr)
    (setf mt (make-array (list n) :initial-element -1))
    (dotimes (i n (coerce mt 'list))
        (progn
            (setf used (make-array (list n)))
            (try-kuhn i n matr)
        )
    )
)
(setf resb (kuhn n matr))
(print resb)
(print (func-list '+ resb matr))
