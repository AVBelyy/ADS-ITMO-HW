{-# LANGUAGE FlexibleContexts #-}

module Main where

import Control.Monad
import Control.Monad.ST
import Data.Array.ST
import Data.Array.Unboxed
import Data.STRef
import Data.List

prefix :: String -> [Int]
prefix str = elems $ runSTArray $ do
    pf <- newArray (1, n - 1) 0 :: ST s (STArray s Int Int)
    left <- newSTRef 0
    right <- newSTRef 0
    return ()
    
    forM_ [1..n - 1] $ \i -> do
        l <- readSTRef left
        r <- readSTRef right
        a <- readArray pf (i - l)
        let pfval = incZ i (max 0 (min (r - i) a))
        writeArray pf i pfval
        if (i + pfval >= r) then do
            writeSTRef left i
            writeSTRef right (i + pfval)
        else return ()

    return pf
    where n = length str
          s = listArray (0, n - 1) str :: Array Int Char
          incZ i pfval
            | pfval < n - i && s ! pfval == s ! (i + pfval) = incZ i (pfval + 1)
            | otherwise = pfval

main = do
    (t:_) <- liftM words (readFile "prefix.in")
    writeFile "prefix.out" $ intercalate " " (map show (prefix t)) ++ "\n"
