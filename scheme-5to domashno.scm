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

