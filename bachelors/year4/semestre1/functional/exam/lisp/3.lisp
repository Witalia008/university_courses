(defclass node()
    (
        (node-val
            :initarg :nv
            :initform 0
            :accessor node-val)
        (left-son
            :initarg :ls
            :initform nil
            :accessor left-son)
        (right-son
            :initarg :rs
            :initform nil
            :accessor right-son)
    )
)

(defmethod sum-neg(n &key)
    (if (or (null n) (not (typep n 'node))) 0
        (+ (if (< (node-val n) 0) (node-val n) 0)
            (+ (sum-neg (left-son n)) (sum-neg (right-son n)))
        )
    )
)

(setf a (make-instance 'node :nv -3))
(setf b (make-instance 'node :nv 2))
(setf c (make-instance 'node :nv 8 :ls a))
(setf d (make-instance 'node :nv -5 :rs b))
(setf root (make-instance 'node :nv -1 :ls c :rs d))

(print (sum-neg root))