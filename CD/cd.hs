module Main where

import qualified Data.Set as S

type Problem = [Case]
type Solution = [Answer]
data Case = Case { jacksCds :: [String], jillsCds :: [String] }
data Answer = Answer { duplicateCds :: Int }

main = interact (showSolution . solveProblem . readProblem)

readProblem :: String -> Problem
readProblem s = go ((map (map read . words) . lines) s) []
  where 
    go :: [[Int]] -> [Case] -> Problem
    go ((0:0:[]):[]) p = p
    go ((jack:jill:[]):t) p = go (drop (jack+jill+1) t) ((Case (take jack t) (take jill . drop jack t)):p)

solveProblem :: Problem -> Solution
solveProblem = map solve

showSolution :: Solution -> String
showSolution = show $ map duplicateCds

solve :: Case -> Answer
solve c = S.size duplicates
  where 
    s1 = S.fromList $ jacksCds c
    s2 = S.fromList $ jillsCds c
    duplicates = S.intersection s1 s2