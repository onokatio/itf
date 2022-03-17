import numpy as np
import matplotlib.pyplot as plt

f = open("./givendata202103231157.txt")
nums = f.read().splitlines()

nums2 = []

kaiki = {}

for i in range(len(nums) - 1):
    kaiki[nums[i]] = nums[i+1]

for i in range(len(nums) - 1):
    nums2.append(float(nums[i]))

#print(nums2)
plt.plot(range(len(nums) - 1),nums2)
plt.show()

print(sorted(kaiki.items()))


now = nums[len(nums) - 1]
print(now)
for i in range(len(nums) - 1):
    print(kaiki[now])

#print(kaiki)
#print(float(nums[len(nums)-1]))
