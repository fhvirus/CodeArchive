main = do
    input <- getLine
    let a = (read input :: Integer)
    input <- getLine
    let b = (read input :: Integer)
    print (div a b)
