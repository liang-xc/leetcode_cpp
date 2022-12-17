#include <algorithm>
#include <string>
#include <vector>

//77. Combinations
void backtrack_comb(int n, int k, std::size_t idx,
    std::vector<std::vector<int>>& result, std::vector<int>& path) {
  if (path.size() == k) {
    result.push_back(path);
    return;
  }

  for (std::size_t i = idx; i < n + 2 - (k - path.size()); ++i) {
    path.push_back(i);
    backtrack_comb(n, k, i + 1, result, path);
    path.pop_back();
  }
}

std::vector<std::vector<int>> combine(int n, int k) {
  std::vector<std::vector<int>> result;
  std::vector<int> path;
  backtrack_comb(n, k, 1, result, path);
  return result;
}

//17. Letter Combinations of a Phone Number
void backtrack_17(const std::string& digits, const std::size_t& idx,
    std::vector<std::string>& result, std::string& str, 
    const std::string letter_map[]) {
  if (idx == digits.size()) {
    result.push_back(str);
    return;
  }
  std::size_t d = digits[idx] - '0';  
  std::string letters = letter_map[d];
  for (std::size_t i = idx; i < letters.size(); ++i) {
    str.push_back(letters[i]);
    backtrack_17(digits, idx, result, str, letter_map);
    str.pop_back();
  }
}

std::vector<std::string> letterCombinations(std::string digits) {
  std::vector<std::string> result;
  std::string str;
  if (digits.size() == 0) return result;

  const std::string letter_map[10] = {
    "",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz",
  };
  backtrack_17(digits, 0, result, str, letter_map);
  return result;
}

//39. Combination Sum
void backtrack_39(const std::vector<int>& candidates, int target, std::size_t idx, 
    std::vector<std::vector<int>>& result, std::vector<int>& comb) {
  if (target < 0) return;
  if (target == 0) {
    result.push_back(comb);
    return;
  }

  for (std::size_t i = idx; i < candidates.size() && candidates[i] < target; ++i) {
    comb.push_back(candidates[i]);
    backtrack_39(candidates, target - candidates[i], i, result, comb);
    comb.pop_back();
  }
}

std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
  std::vector<std::vector<int>> result;
  std::vector<int> comb;
  backtrack_39(candidates, target, 0, result, comb);
  return result;
}

//131. Palindrome Partitioning
bool isPalindrome(const std::string& s, int start, int end) {
  for (std::size_t i = start, j = end; i < j; ++i, --j) {
    if (s[i] != s[j]) {
      return false;
    }
  }
  return true;
}

void backtracking_131 (const std::string& s, int startIndex,
                       std::vector<std::vector<std::string>>& result,
                       std::vector<std::string>& path) {
  if (startIndex >= s.size()) {
    result.push_back(path);
    return;
  }

  for (std::size_t i = startIndex; i < s.size(); ++i) {
    if (isPalindrome(s, startIndex, i)) {
      std::string str = s.substr(startIndex, i - startIndex + 1);
      path.push_back(str);
    } else {
      continue;
    }
    backtracking_131(s, i + 1, result, path);
    path.pop_back();
  }
}
std::vector<std::vector<std::string>> partition(std::string s) {
  std::vector<std::vector<std::string>> result;
  std::vector<std::string> path;
  backtracking_131(s, 0, result, path);
  return result;
}
