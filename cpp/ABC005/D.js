function たこ焼き(具材){
    return parseInt(具材, 10);
}
function Main(input) {
    console.log("%d\n", hogewhgoew);
	input = input.split("\n");
    var n = parseInt(input[0], 10);
    var d = {};
    for(i = 0; i < n; i++){
        d[i] = input[1 + i].split(" ").map(たこ焼き);
    }
    var たこ焼きの和 = {};
    for(i = 0; i <= n; i++){
        たこ焼きの和[i] = {};
        たこ焼きの和[0][i] = たこ焼きの和[i][0] = 0;
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            たこ焼きの和[i + 1][j + 1] = たこ焼きの和[i + 1][j] + たこ焼きの和[i][j + 1] - たこ焼きの和[i][j] + d[i][j];
        }
    }
    var 答え = {};
    for(i = 0; i <= n * n; i++){
        答え[i] = 0;
    }
    for(si = 0; si < n; si++){
        for(sj = 0; sj < n; sj++){
            for(ti = si; ti < n; ti++){
                for(tj = sj; tj < n; tj++){
                    var 和 = たこ焼きの和[ti + 1][tj + 1] - たこ焼きの和[ti + 1][sj] - たこ焼きの和[si][tj + 1] + たこ焼きの和[si][sj];
                    var 面積 = (ti - si + 1) * (tj - sj + 1);
                    if(答え[面積] < 和){
                        答え[面積] = 和;
                    }
                }
            }
        }
    }
    for(i = 1; i <= n * n; i++){
        if(答え[i] < 答え[i - 1]){
            答え[i] = 答え[i - 1];
        }
    }
    クエリ = parseInt(input[1 + n], 10);
    for(i = 0; i < クエリ; i++){
        命令 = parseInt(input[2 + n + i], 10);
        console.log("%d", 答え[命令]);
    }
}
Main(require("fs").readFileSync("/dev/stdin", "utf8"));
