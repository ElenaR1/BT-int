(define (reduce op null l);fold-right
           (if (null? l) null 
	     (op (car l) (reduce op null (cdr l)))))
	     
 (define (divide l) (reduce / 1 l)); ako l='(1 2 3 4 5)=>1/2/3/4/5 divide ni dava 15/8, a ne 1/120
 
 (define (reduce2 op null l);fold-left moje prosto v konzolata da napishem (fold-left / 1 '(1 2 3 4 5))
            (if (null? l) null
	       (op (reduce2 op null (cdr l)) (car l))))
	       
 (define (real-division l) (reduce2 / 1 l))
 
 
 ; zad za movies and ratings
;'(("LOTR" 11) ("Fight Club" 9) ("Titanik" 12) ("Gladiator" 14))
 (define (len l) (len-helper l 0))
  (define (len-helper l count)
       (cond ((null? l) count)
         (else (len-helper (cdr l) (+ 1 count)))))
 
(define (sum-of-ratings l)
        (if (null? l) 0
	  (+ (car (cdr (car l))) (sum-of-ratings (cdr l)))))
(define (average-rating l)
          (/ (sum-of-ratings l) (len l)))
	  
;2ri variant
;map tova go pravi na vseki 1 element e.g 1vo cdr l i vrushta (11) posle car (11) i vrushta 11
;nie iskame samite chisla a cdr vinagi vrushta spisuk zatova pravim i vednuj car
(define (avg l)
          (/ (reduce + 0 (map cadr l))  (len l)))
	  
;Може да вземем всички филми с рейтинг, по-висок от средния с filter. 
(define (f l )
       (define (bigger? a)
            (if (> (cadr a) (average-rating l)) #t #f))
                  (filter bigger? l))	    
		  
		  
;rectangle
(define points'((1 1) (3 2 ) (1.5 2.5) (2 4)))
;Map връща списък. Map прави трансформация на списък, чрез функцията, дадена като аргумент.
(define (get-xs points) (map car points));car e f-q koqto vrusha 1viq element ot spisuka
(define (get-ys points) (map cadr points))
;napisano po moi nachin
(define (mapp-xs points)
          (if (null? points) '()
	     (cons (car (car points)) (mapp-xs(cdr points)))))
(define (mapp-ys points)
          (if (null? points) '()
	     (cons (car (cdr (car points))) (mapp-ys(cdr points)))));ako e samo (cdr(car l)) se poluchava: ((1) (2) (2.5) (4))

(define xs (get-xs points))
(define ys (get-ys points))
(define (get-min xs) (reduce min (car xs) xs))
(define (get-min ys) (reduce min (car xs) ys))
(define (get-max xs) (reduce2 max (car xs) xs));FOLD-LEFT I FOLD-RIGHT sa ednakvi i se razlichavat samo pri delene
(define (get-max ys) (reduce2 max (car xs) ys))

(define (min-rect-span points)
(let ((min-x (get-min xs))
       (min-y (get-min ys))
         (max-x (get-max xs))
	   (max-y (get-max ys))) 
         (list (list min-x min-y) (list max-x max-y)))); s '(min-x min-y) ne stava





;1 zad
(define (flatten l)
          (cond ((null? l) '())
	  ((list? (car l)) (append (flatten (car l)) (flatten (cdr l))))
	  (else (append (list (car l)) (flatten (cdr l))))));append takes lists as arguments7
;flatten '(1 3 ("wow" ("nesting") ("overload" 38 91)))) -> '(1 3 "wow" "nesting" "overload 38 91)
;(flatten '(1 2 3)) -> '(1 2 3)
;(flatten '(((3)))) -> '(3)

;2zad
(define (pred a)
          (if (odd? a) #t #f))
	  
(define (any? l)
	  (if (null? l) #f
	    (if (pred (car l)) #t
	     (any? (cdr l)))))
(define (any l)
          (cond ((null? l) #f)
	   ((if (pred (car l)) #t 
	     (any (cdr l))))))
	     
;3 zad
 (define (all? l)
          (if (null? l) #t
        (if (pred (car l)) (all? (cdr l))
          #f)))
	  
; 4 zad
(define (remove-odd l)
           (let ((even-numbers (filter even? l))
	   (odd-numbers (filter odd? l)))
	   (cond ((null? l) '())
	     ((= (length even-numbers) 1) (car even-numbers))
	       (else (car odd-numbers)))))
;(remove-odd '(1 3 17 25 4 13 55)) -> 4
;(remove-odd '(-5 20 12 88 92)) -> -5

; 5 zad
(define (take n l)
         (cond ( (or (= n 0) (null? l)) '())
	  (else (append (list (car l)) (take (- n 1) (cdr l))))
	  ))
;2ri variant
(define (take? n l)
(cond ( (or (= n 0) (null? l)) '())
(else (cons (car l) (take (- n 1) (cdr l))))
))


;6 zad
(define (take-while pred? l)
          (if (or (not (pred? (car l))) (null? l)) '()
	    (cons (car l) (take-while pred? (cdr l)))))
;(take-while even? '(2 4 18 40 21 30 22)) -> '(2 4 18 40)
;(take-while (lambda (x) (= (string-length x) 3)) '("okg" "sdp" "fp"))	    
	    

(define tree (list 1(list 2 '() '())(list 3 (list 4 '() '()) '())))
(define tree1 '(1 ( 2 () ()) ( 3 (4 (5 () ()) ()) ()))) ;taka raboti
(define tree2 '(1 () ()))
 
(define (root tree)
           (car tree))
(define (left-subtree tree)
           (car (cdr tree)));cadr
(define (right-subtree tree)
           (car (cdr (cdr tree))));caddr
(define (empty? tree)
    (null? tree))

(define  (member-tree? tree x)
         (if (empty? tree) #f
	  (if (= (root tree) x) #t
	   (or (member-tree? (left-subtree tree) x) (member-tree? (right-subtree tree) x)))))
; s cond
(define  (member-tree?? tree x)
         (cond ((empty? tree) #f)
	  ((= (root tree) x) #t)
	   (else (or (member-tree? (left-subtree tree) x) (member-tree? (right-subtree tree) x)))))
	   
 (define (leaf? tree)
          (and (not (empty? tree))
	     (empty? (left-subtree tree))
	     (empty? (right-subtree tree))))
	     
(define (member-leaf? tree x)
          (if (empty? tree) #f
	    (if (and (= x (root tree)) (leaf? tree))
	    #t
	     (or (member-leaf? (left-subtree tree) x) (member-leaf? (right-subtree tree) x)))))
