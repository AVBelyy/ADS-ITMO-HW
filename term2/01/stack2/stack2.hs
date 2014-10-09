data LinkedList a = EmptyList | ListNode a (LinkedList a)
                    deriving Show

append :: a -> LinkedList a -> LinkedList a
append xs e = ListNode xs e

first' :: LinkedList a -> a
first' (ListNode x xs) = x

tail' :: LinkedList a -> LinkedList a
tail' (ListNode x xs) = xs
