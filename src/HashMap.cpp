#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//242. Valid Anagram
bool isAnagram(std::string s, std::string t) {
  std::sort(s.begin(), s.end());
  std::sort(t.begin(), t.end());
  return s == t;
}

//1002. Find Common Characters
std::vector<std::string> commonChars(std::vector<std::string>& words) {
  std::vector<int> chars(26, INT8_MAX);
  for (auto a : words) {
    std::vector<int> tmp(26, 0);
    for (auto c : a) {
      ++tmp[c - 'a'];
    }

    for (std::size_t i = 0; i < chars.size(); ++i) {
      chars[i] = std::min(chars[i], tmp[i]);
    }
  }
  
  std::vector<std::string> result;
  for (std::size_t i = 0; i < chars.size(); ++i) {
    while (chars[i]-- > 0) {
      std::string s(1, 'a' + i);
      result.push_back(s);
    }
  }
  return result;
}

//349. Intersection of Two Arrays
std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
  std::unordered_set<int> result;
  std::unordered_set<int> nums_set1(nums1.begin(), nums1.end());
  for (int n : nums2) {
    if (nums_set1.count(n) > 0) {
      result.insert(n);
    }
  }
  return std::vector<int>(result.begin(), result.end());
}

//202. Happy Number
bool isHappy(int n) {
  std::unordered_set<int> result;
  while (n != 1) {
    int tmp = 0;
    while (n > 0) {
      tmp += (n%10) * (n%10);
      n /= 10;
    }
    n = tmp;
    if (result.count(n) > 0) {
      return false;
    } else {
      result.insert(n);
    }
  }
  return true;
}

//1. Two Sum
std::vector<int> twoSum(std::vector<int>& nums, int target) {
  std::unordered_map<int, int> map;
  std::vector<int> result;

  for (std::size_t i = 0; i < nums.size(); ++i) {
    int complement = target - nums[i];
    if (map.count(complement) > 0) {
      result.push_back(i);
      result.push_back(map[complement]);
    } else {
      map[nums[i]] = i;
    }
  }
  return result;
}

//454. 4Sum II
int fourSumCount(std::vector<int>& nums1, 
                std::vector<int>& nums2,
                std::vector<int>& nums3,
                std::vector<int>& nums4) {
  std::unordered_map<int, int> map; //sum of 1 and 2
  for (int a : nums1) {
    for (int b : nums2) {
      ++map[a+b];
    }
  }

  int result = 0;
  for (int c : nums3) {
    for (int d : nums4) {
      int complement = - (c + d);
      if (map.find(complement) != map.end()) {
        result += map[complement];
      }
    }
  }
  return result;
}

//383. Ransom Note
bool canConstruct(std::string ransomNote, std::string magazine) {
  std::vector<int> alphabets(26, 0);
  for (std::size_t i = 0; i < magazine.size(); ++i) {
    ++alphabets[magazine[i] - 'a'];
  }

  for (std::size_t i = 0; i < ransomNote.size(); ++i) {
    if (--alphabets[magazine[i] - 'a'] < 0) return false;
  }
  return true;
}

//15. 3Sum
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
  std::vector<std::vector<int>> result;
  std::sort(nums.begin(), nums.end());
  for (std::size_t i = 0; i < nums.size(); ++i) {
    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }
    std::size_t l = i + 1;
    std::size_t r = nums.size() - 1;
    while (r > l) {
      if (nums[i] + nums[l] + nums[r] > 0) --r;
      else if (nums[i] + nums[l] + nums[r] < 0) ++l;
      else {
        result.push_back(std::vector<int>{nums[i], nums[l], nums[r]});
        while (r > l && nums[r] == nums[r - 1]) --r;
        while (r > l && nums[l] == nums[l + 1]) ++l;

        --r;
        ++l;
      }
    }
  }
  return result;
}
