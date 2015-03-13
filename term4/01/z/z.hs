{-# LANGUAGE FlexibleContexts #-}

module Main where

import Control.Monad
import Control.Monad.ST
import Data.Array.ST
import Data.Array.Unboxed
import Data.STRef
import Data.List

z :: String -> [Int]
z str = elems $ runSTArray $ do
    zf <- newArray (1, n - 1) 0 :: ST s (STArray s Int Int)
    left <- newSTRef 0
    right <- newSTRef 0
    return ()
    
    forM_ [1..n - 1] $ \i -> do
        l <- readSTRef left
        r <- readSTRef right
        a <- readArray zf (i - l)
        let zfval = incZ i (max 0 (min (r - i) a))
        writeArray zf i zfval
        if (i + zfval >= r) then do
            writeSTRef left i
            writeSTRef right (i + zfval)
        else return ()

    return zf
    where n = length str
          s = listArray (0, n - 1) str :: Array Int Char
          incZ i zfval
            | zfval < n - i && s ! zfval == s ! (i + zfval) = incZ i (zfval + 1)
            | otherwise = zfval

main = do
    (t:_) <- liftM words (readFile "z.in")
    writeFile "z.out" $ intercalate " " (map show (z t)) ++ "\n"
