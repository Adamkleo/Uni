(setq a 5)
(setq b 10)
(setq result 0)


(defun main ()
  (print "Starting main function execution...")

  (setf a (+ a b))
  (print a)
  
  (loop while (> b a) do
    (setf b (- b 1))
    (print b))


    (if (< b a) 
        (print "a is less than b")
        (print "a is greater than b")
    )

    (if (< b a) 
        (progn 
            (print "a is less than b")
            (print a)
        )
        (progn 
            (print "a is greater than b")
            (print b)
        )

    )

  (print "Main function execution completed.")
)

