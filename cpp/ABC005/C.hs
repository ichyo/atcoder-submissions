import Control.Monad
import Control.Applicative
main = do
    余裕 <- readLn
    明日 <- getLine
    日曜日 <- (map read . words) <$> getLine
    今日 <- getLine
    土曜日 <- (map read . words) <$> getLine
    putStrLn $ solve 余裕 日曜日 土曜日

solve _ _ [] = "yes"
solve _ [] _ = "no"
solve 余裕 (日:にち) 土曜日@(土:ど)
    | 日 <= 土 && 土 <= 日 + 余裕 = solve 余裕 にち ど
    | otherwise = solve 余裕 にち 土曜日
    

