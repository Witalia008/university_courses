; --------------------------- MATRIXES ------------------
; Matrix's width
(defun width-matr(a)
    (if (null a)
        0
        (list-length (car a))
    )
)
; Matrix's height
(defun height-matr(a)
    (list-length a)
)
; Compute 'func' of two rows (by elements)
(defun comp-row(func a b)
    (if (or (null a) (null b))
        nil
        (append 
            (list (funcall func (car a) (car b)))
            (comp-row func (cdr a) (cdr b))
        )
    )
)
; Compute 'func' of two matrixes (by elements)
(defun comp-matr(func a b)
    (if (or (null a) (null b))
        nil
        (append 
            (list (comp-row func (car a) (car b)))
            (comp-matr func (cdr a) (cdr b))
        )
    )
)
; Output matrix
(defun output-matr(a)
    (if (null a)
        0
        (progn
            (write (car a))
            (write-line "")
            (output-matr (cdr a))
        )
    )
)
; Sum of 'func' of elements of vector
(defun sum-func-row(func a)
    (if (null a)
        0
        (+
            (funcall func (car a))
            (sum-func-row func (cdr a))
        )
    )
)
; Sum of 'func' of elements of matrix
(defun sum-func-matr(func a)
    (if (null a)
        0
        (+
            (sum-func-row func (car a))
            (sum-func-matr func (cdr a))
        )
    )
)
; Gives first column of a matrix as a row
(defun first-column(a)
    (if (null a)
        nil
        (append
            (list (caar a))
            (first-column (cdr a))
        )
    )
)
(defun last-columns(a)
    (if (or (null a) (= (list-length (car a)) 1))
        nil
        (append
            (list (cdar a))
            (last-columns (cdr a))
        )
    )
)
; Tanspose matrix
(defun transp(a)
    (if (null a)
        nil
        (append
            (list (first-column a))
            (transp (last-columns a))
        )
    )
)
; Multiply vector by matrix
(defun mul-vxm(a b)
    (if (or (null a) (null b))
        nil
        (append
            (list (sum-func-row '+ (comp-row '* a (car b))))
            (mul-vxm a (cdr b))
        )    
    )
)
; Multiply matrix by matrix (second is transposed)
(defun mul-matrT(a b)
    (if (or (null a) (null b))
        nil
        (append
            (list (mul-vxm (car a) b))
            (mul-matrT (cdr a) b)
        )
    )
)
; Multiply matrix by matrix
(defun mul-matr(a b)
    (mul-matrT a (transp b))
)
; Limit for numbers in random
(defun rand-limit() 10.0)
; Generate random vector
(defun random-list(n)
    (if (= n 0)
        nil
        (cons
            (random (rand-limit))
            (random-list (1- n))
        )
    )
)
; Generate random matrix
(defun random-matr(n m)
    (if (= n 0)
        nil
        (cons
            (random-list m)
            (random-matr (1- n) m)
        )
    )
)

(defun sqr(a) (* a a))

; ------------------------- NMF ----------------------

; Reconstruction error
(defun alg-err(v w h)
    (/ (sum-func-matr 'sqr (comp-matr '- v (mul-matr w h))) (* (width-matr v) (height-matr v)))
)

; H1 = H * ((Wt * V) / (Wt * W * H))
(defun update-left(v w h)
    (setq nom (mul-matr (transp w) v))
    (setq denom (mul-matr (mul-matr (transp w) w) h))
    (comp-matr '* h (comp-matr '/ nom denom))
)

; W1 = W * ((V * Ht) / (W * H * Ht))
(defun update-right(v w h)
    (setq nom (mul-matr v (transp h)))
    (setq denom (mul-matr (mul-matr w h) (transp h)))
    (comp-matr '* w (comp-matr '/ nom denom))
)

; NMF algorithm
(defun nmf(v w h step)
    ;(write-line "Error:")
    ;(write (alg-err v w h))
    ;(write-line "")
    (if (= step 0)
        (progn
            (write-line "V:")
            (output-matr v)
            (write-line "W:")
            (output-matr w)
            (write-line "H:")
            (output-matr h)
            (write-line "W * H:")
            (output-matr (mul-matr w h))
        )
        (progn
            (setq H1 (update-left v w h))
            (setq W1 (update-right v w H1))
            (nmf v W1 H1 (1- step))
        )
    )
)

; Process
(defun proc(n m k)
    (setq v (random-matr n m))
    (setq r (min 5 (min n m)))
    (setq w (random-matr n r))
    (setq h (random-matr r m))
    (nmf v w h k)
)

;---------------------- MAIN -------------------------

(proc 10 8 100)