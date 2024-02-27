fibonacci :: Int -> Integer
fibonacci n = fst (f n) 

f :: Int -> (Integer, Integer)
f n | n == 0 = (0, 1)
    | even n = (c, d)
    | otherwise = (d, c + d)
    where (a, b) = f (div n 2)
          c = a * (b * 2 - a)
          d = a * a + b * b

main = do
    input <- getLine
    let m = (read input :: Int)
    print (fibonacci(m + 1))
