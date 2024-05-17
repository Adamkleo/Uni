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

  (print "Main function execution completed.")
)

