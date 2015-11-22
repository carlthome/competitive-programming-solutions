main = interact solve

solve :: String -> String
solve p = unlines $ map show solutions
  where 
    problems = map read (lines p) :: [Integer]
    solutions = map digitsInSmallestMultiple problems

digitsInSmallestMultiple n = 1 + (length $ smallestMultiple n)
smallestMultiple n = takeWhile (\x -> rem x n /= 0) ones
ones = map read (map (\x -> replicate x '1') [1..]) :: [Integer]
