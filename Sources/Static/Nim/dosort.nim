import std/[algorithm] # for sort
var cities = @["Frankfurt", "Ahmedabad", "Tokyo", "New York", "Kyiv", "Diu"]
cities.sort do (x, y: string) -> int:
  result = cmp(x.len, y.len)
  if result == 0 and x.len > 0:
    result = cmp(x[0], y[0])
echo cities