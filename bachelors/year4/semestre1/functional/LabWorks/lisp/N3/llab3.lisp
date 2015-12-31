(defclass deposit-offer ()
    (
        (offer-name
            :initarg :oname
            :initform "No name"
            :accessor offer-name)
        (bank-name
            :initarg :bname 
            :initform "National"
            :accessor bank-name)
        (i-rate
            :initarg :irate
            :initform 0
            :accessor i-rate)
        (terms
            :initarg :terms
            :initform '(1 2 5 10)
            :accessor terms)
    )
)
(defmethod initialize-instance :after ((o deposit-offer) &key))
(defmethod offer-to-string ((o deposit-offer) &key)
    (concatenate 'string
        (bank-name o) " "
        (offer-name o) " "
        (write-to-string (i-rate o)))
)
(defmethod compare-bank-names (string-cmp (a deposit-offer) (b deposit-offer) &key)
    (let (    (bna (bank-name a))
            (bnb (bank-name b)))
            (funcall string-cmp bna bnb))
)
(defmethod compare-rates (integer-cmp (a deposit-offer) (b deposit-offer) &key)
    (let (    (ratea (i-rate a))
            (rateb (i-rate b)))
            (funcall integer-cmp ratea rateb))
)


(defclass deposit ()
    (
        (offer
            :initarg :offer
            :initform (error "Must supply bank offer")
            :accessor offer)
        (term
            :initarg :term
            :initform 1
            :accessor term)
        (balance
            :initarg :bal
            :initform (error "Must supply balance")
            :accessor balance)
    )
)
(defmethod deposit-to-string((d deposit) &key)
    (concatenate 'string
        (bank-name (offer d)) " "
        (write-to-string (term d)) " "
        (write-to-string (balance d)))
)


(defparameter item1 (make-instance 'deposit-offer :oname "Simple" :bname "Bank A" :irate 0.1))
(defparameter item2 (make-instance 'deposit-offer :oname "Advanced" :bname "Bank C" :irate 0.2))
(defparameter item3 (make-instance 'deposit-offer :oname "Pro" :bname "Bank B" :irate 0.3))
(defparameter item4 (make-instance 'deposit-offer :oname "VIP" :bname "Bank D" :irate 0.4))
(defparameter lst (list item1 item2 item3 item4))

(capi:define-interface demo ()
    ()
    (:panes
        (sort-by-name-btn capi:push-button
            :text "Sort by Bank Name"
            :data 'aabb
            :selection-callback #'(lambda (data intf) (capi:sorted-object-sort-by offer-list :by-bank-name)))
        (sort-by-rate-btn capi:push-button
            :text "Sort by income rate"
            :data 'ccdd
            :selection-callback #'(lambda (data intf) (capi:sorted-object-sort-by offer-list :by-income-rate)))
        (offer-list capi:list-panel 
            :items lst
            :filter t
            :interaction :single-selection
            :print-function 'offer-to-string
            :sort-descriptions (list
                (capi:make-sorting-description
                    :type :by-bank-name
                    :sort #'(lambda (a b) (compare-bank-names 'string-lessp a b))
                    :reverse-sort #'(lambda (a b) (compare-bank-names 'string-greaterp a b)))
                (capi:make-sorting-description
                    :type :by-income-rate
                    :sort #'(lambda (a b) (compare-rates '< a b))
                    :reverse-sort #'(lambda (a b) (compare-rates '> a b)))
                ))
        (deposit-list capi:list-panel
            :items (list (make-instance 'deposit :offer item1 :term 1 :bal 1000))
            :filter t
            :interaction :single-selection
            :print-function 'deposit-to-string)
        (apply-btn capi:push-button
            :text "Apply For"
            :selection-callback #'(lambda (data intf) (apply-for (capi:choice-selected-item offer-list) deposit-list)))
        (change-bal-btn capi:push-button
            :text "Modify balance"
            :selection-callback #'(lambda (data intf) (modify-deposit (capi:choice-selected-item deposit-list) deposit-list)))
    )
    (:layouts
        (main-layout capi:tab-layout ()
            :items '(("Propositions" bank-offers) ("My deposits" my-deposits))
            :visible-child-function 'second
            :print-function 'car)
        (bank-offers capi:column-layout
            '(sort-pane offer-list apply-btn))
        (my-deposits capi:column-layout
            '(deposit-list change-bal-btn))
        (sort-pane capi:row-layout
            '(sort-by-name-btn sort-by-rate-btn))
    )
    (:default-initargs
        :title "Deposits"
        :visible-min-height 300
        :visible-min-width 300)
)

(defun apply-for (item deposits)
    (setq amount (capi:prompt-for-integer "Enter amount (USD):"))
    (setq term (capi:prompt-with-list '(1 2 5 10) "Term (in years):"))
    (if (and amount term)
        (let ((dep (make-instance 'deposit :offer item :term term :bal amount)))
            (capi:append-items deposits (list dep))
        )
    )
)
(defun modify-deposit (item deposits)
    (setq delta (capi:prompt-for-integer "Enter amount change:"))
    (if delta
        (let ((amount (+ delta (balance item))))
            (if (>= amount 0)
                (progn
                    (setf (balance item) amount)
                    (capi:choice-update-item deposits item))
            )
        )
    )
)

(capi:display (make-instance 'demo))