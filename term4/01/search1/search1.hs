module Main where

import Control.Monad
import Data.List

findAll :: Eq a => [a] -> [a] -> [Int]
findAll hs nd = _find hs 0
    where  n = length hs
           m = length nd
           _find rm pos
               | n - pos < m = []
               | take m rm == nd = pos : _find (tail rm) (pos + 1)
               | otherwise = _find (tail rm) (pos + 1)

main = do
    (p:t:_) <- liftM words (readFile "search1.in")
    let ans = map (show . (+1)) (findAll t p)
    writeFile "search1.out" $
        show (length ans) ++ "\n"
     ++ intercalate " " ans ++ "\n"
