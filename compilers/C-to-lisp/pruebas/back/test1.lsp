(setq a 5)
(setq b 10)
(setq result 0)

(defun addtwonumbers ()
  (setf result (+ a b))
  (print result)
)

(defun multiplytwonumbers ()
  (setf result (* a b))
  (print result)
)


(defun main ()
  (print "Starting main function execution...")

  (setf a (+ a b))
  (print a)

  (print "Main function execution completed.")
)



