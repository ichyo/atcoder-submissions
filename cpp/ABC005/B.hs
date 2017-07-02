import Control.Monad
main = do
    数 <- readLn
    数列 <- replicateM 数 (readLn :: IO Int)
    putStrLn . show $ minimum 数列
