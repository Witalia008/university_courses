(defclass bool-m()
    (
        (sz-n
            :initarg :szn
            :accessor sz-n)
        (sz-m
            :initarg :szm
            :accessor sz-m)
        (elems
            :initarg :els
            :accessor elems)
    )
)

(defmethod initialize-instance :after ((n bool-m) &key defval)
    (setf (elems n) (loop for i from 1 to (sz-n n) collect
        (make-list (sz-m n) :initial-element defval)
    ))
)

(defmethod disjunction((a bool-m) (b bool-m) &key)
    (if (and (= (sz-n a) (sz-n b)) (= (sz-m a) (sz-m b)))
        (progn
            (setf nels
                (loop for rowa in (elems a)
                      for rowb in (elems b)
                collect
                    (loop for ela in rowa
                          for elb in rowb
                    collect
                        (or ela elb)
                    )
                ))
            (setf res (make-instance 'bool-m :szn (sz-n a) :szm (sz-m b)))
            (setf (elems res) nels)
            res
        )
        nil
    )
)

(setf a (make-instance 'bool-m :szn 10 :szm 10 :defval t))
(setf b (make-instance 'bool-m :szn 10 :szm 10 :defval nil))
(describe (disjunction a b))