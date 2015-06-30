(defun random-max() 1000.0)

(defun random-tensor(dimensions)
    (if (null dimensions)
        (random (random-max))
        (loop for i from 1 to (car dimensions)
            collect (random-tensor (cdr dimensions))
        )
    )
)

(defun random-set(dimensions J)
    (loop for i in dimensions collect (random-tensor (list J i)) )
)

(defun output-tensor(tensor)
    (if (and (listp tensor) (listp (car tensor)))
        (loop for i in tensor do (output-tensor i))
        (write tensor)
    )
    (write-line "")
)

(defun print-tensor(str tensor)
    (write-line str)
    (output-tensor tensor)
)

(defun norm-vector(a)
    (setq d (sqrt (loop for i in a sum (* i i))))
    (loop for i in a collect (my-div i d))
)

(defun func-tensor(func Y Z)
    (if (null Y) Z
    (if (listp Y)
        (loop for i in Y for j in Z
            collect (func-tensor func i j)
        )
        (funcall func Y Z)
    ))
)

(defun mul-A-by-At(A)
    (mul-matr A (transp A))
)

(defun hadamard(A B)
    (if (null A) B
        (func-tensor '* A B)
    )
)

(defun mul-matr-n(func A n)
    (setq res nil)
    (loop for An in A
          for i from 0 to (1- (list-length A))
          when (/= i n) do
          (setq res (funcall func res An))
    )
    res
)

(defun epsilon() 0.00001)

(defun diag(A)
    (loop for i in A
          for j from 0 to (1- (list-length A))
        collect (nth j i)
    )
)

(defun one-list(n) (loop for i from 1 to n collect 1))

(defun first-column(A) (loop for i in A collect (car i)))
(defun last-columns(A)
    (if (= (list-length (car A)) 1)
        nil
        (loop for i in A collect (cdr i))
    )
)
(defun transp(A)
    (if (null A) nil
        (cons (first-column A) (transp (last-columns A))))
)

(defun update-func(y-j a-n-j An t2-j t3-j)
    ; x = y-j * a-n-j
    (setq x (loop for i in a-n-j collect (* i y-j)))
    ; y = An * t3-j
    (setq y (loop for i in (transp An) collect
                (sum-tensor (func-tensor '* i t3-j))
            )
    )
    ; z = x + t2-j - y
    (setq z (func-tensor '+ x (func-tensor '- t2-j y)))
    (loop for i in z collect (max 0 i))
)

(defun get-el(Y pos)
    (if (null pos) Y
        (get-el (nth (car pos) Y) (cdr pos))
    )
)

(defun unfold-row-n(Y n i dimensions pos)
    (if (null dimensions)
        (list (get-el Y pos))
        (loop for j from 0 to (1- (car dimensions)) 
            when (or (/= (1+ n) (list-length dimensions)) (= j i)) append
            (unfold-row-n Y n i (cdr dimensions) (cons j pos))
        )
    )
)

(defun unfold-n(Y n dimensions)
    (loop for i from 0 to (1- (nth n dimensions)) collect
        (unfold-row-n Y n i (reverse dimensions) nil)
    )
)

(defun sum-tensor(A)
    (if (numberp A) A
        (loop for i in A sum (sum-tensor i))
    )
)

(defun mul-matr(A B)
    (loop for i in A collect
        (loop for j in (transp B) collect
            (sum-tensor (func-tensor '* i j))
        )
    )
)

(defun khatri-rao(A B)
    (if (null A) B
        (loop for i in A
              for j in B collect
            (loop for x in i append
                (loop for y in j collect (* x y))
            )
        )
    )
)

(defun some-weird-func(Y A dimensions n)
    (setq Yn (unfold-n Y n dimensions))
    (transp (mul-matr Yn 
        (transp (mul-matr-n 'khatri-rao
            (reverse A)
            (- (list-length A) (1+ n))
        ))
    ))
)

(defun norm-matr(A)
    (sum-tensor (func-tensor '* A A))
)

(defun distance(A B)
    (loop for i in A
          for j in B sum
        (norm-matr (func-tensor '- i j))
    )
)

(defun my-div(a b) (if (= b 0) a (/ a b)))

(defun restore(Ax dimensions mul)
    (if (null dimensions)
        mul
        (loop for i from 0 to (1- (car dimensions))
            collect (restore (cdr Ax) (cdr dimensions) (* mul (nth i (car Ax))))
        )
    )
)

(defun restore-tensor(A dimensions J)
    (setq res nil)
    (loop for i from 0 to (1- J) do
        (setq res (func-tensor '+ res
            (restore (loop for An in A collect (nth i An)) dimensions 1)
        ))
    )
    res
)

(defun fast-hals-ntf(Y J dimensions)
    (setq NN (1- (list-length dimensions)))
    ; Initialize randomly
    (setq A (random-set dimensions J))
    ; a-j = a-j / ||a-j||, j = 1..N-1
    (setq A (loop for i from 0 to NN
                  for An in A collect
                (loop for j in An
                    collect (if (= i NN) j (norm-vector j))
        )))
    ; T0 = (A1 * A1t) (.*) ... (.*) (AN * ANt)
    (setq T1
        (mul-matr-n 'hadamard
            (loop for i in A collect (mul-A-by-At i)) -1
        )
    )
    (setq count 0)
    (loop for c from 0 to 200 for newA = (progn
            ;(write c)
            ;(write-line "")
            ; y = diag(AN * ANt)
            (setq yy (diag (mul-A-by-At (nth NN A))))
            (loop for n from 0 to NN
                    for An in A collect (progn
                ; if (n == N - 1) y = 1
                (if (= n NN) (setq yy (one-list J)) nil)
                
                ; T2 = Yn {An(.)-n}
                (setq T2 (some-weird-func Y A dimensions n))
                
                ; T3 = T1 (/) (An * Ant)
                (setq T3 (func-tensor 'my-div T1 (mul-A-by-At An)))
                
                (prog1
                    (setq A1n (loop for y-j in yy
                          for a-n-j in An
                          for t2-j in T2
                          for t3-j in T3
                        collect
                        (progn
                            (setq a1-n-j (update-func y-j a-n-j An t2-j t3-j))
                            ; if n != N - 1 a = a / ||a||
                            (if (< n NN) (norm-vector a1-n-j) a1-n-j)
                        )
                    ))
                    (setq T1 (hadamard T3 (mul-A-by-At A1n)))
                )
            ))
        )
        while (> (distance A newA) (epsilon)) do
        (progn
            (setq A (copy-list newA))
            (setq count (1+ count))
        )
    )
    (write count)
    (write-line "")
    (print-tensor "Y:" Y)
    (print-tensor "A:" A)
    (setq Y-d (restore-tensor A dimensions J))
    ;(print-tensor "Y-d" Y-d)
    (print-tensor "D:" (func-tensor '- Y Y-d))
)

(setq dimensions '(2 3 4 5))
(setq Y (random-tensor dimensions))
(fast-hals-ntf Y 3 dimensions)