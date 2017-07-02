def solve(n)
  return 0 if n <= 2
  a1 = 1
  a2 = 0
  a3 = 0
  (n - 3).times do
    tmp = a1 + a2 + a3
    a3 = a2
    a2 = a1
    a1 = tmp
  end
  return a1 % 10007
end
n = gets.to_i
puts solve(n)
