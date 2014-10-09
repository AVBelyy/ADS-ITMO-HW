{-# LANGUAGE FlexibleInstances, BangPatterns #-}

import qualified Data.ByteString as B
import qualified Data.ByteString.Char8 as C8
import Data.Time.Clock.POSIX
import System.IO

foreign import ccall rand :: IO Int
foreign import ccall srand :: Int -> IO ()

getTime :: IO Int
getTime = round `fmap` getPOSIXTime

initRandom :: IO ()
initRandom = do
    time <- getTime
    srand time

data Treap a = Empty | Node { s :: !Int, y :: !Int, c :: !a
                            , l :: (Treap a), r :: (Treap a) }
data P a = P { ax :: !(Treap a) , ay :: !(Treap a) }

{-# INLINE size #-}
size :: Treap a -> Int
size Empty = 0
size t     = s t

{-# INLINE mkNode #-}
mkNode :: Int -> a -> Treap a -> Treap a -> Treap a
mkNode !y !c !l !r = Node (1 + size l + size r) y c l r

merge :: Treap a -> Treap a -> Treap a
merge Empty Empty = error "oops"
merge t1 Empty = t1
merge Empty t2 = t2
merge t1@(Node _ y1 c1 l1 r1) t2@(Node _ y2 c2 l2 r2)
    | y1 > y2   = mkNode y1 c1 l1 (merge r1 t2)
    | otherwise = mkNode y2 c2 (merge t1 l2) r2

split :: Treap a -> Int -> P a -- (# Treap a, Treap a #)
split !t !k = _split t 0 where
    _split Empty _ = (P Empty Empty)
    _split (Node s y c l r) !a
        | k <= a + (size l) = let (P t1 t2) = (_split l a) in
                              P t1 $ mkNode y c t2 r
        | otherwise         = let (P t1 t2) = (_split r (a + (size l) + 1)) in 
                              P (mkNode y c l t1) t2

doTraverse :: Handle -> Treap Int -> IO ()
doTraverse _ Empty            = return ()
doTraverse h (Node s y c l r) = do
    doTraverse h l
    hPutStr h $ (show c) ++ " "
    doTraverse h r

doCreate :: [Int] -> Treap Int -> IO (Treap Int)
doCreate [] t     = return t
doCreate (c:cs) t = do
    y <- rand
    doCreate cs $ merge t $ mkNode y c Empty Empty

solve :: [Int] -> Treap Int -> Treap Int
solve []       treap = treap
solve (a:b:xs) treap =
    let
        (P t1 t2)   = split treap b
        (P t1' t2') = split t1 (a - 1)
        treap'  = merge t2' t1'
        treap'' = merge treap' t2
    in solve xs treap''

readIntOrFail :: C8.ByteString -> Int
readIntOrFail bs = case C8.readInt bs of
    Nothing -> error $ "fail"
    Just (a, _) -> a

main :: IO ()
main = do
    initRandom
    hOut <- openFile "movetofront.out" WriteMode
    ln <- B.readFile "movetofront.in"
    let parsed = map readIntOrFail $ C8.words ln
        n = parsed !! 0
        input = drop 2 $ parsed
    treap  <- doCreate [1..n] Empty
    let treap' = solve input treap
    doTraverse hOut treap'
    hClose hOut
