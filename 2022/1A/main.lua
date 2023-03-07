#!/usr/bin/env lua5.4
local landCount, planCount = io.read():match("(%d+)[ ]+(%d+)")
landCount = tonumber(landCount)
planCount = tonumber(planCount)

local plans = {}

for _=1,planCount do
  plans[#plans+1] = {
    size = io.read("n"),
    statisfiedCount = 0
  }
end

function calcLandSize(i)
  assert(i > 0)
  if i % 2 == 0 then
    return landCount + 1 - (i / 2)
  else
    return (i + 1) / 2
  end
end

function isUsable(startLand, planSize)
  local totalSize = 0
  local currentLand = startLand
  while totalSize < planSize and currentLand <= landCount do
    totalSize = totalSize + calcLandSize(currentLand)
    currentLand = currentLand + 1
  end
  
  return planSize == totalSize
end

for i=1,landCount do
  io.write(("|%d"):format(calcLandSize(i)))
end
print("|")

for i=1,landCount do
  for _, plan in ipairs(plans) do
    if isUsable(i, plan.size) then
      plan.statisfiedCount = plan.statisfiedCount + 1
    end
  end
end

for _, plan in ipairs(plans) do
  print(plan.statisfiedCount)
end

