module Main where 

main = interact (showSolution . solveProblem . readProblem)

readProblem :: String -> [[Int]]
readProblem = map (map read . words) . init . lines

solveProblem :: [[Int]] -> [Int]
solveProblem [] = []
solveProblem (c:cs) = countZeroes (c !! 0) (c !! 1) : solveProblem cs

showSolution :: [Int] -> String
showSolution = unlines . map show

countZeroes :: Int -> Int -> Int
countZeroes n m = sum $ map (zeroes . show) [n..m]
  where zeroes = length . (filter (=='0'))