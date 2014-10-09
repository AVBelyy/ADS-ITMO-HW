{-# LANGUAGE NoImplicitPrelude, OverloadedStrings #-}

import Prelude hiding (min, max, reverse)
import System.IO

data Tree a = Empty | Node a (Tree a) (Tree a)
              deriving (Show, Eq)

cons :: Int -> Tree Int
cons v = Node v Empty Empty

value :: Tree Int -> Int
value (Node v _ _) = v

insert :: Tree Int -> Int -> Tree Int
insert Empty x = cons x
insert n@(Node v l r) x
    | x == v = n
    | x < v  = Node v (insert l x) r
    | x > v  = Node v l (insert r x)

delete :: Tree Int -> Int -> Tree Int
delete Empty _ = Empty
delete n@(Node v l r) x
    | x == v =
        if l == Empty && r == Empty then
            Empty
        else if l == Empty && r /= Empty then
            r
        else if l /= Empty && r == Empty then
            l
        else
            Node (value (next n x)) l (delete r (value (next n x)))
    | x < v  = Node v (delete l x) r
    | x > v  = Node v l (delete r x)

exists :: Tree Int -> Int -> Bool
exists Empty _ = False
exists n@(Node v l r) x
    | x == v = True
    | x < v  = exists l x
    | x > v  = exists r x

max :: Tree Int -> Int
max Empty = minBound :: Int
max n@(Node v _ Empty) = v
max n@(Node v _ r) = max r

min :: Tree Int -> Int
min Empty = maxBound :: Int
min (Node v Empty _) = v
min (Node v l _) = min l

next :: Tree Int -> Int -> Tree Int
next Empty _ = Empty
next n@(Node v Empty Empty) x
    | v > x = n
    | otherwise = Empty
next n@(Node v l r) x
    | v <= x = next r x
    | max l > x = next l x
    | otherwise = n

prev :: Tree Int -> Int -> Tree Int
prev Empty _ = Empty
prev n@(Node v Empty Empty) x
    | v < x = n
    | otherwise = Empty
prev n@(Node v l r) x
    | v >= x = prev l x
    | min r < x = prev r x
    | otherwise = n

traverse :: Tree Int -> [Int]
traverse t = (reverse . _traverse t) [] where
    _traverse Empty        = id
    _traverse (Node v l r) = _traverse r . (:) v . _traverse l

reverse :: [Int] -> [Int]
reverse l = _reverse l [] where
    _reverse []     ys = ys
    _reverse (x:xs) ys = _reverse xs (x:ys)

wordsWhen :: (Char -> Bool) -> String -> [String]
wordsWhen p s = case dropWhile p s of
    "" -> []
    s' -> w : wordsWhen p s'' where (w, s'') = break p s'

solve :: Handle -> Handle -> Tree Int -> IO ()
solve hIn hOut tree = do
    isEOF <- hIsEOF hIn
    if isEOF then
        return ()
    else do
        ln <- hGetLine hIn
        let parsed = wordsWhen (==' ') ln
        let cmd = parsed !! 0
        let xln = parsed !! 1
        let x = (read xln :: Int)
        if cmd == "insert" then
            solve hIn hOut (insert tree x)
        else if cmd == "delete" then
            solve hIn hOut (delete tree x)
        else if cmd == "exists" then do
            hPutStrLn hOut (if (exists tree x) then "true" else "false")
        else if cmd == "next" then do
            let y = next tree x
            hPutStrLn hOut (if y /= Empty then show (value y) else "none")
        else {- if cmd == "prev" then -} do
            let y = prev tree x
            hPutStrLn hOut (if y /= Empty then show (value y) else "none")
        solve hIn hOut tree

main :: IO ()
main = do
    hIn <- openFile "bstsimple.in" ReadMode
    hOut <- openFile "bstsimple.out" WriteMode
    solve hIn hOut Empty
    hClose hIn
    hClose hOut
