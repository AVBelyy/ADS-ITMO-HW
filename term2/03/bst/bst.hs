{-# LANGUAGE NoImplicitPrelude #-}

import Prelude hiding (min, max)
import System.IO

data Color = R | B deriving (Eq, Show)
data RBTree a = E | T Color a (RBTree a) (RBTree a) deriving (Eq, Show)

min :: Bounded a => RBTree a -> a
min E = maxBound
min (T _ x E _) = x
min (T _ _ l _) = min l

max :: Bounded a => RBTree a -> a
max E = minBound
max (T _ x _ E) = x
max (T _ _ _ r) = max r

prev :: (Bounded a, Ord a) => RBTree a -> a -> a
prev E _ = maxBound
prev (T _ y l r) x
    | y >= x    = prev l x
    | min r < x = prev r x
    | otherwise = y

next :: (Bounded a, Ord a) => RBTree a -> a -> a
next E _ = minBound
next (T _ y l r) x
    | y <= x    = next r x
    | max l > x = next l x
    | otherwise = y

blacken :: RBTree a -> RBTree a
blacken E           = E
blacken (T c y l r) = T B y l r

reden :: RBTree a -> RBTree a
reden (T c y l r) = T R y l r

balance :: Color -> a -> RBTree a -> RBTree a -> RBTree a
balance B y (T R x a b) (T R z c d) = T R y (T B x a b) (T B z c d)
balance B z (T R y (T R x a b) c) d = T R y (T B x a b) (T B z c d)
balance B z (T R x a (T R y b c)) d = T R y (T B x a b) (T B z c d)
balance B x a (T R y b (T R z c d)) = T R y (T B x a b) (T B z c d)
balance B x a (T R z (T R y b c) d) = T R y (T B x a b) (T B z c d)
balance c x l r = T c x l r

exists :: Ord a => RBTree a -> a -> Bool
exists E _ = False
exists (T _ y l r) x | x <  y = exists l x
                     | x >  y = exists r x
                     | x == y = True

insert :: Ord a => RBTree a -> a -> RBTree a
insert t x = blacken $ insert_ t
    where insert_ E = T R x E E
          insert_ (T c y l r) | x <  y = balance c y (insert_ l) r
                              | x >  y = balance c y l (insert_ r)
                              | x == y = T c y l r
          blacken (T c y l r) = T B y l r

delete :: Ord a => RBTree a -> a -> RBTree a
delete t x = blacken $ delete_ t where
    delete_ E = E
    delete_ (T _ y a b) | x <  y    = deleteL y a b
                        | x >  y    = deleteR y a b
                        | otherwise = merge a b
    deleteL y a@(T B _ _ _) b       = balanceL y (delete_ a) b
    deleteL y a b                   = T R y (delete_ a) b
    deleteR y a b@(T B _ _ _)       = balanceR y a (delete_ b)
    deleteR y a b                   = T R y a (delete_ b)

balanceL :: a -> RBTree a -> RBTree a -> RBTree a
balanceL y (T R x a b) c            = T R y (T B x a b) c
balanceL x bl (T B y a b)           = balance B x bl (T R y a b)
balanceL x bl (T R z (T B y a b) c) = T R y (T B x bl a) (balance B z b (reden c))

balanceR :: a -> RBTree a -> RBTree a -> RBTree a
balanceR x a (T R y b c)            = T R x a (T B y b c)
balanceR y (T B x a b) bl           = balance B y (T R x a b) bl
balanceR z (T R x a (T B y b c)) bl = T R y (balance B x (reden a) b) (T B z c bl)

merge :: RBTree a -> RBTree a -> RBTree a
merge E x                     = x
merge x E                     = x
merge (T R x a b) (T R y c d) = case merge b c of
                                    T R z b' c' -> T R z (T R x a b') (T R y c' d)
                                    bc -> T R x a (T R y bc d)
merge (T B x a b) (T B y c d) = case merge b c of
                                    T R z b' c' -> T R z (T B x a b') (T B y c' d)
                                    bc -> balanceL x a (T B y bc d)
merge a (T R x b c)           = T R x (merge a b) c
merge (T R x a b) c           = T R x a (merge b c)

solve :: Handle -> Handle -> RBTree Int -> IO ()
solve hIn hOut tree = do
    isEOF <- hIsEOF hIn
    if isEOF then
        return ()
    else do
        ln <- hGetLine hIn
        if head ln == 'i' then
            solve hIn hOut (insert tree ((read (drop 7 ln)) :: Int))
        else if head ln == 'd' then
            solve hIn hOut (delete tree ((read (drop 7 ln)) :: Int))
        else if head ln == 'e' then do
            hPutStrLn hOut (if (exists tree ((read (drop 7 ln)) :: Int)) then "true" else "false")
        else if head ln == 'n' then do
            let y = next tree ((read (drop 5 ln)) :: Int)
            hPutStrLn hOut (if y /= minBound then show y else "none")
        else {- if head ln == 'p' then -} do
            let y = prev tree ((read (drop 5 ln)) :: Int)
            hPutStrLn hOut (if y /= maxBound then show y else "none")
        solve hIn hOut tree

main :: IO ()
main = do
    hIn <- openFile "bst.in" ReadMode
    hOut <- openFile "bst.out" WriteMode
    solve hIn hOut E
    hClose hIn
    hClose hOut
