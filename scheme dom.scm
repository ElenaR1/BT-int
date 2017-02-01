;0 zad
(define l '((84222 "Being Creative") (84221 "Not Really") (99322 "Oh Well")))
(define (subject-helper l n)
      (if (null? l) (display "this isn't such a number in the list")
         (if (= n (caar l)) (cadar l)
          (subject-helper (cdr l) n))))
	  
;1 zad
(define one 1)
(define two 2)
(define three 3)
(define four 4)
(define five 5)
(define six 6)
(define seven 7)
(define eight 8)
(define nine 9)
(define plus +)
(define minus -)
(define times *)
(define div /)
(define oper '(one (plus (five '()))))
(define oper2 '(nine (div (three '()))))
(define oper3 '(nine (times (nine '()))))

(define (func ls) 
	  (eval (list (caadr ls) (car ls) (car (cadadr ls)))))

;2 zad
(define l1 '(1 2 3 4 5 ))
(define (list-rem n l)
          (cond ((null? l) '())
	    ((> n (length l)) l)
	     ((< n 0) (reverse (list-rem (- n) (reverse l))))
	     ((< n (- (length l))) l)
	        ((= n 0) l)
	         ((= n 1) (cdr l))
	           (else (cons (car l) (list-rem (- n 1) (cdr l))))  ))

;3 zad 
(define l2 '(1 4 2 2 3 4 5 5 5 ))
(define l3 '(1 2 1 1 3 2 4 2 5))


(define (remove l a)              
  (cond ( (null? l) '())          
        ( (= (car l) a) (cdr l))    
        (else (cons (car l)(remove (cdr l) a)))))  
       
(define (smallest l curr);curr-curent smallest element
         (if (null? l) curr
       (if (< (car l) curr) (smallest (cdr l) (car l))
         (smallest (cdr l) curr))))
         
(define (sort l)
   (cond ( (null? l) '() )
         ( else (cons (smallest l (car l)) (sort (remove l (smallest l (car l)))))                       
         )))
	 
 (define (contains-string l) 
            (if (null? l) #f
	      (if (string? (car l)) #t
	       (contains-string (cdr l)))))
	       
;if the list contains only numbers it should be sorted	otherwise it shouldn't be       
(define (make-set l)
      (if (contains-string l) (make-set-helper l)
(sort (make-set-helper l))))
 
(define (make-set-helper l)
        (if (null? l) '()
      (if (member (car l) (cdr l))
              (make-set-helper (cdr l))
(cons (car l) (make-set-helper (cdr l))))))
 

;4 zad
(define (list-rem-matrix n l)
          (cond ((null? l) '())
	    ((> n (length l)) l)
	        ((= n -1) l)
	         ((= n 0) (cdr l))
	           (else (cons (car l) (list-rem-matrix (- n 1) (cdr l))))  ))


(define (remove-ith-col m n)
	  (if (> n (length (car m))) (display "There isn't such a column")
	   (if (null? m) '()
	     (cons (list-rem-matrix n (car m)) (remove-ith-col (cdr m) n)))))
;;ili s map
(define (remove-ith-col m n)
	  (if (> n (length (car m))) (display "There isn't such a column")
	   (if (null? m) '()
	     (map (lambda (x) (list-rem-matrix n x)) m))))
	     
	    	     
	     

;5 zad
(define m '((1 2 3) (4 5 6) (7 8 9)))
;(define (transpose m)
 ; (apply map list m))
(define (transpose m)
          (if (null? (car m)) '()
	     (cons (map car m) (transpose (map cdr m)))))
