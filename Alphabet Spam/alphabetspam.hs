import Data.Char

ratio f s = ((fromIntegral . length) (filter f s)) / ((fromIntegral . length) s)

main = do 
    s <- getLine
    let whitespace = ratio (=='_') s 
    let lower = ratio isLower s
    let upper = ratio isUpper s
    let symbols = 1.0 - whitespace - lower - upper
    (putStrLn . show) whitespace
    (putStrLn . show) lower
    (putStrLn . show) upper
    (putStrLn . show) symbols